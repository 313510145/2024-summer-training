#include "minimum_energy_finder.h"
#include <fstream>

// Main function to read input, calculate minimum energy, and write output
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
        exit(-1);  // Exit if the input file cannot be opened
    }

    // Create a new instance of minimum_energy_finder
    minimum_energy_finder* mef = new minimum_energy_finder();
    
    // Read the input data and calculate the minimum energy
    mef->input_information_and_calculate(input_file);
    input_file.close();  // Close the input file after reading

    // Open the output file
    std::ofstream output_file(argv[2]);
    if (!output_file) {
        std::cout << "Cannot open the output file: " << argv[2] << std::endl;
        delete mef;
        exit(-1);  // Exit if the output file cannot be opened
    }

    // Output the calculated minimum energy
    mef->output_minimum_energy(output_file);
    
    // Clean up by deleting the minimum_energy_finder instance
    delete mef;
    output_file.close();  // Close the output file
    
    return 0;  // Exit the program successfully
}
