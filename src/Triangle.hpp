#pragma once

#include <cmath>
#include "Object.hpp"

class Triangle : public Object {
	public:
		Triangle() : _a(Vect(1, 0, 0)), _b(Vect(0, 1, 0)), _c(Vect(0, 0, 1)), _color(Color(0.5, 0.5, 0.5, 0)) {}
		Triangle(Vect a, Vect b, Vect c, Color color) : _a(a), _b(b), _c(c), _color(color) {}
		~Triangle() {}
		virtual Vect getTriangleNormal() { 
			//Vect CA (_c.getVectX() - _a.getVectX(), _c.getVectY() - _a.getVectY(), _c.getVectZ() - _a.getVectZ());
			//Vect BA (_b.getVectX() - _a.getVectX(), _b.getVectY() - _a.getVectY(), _b.getVectZ() - _a.getVectZ());
			Vect BA = _b - _a;
			Vect CA = _c - _a;
			Vect cross = CA.crossProduct(BA);

			return cross.normalize();
		}
		virtual double getTriangleDistance() {
			auto normal = getTriangleNormal();
			auto distance = normal.dotProduct(_a);
			return distance;
		}
		virtual Color getColor() { return _color; }

		virtual Vect getNormalAt(Vect point);
		virtual double findIntersection(Ray ray);

	private:
		Vect _a;
		Vect _b;
		Vect _c;
		Color _color;
};