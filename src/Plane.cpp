#include "Plane.hpp"

double Plane::findIntersection(Ray ray)
{
	Vect ray_direction = ray.getRayDirection();
	double a = ray_direction.dotProduct(_normal);

	if (a == 0) {
		return -1;
	} else {
		double b = _normal.dotProduct(ray.getRayOrigin() + (_normal * _dist).negative());
		return -1 * b / a;
	}
}