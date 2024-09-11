#include "largest_same_path_finder.h"
#include <fstream>

int main(int argc, char** argv) {
    // Check if correct number of arguments is passed
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return -1;
    }

    // Open input and output files
    std::ifstream input_file(argv[1]);
    std::ofstream output_file(argv[2]);

    // Check if the input file opened successfully
    if (!input_file) {
        std::cerr << "Cannot open the input file!\n";
        return -1;
    }
    
    // Check if the output file opened successfully
    if (!output_file) {
        std::cerr << "Cannot open the output file!\n";
        return -1;
    }

    // Create a new largest_same_path_finder object
    largest_same_path_finder* lspf = new largest_same_path_finder();

    // Process the input and generate the output
    lspf->input_information_and_output_result(input_file, output_file);

    // Clean up memory
    delete lspf;

    // Close the input and output files
    input_file.close();
    output_file.close();

    return 0; // Exit successfully
}
