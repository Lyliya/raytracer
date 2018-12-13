#include "Raytracer.hpp"
#include "Vect.hpp"
#include "Ray.hpp"
#include "Camera.hpp"

Raytracer::Raytracer(int width, int height) : _width(width), _height(height), _percent(0), _made(0), _dpi(72), _pixels(new RGBType[_width * _height])
{

}

Raytracer::~Raytracer()
{
	delete _pixels;
}

void Raytracer::run()
{
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

	for (int x = 0; x < _width; x++) {
		for (int y = 0; y < _height; y++) {

			_pixels[y * _width + x].r = 23;
			_pixels[y * _width + x].g = 222;
			_pixels[y * _width + x].b = 10;

			// Display percent
			_made += 1;
			Utils::displayPercent((_made / (double)(_width * _height)) * 100);
		}
	}

	Utils::saveImage("scene.bmp", _width, _height, _dpi, _pixels);
}