#ifndef GATE_H
#define GATE_H

#include <string>
#include <vector>
#include <bitset>

// Constant representing the length of the bitset used for gate values
const int BIT_LENGTH = 2;

// Enum to represent possible logic values for a gate (S0: 0, S1: 1, X: unknown)
enum VALUE {S0 = 0b00, S1 = 0b11, X = 0b01};

// Enum to represent different types of logic gate functions (e.g., AND, OR, NOT, etc.)
enum GATE_FUNCTION {G_PI, G_PO, G_AND, G_OR, G_XOR, G_NAND, G_NOR, G_XNOR, G_BUF, G_NOT, G_BAD};

class gate {
    public:
        // Add an input gate to the current gate
        void add_input(gate* g_in);

        // Get the number of input gates (fan-in) connected to this gate
        unsigned int get_fan_in_num() const;

        // Get a specific input gate by index
        gate* get_fan_in(unsigned int i) const;

        // Add an output gate that this gate drives
        void add_output(gate* g_in);

        // Get the number of output gates (fan-out) connected to this gate
        unsigned int get_fan_out_num() const;

        // Get a specific output gate by index
        gate* get_fan_out(unsigned int i) const;

        // Set the logic function (GATE_FUNCTION) for this gate
        void set_function(GATE_FUNCTION function_in);

        // Get the current logic function of this gate
        GATE_FUNCTION get_function() const;

        // Set the name of this gate
        void set_name(const std::string& name_in);

        // Get the name of this gate
        std::string get_name() const;

        // Set the logic value (bitset) of this gate
        void set_value(const std::bitset<BIT_LENGTH>& value_in);

        // Get the logic value (bitset) of this gate
        std::bitset<BIT_LENGTH> get_value() const;

        // Set the logic level
        void set_level(unsigned int level_in);

        // Get the current logic level of this gate
        unsigned int get_level() const;

        // Increment the count of certain operations
        void add_count_1();

        // Reset the count to zero
        void reset_count();

        // Get the current count value
        unsigned int get_count() const;

        // Check if the output of this gate is inverted
        bool is_inverted() const;

        // Clear the input and output gate lists
        void clear_list();

        // Default constructor for gate
        gate();

        // Constructor with name and function initialization
        gate(const std::string& name_in, const GATE_FUNCTION& function_in);

        // Destructor for gate
        ~gate();
    private:
        std::string name;  // Name of the gate
        GATE_FUNCTION function;  // Logic function of the gate
        std::bitset<BIT_LENGTH> value;  // Current value of the gate
        unsigned int level;  // Logic level
        unsigned int count;  // Count of some specific operation
        std::vector<gate*> input_list;  // List of input gates connected to this gate
        std::vector<gate*> output_list;  // List of output gates connected to this gate
};

#endif  // GATE_H
