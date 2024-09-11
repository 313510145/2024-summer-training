#ifndef GRAY_IMAGE_H
#define GRAY_IMAGE_H

#include "image.h"

// Derived class from image, specifically for handling grayscale images
class gray_image: public image {
    public:
        // Load grayscale image from a file
        virtual const bool load_image(const std::string& file_name) override;
        // Save grayscale image to a file
        virtual const void dump_image(const std::string& file_name) const override;
        // Apply a box filter with radius r
        virtual const void box(const int& r) override;
        // Apply Sobel edge detection filter
        virtual const void sobel() override;
        // Normalize the grayscale image
        virtual const void normalization() override;
        // Apply mosaic effect with radius r
        virtual const void mosaic(const int& r) override;
        // Resize the grayscale image to new width (nw) and height (nh)
        virtual const void resize(const int& nw, const int& nh) override;
        // Apply photo mosaic effect with radius r
        virtual const void photo_mosaic(const int& r) override;
        // Display grayscale image using X server
        virtual const void display_X_server() const override;
        // Display grayscale image as ASCII art
        virtual const void display_ASCII() const override;
        // Display grayscale image using command-line tools
        virtual const void display_command_line() const override;
        // Get average pixel value of the grayscale image
        virtual const double* const get_average() const override;
        // Assign pixel data from another image to this image
        virtual const void assign_to(int*** const pixel, const int& px, const int& py, const int& w, const int& h) const override;
        
        // Default constructor
        gray_image();
        // Constructor with width, height, and pixel data
        gray_image(const int& w, const int& h, const int** const p);
        // Copy constructor
        gray_image(const gray_image& gi);
        // Virtual destructor
        virtual ~gray_image() override;
        // Assignment operator
        gray_image& operator =(const gray_image& gi);

    private:
        int** pixel;  // Pointer to pixel data of the grayscale image
};

#endif  // GRAY_IMAGE_H
