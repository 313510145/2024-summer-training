#include "RGB_image.h"
#include <cassert>

bool RGB_image::load_image(const std::string& file_name) {
    this->pixel = this->il.load_RGB(file_name, &this->width, &this->height);
    return this->pixel != nullptr;
}

void RGB_image::dump_image(const std::string& file_name) const {
    this->il.dump_RGB(this->width, this->height, this->pixel, file_name);
}

void RGB_image::box(const int& r) {
    this->f.box_RGB(this->width, this->height, this->pixel, r);
}

void RGB_image::sobel() {
    this->f.sobel_RGB(this->width, this->height, this->pixel);
}

void RGB_image::normalization() {
    this->f.normalization_RGB(this->width, this->height, this->pixel);
}

void RGB_image::mosaic(const int& r) {
    this->f.mosaic_RGB(this->width, this->height, this->pixel, r);
}

void RGB_image::resize(const int& nw, const int& nh) {
    this->f.resize_RGB(this->width, this->height, &this->pixel, nw, nh);
}

void RGB_image::photo_mosaic(const std::string& i, const int& r) {
    std::vector<std::string> file_name;
    assert(this->il.list_directory(i, file_name));
    this->f.photo_mosaic_RGB(this->width, this->height, this->pixel, r, file_name);
    file_name.clear();
}

void RGB_image::display_X_server() const {
    this->il.display_RGB_X_server(this->width, this->height, this->pixel);
}

void RGB_image::display_ASCII() const {
    this->il.display_RGB_ASCII(this->width, this->height, this->pixel);
}

void RGB_image::display_command_line() const {
    this->il.dump_RGB(this->width, this->height, this->pixel, "RGB_image.jpg");
    this->il.display_command_line("RGB_image.jpg");
}

double* RGB_image::get_average() const {
    double* average = new double[3] ();
    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            average[0] += this->pixel[y][x][0];
            average[1] += this->pixel[y][x][1];
            average[2] += this->pixel[y][x][2];
        }
    }
    average[0] /= (this->width * this->height);
    average[1] /= (this->width * this->height);
    average[2] /= (this->width * this->height);
    return average;
}

void RGB_image::assign_to(int*** const pixel, const int& px, const int& py, const int& w, const int& h) const {
    int w_here = std::min(w, this->width);
    int h_here = std::min(h, this->height);
    for (int y = 0; y < h_here; ++y) {
        for (int x = 0; x < w_here; ++x) {
            pixel[py + y][px + x][0] = this->pixel[y][x][0];
            pixel[py + y][px + x][1] = this->pixel[y][x][1];
            pixel[py + y][px + x][2] = this->pixel[y][x][2];
        }
    }
}

RGB_image::RGB_image(): pixel(nullptr) {}

RGB_image::RGB_image(const int& w, const int& h, const int*** const p): image(w, h) {
    this->pixel = new int**[this->height];
    for (int y = 0; y < this->height; ++y) {
        this->pixel[y] = new int*[this->width];
        for (int x = 0; x < this->width; ++x) {
            this->pixel[y][x] = new int[3];
            this->pixel[y][x][0] = p[y][x][0];
            this->pixel[y][x][1] = p[y][x][1];
            this->pixel[y][x][2] = p[y][x][2];
        }
    }
}

RGB_image::RGB_image(const RGB_image& RGBi): image(RGBi.width, RGBi.height) {
    this->pixel = new int**[this->height];
    for (int y = 0; y < this->height; ++y) {
        this->pixel[y] = new int*[this->width];
        for (int x = 0; x < this->width; ++x) {
            this->pixel[y][x] = new int[3];
            this->pixel[y][x][0] = RGBi.pixel[y][x][0];
            this->pixel[y][x][1] = RGBi.pixel[y][x][1];
            this->pixel[y][x][2] = RGBi.pixel[y][x][2];
        }
    }
}

RGB_image::~RGB_image() {
    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            delete [] this->pixel[y][x];
        }
        delete [] this->pixel[y];
    }
    delete [] this->pixel;
}

RGB_image& RGB_image::operator =(const RGB_image& RGBi) {
    if (this == &RGBi) {
        return *this;
    }
    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            delete [] this->pixel[y][x];
        }
        delete [] this->pixel[y];
    }
    delete [] this->pixel;
    this->width = RGBi.width;
    this->height = RGBi.height;
    this->pixel = new int**[this->height];
    for (int y = 0; y < this->height; ++y) {
        this->pixel[y] = new int*[this->width];
        for (int x = 0; x < this->width; ++x) {
            this->pixel[y][x] = new int[3];
            this->pixel[y][x][0] = RGBi.pixel[y][x][0];
            this->pixel[y][x][1] = RGBi.pixel[y][x][1];
            this->pixel[y][x][2] = RGBi.pixel[y][x][2];
        }
    }
    return *this;
}
