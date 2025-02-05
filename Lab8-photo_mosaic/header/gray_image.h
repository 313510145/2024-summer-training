#ifndef GRAY_IMAGE_H
#define GRAY_IMAGE_H

#include "image.h"

// Derived class from image, specifically for handling grayscale images
class gray_image: public image {
    public:
        // Load grayscale image from a file
        virtual bool load_image(const std::string& file_name) override;

        // Save grayscale image to a file
        virtual void dump_image(const std::string& file_name) const override;

        // Apply a box filter with radius r
        virtual void box(const int& r) override;

        // Apply Sobel edge detection filter
        virtual void sobel() override;

        // Normalize the grayscale image
        virtual void normalization() override;

        // Apply mosaic effect with radius r
        virtual void mosaic(const int& r) override;

        // Resize the grayscale image to new width (nw) and height (nh)
        virtual void resize(const int& nw, const int& nh) override;

        // Apply photo mosaic effect with images i and radius r
        virtual void photo_mosaic(const std::string& i, const int& r) override;

        // Display grayscale image using X server
        virtual void display_X_server() const override;

        // Display grayscale image as ASCII art
        virtual void display_ASCII() const override;

        // Display grayscale image using command-line tools
        virtual void display_command_line() const override;

        // Get average pixel value of the grayscale image
        virtual double* get_average() const override;

        // Assign pixel data from another image to this image
        virtual void assign_to(int*** const pixel, const int& px, const int& py, const int& w, const int& h) const override;
        
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
        // Pointer to pixel data of the grayscale image
        int** pixel;
};

#endif  // GRAY_IMAGE_H
