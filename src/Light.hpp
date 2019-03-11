#pragma once

#include "Vect.hpp"
#include "Color.hpp"
#include "Source.hpp"

class Light : public Source {
	public:
		Light() : _position(Vect(0, 0, 0)), _color(Color(1, 1, 1, 0)) {}
		Light(Vect position, Color color) : _position(position), _color(color) {}
		~Light() {}
		virtual Vect getLightPosition() { return _position; }
		virtual Color getLightColor() { return _color; }

	private:
		Vect _position;
		Color _color;
};