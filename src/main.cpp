#include "image.h"
#include "common/perlin_noise.h"

// TODO: sort layers by z_lvl

int main(int argc, char** argv) {
	// init vars
	unsigned int width = 255, height = 255;
	layer* base = new layer(width, height, 0);
	image img(width, height);

	int _seed = 16783;

//	img.add_layer(base);

	// TODO: rename writer to image
	// write to image class
	for (int x = 0; x <= width; x++)
	{
		for (int y = 1; y <= height; y++)
		{
			// nice colorful gradient
			//int r = height-y + 1;
			//int b = width-x + 1;
			//int g = 255;

			// perlin noise
			perlin_noise np(_seed);
			float v = np.noise(x*0.000001, y*0.01, 0) * 255;
			
			int n = 30;
			if (x <= v) n = 235;

			int r = n;
			int g = n;
			int b = n;

			base->set_pixel(y, x, new pixel(r, g, b));
		}
	}	

	// add our layers
	img.add_layer(base);

	// and write to output
	img.write("img.ppm");
}
