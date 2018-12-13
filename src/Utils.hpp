#pragma once

#include <iostream>
#include <fstream>
#include <string>

typedef struct RGBType_s {
	double r;
	double g;
	double b;
} RGBType;

class Utils {
	public:
		Utils() = delete;
		~Utils() = delete;
		static void saveImage(std::string filename, int w, int h, int dpi, RGBType *data);
		static void displayPercent(int percent);
};