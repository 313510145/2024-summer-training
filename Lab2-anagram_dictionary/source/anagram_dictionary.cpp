#include "anagram_dictionary.h"
#include <algorithm>

// Method to input strings, group them by their sorted character sequences
// Each input string is stripped of brackets and quotes, sorted, and stored in the map
void anagram_dictionary::input_string_and_group(std::istream& is) {
    std::string current_line;
    
    // Read each line of input separated by a comma
    while (getline(is, current_line, ',')) {
        std::string temp, sorted_temp;
        
        // Remove brackets and quotes from the input
        for (const char& c: current_line) {
            if (c == '\"' || c == '[' || c == ']') {
                continue;
            }
            temp.push_back(c);  // Collect cleaned characters
        }
        
        // Sort the cleaned string to generate the anagram key
        sorted_temp = temp;
        sort(sorted_temp.begin(), sorted_temp.end());
        
        // Group words with the same sorted character sequences
        this->group[sorted_temp].push_front(temp);
    }
}

// Method to output the grouped anagrams
// Outputs each group of anagrams stored in the map
void anagram_dictionary::output_group(std::ostream& os) const {
    for (const auto& g: this->group) {
        // Handle edge case for empty input line
        if (g.first == "") {
            os << "empty line.";
        }

        // Output all words in the anagram group
        for (const auto& w: g.second) {
            os << w << " ";
        }
        os << std::endl;  // Newline after each group
    }
}

// Constructor: Initializes the anagram dictionary
anagram_dictionary::anagram_dictionary() {}

// Destructor: Clears the anagram dictionary map
anagram_dictionary::~anagram_dictionary() {
    this->group.clear();
}
