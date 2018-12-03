#pragma once

#include <stdint.h>

#include "SDL2\SDL_pixels.h"

// a legit color class
struct Color
{
	union
	{
		uint32_t i;
		struct
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};
	};


	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a)
	{

	}
	Color(SDL_Color color) : r(color.r), g(color.g), b(color.b), a(color.a)
	{

	}

	SDL_Color toSDL()
	{
		return { r, g, b, a };
	}
};
