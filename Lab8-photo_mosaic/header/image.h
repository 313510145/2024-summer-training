#ifndef IMAGE_H
#define IMAGE_H

#include "image_loader.h"
#include "filter.h"

// Abstract base class for image processing
class image {
    public:
        // Pure virtual functions defining the interface for image operations
        virtual const bool load_image(const std::string& file_name) = 0;  // Load an image from a file
        virtual const void dump_image(const std::string& file_name) const = 0;  // Save the image to a file
        virtual const void box(const int& r) = 0;  // Apply a box filter with radius r
        virtual const void sobel() = 0;  // Apply the Sobel edge detection filter
        virtual const void normalization() = 0;  // Normalize the image
        virtual const void mosaic(const int& r) = 0;  // Apply a mosaic effect with radius r
        virtual const void resize(const int& nw, const int& nh) = 0;  // Resize the image to new width (nw) and height (nh)
        virtual const void photo_mosaic(const int& r) = 0;  // Apply a photo mosaic effect with radius r
        virtual const void display_X_server() const = 0;  // Display the image in an X server window
        virtual const void display_ASCII() const = 0;  // Display the image as ASCII art
        virtual const void display_command_line() const = 0;  // Display the image using command-line tools
        virtual const double* const get_average() const = 0;  // Get the average pixel values
        virtual const void assign_to(int*** const pixel, const int& px, const int& py, const int& w, const int& h) const = 0;  // Assign pixel data to the image
        image();  // Default constructor
        image(const int& w, const int& h);  // Constructor with width and height
        virtual ~image();  // Virtual destructor
    protected:
        int width, height;  // Image dimensions
        static image_loader il;  // Static instance of image_loader for loading and saving images
        static filter f;  // Static instance of filter for applying filters
};

#endif  // IMAGE_H