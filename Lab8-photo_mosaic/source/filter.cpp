#include "filter.h"
#include "image.h"
#include "gray_image.h"
#include "RGB_image.h"
#include <cmath>
#include <climits>
#include <iostream>

// Applies a box filter to a grayscale image, smoothing the image by averaging pixel values within a defined radius.
// Parameters:
// - w: Width of the image.
// - h: Height of the image.
// - pixel: 2D array representing the grayscale pixel values of the image.
// - r: Radius of the box filter kernel.
const void filter::box_gray(const int& w, const int& h, int** const pixel, const int& r) {
    // Dynamically allocate a 2D array to store the intermediate results after the horizontal pass of the filter.
    double** result_pixel = new double*[h];
    for (auto y = 0; y < h; y++) {
        result_pixel[y] = new double[w];
    }

    // Perform the horizontal box filtering for each row.
    for (auto y = 0; y < h; y++) {
        double sum = 0;   // Initialize sum for the filter kernel.
        int count = 0;    // Initialize count of pixels within the kernel.

        // Calculate the initial sum of pixels in the kernel range for the first window in the row.
        int x_bound = (r < w) ? r : w;  // Determine the bound of the initial kernel based on the radius and image width.
        for (auto x = 0; x < x_bound; x++) {
            count++;
            sum += pixel[y][x];  // Accumulate pixel values in the sum.
        }

        // Slide the box filter window across the row.
        for (auto x = 0; x < w; x++) {
            int left = x - r - 1;  // Index of the pixel leaving the kernel on the left side.
            int right = x + r;     // Index of the pixel entering the kernel on the right side.

            // If the left index is within bounds, subtract the pixel's value from the sum.
            if (left >= 0) {
                count--;
                sum -= pixel[y][left];
            }

            // If the right index is within bounds, add the pixel's value to the sum.
            if (right < w) {
                count++;
                sum += pixel[y][right];
            }

            // Calculate the average value of the pixels within the kernel and store it in the result array.
            result_pixel[y][x] = sum / count;
        }
    }

    // Perform the vertical box filtering on the results from the horizontal pass.
    for (auto x = 0; x < w; x++) {
        double sum = 0;   // Initialize sum for the filter kernel.
        int count = 0;    // Initialize count of pixels within the kernel.

        // Calculate the initial sum of pixels in the kernel range for the first window in the column.
        int y_bound = (r < h) ? r : h;  // Determine the bound of the initial kernel based on the radius and image height.
        for (auto y = 0; y < y_bound; y++) {
            count++;
            sum += result_pixel[y][x];  // Accumulate pixel values in the sum.
        }

        // Slide the box filter window vertically down the column.
        for (auto y = 0; y < h; y++) {
            int up = y - r - 1;    // Index of the pixel leaving the kernel at the top.
            int down = y + r;      // Index of the pixel entering the kernel at the bottom.

            // If the top index is within bounds, subtract the pixel's value from the sum.
            if (up >= 0) {
                count--;
                sum -= result_pixel[up][x];
            }

            // If the bottom index is within bounds, add the pixel's value to the sum.
            if (down < h) {
                count++;
                sum += result_pixel[down][x];
            }

            // Calculate the average value of the pixels within the kernel and assign it back to the original pixel array.
            pixel[y][x] = sum / count;
        }
    }

    // Deallocate the memory used for the intermediate result array to avoid memory leaks.
    for (auto y = 0; y < h; y++) {
        delete[] result_pixel[y];
    }
    delete[] result_pixel;
}

// Applies a box filter to an RGB image by processing each color channel (red, green, blue) independently.
// Parameters:
// - w: Width of the image.
// - h: Height of the image.
// - pixel: 3D array representing the RGB pixel values of the image, with each pixel containing three components (R, G, B).
// - r: Radius of the box filter kernel.
const void filter::box_RGB(const int& w, const int& h, int*** const pixel, const int& r) {
    // Dynamically allocate a 3D array to store the intermediate results after the horizontal pass of the filter.
    double*** result_pixel = new double**[h];
    for (auto y = 0; y < h; y++) {
        result_pixel[y] = new double*[w];
        for (auto x = 0; x < w; x++) {
            result_pixel[y][x] = new double[3];  // Each pixel has three components (R, G, B).
        }
    }

    // Perform the horizontal box filtering for each row and each color channel.
    for (auto y = 0; y < h; y++) {
        double sum[3] = {0};  // Initialize sum for the R, G, and B channels.
        int count = 0;        // Initialize count of pixels within the kernel.

        // Calculate the initial sum of pixels in the kernel range for the first window in the row.
        int x_bound = (r < w) ? r : w;  // Determine the bound of the initial kernel based on the radius and image width.
        for (auto x = 0; x < x_bound; x++) {
            count++;
            sum[0] += pixel[y][x][0];  // Accumulate the R channel.
            sum[1] += pixel[y][x][1];  // Accumulate the G channel.
            sum[2] += pixel[y][x][2];  // Accumulate the B channel.
        }

        // Slide the box filter window across the row for each color channel.
        for (auto x = 0; x < w; x++) {
            int left = x - r - 1;  // Index of the pixel leaving the kernel on the left side.
            int right = x + r;     // Index of the pixel entering the kernel on the right side.

            // If the left index is within bounds, subtract the pixel's value from the sum for each channel.
            if (left >= 0) {
                count--;
                sum[0] -= pixel[y][left][0];
                sum[1] -= pixel[y][left][1];
                sum[2] -= pixel[y][left][2];
            }

            // If the right index is within bounds, add the pixel's value to the sum for each channel.
            if (right < w) {
                count++;
                sum[0] += pixel[y][right][0];
                sum[1] += pixel[y][right][1];
                sum[2] += pixel[y][right][2];
            }

            // Calculate the average value for each channel within the kernel and store it in the result array.
            result_pixel[y][x][0] = sum[0] / count;
            result_pixel[y][x][1] = sum[1] / count;
            result_pixel[y][x][2] = sum[2] / count;
        }
    }

    // Perform the vertical box filtering on the results from the horizontal pass for each color channel.
    for (auto x = 0; x < w; x++) {
        double sum[3] = {0};  // Initialize sum for the R, G, and B channels.
        int count = 0;        // Initialize count of pixels within the kernel.

        // Calculate the initial sum of pixels in the kernel range for the first window in the column.
        int y_bound = (r < h) ? r : h;  // Determine the bound of the initial kernel based on the radius and image height.
        for (auto y = 0; y < y_bound; y++) {
            count++;
            sum[0] += result_pixel[y][x][0];  // Accumulate the R channel.
            sum[1] += result_pixel[y][x][1];  // Accumulate the G channel.
            sum[2] += result_pixel[y][x][2];  // Accumulate the B channel.
        }

        // Slide the box filter window vertically down the column for each color channel.
        for (auto y = 0; y < h; y++) {
            int up = y - r - 1;    // Index of the pixel leaving the kernel at the top.
            int down = y + r;      // Index of the pixel entering the kernel at the bottom.

            // If the top index is within bounds, subtract the pixel's value from the sum for each channel.
            if (up >= 0) {
                count--;
                sum[0] -= result_pixel[up][x][0];
                sum[1] -= result_pixel[up][x][1];
                sum[2] -= result_pixel[up][x][2];
            }

            // If the bottom index is within bounds, add the pixel's value to the sum for each channel.
            if (down < h) {
                count++;
                sum[0] += result_pixel[down][x][0];
                sum[1] += result_pixel[down][x][1];
                sum[2] += result_pixel[down][x][2];
            }

            // Calculate the average value for each channel within the kernel and assign it back to the original pixel array.
            pixel[y][x][0] = sum[0] / count;
            pixel[y][x][1] = sum[1] / count;
            pixel[y][x][2] = sum[2] / count;
        }
    }

    // Deallocate the memory used for the intermediate result array to avoid memory leaks.
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            delete[] result_pixel[y][x];
        }
        delete[] result_pixel[y];
    }
    delete[] result_pixel;
}

// Applies the Sobel filter to a grayscale image, detecting edges by calculating the gradient magnitude.
// Parameters:
// - w: Width of the image.
// - h: Height of the image.
// - pixel: 2D array representing the grayscale pixel values of the image.
const void filter::sobel_gray(const int& w, const int& h, int** const pixel) {
    // Dynamically allocate a 2D array to store the results of the Sobel operation.
    int** result_pixel = new int*[h];
    for (auto y = 0; y < h; y++) {
        result_pixel[y] = new int[w];

        // Iterate over each pixel in the image.
        for (auto x = 0; x < w; x++) {
            int temp[8]; // Array to hold the values of the 8 neighboring pixels.

            // Gather the 8 neighboring pixel values with boundary checks.
            temp[0] = ((y - 1 >= 0) && (x - 1 >= 0)) ? pixel[y - 1][x - 1] : 0;
            temp[1] = (y - 1 >= 0) ? pixel[y - 1][x] : 0;
            temp[2] = ((y - 1 >= 0) && (x + 1 < w)) ? pixel[y - 1][x + 1] : 0;
            temp[3] = (x - 1 >= 0) ? pixel[y][x - 1] : 0;
            temp[4] = (x + 1 < w) ? pixel[y][x + 1] : 0;
            temp[5] = ((y + 1 < h) && (x - 1 >= 0)) ? pixel[y + 1][x - 1] : 0;
            temp[6] = (y + 1 < h) ? pixel[y + 1][x] : 0;
            temp[7] = ((y + 1 < h) && (x + 1 < w)) ? pixel[y + 1][x + 1] : 0;

            // Apply the Sobel filter in both the X and Y directions.
            int gx = abs(temp[0] - temp[2] + temp[3] * 2 - temp[4] * 2 + temp[5] - temp[7]);
            int gy = abs(temp[0] + temp[1] * 2 + temp[2] - temp[5] - temp[6] * 2 - temp[7]);

            // Combine the gradients to get the edge magnitude and store it in the result array.
            result_pixel[y][x] = gx + gy;
        }
    }

    // Copy the result back into the original pixel array.
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            pixel[y][x] = result_pixel[y][x];
        }
        delete[] result_pixel[y];  // Deallocate each row.
    }
    delete[] result_pixel;  // Deallocate the array.

    // Normalize the pixel values to fit within the 0-255 range.
    normalization_gray(w, h, pixel);
}

// Applies the Sobel filter to an RGB image, detecting edges by calculating the gradient magnitude independently for each color channel.
// Parameters:
// - w: Width of the image.
// - h: Height of the image.
// - pixel: 3D array representing the RGB pixel values of the image.
const void filter::sobel_RGB(const int& w, const int& h, int*** const pixel) {
    // Dynamically allocate a 3D array to store the results of the Sobel operation.
    int*** result_pixel = new int**[h];
    for (auto y = 0; y < h; y++) {
        result_pixel[y] = new int*[w];
        for (auto x = 0; x < w; x++) {
            result_pixel[y][x] = new int[3];

            // Process each color channel (R, G, B) independently.
            for (auto c = 0; c < 3; c++) {
                int temp[8]; // Array to hold the values of the 8 neighboring pixels for the current channel.

                // Gather the 8 neighboring pixel values with boundary checks for the current channel.
                temp[0] = ((y - 1 >= 0) && (x - 1 >= 0)) ? pixel[y - 1][x - 1][c] : 0;
                temp[1] = (y - 1 >= 0) ? pixel[y - 1][x][c] : 0;
                temp[2] = ((y - 1 >= 0) && (x + 1 < w)) ? pixel[y - 1][x + 1][c] : 0;
                temp[3] = (x - 1 >= 0) ? pixel[y][x - 1][c] : 0;
                temp[4] = (x + 1 < w) ? pixel[y][x + 1][c] : 0;
                temp[5] = ((y + 1 < h) && (x - 1 >= 0)) ? pixel[y + 1][x - 1][c] : 0;
                temp[6] = (y + 1 < h) ? pixel[y + 1][x][c] : 0;
                temp[7] = ((y + 1 < h) && (x + 1 < w)) ? pixel[y + 1][x + 1][c] : 0;

                // Apply the Sobel filter in both the X and Y directions for the current channel.
                int gx = abs(temp[0] - temp[2] + temp[3] * 2 - temp[4] * 2 + temp[5] - temp[7]);
                int gy = abs(temp[0] + temp[1] * 2 + temp[2] - temp[5] - temp[6] * 2 - temp[7]);

                // Combine the gradients to get the edge magnitude and store it in the result array for the current channel.
                result_pixel[y][x][c] = gx + gy;
            }
        }
    }

    // Copy the result back into the original pixel array.
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            pixel[y][x][0] = result_pixel[y][x][0];
            pixel[y][x][1] = result_pixel[y][x][1];
            pixel[y][x][2] = result_pixel[y][x][2];
            delete[] result_pixel[y][x];  // Deallocate the channel array.
        }
        delete[] result_pixel[y];  // Deallocate each row.
    }
    delete[] result_pixel;  // Deallocate the array.

    // Normalize the pixel values of each channel to fit within the 0-255 range.
    normalization_RGB(w, h, pixel);
}

// Normalizes the pixel values of a grayscale image to fit within the range [0, 255].
// Parameters:
// - w: Width of the image.
// - h: Height of the image.
// - pixel: 2D array representing the grayscale pixel values of the image.
const void filter::normalization_gray(const int& w, const int& h, int** const pixel) {
    int max = 0, min = INT_MAX;

    // Find the maximum and minimum pixel values.
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            max = (pixel[y][x] > max) ? pixel[y][x] : max;
            min = (pixel[y][x] < min) ? pixel[y][x] : min;
        }
    }

    // Normalize each pixel value based on the minimum and maximum values found.
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            pixel[y][x] = (pixel[y][x] - min) / static_cast<double>(max - min) * 255;
        }
    }
}

// Normalizes the pixel values of an RGB image to fit within the range [0, 255] for each color channel.
// Parameters:
// - w: Width of the image.
// - h: Height of the image.
// - pixel: 3D array representing the RGB pixel values of the image.
const void filter::normalization_RGB(const int& w, const int& h, int*** const pixel) {
    int max[3] = {0}, min[3] = {INT_MAX, INT_MAX, INT_MAX};

    // Find the maximum and minimum pixel values for each color channel.
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            for (auto c = 0; c < 3; c++) {
                max[c] = (pixel[y][x][c] > max[c]) ? pixel[y][x][c] : max[c];
                min[c] = (pixel[y][x][c] < min[c]) ? pixel[y][x][c] : min[c];
            }
        }
    }

    // Normalize each pixel value for each channel based on the minimum and maximum values found.
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            pixel[y][x][0] = (pixel[y][x][0] - min[0]) / static_cast<double>(max[0] - min[0]) * 255;
            pixel[y][x][1] = (pixel[y][x][1] - min[1]) / static_cast<double>(max[1] - min[1]) * 255;
            pixel[y][x][2] = (pixel[y][x][2] - min[2]) / static_cast<double>(max[2] - min[2]) * 255;
        }
    }
}

// Applies a mosaic filter to a grayscale image by averaging pixel values within non-overlapping square blocks of size r x r.
const void filter::mosaic_gray(const int& w, const int& h, int** const pixel, const int& r) {
    int sum, count;  // Variables to store the sum of pixel values and the count of pixels in the block.
    // Iterate over the image with steps of size r in both x and y directions.
    for (auto y = 0; y < h; y += r) {
        for (auto x = 0; x < w; x += r) {
            sum = 0;    // Reset sum for each block.
            count = 0;  // Reset count for each block.
            // Sum the pixel values within the current r x r block.
            for (auto i = 0; i < r; i++) {
                for (auto j = 0; j < r; j++) {
                    // Check that the pixel is within the image boundaries.
                    if ((y + i < h) && (x + j < w)) {
                        sum += pixel[y + i][x + j];
                        count++;
                    }
                }
            }
            // Calculate the average pixel value for the block.
            sum = sum / count;
            // Assign the average value to all pixels in the current block.
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

// Applies a mosaic filter to an RGB image by averaging pixel values within non-overlapping square blocks of size r x r for each color channel.
const void filter::mosaic_RGB(const int& w, const int& h, int*** const pixel, const int& r) {
    int sum[3], count;  // sum[3] stores the sum of pixel values for each color channel (R, G, B).
    // Iterate over the image with steps of size r in both x and y directions.
    for (auto y = 0; y < h; y += r) {
        for (auto x = 0; x < w; x += r) {
            // Iterate over each color channel (0 = R, 1 = G, 2 = B).
            for (auto c = 0; c < 3; c++) {
                sum[c] = 0;  // Reset sum for each color channel.
                count = 0;   // Reset count for each block.
                // Sum the pixel values within the current r x r block for the current color channel.
                for (auto i = 0; i < r; i++) {
                    for (auto j = 0; j < r; j++) {
                        if ((y + i < h) && (x + j < w)) {
                            sum[c] += pixel[y + i][x + j][c];
                            count++;
                        }
                    }
                }
                // Calculate the average pixel value for the block for the current color channel.
                sum[c] /= count;
                // Assign the average value to all pixels in the current block for the current color channel.
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

// Resizes a grayscale image to new dimensions (nw x nh) using nearest-neighbor interpolation.
const void filter::resize_gray(int& w, int& h, int*** const pixel, const int& nw, const int& nh) {
    double w_scale = static_cast<double>(w) / nw;  // Width scaling factor.
    double h_scale = static_cast<double>(h) / nh;  // Height scaling factor.
    int** resized_pixel = new int*[nh];  // Allocate memory for the resized image.
    
    // Iterate over the new image dimensions.
    for (auto y = 0; y < nh; y++) {
        resized_pixel[y] = new int[nw];  // Allocate memory for each row.
        for (auto x = 0; x < nw; x++) {
            // Calculate the corresponding pixel in the original image.
            int source_x = (x * w_scale);
            int source_y = (y * h_scale);
            // Ensure the source coordinates do not exceed the original image boundaries.
            if (source_x >= w) {
                source_x = w - 1;
            }
            if (source_y >= h) {
                source_y = h - 1;
            }
            // Assign the nearest pixel value from the original image to the resized image.
            resized_pixel[y][x] = (*pixel)[source_y][source_x];
        }
    }
    
    // Deallocate memory for the original image.
    for (auto y = 0; y < h; y++) {
        delete [] (*pixel)[y];
    }
    delete [] (*pixel);
    
    // Update the image dimensions and pixel data pointer to the resized image.
    w = nw;
    h = nh;
    *pixel = resized_pixel;
}

// Resizes an RGB image to new dimensions (nw x nh) using nearest-neighbor interpolation.
const void filter::resize_RGB(int& w, int& h, int**** const pixel, const int& nw, const int& nh) {
    double w_scale = static_cast<double>(w) / nw;  // Width scaling factor.
    double h_scale = static_cast<double>(h) / nh;  // Height scaling factor.
    int*** resized_pixel = new int**[nh];  // Allocate memory for the resized image.
    
    // Iterate over the new image dimensions.
    for (auto y = 0; y < nh; y++) {
        resized_pixel[y] = new int*[nw];  // Allocate memory for each row.
        for (auto x = 0; x < nw; x++) {
            resized_pixel[y][x] = new int[3];  // Allocate memory for each color channel.
            for (auto c = 0; c < 3; c++) {
                // Calculate the corresponding pixel in the original image.
                int source_x = (x * w_scale);
                int source_y = (y * h_scale);
                // Ensure the source coordinates do not exceed the original image boundaries.
                if (source_x >= w) {
                    source_x = w - 1;
                }
                if (source_y >= h) {
                    source_y = h - 1;
                }
                // Assign the nearest pixel value from the original image to the resized image.
                resized_pixel[y][x][c] = (*pixel)[source_y][source_x][c];
            }
        }
    }
    
    // Deallocate memory for the original image.
    for (auto y = 0; y < h; y++) {
        for (auto x = 0; x < w; x++) {
            delete [] (*pixel)[y][x];
        }
        delete [] (*pixel)[y];
    }
    delete [] (*pixel);
    
    // Update the image dimensions and pixel data pointer to the resized image.
    w = nw;
    h = nh;
    *pixel = resized_pixel;
}

// Creates a photo mosaic effect on a grayscale image by replacing each block with a smaller image from a provided list, based on average brightness.
const void filter::photo_mosaic_gray(const int& w, const int& h, int** pixel, const int& r, const std::vector<std::string>& file_name) {
    std::vector<std::pair<image*, const double*>> gray_image_map;  // Vector to store grayscale images and their average brightness values.
    
    // Load each image from the provided file names, resize it, and calculate its average brightness.
    for (const auto& fn: file_name) {
        image* temp_image = new gray_image();  // Create a new grayscale image object.
        temp_image->load_image(fn);  // Load the image from file.
        temp_image->resize(r, r);  // Resize the image to r x r.
        const double* average = temp_image->get_average();  // Get the average brightness of the image.
        gray_image_map.push_back(std::make_pair(temp_image, average));  // Store the image and its average brightness.
    }
    
    // Iterate over the original image in blocks of size r x r.
    for (auto y = 0; y < h; y += r) {
        for (auto x = 0; x < w; x += r) {
            double average = 0;  // Variable to store the average brightness of the current block.
            unsigned int count = 0;  // Variable to count the number of pixels in the block.
            
            // Calculate the average brightness of the current block.
            for (auto i = 0; i < r; i++) {
                for (auto j = 0; j < r; j++) {
                    if ((y + i < h) && (x + j < w)) {
                        average += pixel[y + i][x + j];
                        count++;
                    }
                }
            }
            average /= count;  // Calculate the average brightness.
            
            // Find the image in gray_image_map with the closest average brightness to the current block.
            double min_difference = DBL_MAX;
            const image* temp_image = nullptr;
            for (const auto& gim: gray_image_map) {
                double diff = abs(*(gim.second) - average);  // Calculate the difference in brightness.
                if (diff < min_difference) {
                    min_difference = diff;
                    temp_image = gim.first;
                }
            }
            
            // Determine the size of the current block.
            int h_range = (y + r > h) ? (h - y) : r;
            int w_range = (x + r > w) ? (w - x) : r;
            // Replace the current block with the selected image.
            temp_image->assign_to(&pixel, x, y, w_range, h_range);
        }
    }
    
    // Clean up by deleting the loaded images and their average brightness values.
    for (const auto& gim: gray_image_map) {
        delete gim.first;
        delete gim.second;
    }
    gray_image_map.clear();
}

// Creates a photo mosaic effect on an RGB image by replacing each block with a smaller image from a provided list, based on average color.
const void filter::photo_mosaic_RGB(const int& w, const int& h, int*** pixel, const int& r, const std::vector<std::string>& file_name) {
    std::vector<std::pair<image*, const double*>> RGB_image_map;  // Vector to store RGB images and their average color values.
    
    // Load each image from the provided file names, resize it, and calculate its average color.
    for (const auto& fn: file_name) {
        image* temp_image = new RGB_image();  // Create a new RGB image object.
        temp_image->load_image(fn);  // Load the image from file.
        temp_image->resize(r, r);  // Resize the image to r x r.
        const double* average = temp_image->get_average();  // Get the average color of the image.
        RGB_image_map.push_back(std::make_pair(temp_image, average));  // Store the image and its average color.
    }
    
    // Iterate over the original image in blocks of size r x r.
    for (auto y = 0; y < h; y += r) {
        for (auto x = 0; x < w; x += r) {
            double average[3] = {0};  // Array to store the average color of the current block.
            unsigned int count = 0;  // Variable to count the number of pixels in the block.
            
            // Calculate the average color of the current block.
            for (auto i = 0; i < r; i++) {
                for (auto j = 0; j < r; j++) {
                    if ((y + i < h) && (x + j < w)) {
                        average[0] += pixel[y + i][x + j][0];  // Red channel.
                        average[1] += pixel[y + i][x + j][1];  // Green channel.
                        average[2] += pixel[y + i][x + j][2];  // Blue channel.
                        count++;
                    }
                }
            }
            // Calculate the average color for each channel.
            average[0] /= count;
            average[1] /= count;
            average[2] /= count;
            
            // Find the image in RGB_image_map with the closest average color to the current block.
            double min_difference = DBL_MAX;
            const image* temp_image = nullptr;
            for (const auto& RGBim: RGB_image_map) {
                double diff = abs(RGBim.second[0] - average[0]) +
                              abs(RGBim.second[1] - average[1]) +
                              abs(RGBim.second[2] - average[2]);  // Calculate the difference in color.
                if (diff < min_difference) {
                    min_difference = diff;
                    temp_image = RGBim.first;
                }
            }
            
            // Determine the size of the current block.
            int h_range = (y + r > h) ? (h - y) : r;
            int w_range = (x + r > w) ? (w - x) : r;
            // Replace the current block with the selected image.
            temp_image->assign_to(pixel, x, y, w_range, h_range);
        }
    }
    
    // Clean up by deleting the loaded images and their average color values.
    for (const auto& RGBim: RGB_image_map) {
        delete RGBim.first;
        delete [] RGBim.second;
    }
    RGB_image_map.clear();
}

// Constructor for the filter class.
filter::filter() {}

// Destructor for the filter class.
filter::~filter() {}
