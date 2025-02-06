#include "gray_image.h"
#include <cassert>

// Load a grayscale image from a file
bool gray_image::load_image(const std::string& file_name) {
    this->pixel = this->il.load_gray(file_name, &this->width, &this->height);
    if (this->pixel == nullptr) {
        return false;  // Failed to load image
    }
    return true;  // Successfully loaded image
}

// Save the grayscale image to a file
void gray_image::dump_image(const std::string& file_name) const {
    this->il.dump_gray(this->width, this->height, this->pixel, file_name);
}

// Apply a box filter to the grayscale image
void gray_image::box(const int& r) {
    this->f.box_gray(this->width, this->height, this->pixel, r);
}

// Apply Sobel edge detection to the grayscale image
void gray_image::sobel() {
    this->f.sobel_gray(this->width, this->height, this->pixel);
}

// Normalize the grayscale image
void gray_image::normalization() {
    this->f.normalization_gray(this->width, this->height, this->pixel);
}

// Apply mosaic effect to the grayscale image
void gray_image::mosaic(const int& r) {
    this->f.mosaic_gray(this->width, this->height, this->pixel, r);
}

// Resize the grayscale image
void gray_image::resize(const int& nw, const int& nh) {
    this->f.resize_gray(this->width, this->height, &this->pixel, nw, nh);
}

// Apply photo mosaic effect to the grayscale image
void gray_image::photo_mosaic(const std::string& i, const int& r) {
    std::vector<std::string> file_name;
    assert(this->il.list_directory(i, file_name));  // List files for photo mosaic
    this->f.photo_mosaic_gray(this->width, this->height, this->pixel, r, file_name);
    file_name.clear();  // Clear the list of file names
}

// Display the grayscale image using X server
void gray_image::display_X_server() const {
    this->il.display_gray_X_server(this->width, this->height, this->pixel);
}

// Display the grayscale image as ASCII art
void gray_image::display_ASCII() const {
    this->il.display_gray_ASCII(this->width, this->height, this->pixel);
}

// Display the grayscale image using command-line tools
void gray_image::display_command_line() const {
    this->il.dump_gray(this->width, this->height, this->pixel, "gray_image.jpg");
    this->il.display_command_line("gray_image.jpg");
}

// Calculate and return the average pixel value of the grayscale image
double* gray_image::get_average() const {
    double* average = new double(0);  // Initialize average to 0
    for (auto y = 0; y < this->height; y++) {
        for (auto x = 0; x < this->width; x++) {
            *average += this->pixel[y][x];
        }
    }
    *average /= this->width * this->height;  // Compute average
    return average;
}

// Assign pixel data from another image to this image
void gray_image::assign_to(int*** const pixel, const int& px, const int& py, const int& w, const int& h) const {
    int w_here = (w > this->width) ? this->width : w;
    int h_here = (h > this->height) ? this->height : h;
    for (auto y = 0; y < h_here; y++) {
        for (auto x = 0; x < w_here; x++) {
            (*pixel)[py + y][px + x] = this->pixel[y][x];
        }
    }
}

// Default constructor
gray_image::gray_image(): pixel(nullptr) {}

// Constructor with width, height, and pixel data
gray_image::gray_image(const int& w, const int& h, const int** const p): image(w, h) {
    this->pixel = new int*[this->height];
    for (auto y = 0; y < this->height; y++) {
        this->pixel[y] = new int[this->width];
        for (auto x = 0; x < this->width; x++) {
            this->pixel[y][x] = p[y][x];
        }
    }
}

// Copy constructor
gray_image::gray_image(const gray_image& gi): image(gi.width, gi.height) {
    this->pixel = new int*[this->height];
    for (auto y = 0; y < this->height; y++) {
        this->pixel[y] = new int[this->width];
        for (auto x = 0; x < this->width; x++) {
            this->pixel[y][x] = gi.pixel[y][x];
        }
    }
}

// Destructor
gray_image::~gray_image() {
    for (auto y = 0; y < this->height; y++) {
        delete [] this->pixel[y];  // Delete each row
    }
    delete [] this->pixel;  // Delete the array of rows
}

// Assignment operator
gray_image& gray_image::operator =(const gray_image& gi) {
    if (this == &gi) {
        return *this;  // Handle self-assignment
    }
    // Clean up existing resources
    for (auto y = 0; y < this->height; y++) {
        delete [] this->pixel[y];
    }
    delete [] this->pixel;
    // Copy new data
    this->width = gi.width;
    this->height = gi.height;
    this->pixel = new int*[this->height];
    for (auto y = 0; y < this->height; y++) {
        this->pixel[y] = new int[this->width];
        for (auto x = 0; x < this->width; x++) {
            this->pixel[y][x] = gi.pixel[y][x];
        }
    }
    return *this;
}
