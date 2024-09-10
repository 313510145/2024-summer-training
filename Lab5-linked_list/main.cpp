#include "linked_list.h"
#include <fstream>

int main(int argc, char** argv) {
    // Open the input file for reading
    std::ifstream input_file(argv[1]);
    // Open the output file for writing
    std::ofstream output_file(argv[2]);

    // Check if the input file was successfully opened
    if (!input_file) {
        std::cerr << "Cannot open the input file!\n";
        return -1; // Exit with error code
    }
    // Check if the output file was successfully opened
    if (!output_file) {
        std::cerr << "Cannot open the output file!\n";
        return -1; // Exit with error code
    }

    // Create a new linked_list object
    linked_list* ll = new linked_list();

    // Process commands from the input file and output results to the output file
    ll->input_operation_and_output_result(input_file, output_file);

    // Deallocate memory used by the linked list
    delete ll;

    // Close the input and output files
    input_file.close();
    output_file.close();

    return 0; // Indicate successful execution
}
