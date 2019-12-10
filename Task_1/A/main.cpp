#include <iostream>
#include <fstream>
#include <string>
#include "substring_finder.h"



int main() {
	std::string pattern;
	std::ifstream inp("input.txt");
	inp >> pattern;
	substring_finder finder(pattern);
	finder.getAnswer();

	return 0;
}
