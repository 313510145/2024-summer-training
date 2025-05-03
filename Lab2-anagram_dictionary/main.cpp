#include "anagram_dictionary.h"
#include <fstream>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        exit(-1);
    }
    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cout << "Cannot open the input file: " << argv[1] << std::endl;
        exit(-1);
    }
    anagram_dictionary* ad = new anagram_dictionary();
    ad->input_string_and_group(input_file);
    input_file.close();
    std::ofstream output_file(argv[2]);
    if (!output_file) {
        std::cout << "Cannot open the output file: " << argv[2] << std::endl;
        delete ad;
        exit(-1);
    }
    ad->output_group(output_file);
    delete ad;
    output_file.close();
    return 0;
}
