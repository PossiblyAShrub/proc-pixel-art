#include "writer.h"

#include <iostream>

writer::writer(const char* file_out, unsigned int width, unsigned int height)
	: file_out_(file_out), width_(width), height_(height), pixels_()
{
	// becuase we are speedy
	pixels_.resize(width_*height_+1);
}

writer::~writer() {}

void writer::write() {
	// for logging
	std::cerr << "Writing to output file: \"" << file_out_ << "\"" << std::endl;

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

pixel* writer::get_pixel(unsigned int x, unsigned int y)
{
	return pixels_[y*width_+x];
}

void writer::set_pixel(unsigned int x, unsigned int y, pixel* p)
{
	// clamp pixels to 255
	if (p->r > 255) p->r = 255; if (p->g > 255) p->g = 255; if (p->b > 255) p->b = 255;

	// make sure this pixel is within bounds
	if (x <= width_ && y <= height_)
		pixels_[y*width_+x] = p;
}
