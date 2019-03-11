#pragma once

#include <cmath>
#include "Object.hpp"

class Sphere : public Object {
	public:
		Sphere() : _center(Vect(0, 0, 0)), _radius(1), _color(Color(0.5, 0.5, 0.5, 0)) {}
		Sphere(Vect position, double radius, Color color) : _center(position), _radius(radius), _color(color) {}
		~Sphere() {}
		virtual Vect getSphereCenter() { return _center; }
		virtual double getSphereRadius() { return _radius; }
		virtual Color getColor() { return _color; }
		virtual Vect getNormalAt(Vect point);

		virtual double findIntersection(Ray ray);

	private:
		Vect _center;
		double _radius;
		Color _color;
};