#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <string>

class filter {
    public:
        // Applies a box filter to a grayscale image.
        static const void box_gray(const int& w, const int& h, int** const pixel, const int& r);

        // Applies a box filter to an RGB image.
        static const void box_RGB(const int& w, const int& h, int*** const pixel, const int& r);

        // Applies the Sobel filter to a grayscale image for edge detection.
        static const void sobel_gray(const int& w, const int& h, int** const pixel);

        // Applies the Sobel filter to an RGB image for edge detection.
        static const void sobel_RGB(const int& w, const int& h, int*** const pixel);

        // Normalizes pixel values of a grayscale image to the range [0, 255].
        static const void normalization_gray(const int& w, const int& h, int** const pixel);

        // Normalizes pixel values of an RGB image to the range [0, 255].
        static const void normalization_RGB(const int& w, const int& h, int*** const pixel);

        // Applies a mosaic effect to a grayscale image.
        static const void mosaic_gray(const int& w, const int& h, int** const pixel, const int& r);

        // Applies a mosaic effect to an RGB image.
        static const void mosaic_RGB(const int& w, const int& h, int*** const pixel, const int& r);

        // Resizes a grayscale image to new dimensions.
        static const void resize_gray(int& w, int& h, int*** const pixel, const int& nw, const int& nh);

        // Resizes an RGB image to new dimensions.
        static const void resize_RGB(int& w, int& h, int**** const pixel, const int& nw, const int& nh);

        // Applies a photo mosaic effect to a grayscale image.
        static const void photo_mosaic_gray(const int& w, const int& h, int** pixel, const int& r, const std::vector<std::string>& file_name);

        // Applies a photo mosaic effect to an RGB image.
        static const void photo_mosaic_RGB(const int& w, const int& h, int*** pixel, const int& r, const std::vector<std::string>& file_name);

        // Default constructor
        filter();

        // Destructor
        ~filter();
    private:
};

#endif  // FILTER_H
