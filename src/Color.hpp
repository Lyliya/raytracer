#pragma once

class Color {
	public:
		Color(double r = 0.5, double g = 0.5, double b = 0.5, double special = 0) : _r(r), _g(g), _b(b), _special(special) {}
		~Color() {}
		double getColorR() { return _r; }
		double getColorG() { return _g; }
		double getColorB() { return _b; }
		double getSpecial() { return _special; }
		void setColorRed(double r) { _r = r; };
		void setColorGreen(double g) { _g = g; };
		void setColorBlue(double b) { _b = b; };
		void setSpecial(double special) { _special = special; }
		double brightness() { return ((_r + _g + _b) / 3); }
		Color colorScalar(double scalar) { return Color(_r * scalar, _g * scalar, _b * scalar, _special); }
		Color operator+(Color color) { return Color(_r + color.getColorR(), _g + color.getColorG(), _b + color.getColorB(), _special); }
		Color operator*(Color color) { return Color(_r * color.getColorR(), _g * color.getColorG(), _b * color.getColorB(), _special); }
		Color colorAdd(Color color) { return Color(_r + color.getColorR(), _g + color.getColorG(), _b + color.getColorB(), _special); }
		Color colorMultiply(Color color) { return Color(_r * color.getColorR(), _g * color.getColorG(), _b * color.getColorB(), _special); }
		Color colorAverage(Color color) { return Color((_r + color.getColorR()) / 2, (_g + color.getColorG()) / 2, (_b + color.getColorB()) / 2, _special); }

		Color clip() {
		double alllight = _r + _g + _b;
		double excesslight = alllight - 3;
		if (excesslight > 0) {
			_r = _r + excesslight*(_r/alllight);
			_g = _g + excesslight*(_g/alllight);
			_b = _b + excesslight*(_b/alllight);
		}
		if (_r > 1) {_r = 1;}
		if (_g > 1) {_g = 1;}
		if (_b > 1) {_b = 1;}
		if (_r < 0) {_r = 0;}
		if (_g < 0) {_g = 0;}
		if (_b < 0) {_b = 0;}
		
		return Color (_r, _g, _b, _special);
}

	private:
		double _r;
		double _g;
		double _b;
		double _special;
};