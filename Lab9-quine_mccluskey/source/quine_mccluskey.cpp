#include "quine_mccluskey.h"
#include <regex>
#include <queue>
#include <algorithm>

void quine_mccluskey::input_verilog(std::istream& is) {
    std::string str; // String to hold each line of input
    std::regex reg("[a-zA-Z_][a-zA-Z0-9_]*"); // Regex to match valid identifiers
    std::sregex_iterator srit_end; // Iterator for the end of regex matches

    // Loop until the module name, PI_list, PO_list, and netlist are populated
    while (
        this->name == "" ||
        this->PI_list.empty() ||
        this->PO_list.empty() ||
        this->netlist.empty()
    ) {
        getline(is, str); // Read a line from the input stream
        std::sregex_iterator srit(str.begin(), str.end(), reg); // Find identifiers in the line
        
        // Check if the line contains the module definition
        if (str.find("module") != std::string::npos) {
            this->name = (++srit)->str(); // Store the module name
        }
        // Check if the line contains input definitions
        else if (str.find("input") != std::string::npos) {
            while (++srit != srit_end) {
                gate* g = new gate(srit->str(), G_PI); // Create a new gate for each input
                this->PI_list.push_back(g); // Add the gate to the PI_list
            }
        }
        // Check if the line contains output definitions
        else if (str.find("output") != std::string::npos) {
            while (++srit != srit_end) {
                gate* g = new gate(srit->str(), G_PO); // Create a new gate for each output
                this->PO_list.push_back(g); // Add the gate to the PO_list
            }
        }
        // Check if the line contains wire definitions
        else if (str.find("wire") != std::string::npos) {
            while (++srit != srit_end) {
                gate* g = new gate(srit->str(), G_BAD); // Create a new gate for each wire
                this->netlist.push_back(g); // Add the gate to the netlist
            }
        }
    }

    // Add PI gates to the netlist
    for (auto i: this->PI_list) {
        this->netlist.push_back(i);
    }
    // Add PO gates to the netlist with modified names
    for (auto i: this->PO_list) {
        gate* g = new gate(i->get_name(), G_BAD); // Create a new gate for output
        this->netlist.push_back(i); // Add the output gate to the netlist
        this->netlist.push_back(g); // Add the new gate to the netlist
        i->set_name("PO_" + i->get_name()); // Prefix 'PO_' to the output gate name
        g->add_output(i); // Set the output gate's output to the original gate
        i->add_input(g); // Set the original gate's input to the new gate
    }

    // Continue reading lines until the end of the module is reached
    while (getline(is, str)) {
        if (str.find("endmodule") != std::string::npos) {
            break; // Exit the loop if the end of the module is found
        }
        std::sregex_iterator srit(str.begin(), str.end(), reg); // Create an iterator to find identifiers in the line based on the regex pattern 'reg'
        std::sregex_iterator srit_last; // Declare an iterator to keep track of the last found identifier

        ++(++srit); // Move the iterator forward twice to position it at the last identifier
        for (std::sregex_iterator it = srit; it != srit_end; ++it) { // Iterate through all remaining identifiers in the string
            srit_last = it; // Update srit_last to the current iterator position
        }
        
        // Find the corresponding output gate in the netlist
        gate* g_out = nullptr;
        for (unsigned int i = 0; i < this->netlist.size(); i++) {
            if (this->netlist[i]->get_name() == srit_last->str()) {
                g_out = this->netlist[i]; // Set the output gate
                break;
            }
        }

        // Determine the gate function based on the line content
        if (str.substr(0, 3) == "and") {
            g_out->set_function(G_AND); // Set function to AND
        }
        else if (str.substr(0, 2) == "or") {
            g_out->set_function(G_OR); // Set function to OR
        }
        else if (str.substr(0, 3) == "xor") {
            g_out->set_function(G_XOR); // Set function to XOR
        }
        else if (str.substr(0, 4) == "nand") {
            g_out->set_function(G_NAND); // Set function to NAND
        }
        else if (str.substr(0, 3) == "nor") {
            g_out->set_function(G_NOR); // Set function to NOR
        }
        else if (str.substr(0, 4) == "xnor") {
            g_out->set_function(G_XNOR); // Set function to XNOR
        }
        else if (str.substr(0, 3) == "buf") {
            g_out->set_function(G_BUF); // Set function to BUF
        }
        else if (str.substr(0, 3) == "not") {
            g_out->set_function(G_NOT); // Set function to NOT
        }

        // Iterate through the inputs and link them to the output gate
        for (std::sregex_iterator it = srit; it != srit_last; ++it) {
            gate* g_in = nullptr;
            // Find the input gate in the netlist
            for (unsigned int i = 0; i < this->netlist.size(); i++) {
                if (this->netlist[i]->get_name() == it->str()) {
                    g_in = this->netlist[i]; // Set the input gate
                    break;
                }
            }
            // If the input gate is found, link it to the output gate
            if (g_in) {
                g_out->add_input(g_in); // Add the input gate to the output gate
                g_in->add_output(g_out); // Add the output gate to the input gate
            }
        }
    }
    
    // Perform levelization, enumerate all combinations, and execute the Quine-McCluskey algorithm
    levelization();
    enumerate_all_combination();
    do_quine_mccluskey();
}

void quine_mccluskey::output_blif(std::ostream& os) {
    // Output the model name
    os << ".model " << this->name << std::endl
       << ".inputs"; // Begin the inputs section
    
    // Output each primary input (PI) gate name
    for (const auto i: this->PI_list) {
        os << " " << i->get_name(); // Append each PI name
    }
    
    os << std::endl
       << ".outputs"; // Begin the outputs section

    // Output each primary output (PO) gate name, removing the "PO_" prefix
    for (const auto i: this->PO_list) {
        os << " " << i->get_name().substr(3, i->get_name().length() - 3); // Append each PO name
    }

    os << "\n";

    for (unsigned int o = 0; o < this->PO_list.size(); o++) {
        os << "\n.names"; // Begin the names section
        // Output each primary input (PI) gate name again
        for (const auto pi: this->PI_list) {
            os << " " << pi->get_name(); // Append each PI name
        }
        // Output each primary output (PO) gate name again, removing the "PO_" prefix
        os << " " << this->PO_list[o]->get_name().substr(3, this->PO_list[o]->get_name().length() - 3); // Append each PO name
        os << std::endl;
        // Output the on-set values
        for (unsigned int i = 0; i <= this->PI_list.size(); i++) {
            for (unsigned int j = 0; j <= this->PI_list.size() - i; j++) {
                // Iterate through the on-set to find true outputs
                for (auto l: this->on_set[o][i][j]) {
                    if (l.second == true) { // Check if the output is true
                        os << l.first << " 1" << std::endl; // Output the input combination with a value of 1
                    }
                }
            }
        }
    }



    os << "\n.end\n"; // End of the BLIF output
}

quine_mccluskey::quine_mccluskey() {
    // Initialize the maximum level of the circuit
    this->max_level = 0;
    
    // Initialize the on-set pointer to null
    this->on_set = nullptr;
}

quine_mccluskey::~quine_mccluskey() {
    // Clear and delete the on-set arrays
    for (unsigned int o = 0; o < this->PO_list.size(); o++) {
        for (unsigned int i = 0; i <= this->PI_list.size(); i++) {
            for (unsigned int j = 0; j <= this->PI_list.size() - i; j++) {
                // Clear the entries in the on-set for the current (i, j) pair
                this->on_set[o][i][j].clear();
            }
            // Delete the dynamically allocated array for the current level
            delete [] this->on_set[o][i];
        }
        delete [] this->on_set[o];
    }
    // Delete the dynamically allocated array for on-set
    delete [] this->on_set;

    // Clear the primary input (PI) list
    this->PI_list.clear();
    
    // Clear the primary output (PO) list
    this->PO_list.clear();
    
    // Iterate through the netlist to clear and delete gates
    for (auto i: this->netlist) {
        i->clear_list(); // Clear any internal lists in the gate
        delete i; // Delete the gate object
    }
    // Clear the netlist after deleting all gates
    this->netlist.clear();
}

void quine_mccluskey::levelization() {
    // Initialize a queue to perform levelization
    std::queue<gate*> q;

    // Iterate through each primary input (PI) in the circuit
    for (const auto i: this->PI_list) {
        // For each fan-out of the PI gate
        for (unsigned int j = 0; j < i->get_fan_out_num(); j++) {
            gate* g = i->get_fan_out(j); // Get the fan-out gate
            
            g->add_count_1(); // Increment the count of inputs received by the gate
            
            // If the gate has received all its fan-in signals
            if (g->get_count() == g->get_fan_in_num()) {
                i->get_fan_out(j)->set_level(1); // Set the level of the gate to 1
                q.push(i->get_fan_out(j)); // Add the gate to the queue for processing
            }
        }
    }

    // Process the queue until it's empty
    while (!q.empty()) {
        const gate* g = q.front(); // Get the front gate in the queue
        q.pop(); // Remove it from the queue

        // For each fan-out of the current gate
        for (unsigned int i = 0; i < g->get_fan_out_num(); i++) {
            gate* g_out = g->get_fan_out(i); // Get the fan-out gate

            // If the output gate's level is less than or equal to the current gate's level
            if (g_out->get_level() <= g->get_level()) {
                g_out->set_level(g->get_level() + 1); // Set its level to the current level + 1
            }
            g_out->add_count_1(); // Increment the count of inputs received by the output gate
            
            // If the output gate has received all its fan-in signals
            if (g_out->get_count() == g_out->get_fan_in_num()) {
                q.push(g_out); // Add it to the queue for further processing
            }
        }
    }

    // Reset counts and determine the maximum level in the netlist
    for (auto i: this->netlist) {
        i->reset_count(); // Reset the input count for each gate
        // Update the maximum level if the current gate's level is higher
        if (i->get_level() > this->max_level) {
            this->max_level = i->get_level();
        }
    }
}

void quine_mccluskey::enumerate_all_combination() {
    // Create an array of queues to hold gates at each level for processing
    std::queue<gate*>* q = new std::queue<gate*>[this->max_level + 1];
    
    // Initialize on_set to hold combinations of inputs and their corresponding states
    this->on_set = new std::vector<std::pair<std::string, bool>>**[this->PO_list.size()];
    for (unsigned int o = 0; o < this->PO_list.size(); o++) {
        this->on_set[o] = new std::vector<std::pair<std::string, bool>>*[this->PI_list.size() + 1];
        for (unsigned int i = 0; i <= this->PI_list.size(); i++) {
            this->on_set[o][i] = new std::vector<std::pair<std::string, bool>>[this->PI_list.size() + 1 - i];
        }

    }

    // Set initial values for primary inputs (PIs) to S0 and increment their counts
    for (unsigned int i = 0; i < this->PI_list.size(); i++) {
        this->PI_list[i]->set_value(S0);
        this->PI_list[i]->add_count_1();
    }

    // Process the combinations until all have been enumerated
    do {
        // Update counts for PIs and push their fan-out gates to the queues
        for (unsigned int i = 0; i < this->PI_list.size(); i++) {
            if (this->PI_list[i]->get_count() > 0) {
                this->PI_list[i]->reset_count(); // Reset count before processing fan-outs
                
                // For each fan-out of the PI, update counts and push to queue
                for (unsigned int j = 0; j < this->PI_list[i]->get_fan_out_num(); j++) {
                    if (this->PI_list[i]->get_fan_out(j)->get_count() == 0) {
                        this->PI_list[i]->get_fan_out(j)->add_count_1(); // Increment count
                        q[this->PI_list[i]->get_fan_out(j)->get_level()].push(this->PI_list[i]->get_fan_out(j)); // Push to queue
                    }
                }
            }
        }

        // Process gates at each level in the queue
        for (unsigned int i = 0; i <= this->max_level; i++) {
            while (!q[i].empty()) {
                gate* g = q[i].front(); // Get the front gate from the queue
                q[i].pop(); // Remove it from the queue
                g->reset_count(); // Reset the gate's count

                // Start computing the gate's value based on its fan-in values
                std::bitset<BIT_LENGTH> value = g->get_fan_in(0)->get_value(); // Initialize value with the first fan-in
                switch (g->get_function()) { // Determine the function of the gate
                    case G_AND:
                    case G_NAND:
                        for (unsigned int k = 1; k < g->get_fan_in_num(); k++) {
                            value &= g->get_fan_in(k)->get_value(); // Perform AND operation
                        }
                        break;
                    case G_OR:
                    case G_NOR:
                        for (unsigned int k = 1; k < g->get_fan_in_num(); k++) {
                            value |= g->get_fan_in(k)->get_value(); // Perform OR operation
                        }
                        break;
                    case G_XOR:
                    case G_XNOR:
                        for (unsigned int k = 1; k < g->get_fan_in_num(); k++) {
                            value ^= g->get_fan_in(k)->get_value(); // Perform XOR operation
                        }
                        break;
                    default:
                        break;
                }

                // If the gate is inverted, flip the value
                if (g->is_inverted()) {
                    value = ~value; // Bitwise NOT
                    bool temp = value[0];
                    value[0] = value[1];
                    value[1] = temp; // Swap the first two bits
                }

                // If the computed value is different from the current value, update it
                if (g->get_value() != value) {
                    g->set_value(value); // Update the gate's value
                    // Push fan-out gates to the queue if they haven't been counted yet
                    for (unsigned int j = 0; j < g->get_fan_out_num(); j++) {
                        if (g->get_fan_out(j)->get_count() == 0) {
                            g->get_fan_out(j)->add_count_1(); // Increment count
                            q[g->get_fan_out(j)->get_level()].push(g->get_fan_out(j)); // Push to queue
                        }
                    }
                }
            }
        }

        // Record the input combinations that produce a high output (S1) at the primary outputs (POs)
        for (unsigned int i = 0; i < this->PO_list.size(); i++) {
            if (this->PO_list[i]->get_value() == S1) {
                std::string str = "";
                unsigned int num_1 = 0;
                // Construct the input string based on current PI values
                for (unsigned int j = 0; j < this->PI_list.size(); j++) {
                    if (this->PI_list[j]->get_value() == S0) {
                        str = str + "0"; // Append '0' for S0
                    }
                    else if (this->PI_list[j]->get_value() == S1) {
                        str = str + "1"; // Append '1' for S1
                        num_1++; // Count the number of '1's
                    }
                }
                this->on_set[i][0][num_1].push_back(make_pair(str, true)); // Store the combination
            }
        }
    } while (next_permutation()); // Generate the next input combination

    // Cleanup dynamically allocated memory for queues
    delete [] q;
}

void quine_mccluskey::do_quine_mccluskey() {
    // Vector to hold indices where differences occur
    std::vector<unsigned int> v;

    // Iterate over the on_set to compare combinations of different sizes
    for (unsigned int o = 0; o < this->PO_list.size(); o++) {
        for (unsigned int i = 0; i < this->PI_list.size(); i++) {
            for (unsigned int j = 0; j < this->PI_list.size() - i; j++) {
                // Loop through each combination at current size j
                for (auto& l: this->on_set[o][i][j]) {
                    // Compare with the next size (j + 1)
                    for (auto& m: this->on_set[o][i][j + 1]) {
                        // Check for differing positions between two combinations
                        for (unsigned int n = 0; n < this->PI_list.size(); n++) {
                            if (l.first[n] != m.first[n]) {
                                v.push_back(n); // Record the differing index
                            }
                        }
                        // If exactly one difference was found
                        if (v.size() == 1) {
                            // Ensure the differing positions are not '-' (don't allow don't-care states)
                            if (l.first[v[0]] != '-' && m.first[v[0]] != '-') {
                                l.second = false; // Mark current as non-essential
                                m.second = false; // Mark next as non-essential
                                std::string str = l.first;
                                str[v[0]] = '-'; // Replace differing bit with '-'

                                // Check if the new combination is already in the next set
                                if (std::find(on_set[o][i + 1][j].begin(), on_set[o][i + 1][j].end(), make_pair(str, true)) == on_set[o][i + 1][j].end()) {
                                    this->on_set[o][i + 1][j].push_back(make_pair(str, true)); // Add the new combination
                                }
                            }
                        }
                        v.clear(); // Clear the vector for the next iteration
                    }
                }
            }
        }
    }
}

bool quine_mccluskey::next_permutation() {
    // Iterate through primary inputs (PIs) to generate the next input combination
    for (unsigned int i = 0; i < this->PI_list.size(); i++) {
        // Check if the current PI is not set to S1
        if (this->PI_list[i]->get_value() != S1) {
            this->PI_list[i]->set_value(S1); // Set to S1
            this->PI_list[i]->add_count_1(); // Increment the count for this PI
            return true; // Successfully generated the next combination
        }
        else {
            this->PI_list[i]->set_value(S0); // Reset current PI to S0
            this->PI_list[i]->add_count_1(); // Increment the count for this PI
        }
    }
    return false; // No more combinations can be generated
}
