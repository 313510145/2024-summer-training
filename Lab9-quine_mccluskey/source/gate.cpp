#include "gate.h"

// Adds an input gate to the current gate's input list
void gate::add_input(gate* g_in) {
    this->input_list.push_back(g_in);
}

// Returns the number of input gates connected to the current gate
unsigned int gate::get_fan_in_num() const {
    return this->input_list.size();
}

// Retrieves the input gate at the specified index
gate* gate::get_fan_in(unsigned int i) const {
    return this->input_list[i];
}

// Adds an output gate to the current gate's output list
void gate::add_output(gate* g_in) {
    this->output_list.push_back(g_in);
}

// Returns the number of output gates connected to the current gate
unsigned int gate::get_fan_out_num() const {
    return this->output_list.size();
}

// Retrieves the output gate at the specified index
gate* gate::get_fan_out(unsigned int i) const {
    return this->output_list[i];
}

// Sets the function (logic operation) of the current gate
void gate::set_function(GATE_FUNCTION function_in) {
    this->function = function_in;
}

// Returns the current function (logic operation) of the gate
GATE_FUNCTION gate::get_function() const {
    return this->function;
}

// Sets the name of the current gate
void gate::set_name(const std::string& name_in) {
    this->name = name_in;
}

// Returns the name of the current gate
std::string gate::get_name() const {
    return this->name;
}

// Sets the value (logic state) of the current gate
void gate::set_value(const std::bitset<BIT_LENGTH>& value_in) {
    this->value = value_in;
}

// Returns the current value (logic state) of the gate
std::bitset<BIT_LENGTH> gate::get_value() const {
    return this->value;
}

// Sets the level (depth in the circuit) of the current gate
void gate::set_level(unsigned int level_in) {
    this->level = level_in;
}

// Returns the current level (depth) of the gate in the circuit
unsigned int gate::get_level() const {
    return this->level;
}

// Increments the count of operations or events associated with the gate
void gate::add_count_1() {
    this->count++;
}

// Resets the count to zero
void gate::reset_count() {
    this->count = 0;
}

// Returns the current count value
unsigned int gate::get_count() const {
    return this->count;
}

// Determines if the gate's function is an inverted type (e.g., NAND, NOR, XNOR, NOT)
bool gate::is_inverted() const {
    if (
        this->function == G_NAND ||
        this->function == G_NOR ||
        this->function == G_XNOR ||
        this->function == G_NOT
    ) {
        return true;
    }
    return false;
}

// Clears the input and output lists of the gate
void gate::clear_list() {
    this->input_list.clear();
    this->output_list.clear();
}

// Default constructor initializing member variables
gate::gate() {
    this->name = "";
    this->function = G_BAD;
    this->value = X;
    this->level = 0;
    this->count = 0;
}

// Constructor with parameters to initialize name and function
gate::gate(const std::string& name_in, const GATE_FUNCTION& function_in) {
    this->name = name_in;
    this->function = function_in;
    this->value = X;
    this->level = 0;
    this->count = 0;
}

// Destructor for the gate class
gate::~gate() {}
