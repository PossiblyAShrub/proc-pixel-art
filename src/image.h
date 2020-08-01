#pragma once

#include <vector>

#include "pixel.h"
#include "layer.h"

class image
{
public:
	image(unsigned int width, unsigned int height);
	~image();
public:
	// write current image data to [file_out]
	void write(const char* file_out);

	void add_layer(layer* l);
private:
	void flatten_layers();
private:
	unsigned int width_, height_;
	std::vector<layer*> layers_;

	std::vector<pixel*> pixels_;
};

