#ifndef ANAGRAM_DICTIONARY_H
#define ANAGRAM_DICTIONARY_H

#include <map>
#include <string>
#include <iostream>
#include <list>

class anagram_dictionary {
    public:
        void input_string_and_group(std::istream& is);
        void output_group(std::ostream& os) const;
        anagram_dictionary();
        ~anagram_dictionary();
    private:
        std::map<std::string, std::list<std::string>> group;
};

#endif  // ANAGRAM_DICTIONARY_H
