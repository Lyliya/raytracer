#pragma once

#include <cmath>

class Vect {
	public:
		Vect(double x = 0, double y = 0, double z = 0) : _x(x), _y(y), _z(z) {}
		~Vect() {}
		double getVectX() { return _x; }
		double getVectY() { return _y; }
		double getVectZ() { return _z; }
		double magnitude() { return std::sqrt((_x * _x) + (_y * _y) + (_z * _z)); }
		Vect normalize();
		Vect negative();
		double dotProduct(Vect v);
		Vect crossProduct(Vect v);
		Vect addVector(Vect v);
		Vect multVector(double scalar);

	private:
		double _x;
		double _y;
		double _z;
};