#include <limits>
#include "Raytracer.hpp"
#include "Vect.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Triangle.hpp"

Raytracer::Raytracer(int width, int height) : _width(width), _height(height), _percent(0), _made(0), _dpi(72), _aspectratio((double)_width/(double)_height) ,_pixels(new RGBType[_width * _height])
{

}

Raytracer::~Raytracer()
{
	delete _pixels;
}

int Raytracer::winningObjectIndex(std::vector<double> intersections)
{
	int min_index = -1;

	if (intersections.size() == 0) {
		return -1;
	} else if (intersections.size() == 1) {
		if (intersections[0] > 0) {
			return 0;
		} else {
			return -1;
		}
	} else {
		double max = std::numeric_limits<double>::max();
		for (int i = 0; i < intersections.size(); i++) {
			if (intersections[i] > 0 && intersections[i] <= max) {
				max = intersections[i];
				min_index = i;
			}
		}
		return min_index;
	}
}

Color Raytracer::getColorAt(Vect intersection_position, Vect intersecting_ray_direction, std::vector<Object *> objects, int closer, std::vector<Source *> light_sources, double accuracy, double ambientlight)
{
	Color closer_color = objects[closer]->getColor();
	Vect closer_normal = objects[closer]->getNormalAt(intersection_position);

	if (closer_color.getSpecial() == 2) {
		int square = (int)std::floor(intersection_position.getVectX()) + (int)std::floor(intersection_position.getVectZ());

		if ((square % 2) == 0) {
			closer_color.setColorRed(0);
			closer_color.setColorGreen(0);
			closer_color.setColorBlue(0);
		} else {
			closer_color.setColorRed(1);
			closer_color.setColorGreen(1);
			closer_color.setColorBlue(1);
		}
	}

	Color final_color = closer_color.colorScalar(ambientlight);

	//Reflection
	if (closer_color.getSpecial() > 0 && closer_color.getSpecial() <= 1) {
		double dot1 = closer_normal.dotProduct(intersecting_ray_direction.negative());
		Vect scalar1 = closer_normal * dot1;
		Vect add1 = scalar1 + intersecting_ray_direction;
		Vect scalar2 = add1 * 2;
		Vect add2 = intersecting_ray_direction.negative() + scalar2;
		Vect reflection_direction = add2.normalize();
		Ray reflection_ray(intersection_position, reflection_direction);

		std::vector<double> reflection_intersections;

		for (int r = 0; r < objects.size(); r++) {
			reflection_intersections.push_back(objects[r]->findIntersection(reflection_ray));
		}
		int index_with_reflection = winningObjectIndex(reflection_intersections);
		if (index_with_reflection != -1) {
			if (reflection_intersections[index_with_reflection] > accuracy) {
				Vect reflection_intersection_position = intersection_position + (reflection_direction * reflection_intersections[index_with_reflection]);
				Vect reflection_intersection_direction = reflection_direction;
				Color reflection_intersection_color = getColorAt(reflection_intersection_position, reflection_intersection_direction, objects, index_with_reflection, light_sources, accuracy, ambientlight);
				final_color = final_color + (reflection_intersection_color.colorScalar(closer_color.getSpecial()));
			}
		}
	}

	// Shadow
	for (int i = 0; i < light_sources.size(); i++) {
		Vect light_dir = (light_sources[i]->getLightPosition() + intersection_position.negative()).normalize();
		float cos_angle = closer_normal.dotProduct(light_dir);

		if (cos_angle > 0) {
			bool shadowed = false;
			Vect distance_to_light = (light_sources[i]->getLightPosition() + intersection_position.negative()).normalize();
			float distance_to_light_magnitude = distance_to_light.magnitude();

			Ray shadow_ray (intersection_position, distance_to_light);
			std::vector<double> secondary_intersections;

			for (int x = 0; x < objects.size() && shadowed == false; x++) {
				secondary_intersections.push_back(objects[x]->findIntersection(shadow_ray));
			}
			for (int c = 0; c < secondary_intersections.size(); c++) {
				if (secondary_intersections[c] > accuracy) {
					if (secondary_intersections[c] <= distance_to_light_magnitude) {
						shadowed = true;
					}
					break;
				}
			}

			if (shadowed == false) {
				final_color = (final_color + (closer_color * light_sources[i]->getLightColor()).colorScalar(cos_angle));

				if (closer_color.getSpecial() > 0 && closer_color.getSpecial() <= 1) {
					double dot1 = closer_normal.dotProduct(intersecting_ray_direction.negative());
					Vect scalar1 = closer_normal * dot1;
					Vect add1 = scalar1 + intersecting_ray_direction;
					Vect scalar2 = add1 * 2;
					Vect add2 = intersecting_ray_direction.negative() + scalar2;
					Vect reflection_direction = add2.normalize();

					double specular = reflection_direction.dotProduct(light_dir);
					if (specular > 0) {
						specular = std::pow(specular, 10);
						final_color = final_color + light_sources[i]->getLightColor().colorScalar(specular * closer_color.getSpecial());
					}
				}
			}
		}
	}
	return final_color.clip();
}

void Raytracer::run()
{
	//Anti Aliasing
	const int aadepth = 8;
	double aathreshold = 0.1;

	Vect X(1, 0, 0);
	Vect Y(0, 1, 0);
	Vect Z(0, 0, 1);

	// Camera
	Vect lookat(0, 0, 0);
	Vect campos(3, 1.5, -4);
	Vect diffBtw(campos.getVectX() - lookat.getVectX(), campos.getVectY() - lookat.getVectY(), campos.getVectZ() - lookat.getVectZ());

	Vect camdir = diffBtw.negative().normalize();
	Vect camright = Y.crossProduct(camdir).normalize();
	Vect camdown = camright.crossProduct(camdir);
	Camera camera(campos, camdir, camright, camdown);

	Color white_light(1.0, 1.0, 1.0, 0);
	Color pretty_green(0.5, 1.0, 0.5, 1);
	Color tile_floor(1, 1, 1, 2);
	Color Black(0, 0, 0, 0);

	//Light
	double ambientlight = 0.2;
	double accuracy = 0.00000001;

	Vect light_position(-7, 10, -10);
	Light scene_light(light_position, white_light);
	std::vector<Source *> light_sources;
	light_sources.push_back(dynamic_cast<Source *>(&scene_light));

	//Object
	Sphere scene_sphere(Vect(0, 0, 0), 1, pretty_green);
	Sphere scene_sphere2 (Vect(1.75, -0.25, 0), 0.5, Color(0.5, 0.25, 0.25, 0));
	Plane scene_plane(Y, -1, tile_floor);
	Triangle scene_triangle(Vect(3,0,0), Vect(0, 3, 0), Vect(0, 0, 3), pretty_green);

	std::vector<Object *> objects;
	objects.push_back(dynamic_cast<Object *>(&scene_sphere));
	objects.push_back(dynamic_cast<Object *>(&scene_plane));
	objects.push_back(dynamic_cast<Object *>(&scene_sphere2));
	objects.push_back(dynamic_cast<Object *>(&scene_triangle));

	double xamnt, yamnt;

	for (int x = 0; x < _width; x++) {
		for (int y = 0; y < _height; y++) {
			
			// start with a blank pixel
			double tempRed[aadepth * aadepth];
			double tempGreen[aadepth * aadepth];
			double tempBlue[aadepth * aadepth];
			
			for (int aax = 0; aax < aadepth; aax++) {
				for (int aay = 0; aay < aadepth; aay++) {
					
					// create the ray from the camera to this pixel
					if (aadepth == 1) {
					
						// start with no anti-aliasing
						if (_width > _height) {
							// the image is wider than it is tall
							xamnt = ((x+0.5)/_width)*_aspectratio - (((_width-_height)/(double)_height)/2);
							yamnt = ((_height - y) + 0.5)/_height;
						}
						else if (_height > _width) {
							// the imager is taller than it is wide
							xamnt = (x + 0.5)/ _width;
							yamnt = (((_height - y) + 0.5)/_height)/_aspectratio - (((_height - _width)/(double)_width)/2);
						}
						else {
							// the image is square
							xamnt = (x + 0.5)/_width;
							yamnt = ((_height - y) + 0.5)/_height;
						}
					}
					else {
						// anti-aliasing
						if (_width > _height) {
							// the image is wider than it is tall
							xamnt = ((x + (double)aax/((double)aadepth - 1))/_width)*_aspectratio - (((_width-_height)/(double)_height)/2);
							yamnt = ((_height - y) + (double)aax/((double)aadepth - 1))/_height;
						}
						else if (_height > _width) {
							// the imager is taller than it is wide
							xamnt = (x + (double)aax/((double)aadepth - 1))/ _width;
							yamnt = (((_height - y) + (double)aax/((double)aadepth - 1))/_height)/_aspectratio - (((_height - _width)/(double)_width)/2);
						}
						else {
							// the image is square
							xamnt = (x + (double)aax/((double)aadepth - 1))/_width;
							yamnt = ((_height - y) + (double)aax/((double)aadepth - 1))/_height;
						}
					}
					
					Vect cam_ray_origin = camera.getCameraPosition();
					Vect cam_ray_direction = ((camdir + ((camright * (xamnt - 0.5)) + (camdown * (yamnt - 0.5))))).normalize();
					
					Ray cam_ray (cam_ray_origin, cam_ray_direction);
					
					std::vector<double> intersections;
					
					for (int index = 0; index < objects.size(); index++) {
						intersections.push_back(objects[index]->findIntersection(cam_ray));
					}
					
					int index_of_winning_object = winningObjectIndex(intersections);
					
					if (index_of_winning_object == -1) {
						// set the backgroung black
						tempRed[aay * aadepth + aax] = 0;
						tempGreen[aay * aadepth + aax] = 0;
						tempBlue[aay * aadepth + aax] = 0;
					}
					else{
						// index coresponds to an object in our scene
						if (intersections.at(index_of_winning_object) > accuracy) {
							// determine the position and direction vectors at the point of intersection
							
							Vect intersection_position = cam_ray_origin.vectAdd(cam_ray_direction.vectMult(intersections.at(index_of_winning_object)));
							Vect intersecting_ray_direction = cam_ray_direction;
		
							Color intersection_color = getColorAt(intersection_position, intersecting_ray_direction, objects, index_of_winning_object, light_sources, accuracy, ambientlight);

							tempRed[aay * aadepth + aax] = intersection_color.getColorR();
							tempGreen[aay * aadepth + aax] = intersection_color.getColorG();
							tempBlue[aay * aadepth + aax] = intersection_color.getColorB();
						}
					}
				}
			}
			
			// average the pixel color
			double totalRed = 0;
			double totalGreen = 0;
			double totalBlue = 0;
			
			for (int iRed = 0; iRed < aadepth*aadepth; iRed++) {
				totalRed = totalRed + tempRed[iRed];
			}
			for (int iGreen = 0; iGreen < aadepth*aadepth; iGreen++) {
				totalGreen = totalGreen + tempGreen[iGreen];
			}
			for (int iBlue = 0; iBlue < aadepth*aadepth; iBlue++) {
				totalBlue = totalBlue + tempBlue[iBlue];
			}
			
			double avgRed = totalRed/(aadepth*aadepth);
			double avgGreen = totalGreen/(aadepth*aadepth);
			double avgBlue = totalBlue/(aadepth*aadepth);

			_pixels[y * _width + x].r = avgRed;
			_pixels[y * _width + x].g = avgGreen;
			_pixels[y * _width + x].b = avgBlue;
			//Discplay Percent of completion
			_made += 1;
			Utils::displayPercent((_made / (double)(_width * _height)) * 100);
		}

		Utils::saveImage("scene_aa.bmp", _width, _height, _dpi, _pixels);
	}
}