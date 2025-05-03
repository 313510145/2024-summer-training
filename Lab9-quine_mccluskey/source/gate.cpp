#include "gate.h"

void gate::add_input(gate* g_in) {
    this->input_list.push_back(g_in);
}

void gate::add_output(gate* g_in) {
    this->output_list.push_back(g_in);
}

unsigned int gate::get_fan_in_num() const {
    return this->input_list.size();
}

unsigned int gate::get_fan_out_num() const {
    return this->output_list.size();
}

gate* gate::get_fan_in(unsigned int i) const {
    return this->input_list[i];
}

gate* gate::get_fan_out(unsigned int i) const {
    return this->output_list[i];
}

std::string gate::get_name() const {
    return this->name;
}

GATE_FUNCTION gate::get_function() const {
    return this->function;
}

std::bitset<BIT_LENGTH> gate::get_value() const {
    return this->value;
}

unsigned int gate::get_level() const {
    return this->level;
}

unsigned int gate::get_count() const {
    return this->count;
}

void gate::set_name(const std::string& name_in) {
    this->name = name_in;
}

void gate::set_function(GATE_FUNCTION function_in) {
    this->function = function_in;
}

void gate::set_value(const std::bitset<BIT_LENGTH>& value_in) {
    this->value = value_in;
}

void gate::set_level(unsigned int level_in) {
    this->level = level_in;
}

void gate::add_count_1() {
    this->count++;
}

void gate::reset_count() {
    this->count = 0;
}

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

gate::gate() {
    this->name = "";
    this->function = G_BAD;
    this->value = X;
    this->level = 0;
    this->count = 0;
}

gate::~gate() {}
