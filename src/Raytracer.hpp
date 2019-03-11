#pragma once

#include <vector>
#include "Object.hpp"
#include "Source.hpp"
#include "Light.hpp"
#include "Utils.hpp"

class Raytracer {
	public:
		Raytracer(int width, int height);
		~Raytracer();
		void run();
		int winningObjectIndex(std::vector<double> intersections);
		Color getColorAt(Vect intersection_position, Vect intersecting_ray_direction, std::vector<Object *> objects, int closer, std::vector<Source *> light_sources, double accuracy, double ambientlight);

	private:
		int _width;
		int _height;
		int _percent;
		int _made;
		int _dpi;
		double _aspectratio;
		RGBType *_pixels;
};