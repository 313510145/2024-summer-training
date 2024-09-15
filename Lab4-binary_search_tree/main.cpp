#include "binary_search_tree.h"
#include <fstream>

// Main function to read input, perform operations, and output results
int main(int argc, char** argv) {
    // Check if correct number of arguments is passed
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        exit(-1);
    }

    std::ifstream input_file(argv[1]);
    std::ofstream output_file(argv[2]);
    
    // Handle file opening errors
    if (!input_file) {
        std::cout << "Cannot open the input file: " << argv[1] << std::endl;
        exit(-1);
    }
    if (!output_file) {
        std::cout << "Cannot open the output file: " << argv[2] << std::endl;
        exit(-1);
    }

    // Create a binary search tree (BST) object
    binary_search_tree* bst = new binary_search_tree();
    
    // Perform operations based on input commands and write results to output file
    bst->input_operation_and_output_result(input_file, output_file);
    
    // Clean up the BST object
    delete bst;
    
    // Close input and output files
    input_file.close();
    output_file.close();
    
    return 0;  // Exit successfully
}
