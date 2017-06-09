#include <iostream>
#include "Gradient.h"

int main(int argc, char* argv[]) {
	std::cout << ".============== Gradient Creator ===============.\n"
		<< "| Creates simple left to right gradient bitmaps |\n"
		<< "|          using specified hex colors.          |\n" 
		<< "'==============================================='\n\n";

	std::string w, h;
	std::cout << "Enter image dimensions: \n";

	for (;;) {
		std::cout << "Width (default 500): ";
		getline(std::cin, w);
		if (w.size() == 0 || isalpha(w[0])) w = "500";
		else if (std::stoi(w) % 4 != 0) {
			std::cout << "Must be a multiple of 4\n";
			continue;
		}
		break;
	}
	for (;;) {
		std::cout << "Height (default 500): ";
		getline(std::cin, h);
		if (h.size() == 0 || isalpha(h[0])) h = "500";
		else if (std::stoi(h) % 4 != 0) {
			std::cout << "Must be a multiple of 4\n";
			continue;
		}
		break;
	}

	std::cout << "Enter two colors (RGB Hex) for gradient: \n";
	std::string color1, color2;
	getline(std::cin, color1);
	getline(std::cin, color2);
	if (color1[0] == '#') color1 = color1.substr(1);
	if (color2[0] == '#') color2 = color2.substr(1);

	Gradient gradient(w, h, color1, color2);
	gradient.writeImage();

	return 0;
}