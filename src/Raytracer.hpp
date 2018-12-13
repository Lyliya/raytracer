#pragma once

#include "Utils.hpp"

class Raytracer {
	public:
		Raytracer(int width, int height);
		~Raytracer();
		void run();
	private:
		int _width;
		int _height;
		int _percent;
		int _made;
		int _dpi;
		RGBType *_pixels;
};