#include "image.h"

int main(int, char**) {
	// init vars
	unsigned int width = 255, height = 255;
	image img(width, height);

	// TODO: rename writer to image
	// write to image class
	for (int x = 0; x <= width; x++)
	{
		for (int y = 1; y <= height; y++)
		{
			// nice colorful gradient
			int r = height-y + 1;
			int b = width-x + 1;
			int g = 255;

			img.set_pixel(y, x, new pixel(r, g, b));
		}
	}	

	// and write to output
	img.write("img.ppm");
}
