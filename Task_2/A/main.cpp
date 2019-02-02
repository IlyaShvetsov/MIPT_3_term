#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::string;
using std::vector;
vector <long long> p;
vector <long long> lcp;



void suff_arr(string& text)
{
	text += '#';
	const long long n = static_cast<int>(text.size());
	const long long maxlen = n; // максимальная длина строки
	const long long alphabet = 256; // размер алфавита, <= maxlen

	p.resize(maxlen);
	vector <long long> c(maxlen), cnt(alphabet);
	for (long long i = 0; i < n; ++i)
		++cnt[text[i]];
	for (long long i = 1; i < alphabet; ++i)
		cnt[i] += cnt[i - 1];
	for (long long i = 0; i < n; ++i)
		p[--cnt[text[i]]] = i;
	c[p[0]] = 0;
	long long classes = 1;
	for (long long i = 1; i < n; ++i)
	{
		if (text[p[i]] != text[p[i - 1]])
			++classes;
		c[p[i]] = classes - 1;
	}

	vector <long long> pn(maxlen), cn(maxlen);
	for (long long h = 0; (1 << h) < n; ++h)
	{
		for (long long i = 0; i < n; ++i)
		{
			pn[i] = p[i] - (1 << h);
			if (pn[i] < 0)  pn[i] += n;
		}

		for (long long i = 0; i < classes; ++i)
			cnt[i] = 0;

		for (long long i = 0; i < n; ++i)
			++cnt[c[pn[i]]];
		for (long long i = 1; i < classes; ++i)
			cnt[i] += cnt[i - 1];
		for (long long i = n - 1; i >= 0; --i)
			p[--cnt[c[pn[i]]]] = pn[i];
		cn[p[0]] = 0;
		classes = 1;
		for (long long i = 1; i < n; ++i)
		{
			long long mid1 = (p[i] + (1 << h)) % n, mid2 = (p[i - 1] + (1 << h)) % n;
			if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2])
				++classes;
			cn[p[i]] = classes - 1;
		}

		for (long long i = 0; i < n; ++i)
			c[i] = cn[i];
	}
}



void buildLCP(string& text)
{
	long long n = static_cast<int>(text.size());
	lcp.resize(n);
	vector <long long> pos(n);  // pos[] — массив, обратный массиву suf 
	for (long long i = 0; i < n; ++i)
		pos[p[i]] = i;

	long long k = 0;
	for (long long i = 0; i < n; ++i)
	{
		if (k > 0)
			k--;
		if (pos[i] == n - 1)
		{
			lcp[n - 1] = -1;
			k = 0;
		}
		else
		{
			long long j = p[pos[i] + 1];
			while (std::max(i + k, j + k) < n && text[i + k] == text[j + k])
				k++;
			lcp[pos[i]] = k;
		}
	}
}



int main()
{
	string text;
	std::cin >> text;

	suff_arr(text);
	buildLCP(text);

	long long s = (static_cast<int>(text.size()) - 1) * (static_cast<int>(text.size()) - 1);
	for (long long i = 1; i < static_cast<int>(text.size()); ++i)
		s -= p[i];
	for (long long i = 1; i < static_cast<int>(text.size()) - 1; ++i)
		s -= lcp[i];
	std::cout << s << std::endl;

	return 0;
}