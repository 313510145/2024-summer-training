#include "rob_master.h"
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
    rob_master* rm = new rob_master();
    rm->input_information_and_calculate(input_file);
    input_file.close();
    std::ofstream output_file(argv[2]);
    if (!output_file) {
        std::cout << "Cannot open the output file: " << argv[2] << std::endl;
        delete rm;
        exit(-1);
    }
    rm->output_maximum_amount(output_file);
    delete rm;
    output_file.close();
    return 0;
}
