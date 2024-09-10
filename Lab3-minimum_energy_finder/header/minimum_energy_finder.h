#ifndef MINIMUM_ENERGY_FINDER_H
#define MINIMUM_ENERGY_FINDER_H

#include <iostream>
#include <map>
#include <list>

// Struct to represent an item with weight and time properties
struct item {
    unsigned int weight, time;
};

// Class to calculate the minimum energy based on item weights and times
class minimum_energy_finder {
    public:
        // Method to input item information and calculate the minimum energy
        const void input_information_and_calculate(std::istream& is);
        
        // Method to output the calculated minimum energy
        const void output_minimum_energy(std::ostream& os) const;
        
        // Constructor to initialize minimum energy
        minimum_energy_finder();
        
        // Destructor to clear the stored data
        ~minimum_energy_finder();
    
    private:
        // Method to calculate the minimum energy based on input data
        const void calculate_minimum_energy();
        
        // A map that organizes items by their weight-to-time ratio
        std::map<double, std::list<item>> garage;
        
        // Variable to store the computed minimum energy
        unsigned int minimum_energy;
};

#endif  // MINIMUM_ENERGY_FINDER_H
