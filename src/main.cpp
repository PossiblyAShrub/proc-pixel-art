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
	if (max_fracg < min_fracg) std::cerr << "WARNING: \"min_fracg > max_fracg\" this may result in undefined behaviour";

	sky_layer sky_layers[sky_layer_count];

	//perlin noise
	perlin_noise np(_seed);

	std::cout << "Pre-Computing sky layers" << std::endl;
	for (int i = 0; i < sky_layer_count; i++)
	{
		float local_frac = i / sky_layer_count;
		float max_frac = ((max_fracg - min_fracg)/sky_layer_count)*i + min_fracg;

		float r = 1-(max_frac/max_fracg) * 200;
		float g = ((max_frac/max_fracg) * 50)+150;
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

float fbm(perlin_noise* pn, int x, int y, int z, unsigned int octaves,
		float s_freq, float s_amp, float deg, float pow)
{
	float v = 0;

	float f = s_freq; // frequency
	float A = s_amp; // amplitude

	for (int i = 0; i < octaves; i++)
	{
		v += pn->noise(x*f, y*f, z*f) * A;

		f *= deg;
		A *= pow;
	}

	return v;
}

void draw_mountains(layer* mtns, int _seed, unsigned int width, unsigned int height)
{
	// perlin noise
	perlin_noise np(_seed);

	fbm(&np, 0, 1, 0, 10, 0.1, 1, 0.8, 0.5);

	// fill pixels
	for (int y = 0; y <= height; y++)
	{
		for (int x = 1; x <= width; x++)
		{
			float r = 0;
			float g = 0;
			float b = 0;

			float h = 0.0125;
			float v =0.5;// abs(sin(y/50));
			v *= fbm(&np, 0, y, 0, 3, h, 0.75, 2.5, 0.5);
			
			if (v*.5 * height >= x)
			{
				r = 20;
				g = 20;
				b = 20;
			}

			mtns->set_pixel(x, y, new pixel(r, g, b));
		}
	}
}

void draw_mtn_view(image* img, int _seed) {
    unsigned int width = img->get_width(), height = img->get_height();
    auto* sky = new layer(width, height, 0);
    auto* mtns = new layer(width, height, 1);

    // draw to image
    draw_sky(sky, _seed, width, height);
    draw_mountains(mtns, _seed, width, height);

    // add our layers
    img->add_layer(sky);
    img->add_layer(mtns);
}

int main(int argc, char** argv) {
	// init vars
	unsigned int width = 128, height = 128;
	image img(width, height);

	int _seed = 16780;

	draw_mtn_view(&img, _seed);

	// and write to output
	img.write("img.ppm");
}
