#include "rob_master.h"
#include <fstream>

int main(int argc, char** argv) {
    // Ensure there are enough command-line arguments
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

    // Create a new rob_master object to process the houses
    rob_master* rm = new rob_master();

    // Read input and calculate maximum collectible money
    rm->input_information_and_calculate(input_file);
    input_file.close(); // Close the input file after reading

    // Open the output file
    std::ofstream output_file(argv[2]);
    if (!output_file) {
        std::cout << "Cannot open the output file: " << argv[2] << std::endl;
        delete rm; // Clean up before exit
        exit(-1);
    }

    // Output the maximum collectible money
    rm->output_maximum_amount(output_file);
    
    // Clean up memory by deleting the rob_master object
    delete rm;

    // Close the output file
    output_file.close();

    return 0; // Exit successfully
}
