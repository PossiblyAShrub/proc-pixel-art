#pragma once

#include <vector>

#include "pixel.h"

class layer
{
public:
	layer(unsigned int width, unsigned int height, unsigned int z_lvl);
	~layer();
public:
	pixel* get_pixel(unsigned int x, unsigned int y);
	void set_pixel(unsigned int x, unsigned int y, pixel* p);
public:
	unsigned int width_, height_;
	unsigned int z_lvl_;
	std::vector<pixel*> pixels_;
};
  
