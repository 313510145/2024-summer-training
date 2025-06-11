#include "image_loader.h"
#include <fstream>
#include <cassert>
#include <iostream>

int** image_loader::load_gray(const std::string& file_name, int* const w, int* const h) const {
    assert(file_exist(file_name));
    cimg_library::CImg<unsigned char> image(file_name.c_str());
    *w = image.width();
    *h = image.height();
    int _c = image.spectrum();
    int** pixel = new int*[*h];
    for (auto y = 0; y < *h; y++) {
        pixel[y] = new int[*w];
    }
    if (_c == 1) {
        cimg_forXY(image, x, y) {
            pixel[y][x] = (int)image(x, y);
        }
        return pixel;
    }
    else if (_c == 3) {
        cimg_library::CImg<unsigned char> gray_scale_image(*w, *h, 1);
        cimg_forXY(gray_scale_image, x, y) {
            gray_scale_image(x, y) = (unsigned char)(R_FACTOR * image(x, y, 0, 0) +
                                                     G_FACTOR * image(x, y, 0, 1) +
                                                     B_FACTOR * image(x, y, 0, 2));
        }
        cimg_forXY(image, x, y) {
            pixel[y][x] = (int)gray_scale_image(x, y);
        }
        return pixel;
    }
    else if (_c == 4) {
        int*** pixel_3D = new int**[*h];
        for (auto y = 0; y < *h; y++) {
            pixel_3D[y] = new int*[*w];
            for (auto x = 0; x < *w; x++) {
                pixel_3D[y][x] = new int[3];
            }
        }
        cimg_forXYC(image, x, y, c) {
            if (c < 3) {
                pixel_3D[y][x][c] = image(x, y, c);
            }
        }
        for (auto y = 0; y < *h; y++) {
            for (auto x = 0; x < *w; x++) {
                pixel[y][x] = R_FACTOR * pixel_3D[y][x][0] +
                              G_FACTOR * pixel_3D[y][x][1] +
                              B_FACTOR * pixel_3D[y][x][2];
            }
        }
        for (auto y = 0; y < *h; y++) {
            for (auto x = 0; x < *w; x++) {
                delete [] pixel_3D[y][x];
            }
            delete [] pixel_3D[y];
        }
        delete [] pixel_3D;
        return pixel;
    }
    return nullptr;
}

int*** image_loader::load_RGB(const std::string& file_name, int* const w, int* const h) {
    assert(file_exist(file_name));
    cimg_library::CImg<unsigned char> image(file_name.c_str());
    *w = image.width();
    *h = image.height();
    int _c = image.spectrum();
    if (_c < 3) {
        return nullptr;
    }
    int*** pixel = new int**[*h];
    for (auto y = 0; y < *h; y++) {
        pixel[y] = new int*[*w];
        for (auto x = 0; x < *w; x++) {
            pixel[y][x] = new int[3];
        }
    }
    cimg_forXYC(image, x, y, c) {
        if (c < 3) {
            pixel[y][x][c] = image(x, y, c);
        }
    }
    return pixel;
}

void image_loader::dump_gray(const int& w, const int& h, int** const pixel, const std::string& file_name) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));
    cimg_library::CImg<unsigned char> image(w, h, 1, 1);
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            image(x, y) = (unsigned char)pixel[y][x];
        }
    }
    image.save(file_name.c_str());
}

void image_loader::dump_RGB(const int& w, const int& h, int*** const pixel, const std::string& file_name) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));
    cimg_library::CImg<unsigned char> image(w, h, 1, 3);
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            image(x, y, 0) = pixel[y][x][0];
            image(x, y, 1) = pixel[y][x][1];
            image(x, y, 2) = pixel[y][x][2];
        }
    }
    image.save(file_name.c_str());
}

void image_loader::display_gray_X_server(const int& w, const int& h, int** const pixel) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));
    cimg_library::CImg<unsigned char> image(w, h, 1);
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            image(x, y) = (unsigned char)pixel[y][x];
        }
    }
    cimg_library::CImgDisplay display(image, "image");
    while (!display.is_closed()) {
        display.wait();
    }
}

void image_loader::display_RGB_X_server(const int& w, const int& h, int*** const pixel) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));
    cimg_library::CImg<unsigned char> image(w, h, 1, 3);
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            image(x, y, 0, 0) = (unsigned char)pixel[y][x][0];
            image(x, y, 0, 1) = (unsigned char)pixel[y][x][1];
            image(x, y, 0, 2) = (unsigned char)pixel[y][x][2];
        }
    }
    cimg_library::CImgDisplay display(image, "image");
    while (!display.is_closed()) {
        display.wait();
    }
}

void image_loader::display_gray_ASCII(const int& w, const int& h, int** const pixel) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));
    const char* shade = " .-+#@";
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            int intensity = pixel[y][x];
            int index = intensity * strlen(shade) / 255;
            std::cout << shade[index] << shade[index];
        }
        std::cout << std::endl;
    }
}

void image_loader::display_RGB_ASCII(const int& w, const int& h, int*** const pixel) {
    assert((pixel != nullptr) && (w > 0) && (h > 0));
    const char* shade = " .-+#@";
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            int intensity = (pixel[y][x][0] + pixel[y][x][1] + pixel[y][x][2]) / 3;
            int index = intensity * strlen(shade) / 255;
            std::cout << shade[index] << shade[index];
        }
        std::cout << std::endl;
    }
}

void image_loader::display_command_line(const std::string& file_name) {
    assert(file_exist(file_name));
    std::string command = "./library/catimg/bin/catimg " + file_name;
    system(command.c_str());
    command = "rm " + file_name;
    system(command.c_str());
}

bool image_loader::list_directory(const std::string& directory_path, std::vector<std::string>& file_name) {
    struct dirent* entry;
    DIR* dp = opendir(directory_path.c_str());
    if (dp == NULL) {
        perror("opendir: path does not exist or could not be read");
        return false;
    }
    while ((entry = readdir(dp))) {
        if ((std::string(entry->d_name) == ".") || (std::string(entry->d_name) == "..")) {
            continue;
        }
        file_name.push_back(directory_path + "/" + entry->d_name);
    }
    closedir(dp);
    return true;
}

image_loader::image_loader(): R_FACTOR(0.2126), G_FACTOR(0.7152), B_FACTOR(0.0722) {}

image_loader::~image_loader() {}

bool image_loader::file_exist(const std::string& file_name) {
    std::ifstream input_file(file_name);
    return input_file.good();
}
