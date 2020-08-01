#pragma once

struct pixel
{
public:
	pixel(unsigned int r_, unsigned int g_, unsigned int b_);
	~pixel();
public:
	unsigned int r, g, b;
};

