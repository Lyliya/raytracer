#pragma once

#include "Ray.hpp"
#include "Vect.hpp"
#include "Color.hpp"

class Object {
	public:
		Object() {}
		~Object() {}

		virtual Color getColor() { return Color(1, 0, 0, 0); }
		virtual double findIntersection(Ray ray) { return 0; }
		virtual Vect getNormalAt(Vect point) { return Vect(); };
};