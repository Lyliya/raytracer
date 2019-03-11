#include <iostream>
#include <chrono>
#include "Raytracer.hpp"

int main() {
	//Timer
	auto start = std::chrono::high_resolution_clock::now();

	Raytracer raytracer(640, 480);

	raytracer.run();

	//Stop timer
	auto stop = std::chrono::high_resolution_clock::now();
	double duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
	std::cout << "Rendering time : " << duration / 1000 << "s" << std::endl;
}