// �� �������� � ��������� (����� ���� - (0,0), { (-1, -1), (1, 1) }

#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <vector>
using std::vector;



struct Point
{
	double x;
	double y;
	Point(double x, double y) : x(x), y(y) {}
	Point() {}
	Point operator+(const Point& a)
	{
		return Point(x + a.x, y + a.y);
	}
};



// векторное произведение
double rotate(Point a, Point b, Point c)
{
	return (b.x - a.x)*(c.y - b.y) - (b.y - a.y)*(c.x - b.x);
}



bool intersect(Point a, Point b, Point c, Point d)
{
	return (rotate(a, b, c)*rotate(a, b, d) <= 0) && (rotate(c, d, a)*rotate(c, d, b) < 0);
}



// первым элементом делает самый нижний (среди них берет самый левый)
void Y_sort_vector(vector <Point>& p)
{
	double min = p[0].y, min_x = p[0].x;
	int index, n = p.size();
	for (int i = 1; i < n; ++i)
		if (p[i].y < min)
		{
			min = p[i].y;
			min_x = p[i].x;
		}
	for (int i = 0; i < n; ++i)
		if (p[i].y == min && p[i].x <= min_x)
		{
			min_x = p[i].x;
			index = i;
		}

	vector <Point> tmp = p;
	for (int i = 0; i < n; ++i)
	{
		p[i] = tmp[index];
		index = (index + 1) % n;
	}
}



double dist(Point a, Point b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}



bool is_point_inside_polygon(const Point& point, vector <Point>& polygon)
{
	int n = polygon.size();

	if (rotate(polygon[0], polygon[1], point) == 0)
		if ((dist(polygon[0], point) > dist(polygon[0], polygon[1])) || (dist(polygon[1], point) > dist(polygon[0], polygon[1])))
			return false;
	if (rotate(polygon[0], polygon[1], point) < 0 || rotate(polygon[0], polygon[n - 1], point) > 0)
		return false;

	int l = 1, r = n - 1;
	while (r - l > 1)
	{
		int q = (l + r) / 2;
		if (rotate(polygon[0], polygon[q], point) < 0)
			r = q;
		else
			l = q;
	}
	return !intersect(polygon[0], point, polygon[l], polygon[r]);
}



double angle(Point& a, Point& b)
{
	double tan = std::atan2(b.y - a.y, b.x - a.x);
	return tan >= 0 ? tan : tan + 2 * 4; // PI = 4
}



void build_Minkowski(const vector <Point>& first, const vector <Point>& second, vector <Point>& Minkowski)
{
	int i = 0, j = 0;
	int n = first.size();
	int m = second.size();
	vector <Point> V(n), W(m);
	for (int i = 0; i < n; ++i)
		V[i] = first[i];
	for (int i = 0; i < m; ++i)
		W[i] = second[i];

	V.push_back(V[0]);
	V.push_back(V[1]);
	W.push_back(W[0]);
	W.push_back(W[1]);
	while (i <= n && j <= m)
	{
		Minkowski.push_back(V[i] + W[j]);
		if (angle(V[i], V[i + 1]) < angle(W[j], W[j + 1]))
			++i;
		else
			if (angle(V[i], V[i + 1]) > angle(W[j], W[j + 1]))
				++j;
			else
			{
				++i;
				++j;
			}
	}
}



int main()
{
	int n, m;
	double x, y;
	std::ifstream inp("input.txt");
	inp >> n;
	vector <Point> first(n);
	for (int i = n - 1; i >= 0; --i)  // reverse
	{
		inp >> x >> y;
		first[i] = Point(x, y);
	}
	inp >> m;
	vector <Point> second(m);
	for (int i = m - 1; i >= 0; --i)  // reverse
	{
		inp >> x >> y;
		second[i] = Point(-x, -y);
	}

	bool result;
	Y_sort_vector(first);
	Y_sort_vector(second);
	vector <Point> Minkowski;
	build_Minkowski(first, second, Minkowski);

	// проверяем, что (0, 0) лежит в получившемся многоугольнике
	Point p(0, 0);
	result = is_point_inside_polygon(p, Minkowski);

	std::cout << (result ? "YES" : "NO") << std::endl;
	inp.close();
	return 0;
}