#include "dataloader.h"


cData::cData() : imgName(" "), row(1), col(1) {}

cData::cData(std::string imgName, int row, int col) : imgName(imgName), row(row), col(col) {}


//returns a vector of cData that I can use in conjunction with
//populating my state_animations vector in a character class
std::vector<cData> loadData(std::string filename) {
	std::vector<cData> omegalul;
	std::string line, imgName;
	int row, col;
	std::ifstream myFile;
	myFile.open(filename);
	if (myFile.is_open()) {
		std::cout << "Opened!" << std::endl;
		std::cout << "Outputting contents" << std::endl;
		while (getline(myFile, line)) {
			std::cout << line << std::endl;
			std::istringstream iss(line);
			std::string g1, g2, g3;
			iss >> g1 >> imgName >> g2 >> row >> g3 >> col;

			omegalul.push_back(cData(imgName, row, col));
		}
	}
	else {
		std::cout << "Error loading contents!" << std::endl;
		omegalul.push_back(cData());
	}
	return omegalul;
}
