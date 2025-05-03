#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#define cimg_use_jpeg
#define cimg_use_png

#include "CImg.h"
#include <string>
#include <vector>

class image_loader {
public:
    int** load_gray(const std::string& file_name, int* const w, int* const h) const;
    static int*** load_RGB(const std::string& file_name, int* const w, int* const h);
    static void dump_gray(const int& w, const int& h, int** const pixel, const std::string& file_name);
    static void dump_RGB(const int& w, const int& h, int*** const pixel, const std::string& file_name);
    static void display_gray_X_server(const int& w, const int& h, int** const pixel);
    static void display_RGB_X_server(const int& w, const int& h, int*** const pixel);
    static void display_gray_ASCII(const int& w, const int& h, int** const pixel);
    static void display_RGB_ASCII(const int& w, const int& h, int*** const pixel);
    static void display_command_line(const std::string& file_name);
    static bool list_directory(const std::string& directory_path, std::vector<std::string>& file_name);
    image_loader();
    ~image_loader();
private:
    static bool file_exist(const std::string& file_name);
    const double R_FACTOR, G_FACTOR, B_FACTOR;
};

#endif  // IMAGE_LOADER_H
