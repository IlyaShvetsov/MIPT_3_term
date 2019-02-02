#pragma once
#include <string>
#include <vector>



class bohr {
private:
	struct bohr_vertex {
		bool flag;                        
		int suff_link;						
		int good_suff_link;					
		int parent;							
		char symb;                          // symbol on the edge from parent to this vertex 
		std::vector <int> auto_move;        // memorization of the moving of the automate
		std::vector <int> next_vertex;		// number of vertex, that we come to by symbol 'i'
		int pattern_size;                   
		std::vector <int> pattern_pos;      // start position of pattern occurrence

		// constructor
		bohr_vertex(int _parent, char _symb) :
			parent(_parent), symb(_symb),
			flag(false), suff_link(-1),
			good_suff_link(-1),
			auto_move(ALPH_SIZE, -1),
			next_vertex(ALPH_SIZE, -1)
		{}
	};
	std::vector <bohr_vertex> vertices;
	std::string pattern;
	std::vector <int> pos;
	std::vector <int> pos_of_pattern;

	int add_pattern(const std::string& pattern);
	void add_string(const std::string& s, int pos);
	int get_auto_move(int v, char ch);
	int get_suff_link(int v);
	int get_good_suff_link(int v);
	void check(int v, int i);

public:
	bohr();
	vector <int> find_all_pos(const std::string& text, const std::string& pattern);
};