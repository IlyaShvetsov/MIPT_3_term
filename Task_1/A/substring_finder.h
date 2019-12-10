#pragma once
#include <vector>
#include <string>



class substring_finder {
private:
	std::string pattern;
	std::vector <int> pattern_z;

	void find_z(std::vector <int>& ans);    // find Z-function for the main string
	void find_pattern_z();                  // find Z-function for the pattern

public:
	substring_finder(std::string& _pattern);
	void getAnswer();                       // show all appearances of the pattern in the main string 
};
