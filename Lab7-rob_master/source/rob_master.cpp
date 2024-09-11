#include "rob_master.h"

// Reads house money information, calculates maximum collectible amount for each house using dynamic programming
const void rob_master::input_information_and_calculate(std::istream& is) {
    house temp_house;
    temp_house.money = 0;

    // Read money values for each house from the input stream
    while (is >> temp_house.money) {
        switch (this->community.size()) {
            case 0 ... 1:
                // For the first two houses, the maximum collectible is the money in the house
                temp_house.maximum_amount = temp_house.money;
                break;
            case 2:
                // For the third house, you can only rob house 1 and house 3, so sum them
                temp_house.maximum_amount = this->community[0].maximum_amount + temp_house.money;
                break;
            default:
                // For subsequent houses, choose between two options:
                // 1. Rob the house before the previous house and add the current house's money.
                // 2. Rob the house just before the current one.
                if (this->community[this->community.size() - 2].maximum_amount < this->community[this->community.size() - 3].maximum_amount) {
                    temp_house.maximum_amount = this->community[this->community.size() - 3].maximum_amount + temp_house.money;
                } else {
                    temp_house.maximum_amount = this->community[this->community.size() - 2].maximum_amount + temp_house.money;
                }
                break;
        }

        // Add the house to the community
        this->community.push_back(temp_house);
    }
}

// Outputs the maximum collectible amount across all houses
const void rob_master::output_maximum_amount(std::ostream& os) const {
    // If there are no houses, the maximum amount collectible is 0
    if (!this->community.size()) {
        os << 0;
    } else {
        // Otherwise, output the maximum amount at the last house
        os << this->community[this->community.size() - 1].maximum_amount;
    }
    os << std::endl; // End the output with a newline
}

// Constructor: no special initialization needed
rob_master::rob_master() {}

// Destructor: clears the community vector
rob_master::~rob_master() {
    this->community.clear();
}
