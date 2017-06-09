#include <Windows.h>
#include <iostream>
#include "Gradient.h"

Gradient::Gradient(std::string w, std::string h, std::string c1, std::string c2) {
	filename = c1 + "_to_" + c2 + "_" + w + "x" + h + ".bmp";
	width = std::stoi(w);
	height = std::stoi(h);
	color1 = std::stoi(c1, 0, 16);
	color2 = std::stoi(c2, 0, 16);
}

void Gradient::writeHeader(std::ostream& file) {
	BITMAPFILEHEADER bFH;
	bFH.bfType = 0x4d42;
	bFH.bfSize = 54 + (width*height * 3);
	bFH.bfReserved1 = 0;
	bFH.bfReserved2 = 0;
	bFH.bfOffBits = 54;

	BITMAPINFOHEADER bIH;
	bIH.biSize = sizeof(BITMAPINFOHEADER);
	bIH.biWidth = width;
	bIH.biHeight = height;
	bIH.biPlanes = 1;
	bIH.biBitCount = 24;
	bIH.biCompression = BI_RGB;
	bIH.biSizeImage = width * height * 3;

	file.write((char*)(&bFH), 14);
	file.write((char*)(&bIH), 40);
}

void Gradient::writeImage() {
	int color1arr[3] = { (color1 & 0xFF0000) >> 16, (color1 & 0x00FF00) >> 8, color1 & 0x0000FF }; //Stored as RGB
	int color2arr[3] = { (color2 & 0xFF0000) >> 16, (color2 & 0x00FF00) >> 8, color2 & 0x0000FF }; 

	std::ofstream file;
	file.open(filename, std::ios::binary);
	if (file.is_open()) {
		std::cout << "Writing to " << filename;
		writeHeader(file);

		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				file << gradientAlgorithm(color1arr[2], color2arr[2], col); //Written as BGR
				file << gradientAlgorithm(color1arr[1], color2arr[1], col);
				file << gradientAlgorithm(color1arr[0], color2arr[0], col);
			}
		}

		file.close();
		std::cout << "Wrote to " << filename;
	}
	else {
		std::cout << "\nProblem creating file " + filename + ".\nVerify that the 'Output' folder is located with the program.";
		getchar();
	}
}

unsigned char Gradient::gradientAlgorithm(int pColor1, int pColor2, int col) {
	float diff = abs(pColor1 - pColor2) / ((float)width / ((float)col + 0.1));
	if (pColor1 > pColor2)	return (unsigned char)(pColor1 - diff);
	else					return (unsigned char)(pColor1 + diff);
}
