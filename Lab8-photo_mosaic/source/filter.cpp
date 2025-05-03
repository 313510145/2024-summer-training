#include "filter.h"
#include "image.h"
#include "gray_image.h"
#include "RGB_image.h"
#include <cmath>
#include <climits>
#include <iostream>

void filter::box_gray(const int& w, const int& h, int** const pixel, const int& r) {
    double** result_pixel = new double*[h];
    for (auto y = 0; y < h; y++) {
        result_pixel[y] = new double[w];
    }
    for (auto y = 0; y < h; y++) {
        double sum = 0;
        int count = 0;
        int x_bound = (r < w) ? r : w;
        for (auto x = 0; x < x_bound; x++) {
            count++;
            sum += pixel[y][x];
        }
        for (auto x = 0; x < w; x++) {
            int left = x - r - 1;
            int right = x + r;
            if (left >= 0) {
                count--;
                sum -= pixel[y][left];
            }
            if (right < w) {
                count++;
                sum += pixel[y][right];
            }
            result_pixel[y][x] = sum / count;
        }
    }
    for (auto x = 0; x < w; x++) {
        double sum = 0;
        int count = 0;
        int y_bound = (r < h) ? r : h;
        for (auto y = 0; y < y_bound; y++) {
            count++;
            sum += result_pixel[y][x];
        }
        for (auto y = 0; y < h; y++) {
            int up = y - r - 1;
            int down = y + r;
            if (up >= 0) {
                count--;
                sum -= result_pixel[up][x];
            }
            if (down < h) {
                count++;
                sum += result_pixel[down][x];
            }
            pixel[y][x] = sum / count;
        }
    }
    for (auto y = 0; y < h; y++) {
        delete[] result_pixel[y];
    }
    delete[] result_pixel;
}

void filter::box_RGB(const int& w, const int& h, int*** const pixel, const int& r) {
    double*** result_pixel = new double**[h];
    for (auto y = 0; y < h; y++) {
        result_pixel[y] = new double*[w];
        for (auto x = 0; x < w; x++) {
            result_pixel[y][x] = new double[3];
        }
    }
    for (auto y = 0; y < h; y++) {
        double sum[3] = {0};
        int count = 0;
        int x_bound = (r < w) ? r : w;
        for (auto x = 0; x < x_bound; x++) {
            count++;
            sum[0] += pixel[y][x][0];
            sum[1] += pixel[y][x][1];
            sum[2] += pixel[y][x][2];
        }
        for (auto x = 0; x < w; x++) {
            int left = x - r - 1;
            int right = x + r;
            if (left >= 0) {
                count--;
                sum[0] -= pixel[y][left][0];
                sum[1] -= pixel[y][left][1];
                sum[2] -= pixel[y][left][2];
            }
            if (right < w) {
                count++;
                sum[0] += pixel[y][right][0];
                sum[1] += pixel[y][right][1];
                sum[2] += pixel[y][right][2];
            }
            result_pixel[y][x][0] = sum[0] / count;
            result_pixel[y][x][1] = sum[1] / count;
            result_pixel[y][x][2] = sum[2] / count;
        }
    }
    for (auto x = 0; x < w; x++) {
        double sum[3] = {0};
        int count = 0;
        int y_bound = (r < h) ? r : h;
        for (auto y = 0; y < y_bound; y++) {
            count++;
            sum[0] += result_pixel[y][x][0];
            sum[1] += result_pixel[y][x][1];
            sum[2] += result_pixel[y][x][2];
        }
        for (auto y = 0; y < h; y++) {
            int up = y - r - 1;
            int down = y + r;
            if (up >= 0) {
                count--;
                sum[0] -= result_pixel[up][x][0];
                sum[1] -= result_pixel[up][x][1];
                sum[2] -= result_pixel[up][x][2];
            }
            if (down < h) {
                count++;
                sum[0] += result_pixel[down][x][0];
                sum[1] += result_pixel[down][x][1];
                sum[2] += result_pixel[down][x][2];
            }
            pixel[y][x][0] = sum[0] / count;
            pixel[y][x][1] = sum[1] / count;
            pixel[y][x][2] = sum[2] / count;
        }
    }
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            delete[] result_pixel[y][x];
        }
        delete[] result_pixel[y];
    }
    delete[] result_pixel;
}

void filter::sobel_gray(const int& w, const int& h, int** const pixel) {
    int** result_pixel = new int*[h];
    for (auto y = 0; y < h; y++) {
        result_pixel[y] = new int[w];
        for (auto x = 0; x < w; x++) {
            int temp[8];
            temp[0] = ((y - 1 >= 0) && (x - 1 >= 0)) ? pixel[y - 1][x - 1] : 0;
            temp[1] = (y - 1 >= 0) ? pixel[y - 1][x] : 0;
            temp[2] = ((y - 1 >= 0) && (x + 1 < w)) ? pixel[y - 1][x + 1] : 0;
            temp[3] = (x - 1 >= 0) ? pixel[y][x - 1] : 0;
            temp[4] = (x + 1 < w) ? pixel[y][x + 1] : 0;
            temp[5] = ((y + 1 < h) && (x - 1 >= 0)) ? pixel[y + 1][x - 1] : 0;
            temp[6] = (y + 1 < h) ? pixel[y + 1][x] : 0;
            temp[7] = ((y + 1 < h) && (x + 1 < w)) ? pixel[y + 1][x + 1] : 0;
            int gx = abs(temp[0] - temp[2] + temp[3] * 2 - temp[4] * 2 + temp[5] - temp[7]);
            int gy = abs(temp[0] + temp[1] * 2 + temp[2] - temp[5] - temp[6] * 2 - temp[7]);
            result_pixel[y][x] = gx + gy;
        }
    }
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            pixel[y][x] = result_pixel[y][x];
        }
        delete[] result_pixel[y];
    }
    delete[] result_pixel;
    normalization_gray(w, h, pixel);
}

void filter::sobel_RGB(const int& w, const int& h, int*** const pixel) {
    int*** result_pixel = new int**[h];
    for (auto y = 0; y < h; y++) {
        result_pixel[y] = new int*[w];
        for (auto x = 0; x < w; x++) {
            result_pixel[y][x] = new int[3];
            for (auto c = 0; c < 3; c++) {
                int temp[8];
                temp[0] = ((y - 1 >= 0) && (x - 1 >= 0)) ? pixel[y - 1][x - 1][c] : 0;
                temp[1] = (y - 1 >= 0) ? pixel[y - 1][x][c] : 0;
                temp[2] = ((y - 1 >= 0) && (x + 1 < w)) ? pixel[y - 1][x + 1][c] : 0;
                temp[3] = (x - 1 >= 0) ? pixel[y][x - 1][c] : 0;
                temp[4] = (x + 1 < w) ? pixel[y][x + 1][c] : 0;
                temp[5] = ((y + 1 < h) && (x - 1 >= 0)) ? pixel[y + 1][x - 1][c] : 0;
                temp[6] = (y + 1 < h) ? pixel[y + 1][x][c] : 0;
                temp[7] = ((y + 1 < h) && (x + 1 < w)) ? pixel[y + 1][x + 1][c] : 0;
                int gx = abs(temp[0] - temp[2] + temp[3] * 2 - temp[4] * 2 + temp[5] - temp[7]);
                int gy = abs(temp[0] + temp[1] * 2 + temp[2] - temp[5] - temp[6] * 2 - temp[7]);
                result_pixel[y][x][c] = gx + gy;
            }
        }
    }
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            pixel[y][x][0] = result_pixel[y][x][0];
            pixel[y][x][1] = result_pixel[y][x][1];
            pixel[y][x][2] = result_pixel[y][x][2];
            delete[] result_pixel[y][x];
        }
        delete[] result_pixel[y];
    }
    delete[] result_pixel;
    normalization_RGB(w, h, pixel);
}

void filter::normalization_gray(const int& w, const int& h, int** const pixel) {
    int max = 0, min = INT_MAX;
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            max = (pixel[y][x] > max) ? pixel[y][x] : max;
            min = (pixel[y][x] < min) ? pixel[y][x] : min;
        }
    }
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            pixel[y][x] = (pixel[y][x] - min) / static_cast<double>(max - min) * 255;
        }
    }
}

void filter::normalization_RGB(const int& w, const int& h, int*** const pixel) {
    int max[3] = {0}, min[3] = {INT_MAX, INT_MAX, INT_MAX};
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            for (auto c = 0; c < 3; c++) {
                max[c] = (pixel[y][x][c] > max[c]) ? pixel[y][x][c] : max[c];
                min[c] = (pixel[y][x][c] < min[c]) ? pixel[y][x][c] : min[c];
            }
        }
    }
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            pixel[y][x][0] = (pixel[y][x][0] - min[0]) / static_cast<double>(max[0] - min[0]) * 255;
            pixel[y][x][1] = (pixel[y][x][1] - min[1]) / static_cast<double>(max[1] - min[1]) * 255;
            pixel[y][x][2] = (pixel[y][x][2] - min[2]) / static_cast<double>(max[2] - min[2]) * 255;
        }
    }
}

void filter::mosaic_gray(const int& w, const int& h, int** const pixel, const int& r) {
    int sum, count;
    for (auto y = 0; y < h; y += r) {
        for (auto x = 0; x < w; x += r) {
            sum = 0;
            count = 0;
            for (auto i = 0; i < r; i++) {
                for (auto j = 0; j < r; j++) {
                    if ((y + i < h) && (x + j < w)) {
                        sum += pixel[y + i][x + j];
                        count++;
                    }
                }
            }
            sum = sum / count;
            for (auto i = 0; i < r; i++) {
                for (auto j = 0; j < r; j++) {
                    if ((y + i < h) && (x + j < w)) {
                        pixel[y + i][x + j] = sum;
                    }
                }
            }
        }
    }
}

void filter::mosaic_RGB(const int& w, const int& h, int*** const pixel, const int& r) {
    int sum[3], count;
    for (auto y = 0; y < h; y += r) {
        for (auto x = 0; x < w; x += r) {
            for (auto c = 0; c < 3; c++) {
                sum[c] = 0;
                count = 0;
                for (auto i = 0; i < r; i++) {
                    for (auto j = 0; j < r; j++) {
                        if ((y + i < h) && (x + j < w)) {
                            sum[c] += pixel[y + i][x + j][c];
                            count++;
                        }
                    }
                }
                sum[c] /= count;
                for (auto i = 0; i < r; i++) {
                    for (auto j = 0; j < r; j++) {
                        if ((y + i < h) && (x + j < w)) {
                            pixel[y + i][x + j][c] = sum[c];
                        }
                    }
                }
            }
        }
    }
}

void filter::resize_gray(int& w, int& h, int*** const pixel, const int& nw, const int& nh) {
    double w_scale = static_cast<double>(w) / nw;
    double h_scale = static_cast<double>(h) / nh;
    int** resized_pixel = new int*[nh];
    for (auto y = 0; y < nh; y++) {
        resized_pixel[y] = new int[nw];
        for (auto x = 0; x < nw; x++) {
            int source_x = (x * w_scale);
            int source_y = (y * h_scale);
            if (source_x >= w) {
                source_x = w - 1;
            }
            if (source_y >= h) {
                source_y = h - 1;
            }
            resized_pixel[y][x] = (*pixel)[source_y][source_x];
        }
    }
    for (auto y = 0; y < h; y++) {
        delete [] (*pixel)[y];
    }
    delete [] (*pixel);
    w = nw;
    h = nh;
    *pixel = resized_pixel;
}

void filter::resize_RGB(int& w, int& h, int**** const pixel, const int& nw, const int& nh) {
    double w_scale = static_cast<double>(w) / nw;
    double h_scale = static_cast<double>(h) / nh;
    int*** resized_pixel = new int**[nh];
    for (auto y = 0; y < nh; y++) {
        resized_pixel[y] = new int*[nw];
        for (auto x = 0; x < nw; x++) {
            resized_pixel[y][x] = new int[3];
            for (auto c = 0; c < 3; c++) {
                int source_x = (x * w_scale);
                int source_y = (y * h_scale);
                if (source_x >= w) {
                    source_x = w - 1;
                }
                if (source_y >= h) {
                    source_y = h - 1;
                }
                resized_pixel[y][x][c] = (*pixel)[source_y][source_x][c];
            }
        }
    }
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            delete [] (*pixel)[y][x];
        }
        delete [] (*pixel)[y];
    }
    delete [] (*pixel);
    w = nw;
    h = nh;
    *pixel = resized_pixel;
}

void filter::photo_mosaic_gray(const int& w, const int& h, int** pixel, const int& r, const std::vector<std::string>& file_name) {
    std::vector<std::pair<image*, const double*>> gray_image_map;
    for (const auto& fn: file_name) {
        image* temp_image = new gray_image();
        temp_image->load_image(fn);
        temp_image->resize(r, r);
        const double* average = temp_image->get_average();
        gray_image_map.push_back(std::make_pair(temp_image, average));
    }
    for (auto y = 0; y < h; y += r) {
        for (auto x = 0; x < w; x += r) {
            double average = 0;
            unsigned int count = 0;
            for (auto i = 0; i < r; i++) {
                for (auto j = 0; j < r; j++) {
                    if ((y + i < h) && (x + j < w)) {
                        average += pixel[y + i][x + j];
                        count++;
                    }
                }
            }
            average /= count;
            double min_difference = DBL_MAX;
            const image* temp_image = nullptr;
            for (const auto& gim: gray_image_map) {
                double diff = abs(*(gim.second) - average);
                if (diff < min_difference) {
                    min_difference = diff;
                    temp_image = gim.first;
                }
            }
            int h_range = (y + r > h) ? (h - y) : r;
            int w_range = (x + r > w) ? (w - x) : r;
            temp_image->assign_to(&pixel, x, y, w_range, h_range);
        }
    }
    for (const auto& gim: gray_image_map) {
        delete gim.first;
        delete gim.second;
    }
    gray_image_map.clear();
}

void filter::photo_mosaic_RGB(const int& w, const int& h, int*** pixel, const int& r, const std::vector<std::string>& file_name) {
    std::vector<std::pair<image*, const double*>> RGB_image_map;
    for (const auto& fn: file_name) {
        image* temp_image = new RGB_image();
        temp_image->load_image(fn);
        temp_image->resize(r, r);
        const double* average = temp_image->get_average();
        RGB_image_map.push_back(std::make_pair(temp_image, average));
    }
    for (auto y = 0; y < h; y += r) {
        for (auto x = 0; x < w; x += r) {
            double average[3] = {0};
            unsigned int count = 0;
            for (auto i = 0; i < r; i++) {
                for (auto j = 0; j < r; j++) {
                    if ((y + i < h) && (x + j < w)) {
                        average[0] += pixel[y + i][x + j][0];
                        average[1] += pixel[y + i][x + j][1];
                        average[2] += pixel[y + i][x + j][2];
                        count++;
                    }
                }
            }
            average[0] /= count;
            average[1] /= count;
            average[2] /= count;
            double min_difference = DBL_MAX;
            const image* temp_image = nullptr;
            for (const auto& RGBim: RGB_image_map) {
                double diff = abs(RGBim.second[0] - average[0]) +
                              abs(RGBim.second[1] - average[1]) +
                              abs(RGBim.second[2] - average[2]);
                if (diff < min_difference) {
                    min_difference = diff;
                    temp_image = RGBim.first;
                }
            }
            int h_range = (y + r > h) ? (h - y) : r;
            int w_range = (x + r > w) ? (w - x) : r;
            temp_image->assign_to(pixel, x, y, w_range, h_range);
        }
    }
    for (const auto& RGBim: RGB_image_map) {
        delete RGBim.first;
        delete [] RGBim.second;
    }
    RGB_image_map.clear();
}

filter::filter() {}

filter::~filter() {}
