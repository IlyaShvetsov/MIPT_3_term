#pragma once
#include <string>
#include <vector>



class builder {
private:
	const char* alphabet;
	int alphabet_size;
	std::vector <int> prefix;
	std::vector <int> z;
	std::string text;

	void build_Z_from_prefix();
	void build_string_from_Z();

public:
	builder(std::vector <int>& _prefix);

	std::string getText() const;
};
