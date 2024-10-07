#include "quine_mccluskey.h"
#include <fstream>

int main(int argc, char** argv) {
    // Check if sufficient arguments are provided
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        exit(-1); // Exit if the input/output file arguments are missing
    }
    
    // Attempt to open the input file
    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cout << "Cannot open the input file: " << argv[1] << std::endl;
        exit(-1); // Exit if the input file cannot be opened
    }

    // Create a new instance of the quine_mccluskey class
    quine_mccluskey* qm = new quine_mccluskey();
    
    // Read the Verilog input from the file
    qm->input_verilog(input_file);
    input_file.close(); // Close the input file after reading

    // Attempt to open the output file
    std::ofstream output_file(argv[2]);
    if (!output_file) {
        std::cout << "Cannot open the output file: " << argv[2] << std::endl;
        delete qm; // Clean up the dynamically allocated memory
        exit(-1); // Exit if the output file cannot be opened
    }

    // Write the output in BLIF format to the output file
    qm->output_blif(output_file);
    
    // Clean up by deleting the quine_mccluskey instance
    delete qm;
    output_file.close(); // Close the output file after writing
    return 0; // Return success
}
