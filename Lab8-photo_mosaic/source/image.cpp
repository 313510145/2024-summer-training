#include "image.h"

// Static member initialization
image_loader image::il = image_loader();  // Initialize static image_loader instance
filter image::f = filter();  // Initialize static filter instance

// Default constructor
image::image(): width(0), height(0) {}

// Constructor with width and height
image::image(const int& w, const int& h): width(w), height(h) {}

// Virtual destructor
image::~image() {}
