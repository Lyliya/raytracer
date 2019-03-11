#include "Sphere.hpp"

Vect Sphere::getNormalAt(Vect point)
{
	Vect normal_Vect = point.vectAdd(_center.negative()).normalize();
	return normal_Vect;
}

double Sphere::findIntersection(Ray ray)
{
	Vect ray_origin = ray.getRayOrigin();
	Vect ray_direction = ray.getRayDirection();

	double b = (2 * (ray_origin.getVectX() - _center.getVectX()) * ray_direction.getVectX()) + (2 * (ray_origin.getVectY() - _center.getVectY()) * ray_direction.getVectY()) + (2 * (ray_origin.getVectZ() - _center.getVectZ()) * ray_direction.getVectZ());
	double c = std::pow(ray_origin.getVectX() - _center.getVectX(), 2) + std::pow(ray_origin.getVectY() - _center.getVectY(), 2) + std::pow(ray_origin.getVectZ() - _center.getVectZ(), 2) - (_radius * _radius);

	double discriminant = b * b - 4*c;

	if (discriminant > 0) {
		double d1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.000001;

		if (d1 > 0)
			return d1;
		return ((sqrt(discriminant) - b) / 2) - 0.000001;
	} else {
		return -1;
	}
}