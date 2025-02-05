#include "quine_mccluskey.h"
#include <queue>
#include <algorithm>

// Function to parse Verilog input and construct internal gate representations
void quine_mccluskey::input_verilog(std::istream& is) {
    std::string str;
    
    // Read module name
    is >> str >> this->name;
    getline(is, str);

    // Parse primary inputs (PI)
    is >> str;
    do {
        is >> str;
        gate* g = new gate();
        g->set_name(str.substr(0, str.size() - 1)); // Remove trailing comma/semicolon
        g->set_function(G_PI); // Set gate function as primary input
        this->PI_list.push_back(g); // Add to PI list
        this->name_to_gate[g->get_name()] = g; // Map name to gate
    } while (str[str.size() - 1] != ';'); // Continue until ';' is found

    // Parse primary outputs (PO)
    is >> str;
    do {
        is >> str;
        gate* g = new gate();
        g->set_name(str.substr(0, str.size() - 1)); // Remove trailing comma/semicolon
        g->set_function(G_PO); // Set gate function as primary output
        this->PO_list.push_back(g); // Add to PO list
    } while (str[str.size() - 1] != ';'); // Continue until ';' is found

    // Parse internal gates
    is >> str;
    do {
        is >> str;
        gate* g = new gate();
        g->set_name(str.substr(0, str.size() - 1)); // Remove trailing comma/semicolon
        this->netlist.push_back(g); // Add to netlist
        this->name_to_gate[g->get_name()] = g; // Map name to gate
    } while (str[str.size() - 1] != ';'); // Continue until ';' is found

    // Add PI gates to netlist
    for (auto i: this->PI_list) {
        this->netlist.push_back(i);
    }

    // Add PO gates to netlist and connect them to internal gates
    for (auto i: this->PO_list) {
        gate* g = new gate();
        g->set_name(i->get_name());
        i->set_name("PO_" + i->get_name()); // Prefix PO name with "PO_"
        g->add_output(i);
        i->add_input(g);
        this->netlist.push_back(i);
        this->netlist.push_back(g);
        this->name_to_gate[g->get_name()] = g;
    }

    // Parse gate connections and functions
    std::vector<std::string> v;
    is >> str;
    while (str != "endmodule") {
        str.resize(str.find('_')); // Trim to base name
        v.push_back(str);
        is >> str;
        do {
            is >> str;
            v.push_back(str);
        } while (str[str.size() - 1] != ';'); // Continue until ';' is found

        // Configure gate function and inputs
        str = v.back();
        v.pop_back();
        str.resize(str.size() - 2); // Remove trailing characters
        gate* g = this->name_to_gate[str];
        g->set_function(this->name_to_function[v[0]]);

        // Connect inputs to gate
        str = v[1];
        str = str.substr(1, str.size() - 2); // Remove parentheses
        g->add_input(this->name_to_gate[str]);
        this->name_to_gate[str]->add_output(g);

        // Add additional inputs for multi-input gates
        GATE_FUNCTION gf = g->get_function();
        if (gf != G_BUF && gf != G_NOT) { // Skip single-input gates
            for (unsigned int i = 2; i < v.size(); i++) {
                str = v[i];
                str.resize(str.size() - 1); // Remove trailing comma/semicolon
                g->add_input(this->name_to_gate[str]);
                this->name_to_gate[str]->add_output(g);
            }
        }
        v.clear();
        is >> str;
    }

    // Perform levelization and minimize using Quine-McCluskey algorithm
    levelization();
    enumerate_all_combination();
    do_quine_mccluskey();
}

// Function to output the design in BLIF format
void quine_mccluskey::output_blif(std::ostream& os) {
    os << ".model " << this->name << std::endl
       << ".inputs";

    // Output all primary inputs
    for (const auto i: this->PI_list) {
        os << " " << i->get_name();
    }
    os << "\n.outputs";

    // Output all primary outputs
    for (const auto i: this->PO_list) {
        os << " " << i->get_name().substr(3, i->get_name().length() - 3);
    }
    os << "\n";

    // Write logic table for each output
    for (unsigned int o = 0; o < this->PO_list.size(); o++) {
        os << "\n.names";
        for (const auto pi: this->PI_list) {
            os << " " << pi->get_name();
        }
        os << " " << this->PO_list[o]->get_name().substr(3, this->PO_list[o]->get_name().length() - 3) << std::endl;

        // Output minterms
        for (std::set<std::string>::reverse_iterator it = this->prime_implicant[o].rbegin(); it != this->prime_implicant[o].rend(); ++it) {
            os << (*it) << " 1" << std::endl;
        }
    }
    os << "\n.end\n";
}

// Constructor to initialize variables and gate functions
quine_mccluskey::quine_mccluskey() {
    this->name = "";

    // Map string representations to gate functions
    name_to_function["and"] = G_AND;
    name_to_function["or"] = G_OR;
    name_to_function["xor"] = G_XOR;
    name_to_function["nand"] = G_NAND;
    name_to_function["nor"] = G_NOR;
    name_to_function["xnor"] = G_XNOR;
    name_to_function["buf"] = G_BUF;
    name_to_function["not"] = G_NOT;

    this->max_level = 0;
    this->on_set = nullptr;
    this->prime_implicant = nullptr;
}

// Destructor to free memory and clear data structures
quine_mccluskey::~quine_mccluskey() {
    this->name_to_function.clear(); // Clear function map
    this->name_to_gate.clear();    // Clear gate map

    // Free memory allocated for minterms and prime implicants
    for (unsigned int o = 0; o < this->PO_list.size(); o++) {
        for (unsigned int i = 0; i <= this->PI_list.size(); i++) {
            this->on_set[o][i].clear();
        }
        this->on_set[o].clear();
        this->prime_implicant[o].clear();
    }
    delete [] this->on_set;
    delete [] this->prime_implicant;

    // Clear and delete gate objects
    this->PI_list.clear();
    this->PO_list.clear();
    for (auto i: this->netlist) {
        delete i;
    }
    this->netlist.clear();
}

void quine_mccluskey::levelization() {
    // Create a queue to store gates for processing
    std::queue<gate*> q;
    
    // Initialize levels for primary inputs (PIs)
    for (const auto i: this->PI_list) {
        for (unsigned int j = 0; j < i->get_fan_out_num(); j++) {
            gate* g = i->get_fan_out(j);
            g->add_count_1();
            if (g->get_count() == g->get_fan_in_num()) {
                // Set the level of gates connected to PIs
                i->get_fan_out(j)->set_level(1);
                q.push(g);
            }
        }
    }
    
    // Process the queue to propagate levels through the netlist
    while (!q.empty()) {
        const gate* g = q.front();
        q.pop();
        for (unsigned int i = 0; i < g->get_fan_out_num(); i++) {
            gate* g_out = g->get_fan_out(i);
            if (g_out->get_level() <= g->get_level()) {
                g_out->set_level(g->get_level() + 1);
            }
            g_out->add_count_1();
            if (g_out->get_count() == g_out->get_fan_in_num()) {
                q.push(g_out);
            }
        }
    }

    // Reset counts and determine the maximum level
    for (auto i: this->netlist) {
        i->reset_count();
        if (i->get_level() > this->max_level) {
            this->max_level = i->get_level();
        }
    }
}

void quine_mccluskey::enumerate_all_combination() {
    // Create a queue for each level in the netlist
    std::queue<gate*>* q = new std::queue<gate*>[this->max_level + 1];

    // Allocate memory for on-sets and prime implicants
    this->on_set = new std::vector<std::vector<std::pair<std::string, bool>>>[this->PO_list.size()];
    this->prime_implicant = new std::set<std::string>[this->PO_list.size()];

    // Initialize on-sets for each primary output (PO)
    for (unsigned int i = 0; i < this->PO_list.size(); i++) {
        this->on_set[i].resize(this->PI_list.size() + 1);
    }

    // Initialize primary inputs (PIs) to S0 and increment count
    for (unsigned int i = 0; i < this->PI_list.size(); i++) {
        this->PI_list[i]->set_value(S0);
        this->PI_list[i]->add_count_1();
    }

    do {
        // Process each primary input
        for (unsigned int i = 0; i < this->PI_list.size(); i++) {
            if (this->PI_list[i]->get_count() > 0) {
                this->PI_list[i]->reset_count();
                for (unsigned int j = 0; j < this->PI_list[i]->get_fan_out_num(); j++) {
                    if (this->PI_list[i]->get_fan_out(j)->get_count() == 0) {
                        this->PI_list[i]->get_fan_out(j)->add_count_1();
                        q[this->PI_list[i]->get_fan_out(j)->get_level()].push(this->PI_list[i]->get_fan_out(j));
                    }
                }
            }
        }

        // Process each level in the netlist
        for (unsigned int i = 0; i <= this->max_level; i++) {
            while (!q[i].empty()) {
                gate* g = q[i].front();
                q[i].pop();
                g->reset_count();
                std::bitset<BIT_LENGTH> value = g->get_fan_in(0)->get_value();

                // Perform logic operations based on gate function
                switch (g->get_function()) {
                    case G_AND:
                    case G_NAND:
                        for (unsigned int k = 1; k < g->get_fan_in_num(); k++) {
                            value &= g->get_fan_in(k)->get_value();
                        }
                        break;
                    case G_OR:
                    case G_NOR:
                        for (unsigned int k = 1; k < g->get_fan_in_num(); k++) {
                            value |= g->get_fan_in(k)->get_value();
                        }
                        break;
                    case G_XOR:
                    case G_XNOR:
                        for (unsigned int k = 1; k < g->get_fan_in_num(); k++) {
                            value ^= g->get_fan_in(k)->get_value();
                        }
                        break;
                    default:
                        break;
                }

                // Handle inverted gates
                if (g->is_inverted()) {
                    value = ~value;
                    bool temp = value[0];
                    value[0] = value[1];
                    value[1] = temp;
                }

                // Propagate updated values to fan-outs
                if (g->get_value() != value) {
                    g->set_value(value);
                    for (unsigned int j = 0; j < g->get_fan_out_num(); j++) {
                        if (g->get_fan_out(j)->get_count() == 0) {
                            g->get_fan_out(j)->add_count_1();
                            q[g->get_fan_out(j)->get_level()].push(g->get_fan_out(j));
                        }
                    }
                }
            }
        }

        // Update on-sets based on PO values
        for (unsigned int i = 0; i < this->PO_list.size(); i++) {
            if (this->PO_list[i]->get_value() == S1) {
                std::string str = "";
                unsigned int num_1 = 0;
                for (unsigned int j = 0; j < this->PI_list.size(); j++) {
                    if (this->PI_list[j]->get_value() == S0) {
                        str = str + "0";
                    }
                    else {
                        str = str + "1";
                        num_1++;
                    }
                }
                this->on_set[i][num_1].push_back(make_pair(str, true));
            }
        }
    } while (next_permutation());

    // Free dynamically allocated memory for queues
    delete [] q;
}

void quine_mccluskey::do_quine_mccluskey() {
    // Reduce implicants using Quine-McCluskey method
    std::pair<std::string, bool> temp_implicant;
    std::vector<std::pair<std::string, bool>> v;
    unsigned int count;
    temp_implicant.second = true;

    // Process prime implicants for each PO
    for (unsigned int o = 0; o < this->PO_list.size(); o++) {
        for (unsigned int i = 0; i < this->PI_list.size(); i++) {
            for (unsigned int j = 0; j < this->PI_list.size() - i; j++) {
                for (auto& l: this->on_set[o][j]) {
                    for (auto& m: this->on_set[o][j + 1]) {
                        temp_implicant.first = "";
                        count = 0;
                        for (unsigned int n = 0; n < this->PI_list.size(); n++) {
                            if (l.first[n] != m.first[n]) {
                                temp_implicant.first += "-";
                                count++;
                            }
                            else {
                                temp_implicant.first += l.first[n];
                            }
                        }
                        if (count == 1) {
                            if (std::find(v.begin(), v.end(), temp_implicant) == v.end()) {
                                v.push_back(temp_implicant);
                            }
                            l.second = false;
                            m.second = false;
                        }
                    }
                    if (l.second == true) {
                        this->prime_implicant[o].insert(l.first);
                    }
                }
                this->on_set[o][j] = v;
                v.clear();
            }
        }
        for (unsigned int i = 0; i <= this->PI_list.size(); i++) {
            for (auto j: this->on_set[o][i]) {
                if (j.second == true) {
                    this->prime_implicant[o].insert(j.first);
                }
            }
        }
    }
}

bool quine_mccluskey::next_permutation() {
    // Generate next permutation of input combinations
    for (unsigned int i = 0; i < this->PI_list.size(); i++) {
        if (this->PI_list[i]->get_value() != S1) {
            this->PI_list[i]->set_value(S1);
            this->PI_list[i]->add_count_1();
            return true;
        }
        else {
            this->PI_list[i]->set_value(S0);
            this->PI_list[i]->add_count_1();
        }
    }
    return false;
}
