#include <string>
#include <vector>
#include "Aho_Corasick.h"
using std::string;
using std::vector;

const int ALPH_SIZE = 26;



// constructor
bohr::bohr()
{
	// add root
	vertices.push_back(bohr_vertex(0, 0));
}



// split pattern by '?' and return count of patterns
int bohr::add_pattern(const string& pattern)
{
	int count = 0;
	pos.push_back(0);
	for (int i = 0; i < pattern.size(); ++i)
		if (pattern[i] == '?')
		{
			count++;
			pos.push_back(i + 1);
		}

	vector <string> patterns(count + 1);
	count = 0;
	for (int i = 0; i < pattern.size(); ++i)
		if (pattern[i] == '?')
			count++;
		else
			patterns[count] += pattern[i];

	// if pattern[i] is empty than add 1 to all pos_of_all_pattern[] 
	pos_of_pattern.push_back(0);
	for (int i = 0; i < patterns.size(); ++i)
	{
		add_string(patterns[i], pos[i]);
		if (patterns[i] == "")
			pos_of_pattern[0]++;
	}
	
	return count + 1;
}



// add new string to bohr
void bohr::add_string(const string& str, int pos)
{
	int num = 0; // starts from root 
	for (int i = 0; i < str.size(); ++i)
	{
		char ch = str[i] - 'a'; 
		if (vertices[num].next_vertex[ch] == -1)
		{
			vertices.push_back(bohr_vertex(num, ch));
			vertices[num].next_vertex[ch] = vertices.size() - 1;
		}
		num = vertices[num].next_vertex[ch];
	}
	vertices[num].flag = true;
	vertices[num].pattern_size = str.size();
	vertices[num].pattern_pos.push_back(pos);
}



// getting of the suffix link
int bohr::get_suff_link(int vert)
{
	if (vertices[vert].suff_link == -1)			
		if (vert == 0 || vertices[vert].parent == 0)
			vertices[vert].suff_link = 0;
		else
			vertices[vert].suff_link = get_auto_move(get_suff_link(vertices[vert].parent), vertices[vert].symb);
	return vertices[vert].suff_link;
}



// getting of the automate moving
int bohr::get_auto_move(int vert, char ch)
{
	if (vertices[vert].auto_move[ch] == -1)
		if (vertices[vert].next_vertex[ch] != -1)
			vertices[vert].auto_move[ch] = vertices[vert].next_vertex[ch];
		else
			if (vert == 0)
				vertices[vert].auto_move[ch] = 0;
			else
				vertices[vert].auto_move[ch] = get_auto_move(get_suff_link(vert), ch);
	return vertices[vert].auto_move[ch];
}



// getting of the good suffix link
int bohr::get_good_suff_link(int vert)
{
	if (vertices[vert].good_suff_link == -1)
	{
		int u = get_suff_link(vert);
		if (u == 0)	
			vertices[vert].good_suff_link = 0;
		else
			vertices[vert].good_suff_link = (vertices[u].flag) ? u : get_good_suff_link(u);
	}
	return vertices[vert].good_suff_link;
}




// procedure for walking on a "good" suffix links
void bohr::check(int vert, int i)
{
	for (int u = vert; u != 0; u = get_good_suff_link(u))
		if (vertices[u].flag)
		{
			int position = i - vertices[u].pattern_pos[0] + 1;
			for (int i = 0; i < vertices[u].pattern_pos.size(); ++i)
				if (position - vertices[u].pattern_size >= 0)
					pos_of_pattern[position - vertices[u].pattern_size]++;
		}
}



// find all appearances of the pattern in the main string 
vector <int> bohr::find_all_pos(const string& text, const string& pattern)
{
	vector <int> ans;

	int count_of_patterns = add_pattern(pattern);
	pos_of_pattern.assign(text.size(), pos_of_pattern[0]);

	int vert = 0;
	for (int i = 0; i < text.size(); ++i)
	{
		vert = get_auto_move(vert, text[i] - 'a');
		check(vert, i);
	}
	for (int i = 0; i < static_cast<int>(text.size()) - static_cast<int>(pattern.size()) + 1; ++i)
		if (pos_of_pattern[i] == count_of_patterns)
			ans.push_back(i);

	return ans;
}