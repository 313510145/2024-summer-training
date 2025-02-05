#include "gate.h"

// Add an input gate to the input list
void gate::add_input(gate* g_in) {
    this->input_list.push_back(g_in);
}

// Add an output gate to the output list
void gate::add_output(gate* g_in) {
    this->output_list.push_back(g_in);
}

// Get the number of fan-in connections
unsigned int gate::get_fan_in_num() const {
    return this->input_list.size();
}

// Get the number of fan-out connections
unsigned int gate::get_fan_out_num() const {
    return this->output_list.size();
}

// Get a specific fan-in gate by index
gate* gate::get_fan_in(unsigned int i) const {
    return this->input_list[i];
}

// Get a specific fan-out gate by index
gate* gate::get_fan_out(unsigned int i) const {
    return this->output_list[i];
}

// Get the gate name
std::string gate::get_name() const {
    return this->name;
}

// Get the gate function
GATE_FUNCTION gate::get_function() const {
    return this->function;
}

// Get the gate value
std::bitset<BIT_LENGTH> gate::get_value() const {
    return this->value;
}

// Get the gate level
unsigned int gate::get_level() const {
    return this->level;
}

// Get the gate count value
unsigned int gate::get_count() const {
    return this->count;
}

// Set the gate name
void gate::set_name(const std::string& name_in) {
    this->name = name_in;
}

// Set the gate function
void gate::set_function(GATE_FUNCTION function_in) {
    this->function = function_in;
}

// Set the gate value
void gate::set_value(const std::bitset<BIT_LENGTH>& value_in) {
    this->value = value_in;
}

// Set the gate level
void gate::set_level(unsigned int level_in) {
    this->level = level_in;
}

// Increment the gate count by 1
void gate::add_count_1() {
    this->count++;
}

// Reset the gate count to zero
void gate::reset_count() {
    this->count = 0;
}

// Check if the gate is inverted
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

// Constructor: Initialize default values
gate::gate() {
    this->name = "";
    this->function = G_BAD;
    this->value = X;
    this->level = 0;
    this->count = 0;
}

// Destructor: Cleanup resources
gate::~gate() {}
