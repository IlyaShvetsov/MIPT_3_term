#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "substring_finder.h"
using std::string;
using std::vector;



// constructor
substring_finder::substring_finder(string& _pattern) :
	pattern_z(pattern.size()),
	pattern(_pattern)
{}



// find Z-function for the pattern
void substring_finder::find_pattern_z() {
	int left = 0, right = 0;
	for (int i = 1; i < pattern.size(); ++i) {
		if (i <= right)
			pattern_z[i] = std::min(right - i + 1, pattern_z[i - left]);
		else
			pattern_z[i] = 0;
		while (i + pattern_z[i] < pattern.size() && pattern[pattern_z[i]] == pattern[i + pattern_z[i]])
			++pattern_z[i];
		if (i + pattern_z[i] - 1 > right) {
			left = i;
			right = i + pattern_z[i] - 1;
		}
	}
}



// find Z-function for the main string
void substring_finder::find_z(vector <int>& ans) {
	int left = 0, right = 0, z = 0;
	// for (int i = 1; i <= str.size(); ++i)
	std::ifstream inp("input.txt");
	char c;   int i = 1;
	while (inp >> c) {
		if (i <= right)
			z = std::min(right - i + 1, pattern_z[i - left]);
		else
			z = 0;
		while (i + z <= str.size() && pattern[z] == str[i + z - 1])
			++z;
		if (i + z - 1 > right) {
			left = i;
			right = i + z - 1;
		}
		if (z == pattern.size())
			ans.push_back(i - 1);
		i++;
	}
}



// show all appearances of the pattern in the main string 
void substring_finder::getAnswer() {
	vector <int> ans;
	find_pattern_z();
	find_z(ans);
	for (int i = 0; i < ans.size(); ++i)
		std::cout << ans[i] << ' ';
}
