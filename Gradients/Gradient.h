#include <fstream>
#include <string>

class Gradient {
public:
	Gradient(std::string w, std::string h, std::string c1, std::string c2);
	void writeImage();

private:
	int width, height, color1, color2;
	std::string filename;

	void writeHeader(std::ostream&);
	unsigned char gradientAlgorithm(int, int, int);
};