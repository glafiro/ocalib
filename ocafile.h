#pragma once

#include <fstream>
#include <sstream>
#include <string>

std::string ocaReadTextFile(std::string path) {
	std::ifstream myfile{ path };
	std::stringstream ss;
	std::string line;
	while (std::getline(myfile, line)) {
		ss << line << '\n';
	}

	return ss.str();
}