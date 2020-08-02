#include "image.h"
#include "common/perlin_noise.h"

// TODO: sort layers by z_lvl

bool isChecker(unsigned int x, unsigned int y)
{
	return x % 2 == 0 && y % 2 == 0;
}

int main(int argc, char** argv) {
	// init vars
	unsigned int width = 128, height = 128;
	layer* sky = new layer(width, height, 0);
	layer* mtn = new layer(width, height, 0);
	image img(width, height);

	int _seed = 1678;

	// write to layers
	for (int y = 0; y <= height; y++)
	{
		for (int x = 1; x <= width; x++)
		{
////////////////////////// SKY //////////////////////////
			// nice colorful gradient
			int sky_r = width-x + 1;
			int sky_b = 255;
			int sky_g = 255;

			sky->set_pixel(x, y, new pixel(sky_r, sky_g, sky_b));
////////////////////// MOUNTAINS ///////////////////////
			// perlin noise
			perlin_noise np(_seed);

			// get this v
			float h = 0.025;
			float v = np.noise(0, y*h, 0) * height;
			v = v * .85;

			// calc derivative
			float vh = np.noise(0, (y*h)+h, 0) * height;
			vh = vh * .85;
			float m = (vh - v) / h;

			// map [v] & [m] to colors
			int n = 0;
			if (x <= v)
			{
				if (m > 0) n = 150;
				else if (m > -100 && isChecker(x, y)) n = 150;
				else n = 30;
			}

			// apply color mapping
			int mtn_r = n;
			int mtn_g = n;
			int mtn_b = n;

			mtn->set_pixel(x, y, new pixel(mtn_r, mtn_g, mtn_b));
		}
	}	

	// add our layers
	img.add_layer(sky);
	img.add_layer(mtn);

	// and write to output
	img.write("img.ppm");
}
