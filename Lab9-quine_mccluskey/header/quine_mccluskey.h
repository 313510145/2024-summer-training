#ifndef QUINE_MCCLUSKEY_H
#define QUINE_MCCLUSKEY_H

#include "gate.h"
#include <set>
#include <iostream>
#include <unordered_map>

class quine_mccluskey {
    public:
        void input_verilog(std::istream& is);
        void output_blif(std::ostream& os);
        quine_mccluskey();
        ~quine_mccluskey();
    private:
        void levelization();
        void enumerate_all_combination();
        void do_quine_mccluskey();
        bool next_permutation();
        std::string name;
        std::unordered_map<std::string, GATE_FUNCTION> name_to_function;
        std::unordered_map<std::string, gate*> name_to_gate;
        std::vector<gate*> netlist;
        std::vector<gate*> PI_list;
        std::vector<gate*> PO_list;
        unsigned int max_level;
        std::vector<std::vector<std::pair<std::string, bool>>>* on_set;
        std::set<std::string>* prime_implicant;
};

#endif  // QUINE_MCCLUSKEY_H
