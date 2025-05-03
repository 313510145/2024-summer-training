#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <string>

class filter {
    public:
        static void box_gray(const int& w, const int& h, int** const pixel, const int& r);
        static void box_RGB(const int& w, const int& h, int*** const pixel, const int& r);
        static void sobel_gray(const int& w, const int& h, int** const pixel);
        static void sobel_RGB(const int& w, const int& h, int*** const pixel);
        static void normalization_gray(const int& w, const int& h, int** const pixel);
        static void normalization_RGB(const int& w, const int& h, int*** const pixel);
        static void mosaic_gray(const int& w, const int& h, int** const pixel, const int& r);
        static void mosaic_RGB(const int& w, const int& h, int*** const pixel, const int& r);
        static void resize_gray(int& w, int& h, int*** const pixel, const int& nw, const int& nh);
        static void resize_RGB(int& w, int& h, int**** const pixel, const int& nw, const int& nh);
        static void photo_mosaic_gray(const int& w, const int& h, int** pixel, const int& r, const std::vector<std::string>& file_name);
        static void photo_mosaic_RGB(const int& w, const int& h, int*** pixel, const int& r, const std::vector<std::string>& file_name);
        filter();
        ~filter();
    private:
};

#endif  // FILTER_H
