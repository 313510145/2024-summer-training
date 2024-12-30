// Prevent multiple inclusions
#ifndef GATE_H
#define GATE_H

#include <string>   // String type
#include <vector>   // Dynamic arrays
#include <bitset>   // Binary representation

const unsigned int BIT_LENGTH = 2;  // Length of gate value bits

// Gate values
enum VALUE {S0 = 0b00, S1 = 0b11, X = 0b01};

// Gate functions
enum GATE_FUNCTION {G_PI, G_PO, G_AND, G_OR, G_XOR, G_NAND, G_NOR, G_XNOR, G_BUF, G_NOT, G_BAD};

class gate {
    public:
        // Manage input/output connections
        void add_input(gate* g_in);
        void add_output(gate* g_in);

        // Fan-in and fan-out
        unsigned int get_fan_in_num() const;
        unsigned int get_fan_out_num() const;
        gate* get_fan_in(unsigned int i) const;
        gate* get_fan_out(unsigned int i) const;

        // Gate properties
        std::string get_name() const;
        GATE_FUNCTION get_function() const;
        std::bitset<BIT_LENGTH> get_value() const;
        unsigned int get_level() const;
        unsigned int get_count() const;

        // Set properties
        void set_name(const std::string& name_in);
        void set_function(GATE_FUNCTION function_in);
        void set_value(const std::bitset<BIT_LENGTH>& value_in);
        void set_level(unsigned int level_in);

        // Count management
        void add_count_1();
        void reset_count();

        // Utilities
        bool is_inverted() const;
        void clear_list();

        // Constructor and destructor
        gate();
        ~gate();
    private:
        std::string name;                          // Gate name
        GATE_FUNCTION function;                    // Gate type
        std::bitset<BIT_LENGTH> value;             // Gate value
        unsigned int level;                        // Logic level
        unsigned int count;                        // Usage counter
        std::vector<gate*> input_list;             // Input connections
        std::vector<gate*> output_list;            // Output connections
};

#endif  // GATE_H
