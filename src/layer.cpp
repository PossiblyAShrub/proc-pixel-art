#include "layer.h"

layer::layer(unsigned int width, unsigned int height, unsigned int z_lvl)
	: width_(width), height_(height), z_lvl_(z_lvl)
{
	// because  s p e e d
	pixels_.resize(width_*height_+1);
}

layer::~layer() {}

pixel* layer::get_pixel(unsigned int x, unsigned int y)
{
	// check [x] & [y] are within bounds
	if (x > width_ || y > height_) return nullptr;
	return pixels_[y*width_+x];
}

void layer::set_pixel(unsigned int x, unsigned int y, pixel* p)
{
	// make sure [x] & [y] are within bounds
	if (x > width_ || y > height_) return;

	// clamp upper vals of [p] to 255
	if (p->r > 255) p->r=255; if (p->g > 255) p->g=255; if (p->b > 255) p->b=255;

	// and set pixel
	pixels_[y*width_+x] = p;
}
