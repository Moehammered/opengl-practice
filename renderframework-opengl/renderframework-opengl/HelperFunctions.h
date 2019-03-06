#ifndef HELPERFUNCTIONS__H_
#define HELPERFUNCTIONS__H_

#include <string>
#include <iostream>

void printLine(std::string &message)
{
	std::cout << message << std::endl;
}

void printLine(std::string message)
{
	std::cout << message << std::endl;
}

#endif