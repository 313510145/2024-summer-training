#ifndef QUINE_MCCLUSKEY_H
#define QUINE_MCCLUSKEY_H

#include "gate.h"
#include <iostream>

// Class for implementing the Quine-McCluskey algorithm
class quine_mccluskey {
    public:
        // Read input from a Verilog file stream
        void input_verilog(std::istream& is);

        // Write output to a BLIF file stream
        void output_blif(std::ostream& os);

        // Default constructor
        quine_mccluskey();

        // Destructor
        ~quine_mccluskey();
    private:
        // Perform levelization on the netlist (to organize gates by logic level)
        void levelization();

        // Enumerate all possible combinations of the inputs
        void enumerate_all_combination();

        // Execute the Quine-McCluskey algorithm for logic minimization
        void do_quine_mccluskey();

        // Generate the next permutation of the logic values
        bool next_permutation();

        std::string name;  // Name of the netlist or circuit
        std::vector<gate*> netlist;  // List of all gates in the circuit
        std::vector<gate*> PI_list;  // List of primary input gates
        std::vector<gate*> PO_list;  // List of primary output gates
        unsigned int max_level;  // Maximum logic level in the circuit
        std::vector<std::pair<std::string, bool>>*** on_set;  // On-set of logic functions for minimization
};

#endif
