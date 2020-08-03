#include "image.h"
#include "common/perlin_noise.h"

#include <cmath>
#include <iostream>

// TODO: sort layers by z_lvl

bool isChecker(unsigned int x, unsigned int y)
{
	return x % 2 == 0 && y % 2 == 0;
}

float len(int x, int y)
{
	return sqrt((x*x)+(y*y));
}

struct sky_layer
{
public:
	sky_layer(float _max_frac, float _r, float _g, float _b)
		: max_frac(_max_frac), r(_r), g(_g), b(_b)
	{
	}

	sky_layer()
	{
	}
public:
	float r, g, b;
	float max_frac;
};

void draw_sky(layer* sky, int _seed, unsigned int width, unsigned int height)
{
	// precompute sky colors
	const int sky_layer_count = 8;
	const float min_fracg = 0.25;
	const float max_fracg = 1.75;
	assert(max_fracg > min_fracg);

	sky_layer sky_layers[sky_layer_count];

	//perlin noise
	perlin_noise np(_seed);

	std::cout << "Pre-Computing sky layers" << std::endl;
	for (int i = 0; i < sky_layer_count; i++)
	{
		float local_frac = i / sky_layer_count;
		float max_frac = ((max_fracg - min_fracg)/sky_layer_count)*i + min_fracg;

		float r = 1-(max_frac/max_fracg) * 255;
		float g = 200;
		float b = (max_frac/max_fracg) * 255;

		sky_layers[i] = sky_layer(max_frac, r, g, b);
	}


	std::cout << "Drawing sky"<<std::endl;
	// draw sky layer
	for (int y = 0; y <= height; y++)
	{
		for (int x = 1; x <= width; x++)
		{
			float size = width*0.35;
			int p = 0;

			int sky_r = 0;
			int sky_g = 0;
			int sky_b = 0;

			float mro = width * 0.3;
			float rno = np.noise(x*0.1, y*0.1, 50) * mro;
			float ro = np.noise(x*rno*0.1, y*rno*0.1, 50) * mro;
			float o = x + ro;

			for (int i = 0; i < sky_layer_count; i++)
			{
				sky_layer cplayer = sky_layers[i];

				if (o <= width * cplayer.max_frac)
				{
					sky_r = cplayer.r;
					sky_g = cplayer.g;
					sky_b = cplayer.b;
					break;
				}
			}

			sky->set_pixel(x, y, new pixel(sky_r, sky_g, sky_b));
		}
	}	
}

int main(int argc, char** argv) {
	// init vars
	unsigned int width = 128, height = 128;
	layer* sky = new layer(width, height, 1);
	image img(width, height);

	int _seed = 1678;

	draw_sky(sky, _seed, width, height);

	// add our layers
	img.add_layer(sky);

	// and write to output
	img.write("img.ppm");
}
