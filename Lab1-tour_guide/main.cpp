#include "tour_guide.h"
#include <fstream>

// Main function to read input, process the tour, and write output
int main(int argc, char** argv) {
    // Open the input file
    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cout << "Cannot open the input file!\n";
        exit(-1);
    }

    // Create a new tour guide object
    tour_guide* tg = new tour_guide();
    
    // Input the toured track
    tg->input_toured_track_and_tour(input_file);
    input_file.close();  // Close the input file

    // Open the output file
    std::ofstream output_file(argv[2]);
    if (!output_file) {
        std::cout << "Cannot open the output file!\n";
        exit(-1);
    }

    // Output the tour track
    tg->output_tour_track(output_file);
    
    // Clean up and close the output file
    delete tg;
    output_file.close();
    
    return 0;  // Exit the program successfully
}
