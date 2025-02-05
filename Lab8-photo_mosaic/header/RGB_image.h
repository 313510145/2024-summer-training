#ifndef RGB_IMAGE_H
#define RGB_IMAGE_H

#include "image.h"

// RGB_image class extends the base class 'image' to handle RGB images specifically
class RGB_image: public image {
    public:
        // Load an image from a file and initialize the pixel data
        virtual bool load_image(const std::string& file_name) override;

        // Save the current image to a file
        virtual void dump_image(const std::string& file_name) const override;

        // Apply a box filter to the image with radius 'r'
        virtual void box(const int& r) override;

        // Apply the Sobel edge detection algorithm
        virtual void sobel() override;

        // Normalize the image colors
        virtual void normalization() override;

        // Apply a mosaic effect to the image with radius 'r'
        virtual void mosaic(const int& r) override;

        // Resize the image to new width 'nw' and height 'nh'
        virtual void resize(const int& nw, const int& nh) override;

        // Create a photo mosaic from a set of images 'i' with radius 'r'
        virtual void photo_mosaic(const std::string& i, const int& r) override;

        // Display the image on an X server
        virtual void display_X_server() const override;

        // Display the image in ASCII art format
        virtual void display_ASCII() const override;

        // Display the image on the command line
        virtual void display_command_line() const override;

        // Calculate and return the average color values of the image
        virtual double* get_average() const override;

        // Assign a portion of this image's pixel data to another pixel array
        virtual void assign_to(int*** const pixel, const int& px, const int& py, const int& w, const int& h) const override;

        // Default constructor
        RGB_image();

        // Constructor with specified dimensions and pixel data
        RGB_image(const int& w, const int& h, const int*** const p);

        // Copy constructor
        RGB_image(const RGB_image& RGBi);

        // Destructor to clean up dynamically allocated memory
        virtual ~RGB_image() override;

        // Assignment operator
        RGB_image& operator =(const RGB_image& RGBi);

    private:
        // 3D array to store pixel data (height x width x color channels)
        int*** pixel;
};

#endif  // RGB_IMAGE_H
