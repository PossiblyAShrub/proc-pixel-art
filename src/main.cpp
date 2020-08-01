#include "writer.h"

int main(int, char**) {
	// init vars
	unsigned int width = 255, height = 255;
	writer w("out.ppm", width, height);

	// TODO: rename writer to image
	// write to image class
	for (int x = 0; x <= width; x++)
	{
		for (int y = 1; y <= height; y++)
		{
			// nice blue gradient
			int r = height-y + 1;
			int g = width-x + 1;
			int b = 255;

			w.set_pixel(y, x, new pixel(r, g, b));
		}
	}	

	// and write to output
	w.write();
}
