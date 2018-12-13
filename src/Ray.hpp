#pragma once

#include "Vect.hpp"

class Ray {
	public:
		Ray() : _origin(Vect(0, 0, 0)), _direction(Vect(0, 0, 0)) {}
		Ray(Vect origin, Vect direction) : _origin(origin), _direction(direction) {}
		~Ray() {}
		Vect getRayOrigin() { return _origin; }
		Vect getRayDirection() { return _direction; }

	private:
		Vect _origin;
		Vect _direction;
};