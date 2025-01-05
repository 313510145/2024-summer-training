#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#define cimg_use_jpeg  // Enable support for JPEG images in CImg
#define cimg_use_png   // Enable support for PNG images in CImg

#include "CImg.h"      // Include the CImg library for image processing
#include <string>
#include <vector>

class image_loader {
public:
    // Load a grayscale image from the given file and return a 2D array of pixel values
    int** load_gray(const std::string& file_name, int* const w, int* const h) const;

    // Load an RGB image from the given file and return a 3D array of pixel values
    static int*** load_RGB(const std::string& file_name, int* const w, int* const h);

    // Save a grayscale image to a file using pixel data and dimensions
    static void dump_gray(const int& w, const int& h, int** const pixel, const std::string& file_name);

    // Save an RGB image to a file using pixel data and dimensions
    static void dump_RGB(const int& w, const int& h, int*** const pixel, const std::string& file_name);

    // Display a grayscale image in an X server window
    static void display_gray_X_server(const int& w, const int& h, int** const pixel);

    // Display an RGB image in an X server window
    static void display_RGB_X_server(const int& w, const int& h, int*** const pixel);

    // Display a grayscale image as ASCII characters in the terminal
    static void display_gray_ASCII(const int& w, const int& h, int** const pixel);

    // Display an RGB image as ASCII characters in the terminal
    static void display_RGB_ASCII(const int& w, const int& h, int*** const pixel);

    // Display an image using a command line tool
    static void display_command_line(const std::string& file_name);

    // List all files in a directory and store the file names in a vector
    static bool list_directory(const std::string& directory_path, std::vector<std::string>& file_name);

    // Constructor to initialize constants for RGB to grayscale conversion
    image_loader();

    // Destructor to clean up resources
    ~image_loader();

private:
    // Check if a file exists by attempting to open it
    static bool file_exist(const std::string& file_name);

    // Constants used for converting RGB values to grayscale
    const double R_FACTOR, G_FACTOR, B_FACTOR;
};

#endif  // IMAGE_LOADER_H
