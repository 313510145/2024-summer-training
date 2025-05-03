#include "rob_master.h"

void rob_master::input_information_and_calculate(std::istream& is) {
    house temp_house;
    temp_house.money = 0;
    while (is >> temp_house.money) {
        switch (this->community.size()) {
            case 0 ... 1:
                temp_house.maximum_amount = temp_house.money;
                break;
            case 2:
                temp_house.maximum_amount = this->community[0].maximum_amount + temp_house.money;
                break;
            default:
                if (this->community[this->community.size() - 2].maximum_amount < this->community[this->community.size() - 3].maximum_amount) {
                    temp_house.maximum_amount = this->community[this->community.size() - 3].maximum_amount + temp_house.money;
                }
                else {
                    temp_house.maximum_amount = this->community[this->community.size() - 2].maximum_amount + temp_house.money;
                }
                break;
        }
        this->community.push_back(temp_house);
    }
}

void rob_master::output_maximum_amount(std::ostream& os) const {
    if (!this->community.size()) {
        os << 0;
    }
    else {
        os << this->community[this->community.size() - 1].maximum_amount;
    }
    os << std::endl;
}

rob_master::rob_master() {}

rob_master::~rob_master() {
    this->community.clear();
}
