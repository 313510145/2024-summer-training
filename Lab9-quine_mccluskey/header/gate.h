#ifndef GATE_H
#define GATE_H

#include <string>
#include <vector>
#include <bitset>

const unsigned int BIT_LENGTH = 2;

enum VALUE {S0 = 0b00, S1 = 0b11, X = 0b01};
enum GATE_FUNCTION {G_PI, G_PO, G_AND, G_OR, G_XOR, G_NAND, G_NOR, G_XNOR, G_BUF, G_NOT, G_BAD};

class gate {
    public:
        void add_input(gate* g_in);
        void add_output(gate* g_in);
        unsigned int get_fan_in_num() const;
        unsigned int get_fan_out_num() const;
        gate* get_fan_in(unsigned int i) const;
        gate* get_fan_out(unsigned int i) const;
        std::string get_name() const;
        GATE_FUNCTION get_function() const;
        std::bitset<BIT_LENGTH> get_value() const;
        unsigned int get_level() const;
        unsigned int get_count() const;
        void set_name(const std::string& name_in);
        void set_function(GATE_FUNCTION function_in);
        void set_value(const std::bitset<BIT_LENGTH>& value_in);
        void set_level(unsigned int level_in);
        void add_count_1();
        void reset_count();
        bool is_inverted() const;
        gate();
        ~gate();
    private:
        std::string name;
        GATE_FUNCTION function;
        std::bitset<BIT_LENGTH> value;
        unsigned int level;
        unsigned int count;
        std::vector<gate*> input_list;
        std::vector<gate*> output_list;
};

#endif  // GATE_H
