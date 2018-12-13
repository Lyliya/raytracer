#pragma once

#include "Vect.hpp"

class Camera {
	public:
		Camera() : _camPosition(Vect(0,0,0)), _camDirection(Vect(0,0,1)), _camRight(Vect(0,0,0)), _camDown(Vect(0,0,0)) {}
		Camera(Vect position, Vect direction, Vect right, Vect down) : _camPosition(position), _camDirection(direction), _camRight(right), _camDown(down) {}
		~Camera() {}
		Vect getCameraPosition() { return _camPosition; }
		Vect getCameraDirection() { return _camDirection; }
		Vect getCameraRight() { return _camRight; }
		Vect getCameraDown() { return _camDown; }

	private:
		Vect _camPosition;
		Vect _camDirection;
		Vect _camRight;
		Vect _camDown;
};