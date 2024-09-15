#include "anagram_dictionary.h"
#include <fstream>

// Main function to read input, process anagram groups, and write output
int main(int argc, char** argv) {
    // Check if correct number of arguments is passed
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        exit(-1);
    }

    // Open the input file
    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cout << "Cannot open the input file: " << argv[1] << std::endl;
        exit(-1);
    }

    // Create a new anagram dictionary object
    anagram_dictionary* ad = new anagram_dictionary();
    
    // Process the input file and group the words into anagrams
    ad->input_string_and_group(input_file);
    input_file.close();  // Close the input file after processing
    
    // Open the output file
    std::ofstream output_file(argv[2]);
    if (!output_file) {
        std::cout << "Cannot open the output file: " << argv[2] << std::endl;
        delete ad;
        exit(-1);
    }
    
    // Output the grouped anagrams to the file
    ad->output_group(output_file);
    
    // Clean up resources
    delete ad;
    output_file.close();  // Close the output file
    
    return 0;  // Exit the program successfully
}
