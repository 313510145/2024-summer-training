#ifndef IMAGE_H
#define IMAGE_H

#include "image_loader.h"
#include "filter.h"

class image {
    public:
        virtual bool load_image(const std::string& file_name) = 0;
        virtual void dump_image(const std::string& file_name) const = 0;
        virtual void box(const int& r) = 0;
        virtual void sobel() = 0;
        virtual void normalization() = 0;
        virtual void mosaic(const int& r) = 0;
        virtual void resize(const int& nw, const int& nh) = 0;
        virtual void photo_mosaic(const std::string& i, const int& r) = 0;
        virtual void display_X_server() const = 0;
        virtual void display_ASCII() const = 0;
        virtual void display_command_line() const = 0;
        virtual double* get_average() const = 0;
        virtual void assign_to(int*** const pixel, const int& px, const int& py, const int& w, const int& h) const = 0;
        image();
        image(const int& w, const int& h);
        virtual ~image();
    protected:
        int width, height;
        static image_loader il;
        static filter f;
};

#endif  // IMAGE_H
