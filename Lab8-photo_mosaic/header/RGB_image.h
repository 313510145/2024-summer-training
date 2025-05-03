#ifndef RGB_IMAGE_H
#define RGB_IMAGE_H

#include "image.h"

class RGB_image: public image {
    public:
        virtual bool load_image(const std::string& file_name) override;
        virtual void dump_image(const std::string& file_name) const override;
        virtual void box(const int& r) override;
        virtual void sobel() override;
        virtual void normalization() override;
        virtual void mosaic(const int& r) override;
        virtual void resize(const int& nw, const int& nh) override;
        virtual void photo_mosaic(const std::string& i, const int& r) override;
        virtual void display_X_server() const override;
        virtual void display_ASCII() const override;
        virtual void display_command_line() const override;
        virtual double* get_average() const override;
        virtual void assign_to(int*** const pixel, const int& px, const int& py, const int& w, const int& h) const override;
        RGB_image();
        RGB_image(const int& w, const int& h, const int*** const p);
        RGB_image(const RGB_image& RGBi);
        virtual ~RGB_image() override;
        RGB_image& operator =(const RGB_image& RGBi);
    private:
        int*** pixel;
};

#endif  // RGB_IMAGE_H
