#include <iostream>

void displayPercent(int percent) {
	static double save = 0;

	if (percent != save) {
		save = percent;
		std::cout << percent << "%" << std::endl;
	}
}

int main() {
	int w = 1920;
	int h = 1080;
	int percent = 0;
	int made = 0;

	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			percent = (made / (double)(w * h)) * 100;
			displayPercent(percent);
			made += 1;
		}
	}
	std::cout << "Raytracer..." << std::endl;
}