#include "anagram_dictionary.h"
#include <algorithm>

void anagram_dictionary::input_string_and_group(std::istream& is) {
    std::string current_line;
    while (getline(is, current_line, ',')) {
        std::string temp, sorted_temp;
        for (const char& c: current_line) {
            if (c == '\"' || c == '[' || c == ']') {
                continue;
            }
            temp.push_back(c);
        }
        sorted_temp = temp;
        sort(sorted_temp.begin(), sorted_temp.end());
        this->group[sorted_temp].push_front(temp);
    }
}

void anagram_dictionary::output_group(std::ostream& os) const {
    for (const auto& g: this->group) {
        if (g.first == "") {
            os << "empty line.";
        }
        for (const auto& w: g.second) {
            os << w << " ";
        }
        os << std::endl;
    }
}

anagram_dictionary::anagram_dictionary() {}

anagram_dictionary::~anagram_dictionary() {
    this->group.clear();
}
