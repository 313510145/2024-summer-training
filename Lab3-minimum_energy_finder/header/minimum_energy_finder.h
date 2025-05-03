#ifndef MINIMUM_ENERGY_FINDER_H
#define MINIMUM_ENERGY_FINDER_H

#include <iostream>
#include <map>
#include <list>

struct item {
    unsigned int weight, time;
};

class minimum_energy_finder {
    public:
        void input_information_and_calculate(std::istream& is);
        void output_minimum_energy(std::ostream& os) const;
        minimum_energy_finder();
        ~minimum_energy_finder();
    private:
        void calculate_minimum_energy();
        std::map<double, std::list<item>> garage;
        unsigned int minimum_energy;
};

#endif  // MINIMUM_ENERGY_FINDER_H
