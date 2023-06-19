
#include <fstream>
#include <sstream>
#include <string>
using std::string;

#include "ocalib.h"

string ocaReadTextFile(string path) {
	std::ifstream myfile{ path };
	std::stringstream ss;
	string line;
	while (std::getline(myfile, line)) {
		ss << line << '\n';
	}

	return ss.str();
}

