#include "Vect.hpp"

Vect Vect::normalize()
{
	double mag = magnitude();

	return Vect(_x / mag, _y / mag, _z / mag);
}

Vect Vect::negative()
{
	return Vect(-_x, -_y, -_z);
}

double Vect::dotProduct(Vect v)
{
	return (_x * v.getVectX() + _y * v.getVectY() + _z * v.getVectZ());
}

Vect Vect::crossProduct(Vect v)
{
	return Vect(_y * v.getVectZ() - _z * v.getVectY(), _z * v.getVectX() - _x * v.getVectZ(), _x * v.getVectY() - _y * v.getVectX());
}

Vect Vect::operator+(Vect v)
{
	return Vect(_x + v.getVectX(), _y + v.getVectY(), _z + v.getVectZ());
}

Vect Vect::operator-(Vect v)
{
	return Vect(_x - v.getVectX(), _y - v.getVectY(), _z - v.getVectZ());
}

Vect Vect::operator*(double scalar)
{
	return Vect(_x * scalar, _y * scalar, _z * scalar);
}

Vect Vect::vectAdd(Vect v)
{
	return Vect(_x + v.getVectX(), _y + v.getVectY(), _z + v.getVectZ());
}

Vect Vect::vectMult(double scalar)
{
	return Vect(_x * scalar, _y * scalar, _z * scalar);
}