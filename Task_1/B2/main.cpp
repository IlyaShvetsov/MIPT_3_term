#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "builder.h"



int main() {
	std::ifstream inp("input.txt");
	std::ofstream out("output.txt");
	std::vector <int> z;
	int value;

	while (inp >> value)
		z.push_back(value);

	builder text_builder(z);
	out << text_builder.getText();

	inp.close();
	out.close();
	return 0;
}
