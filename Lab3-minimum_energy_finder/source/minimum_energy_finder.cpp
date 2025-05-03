#include "minimum_energy_finder.h"

void minimum_energy_finder::input_information_and_calculate(std::istream& is) {
    unsigned int num_item;
    std::list<item> temp_list;
    is >> num_item;
    for (unsigned int i = 0; i < num_item; i++) {
        item temp_item;
        is >> temp_item.weight;
        temp_item.time = 0;
        temp_list.push_back(temp_item);
    }
    for (auto& tl: temp_list) {
        is >> tl.time;
        this->garage[static_cast<double>(tl.weight) / tl.time].push_front(tl);
    }
    temp_list.clear();
    this->calculate_minimum_energy();
}

void minimum_energy_finder::output_minimum_energy(std::ostream& os) const {
    os << this->minimum_energy;
}

void minimum_energy_finder::calculate_minimum_energy() {
    unsigned int total_weight = 0;
    for (const auto& g: this->garage) {
        for (const auto& g_item: g.second) {
            this->minimum_energy += total_weight * g_item.time;
            total_weight += g_item.weight;
        }
    }
}

minimum_energy_finder::minimum_energy_finder(): minimum_energy(0) {}

minimum_energy_finder::~minimum_energy_finder() {
    this->garage.clear();
}
