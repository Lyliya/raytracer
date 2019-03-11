#pragma once

#include <cmath>
#include "Object.hpp"

class Plane : public Object {
	public:
		Plane() : _normal(Vect(1, 0, 0)), _dist(0), _color(Color(0.5, 0.5, 0.5, 0)) {}
		Plane(Vect normal, double dist, Color color) : _normal(normal), _dist(dist), _color(color) {}
		~Plane() {}
		virtual Vect getPlaneNormal() { return _normal; }
		virtual double getPlaneDistance() { return _dist; }
		virtual Color getColor() { return _color; }

		virtual Vect getNormalAt(Vect point) { return _normal; }
		virtual double findIntersection(Ray ray);

	private:
		Vect _normal;
		double _dist;
		Color _color;
};