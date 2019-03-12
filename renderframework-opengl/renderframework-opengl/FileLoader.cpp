#include "FileLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>


std::string loadTextFile(std::string path)
{
	std::ifstream fileStream;
	fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	fileStream.open(path);
	std::stringstream fileString;
	fileString << fileStream.rdbuf();
	fileStream.close();

	return fileString.str();
}
