#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "builder.h"



int main() {
	std::ifstream inp("input.txt");
	std::ofstream out("output.txt");
	std::vector <int> prefix;
	int value;

	while (inp >> value)
		prefix.push_back(value);

	builder text_builder(prefix);
	out << text_builder.getText();

	inp.close();
	out.close();
	return 0;
}
