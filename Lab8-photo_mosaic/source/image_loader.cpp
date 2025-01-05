#include "image_loader.h"
#include <fstream>
#include <cassert>
#include <iostream>

// Load a grayscale image from the file and return a 2D array of pixel values
int** image_loader::load_gray(const std::string& file_name, int* const w, int* const h) const {
    assert(file_exist(file_name));  // Ensure the file exists
    cimg_library::CImg<unsigned char> image(file_name.c_str());  // Load the image using CImg
    *w = image.width();  // Store image width
    *h = image.height(); // Store image height
    int _c = image.spectrum();  // Get the number of color channels
    int** pixel = new int*[*h];  // Allocate memory for the 2D pixel array
    for (auto y = 0; y < *h; y++) {
        pixel[y] = new int[*w];
    }
    
    // If the image is already in grayscale, copy pixel values directly
    if (_c == 1) {
        cimg_forXY(image, x, y) {
            pixel[y][x] = (int)image(x, y);
        }
        return pixel;
    }
    // If the image is RGB, convert it to grayscale using the RGB conversion factors
    else if (_c == 3) {
        cimg_library::CImg<unsigned char> gray_scale_image(*w, *h, 1);  // Create a grayscale image buffer
        cimg_forXY(gray_scale_image, x, y) {
            gray_scale_image(x, y) = (unsigned char)(R_FACTOR * image(x, y, 0, 0) +
                                                     G_FACTOR * image(x, y, 0, 1) +
                                                     B_FACTOR * image(x, y, 0, 2));
        }
        cimg_forXY(image, x, y) {
            pixel[y][x] = (int)gray_scale_image(x, y);  // Store grayscale pixel values
        }
        return pixel;
    }
    // If the image contains transparency (4 channels), handle RGBA by ignoring the alpha channel
    else if (_c == 4) {
        int*** pixel_3D = new int**[*h];  // Allocate a 3D array for the RGBA pixel values
        for (auto y = 0; y < *h; y++) {
            pixel_3D[y] = new int*[*w];
            for (auto x = 0; x < *w; x++) {
                pixel_3D[y][x] = new int[3];  // Allocate memory for the RGB channels
            }
        }
        // Copy RGB channels, ignoring the alpha channel
        cimg_forXYC(image, x, y, c) {
            if (c < 3) {
                pixel_3D[y][x][c] = image(x, y, c);
            }
        }
        // Convert the RGB values to grayscale
        for (auto y = 0; y < *h; y++) {
            for (auto x = 0; x < *w; x++) {
                pixel[y][x] = R_FACTOR * pixel_3D[y][x][0] +
                              G_FACTOR * pixel_3D[y][x][1] +
                              B_FACTOR * pixel_3D[y][x][2];
            }
        }
        // Clean up the 3D array
        for (auto y = 0; y < *h; y++) {
            for (auto x = 0; x < *w; x++) {
                delete[] pixel_3D[y][x];
            }
            delete[] pixel_3D[y];
        }
        delete[] pixel_3D;
        return pixel;
    }
    return nullptr;
}

// Load an RGB image from the file and return a 3D array of pixel values
int*** image_loader::load_RGB(const std::string& file_name, int* const w, int* const h) {
    assert(file_exist(file_name));  // Ensure the file exists
    cimg_library::CImg<unsigned char> image(file_name.c_str());  // Load the image using CImg
    *w = image.width();  // Store image width
    *h = image.height(); // Store image height
    int _c = image.spectrum();  // Get the number of color channels
    if (_c < 3) {
        return nullptr;  // If there are fewer than 3 channels, return null
    }
    int*** pixel = new int**[*h];  // Allocate memory for the 3D pixel array
    for (auto y = 0; y < *h; y++) {
        pixel[y] = new int*[*w];
        for (auto x = 0; x < *w; x++) {
            pixel[y][x] = new int[3];  // Allocate memory for RGB channels
        }
    }
    // Copy the RGB values into the 3D array
    cimg_forXYC(image, x, y, c) {
        if (c < 3) {
            pixel[y][x][c] = image(x, y, c);
        }
    }
    return pixel;
}

// Save a grayscale image to a file from a 2D pixel array
void image_loader::dump_gray(const int& w, const int& h, int** const pixel, const std::string& file_name) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));  // Ensure the pixel array is valid
    cimg_library::CImg<unsigned char> image(w, h, 1, 1);  // Create a CImg object for the image
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            image(x, y) = (unsigned char)pixel[y][x];  // Copy pixel values
        }
    }
    image.save(file_name.c_str());  // Save the image to a file
}

// Save an RGB image to a file from a 3D pixel array
void image_loader::dump_RGB(const int& w, const int& h, int*** const pixel, const std::string& file_name) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));  // Ensure the pixel array is valid
    cimg_library::CImg<unsigned char> image(w, h, 1, 3);  // Create a CImg object for the image
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            image(x, y, 0) = pixel[y][x][0];  // Red channel
            image(x, y, 1) = pixel[y][x][1];  // Green channel
            image(x, y, 2) = pixel[y][x][2];  // Blue channel
        }
    }
    image.save(file_name.c_str());  // Save the image to a file
}

// Display a grayscale image in an X server window
void image_loader::display_gray_X_server(const int& w, const int& h, int** const pixel) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));  // Ensure the pixel array is valid
    cimg_library::CImg<unsigned char> image(w, h, 1);  // Create a CImg object for the image
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            image(x, y) = (unsigned char)pixel[y][x];  // Copy pixel values
        }
    }
    cimg_library::CImgDisplay display(image, "image");  // Create a window to display the image
    while (!display.is_closed()) {
        display.wait();  // Keep the window open until the user closes it
    }
}

// Display an RGB image in an X server window
void image_loader::display_RGB_X_server(const int& w, const int& h, int*** const pixel) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));  // Ensure the pixel array is valid
    cimg_library::CImg<unsigned char> image(w, h, 1, 3);  // Create a CImg object for the image
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            image(x, y, 0, 0) = (unsigned char)pixel[y][x][0];  // Red channel
            image(x, y, 0, 1) = (unsigned char)pixel[y][x][1];  // Green channel
            image(x, y, 0, 2) = (unsigned char)pixel[y][x][2];  // Blue channel
        }
    }
    cimg_library::CImgDisplay display(image, "image");  // Create a window to display the image
    while (!display.is_closed()) {
        display.wait();  // Keep the window open until the user closes it
    }
}

// Display a grayscale image as ASCII art in the terminal
void image_loader::display_gray_ASCII(const int& w, const int& h, int** const pixel) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));  // Ensure the pixel array is valid
    const char* shade = " .-+#@";  // Character shades to represent pixel intensity
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            int intensity = pixel[y][x];
            int index = intensity * strlen(shade) / 255;  // Map intensity to shade characters
            std::cout << shade[index] << shade[index];  // Print each pixel as two characters
        }
        std::cout << std::endl;
    }
}

// Display an RGB image as ASCII art in the terminal
void image_loader::display_RGB_ASCII(const int& w, const int& h, int*** const pixel) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));  // Ensure the pixel array is valid
    const char* shade = " .-+#@";  // Character shades to represent pixel intensity
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            int intensity = (pixel[y][x][0] + pixel[y][x][1] + pixel[y][x][2]) / 3;  // Compute average intensity
            int index = intensity * strlen(shade) / 255;  // Map intensity to shade characters
            std::cout << shade[index] << shade[index];  // Print each pixel as two characters
        }
        std::cout << std::endl;
    }
}

// Use an external tool to display an image in the terminal using command line
void image_loader::display_command_line(const std::string& file_name) {
    assert(file_exist(file_name));  // Ensure the file exists
    std::string command = "./library/catimg/bin/catimg " + file_name;  // Command to display the image using catimg
    system(command.c_str());  // Execute the command
    command = "rm " + file_name;  // Command to delete the temporary image file
    system(command.c_str());  // Execute the delete command
}

// List the files in a directory and store the names in a vector
bool image_loader::list_directory(const std::string& directory_path, std::vector<std::string>& file_name) {
    struct dirent* entry;
    DIR* dp = opendir(directory_path.c_str());  // Open the directory
    if (dp == NULL) {
        perror("opendir: path does not exist or could not be read");  // Handle directory open error
        return false;
    }
    while ((entry = readdir(dp))) {
        if ((std::string(entry->d_name) == ".") || (std::string(entry->d_name) == "..")) {
            continue;  // Skip the current and parent directory entries
        }
        file_name.push_back(directory_path + "/" + entry->d_name);  // Add file names to the vector
    }
    closedir(dp);  // Close the directory
    return true;
}

// Constructor: Initializes RGB conversion factors for grayscale
image_loader::image_loader(): R_FACTOR(0.2126), G_FACTOR(0.7152), B_FACTOR(0.0722) {}

// Destructor: Empty
image_loader::~image_loader() {}

// Check if a file exists
bool image_loader::file_exist(const std::string& file_name) {
    std::ifstream input_file(file_name);  // Try to open the file
    return input_file.good();  // Return true if the file exists
}
