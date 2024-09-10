#ifndef ANAGRAM_DICTIONARY_H
#define ANAGRAM_DICTIONARY_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <list>

// Class representing an anagram dictionary that groups words by their sorted characters
class anagram_dictionary {
    public:
        // Method to input strings, group them into anagrams, and store them
        const void input_string_and_group(std::istream& is);
        
        // Method to output the grouped anagrams
        const void output_group(std::ostream& os) const;
        
        // Constructor to initialize the dictionary
        anagram_dictionary();
        
        // Destructor to clean up resources
        ~anagram_dictionary();
    private:
        // A map that stores lists of words grouped by their sorted character sequences
        std::unordered_map<std::string, std::list<std::string>> group;
};

#endif  // ANAGRAM_DICTIONARY_H
