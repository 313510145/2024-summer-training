#include "image_loader.h"
#include "image.h"
#include "gray_image.h"
#include "RGB_image.h"
#include "filter.h"

#include <cassert>

// Bitmask constants for various image processing options
const int8_t BOX           = 0b00000001,  // Apply box filter
             SOBEL         = 0b00000010,  // Apply Sobel filter
             NORMALIZATION = 0b00000100,  // Apply normalization
             MOSAIC        = 0b00001000,  // Apply mosaic effect
             RESIZE        = 0b00010000,  // Resize image
             PHOTO_MOSAIC  = 0b00100000;  // Apply photo mosaic effect

// Function to apply selected image processing operations
const void load_case(image* const i, const int8_t& option) {
    // Apply box filter if BOX option is set
    if (option & BOX) {
        i->box(15);
    }
    // Apply Sobel filter if SOBEL option is set
    if (option & SOBEL) {
        i->sobel();
    }
    // Apply normalization if NORMALIZATION option is set
    if (option & NORMALIZATION) {
        i->normalization();
    }
    // Apply mosaic effect if MOSAIC option is set
    if (option & MOSAIC) {
        i->mosaic(31);
    }
    // Resize image if RESIZE option is set
    if (option & RESIZE) {
        i->resize(600, 300);
    }
    // Apply photo mosaic effect if PHOTO_MOSAIC option is set
    if (option & PHOTO_MOSAIC) {
        i->photo_mosaic(32);
    }
}

int main(int argc, char** argv) {
    // Process grayscale image
    image* image_1 = new gray_image();
    if (image_1->load_image(argv[1])) { // Load grayscale image
        int8_t option_1 = PHOTO_MOSAIC; // Define processing options for grayscale image
        load_case(image_1, option_1);  // Apply selected operations
        image_1->dump_image(std::string(argv[2]) + "/image_1.jpg"); // Save processed image
    }
    delete image_1; // Clean up memory
    
    // Process RGB image
    image* image_2 = new RGB_image();
    if (image_2->load_image(argv[1])) { // Load RGB image
        int8_t option_2 = PHOTO_MOSAIC; // Define processing options for RGB image
        load_case(image_2, option_2);  // Apply selected operations
        image_2->dump_image(std::string(argv[2]) + "/image_2.jpg"); // Save processed image
    }
    delete image_2; // Clean up memory
    
    return 0; // Exit program
}
