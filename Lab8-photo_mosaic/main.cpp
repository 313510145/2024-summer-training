#include "image_loader.h"
#include "image.h"
#include "gray_image.h"
#include "RGB_image.h"
#include "filter.h"

#include <iostream>

const int8_t BOX           = 0b00000001,
             SOBEL         = 0b00000010,
             NORMALIZATION = 0b00000100,
             MOSAIC        = 0b00001000,
             RESIZE        = 0b00010000,
             PHOTO_MOSAIC  = 0b00100000;

void load_case(image* const i, const int8_t& option) {
    if (option & BOX) {
        i->box(15);
    }
    if (option & SOBEL) {
        i->sobel();
    }
    if (option & NORMALIZATION) {
        i->normalization();
    }
    if (option & MOSAIC) {
        i->mosaic(31);
    }
    if (option & RESIZE) {
        i->resize(600, 300);
    }
    if (option & PHOTO_MOSAIC) {
        i->photo_mosaic("image/cifar10", 32);
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_image> <output_directory>/\n";
        exit(-1);
    }
    image* image_1 = new gray_image();
    if (image_1->load_image(argv[1])) {
        int8_t option_1 = PHOTO_MOSAIC;
        load_case(image_1, option_1);
        image_1->dump_image(std::string(argv[2]) + "image_1.jpg");
    }
    delete image_1;
    image* image_2 = new RGB_image();
    if (image_2->load_image(argv[1])) {
        int8_t option_2 = PHOTO_MOSAIC;
        load_case(image_2, option_2);
        image_2->dump_image(std::string(argv[2]) + "image_2.jpg");
    }
    delete image_2;
    return 0;
}
