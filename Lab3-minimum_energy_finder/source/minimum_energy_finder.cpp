#include "minimum_energy_finder.h"

// Method to input the item information and calculate the minimum energy
// Reads the number of items, their weight and time values from the input stream
const void minimum_energy_finder::input_information_and_calculate(std::istream& is) {
    unsigned int num_item;
    std::list<item> temp_list;
    
    // Read the number of items
    is >> num_item;
    
    // Input weights for all items and initialize times to zero
    for (unsigned int i = 0; i < num_item; i++) {
        item temp_item;
        is >> temp_item.weight;  // Input weight
        temp_item.time = 0;      // Initialize time to zero
        temp_list.push_back(temp_item);
    }

    // Input times for all items and organize items by weight-to-time ratio
    for (auto& tl: temp_list) {
        is >> tl.time;  // Input time
        // Store item in the map based on its weight/time ratio
        this->garage[static_cast<double>(tl.weight) / tl.time].push_front(tl);
    }
    
    // Clear the temporary list after use
    temp_list.clear();
    
    // Calculate the minimum energy based on the input data
    this->calculate_minimum_energy();
}

// Method to output the calculated minimum energy to the output stream
const void minimum_energy_finder::output_minimum_energy(std::ostream& os) const {
    os << this->minimum_energy;  // Output the minimum energy
}

// Method to calculate the minimum energy by iterating over the organized items
const void minimum_energy_finder::calculate_minimum_energy() {
    unsigned int total_weight = 0;
    
    // Iterate over items sorted by their weight/time ratio
    for (const auto& g: this->garage) {
        for (const auto& g_item: g.second) {
            // Calculate the contribution of each item to the total energy
            this->minimum_energy += total_weight * g_item.time;
            total_weight += g_item.weight;  // Update the total weight
        }
    }
}

// Constructor to initialize the minimum energy to zero
minimum_energy_finder::minimum_energy_finder(): minimum_energy(0) {}

// Destructor to clear the garage map, ensuring proper cleanup
minimum_energy_finder::~minimum_energy_finder() {
    this->garage.clear();  // Clear the map
}
