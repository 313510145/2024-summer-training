// Prevent multiple inclusions
#ifndef QUINE_MCCLUSKEY_H
#define QUINE_MCCLUSKEY_H

#include "gate.h"              // Include gate class
#include <set>                  // Set container
#include <iostream>             // Input/output streams
#include <unordered_map>        // Hash table implementation

class quine_mccluskey {
    public:
        // Input/output methods
        void input_verilog(std::istream& is);   // Read circuit from Verilog format
        void output_blif(std::ostream& os);    // Write circuit in BLIF format

        // Constructor and destructor
        quine_mccluskey();                      // Initialize object
        ~quine_mccluskey();                     // Cleanup resources

    private:
        // Core methods for computation
        void levelization();                     // Perform levelization on gates
        void enumerate_all_combination();        // Enumerate combinations for minimization
        void do_quine_mccluskey();               // Execute Quine-McCluskey algorithm
        bool next_permutation();                 // Generate next permutation

        // Data members
        std::string name;                                            // Circuit name
        std::unordered_map<std::string, GATE_FUNCTION> name_to_function; // Map names to functions
        std::unordered_map<std::string, gate*> name_to_gate;         // Map names to gate objects
        std::vector<gate*> netlist;                                 // List of all gates
        std::vector<gate*> PI_list;                                 // Primary inputs
        std::vector<gate*> PO_list;                                 // Primary outputs
        unsigned int max_level;                                     // Maximum logic level
        std::vector<std::vector<std::pair<std::string, bool>>>* on_set; // On-set for minimization
        std::set<std::string>* prime_implicant;                     // Prime implicants
};

#endif  // QUINE_MCCLUSKEY_H
