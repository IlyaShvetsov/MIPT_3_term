#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Aho_Corasick.h"



int main()
{
	std::ifstream inp("input.txt");
	std::string text, pattern;
	inp >> pattern >> text;

	bohr bohr;
	vector <int> ans = bohr.find_all_pos(text, pattern);

	for (int i = 0; i < ans.size(); ++i)
		std::cout << ans[i] << " ";

	inp.close();
	return 0;
}