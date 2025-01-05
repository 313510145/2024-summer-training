#ifndef ROB_MASTER_H
#define ROB_MASTER_H

#include <iostream>
#include <vector>

// Structure to represent a house, storing money available and maximum amount collectible up to that house
struct house {
    unsigned int money;          // Money in the house
    unsigned int maximum_amount; // Maximum amount collectible by robbing up to this house
};

class rob_master {
    public:
        // Reads input information and calculates the maximum money collectible for each house
        void input_information_and_calculate(std::istream& is);
        
        // Outputs the maximum amount collectible across the entire community
        void output_maximum_amount(std::ostream& os) const;
        
        // Constructor
        rob_master();
        
        // Destructor
        ~rob_master();
        
    private:
        // A vector representing the community of houses
        std::vector<house> community;
};

#endif  // ROB_MASTER_H
