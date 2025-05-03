#include "image.h"

image_loader image::il = image_loader();
filter image::f = filter();

image::image(): width(0), height(0) {}

image::image(const int& w, const int& h): width(w), height(h) {}

image::~image() {}
