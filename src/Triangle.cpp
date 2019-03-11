#include "Triangle.hpp"

Vect Triangle::getNormalAt(Vect point)
{
	auto normal = getTriangleNormal();
	return normal;
}

double Triangle::findIntersection(Ray ray)
{
	Vect ray_direction = ray.getRayDirection();
	auto normal = getTriangleNormal();
	auto dist = getTriangleDistance();
	double a = ray_direction.dotProduct(normal);

	if (a == 0) {
		return -1;
	} else {
		double b = normal.dotProduct(ray.getRayOrigin() + (normal * dist).negative());
		double distance = -1 * b / a;
		double Qx = (ray_direction * distance).getVectX() + ray.getRayOrigin().getVectX();
		double Qy = (ray_direction * distance).getVectY() + ray.getRayOrigin().getVectY();
		double Qz = (ray_direction * distance).getVectZ() + ray.getRayOrigin().getVectZ();

		Vect Q (Qx, Qy, Qz);
		Vect CA = _c - _a;
		Vect QA = Q - _a;
		double t1 = (CA.crossProduct(QA)).dotProduct(normal);

		Vect BC = _b - _c;
		Vect QC = Q - _c;
		double t2 = (BC.crossProduct(QC)).dotProduct(normal);

		Vect AB = _a - _b;
		Vect QB = Q - _b;
		double t3 = (AB.crossProduct(QB)).dotProduct(normal);
		if (t1 >= 0 && t2 >= 0 && t3 >= 0) {
			return -1 * b / a;
		} else {
			return -1;
		}
	}
}