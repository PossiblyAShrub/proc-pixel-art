#pragma once

#include <vector>

class pixel
{
public:
	pixel(unsigned int r_, unsigned int g_, unsigned int b_)
		: r(r_), g(g_), b(b_) {
		// clamp upper
		if (r >= 255) r = 255;
		if (g >= 255) g = 255;
		if (b >= 255) g = 255;

		// no need to clmp lower bc -> r|g|b are unsigned
	}
	~pixel() {}
public:
	unsigned int r, g, b;
};

class writer
{
public:
	writer(const char* file_out, unsigned int width, unsigned int height);
	~writer();
public:
	// write current image data to [file_out]
	void write();

	// gets ptr to pixel at coords [x] & [y]
	pixel* get_pixel(unsigned int x, unsigned int y);
	void set_pixel(unsigned int x, unsigned int y, pixel* p);
private:
	const char* file_out_;
	unsigned int width_, height_;
	std::vector<pixel*> pixels_;
};

