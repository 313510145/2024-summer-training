#include "quine_mccluskey.h"
#include <queue>
#include <algorithm>

void quine_mccluskey::input_verilog(std::istream& is) {
    std::string str;
    is >> str >> this->name;
    getline(is, str);
    is >> str;
    do {
        is >> str;
        gate* g = new gate();
        g->set_name(str.substr(0, str.size() - 1));
        g->set_function(G_PI);
        this->PI_list.push_back(g);
        this->name_to_gate[g->get_name()] = g;
    } while (str[str.size() - 1] != ';');
    is >> str;
    do {
        is >> str;
        gate* g = new gate();
        g->set_name(str.substr(0, str.size() - 1));
        g->set_function(G_PO);
        this->PO_list.push_back(g);
    } while (str[str.size() - 1] != ';');
    is >> str;
    do {
        is >> str;
        gate* g = new gate();
        g->set_name(str.substr(0, str.size() - 1));
        this->netlist.push_back(g);
        this->name_to_gate[g->get_name()] = g;
    } while (str[str.size() - 1] != ';');
    for (auto i: this->PI_list) {
        this->netlist.push_back(i);
    }
    for (auto i: this->PO_list) {
        gate* g = new gate();
        g->set_name(i->get_name());
        i->set_name("PO_" + i->get_name());
        g->add_output(i);
        i->add_input(g);
        this->netlist.push_back(i);
        this->netlist.push_back(g);
        this->name_to_gate[g->get_name()] = g;
    }
    std::vector<std::string> v;
    is >> str;
    while (str != "endmodule") {
        str.resize(str.find('_'));
        v.push_back(str);
        is >> str;
        do {
            is >> str;
            v.push_back(str);
        } while (str[str.size() - 1] != ';');
        str = v.back();
        v.pop_back();
        str.resize(str.size() - 2);
        gate* g = this->name_to_gate[str];
        g->set_function(this->name_to_function[v[0]]);
        str = v[1];
        str = str.substr(1, str.size() - 2);
        g->add_input(this->name_to_gate[str]);
        this->name_to_gate[str]->add_output(g);
        GATE_FUNCTION gf = g->get_function();
        if (gf != G_BUF && gf != G_NOT) {
            for (unsigned int i = 2; i < v.size(); i++) {
                str = v[i];
                str.resize(str.size() - 1);
                g->add_input(this->name_to_gate[str]);
                this->name_to_gate[str]->add_output(g);
            }
        }
        v.clear();
        is >> str;
    }
    levelization();
    enumerate_all_combination();
    do_quine_mccluskey();
}

void quine_mccluskey::output_blif(std::ostream& os) {
    os << ".model " << this->name << std::endl
       << ".inputs";
    for (const auto i: this->PI_list) {
        os << " " << i->get_name();
    }
    os << "\n.outputs";
    for (const auto i: this->PO_list) {
        os << " " << i->get_name().substr(3, i->get_name().length() - 3);
    }
    os << "\n";
    for (unsigned int o = 0; o < this->PO_list.size(); o++) {
        os << "\n.names";
        for (const auto pi: this->PI_list) {
            os << " " << pi->get_name();
        }
        os << " " << this->PO_list[o]->get_name().substr(3, this->PO_list[o]->get_name().length() - 3) << std::endl;
        for (std::set<std::string>::reverse_iterator it = this->prime_implicant[o].rbegin(); it != this->prime_implicant[o].rend(); ++it) {
            os << (*it) << " 1" << std::endl;
        }
    }
    os << "\n.end\n";
}

quine_mccluskey::quine_mccluskey() {
    this->name = "";
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

quine_mccluskey::~quine_mccluskey() {
    this->name_to_function.clear();
    this->name_to_gate.clear();
    for (unsigned int o = 0; o < this->PO_list.size(); o++) {
        for (unsigned int i = 0; i <= this->PI_list.size(); i++) {
            this->on_set[o][i].clear();
        }
        this->on_set[o].clear();
        this->prime_implicant[o].clear();
    }
    delete [] this->on_set;
    delete [] this->prime_implicant;
    this->PI_list.clear();
    this->PO_list.clear();
    for (auto i: this->netlist) {
        delete i;
    }
    this->netlist.clear();
}

void quine_mccluskey::levelization() {
    std::queue<gate*> q;
    for (const auto i: this->PI_list) {
        for (unsigned int j = 0; j < i->get_fan_out_num(); j++) {
            gate* g = i->get_fan_out(j);
            g->add_count_1();
            if (g->get_count() == g->get_fan_in_num()) {
                i->get_fan_out(j)->set_level(1);
                q.push(g);
            }
        }
    }
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
    for (auto i: this->netlist) {
        i->reset_count();
        if (i->get_level() > this->max_level) {
            this->max_level = i->get_level();
        }
    }
}

void quine_mccluskey::enumerate_all_combination() {
    std::queue<gate*>* q = new std::queue<gate*>[this->max_level + 1];
    this->on_set = new std::vector<std::vector<std::pair<std::string, bool>>>[this->PO_list.size()];
    this->prime_implicant = new std::set<std::string>[this->PO_list.size()];
    for (unsigned int i = 0; i < this->PO_list.size(); i++) {
        this->on_set[i].resize(this->PI_list.size() + 1);
    }
    for (unsigned int i = 0; i < this->PI_list.size(); i++) {
        this->PI_list[i]->set_value(S0);
        this->PI_list[i]->add_count_1();
    }
    do {
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
        for (unsigned int i = 0; i <= this->max_level; i++) {
            while (!q[i].empty()) {
                gate* g = q[i].front();
                q[i].pop();
                g->reset_count();
                std::bitset<BIT_LENGTH> value = g->get_fan_in(0)->get_value();
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
                if (g->is_inverted()) {
                    value = ~value;
                    bool temp = value[0];
                    value[0] = value[1];
                    value[1] = temp;
                }
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
    delete [] q;
}

void quine_mccluskey::do_quine_mccluskey() {
    std::pair<std::string, bool> temp_implicant;
    std::vector<std::pair<std::string, bool>> v;
    unsigned int count;
    temp_implicant.second = true;
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
