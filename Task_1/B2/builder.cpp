#include <string>
#include <vector>
#include <algorithm>
#include "builder.h"
using std::string;
using std::vector;



// construct Z-function from a string
void build_z(string& text, vector <int>& z)
{
	int left = 0, right = 0;
	z.resize(text.size());
	for (int i = 1; i < z.size(); ++i)
	{
		if (i <= right)
			z[i] = std::min(right - i + 1, z[i - left]);
		else
			z[i] = 0;
		while (i + z[i] < text.size() && text[z[i]] == text[i + z[i]])
			z[i]++;
		if (i + z[i] - 1 > right)
		{
			left = i;
			right = i + z[i] - 1;
		}
	}
}



// construct string from Z-function
void builder::build_string_from_Z()
{
	int prefixLength = 0;    // length of prefix that we will write
	int pos;                 // position of a symbol that we will write
	text += 'a';
	for (int i = 1; i < z.size(); ++i)
	{
		if (z[i] == 0 && prefixLength == 0)
			for (int j = 0; j < 26; ++j)
			{
				string tmp = text + alphabet[j];   // try to add a symbol
				vector <int> tmp_z;
				build_z(tmp, tmp_z);               // check if the string is suitable
				bool ok = true;
				for (int k = 1; k < tmp_z.size(); ++k)
					if (tmp_z[k] != z[k])
						ok = false;
				if (ok)
				{
					text += alphabet[j];
					break;
				}
			}

		if (z[i] >= prefixLength)
		{
			prefixLength = z[i];
			pos = 0;
		}
		if (prefixLength > 0)
		{
			text += text[pos];
			pos++;
			prefixLength--;
		}
	}
}



// constructor
builder::builder(vector <int>& _prefix) :
	prefix(_prefix),
	alphabet("abcdefghijklmnopqrstuvwxyz"),
	alphabet_size(26)
{
	build_string_from_Z();
}



// give answer
string builder::getText() const
{
	return text;
}