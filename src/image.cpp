#include "image.h"

#include <iostream>
#include <fstream>

image::image(unsigned int width, unsigned int height)
	: width_(width), height_(height), layers_(), pixels_()
{
	// becuase  s p e e d
	pixels_.resize(width_*height_+2);
}

image::~image()
{
	for (auto* l : layers_)
		delete l;

	for (auto* p : pixels_)
		delete p;
}

void image::write(const char* file_out) {
	flatten_layers();

	std::cout << "Writing to output file: \"" << file_out << "\"" << std::endl;
	// open fstream
	std::ofstream fout(file_out);

	// file meta data
	fout << "P3\n" << width_ << " " << height_ << "\n255" << std::endl;
	
	// write pixel data
	for (int x = width_; x > 0; x--)
	{
		for (int y = 0; y < height_; y++)
		{
			pixel* p = pixels_[y*width_+x];
			// make sure [p] isn't a nullptr
			if (p != nullptr)
				fout << p->r << " " << p->g << " " << p->b << std::endl;
			else // otherwise burn their eyes!
				fout << "255 0 255" << std::endl;
		}
	}

	// flush and close ofstream
	fout.flush();
	fout.close();
}

void image::add_layer(layer* l)
{
	layers_.push_back(l);
}

void image::flatten_layers()
{
	std::cout << "Flattening layers" << std::endl;

	for (layer* l : layers_)
	{
		for (int x = 0; x < width_; x++)
		{
			for (int y = 0; y < height_; y++)
			{
				pixel* p = pixels_[y*width_+x];
				pixel* lp = l->get_pixel(x, y);

				// nullptr check/handling
				if (p == nullptr)
				{
					p = new pixel(0, 0, 0);
					pixels_[y*width_+x] = p;
				}

				if (p != nullptr && lp != nullptr)
				{
					// norm  -  TODO: add more combine funcs (w/ enum)
					if (lp->r != 0 && lp->g != 0 && lp->b != 0)
					{
						p->r = lp->r;
						p->g = lp->g;
						p->b = lp->b;
					}
				}
			}
		}
	}
}
