#include "image.h"

#include <iostream>

image::image(unsigned int width, unsigned int height)
	: width_(width), height_(height), pixels_()
{
	// becuase we are speedy
	pixels_.resize(width_*height_+1);
}

image::~image() {}

void image::write(const char* file_out) {
	// for logging
	std::cerr << "Writing to output file: \"" << file_out << "\"" << std::endl;

	// file meta data
	std::cout << "P3\n" << width_ << " " << height_ << "\n255" << std::endl;
	
	// write pixel data
	for (int x = width_; x > 0; x--)
	{
		for (int y = 0; y < height_; y++)
		{
			pixel* p = get_pixel(x, y);
			// make sure [p] isn't a nullptr
			if (p != nullptr)
				std::cout << p->r << " " << p->g << " " << p->b << std::endl;
			else // otherwise burn their eyes!
				std::cout << "255 0 255" << std::endl;
		}
	}
}

pixel* image::get_pixel(unsigned int x, unsigned int y)
{
	return pixels_[y*width_+x];
}

void image::set_pixel(unsigned int x, unsigned int y, pixel* p)
{
	// clamp pixels to 255
	if (p->r > 255) p->r = 255; if (p->g > 255) p->g = 255; if (p->b > 255) p->b = 255;

	// make sure this pixel is within bounds
	if (x <= width_ && y <= height_)
		pixels_[y*width_+x] = p;
}
