// этот метод работает только для 2D
// для 3D не катит :(
/*

#include <iostream>
#include <fstream>
#include <algorithm>


struct Point
{
	int x, y, z;
	Point(int _x, int _y, int _z) :
		x(_x), y(_y), z(_z) {}
};



struct Segment
{
	Point a, b;
	float len;
	Segment(Point _a, Point _b) :
		len(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2))),
		a(_a), b(_b) {}
};



float vector_mult(Point a, Point b, Point c, Point d)
{
	float x1 = b.x - a.x, x2 = d.x - c.x;
	float y1 = b.y - a.y, y2 = d.y - c.y;
	float z1 = b.z - a.z, z2 = d.z - c.z;
	return sqrt(pow(y1*z2 - z1*y2, 2) + pow(x1*z2 - x2*z1, 2) + pow(x1*y2 - y1*x2, 2));
}



float scalar_mult(Point a, Point b, Point c, Point d)
{
	float x1 = b.x - a.x, x2 = d.x - c.x;
	float y1 = b.y - a.y, y2 = d.y - c.y;
	float z1 = b.z - a.z, z2 = d.z - c.z;
	return x1*x2 + y1*y2 + z1*z2;
}



float dist_from_point_to_seg(Point a, Segment seg)
{
	return vector_mult(a, seg.a, a, seg.b) / seg.len;
}



float dist_between_points(Point a, Point b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}



int main()
{
	float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	std::ifstream inp("input.txt");
	inp >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3 >> x4 >> y4 >> z4;
	Point a(x1, y1, z1);
	Point b(x2, y2, z2);
	Point c(x3, y3, z3);
	Point d(x4, y4, z4);
	Segment seg1(a, b);
	Segment seg2(c, d);
	float ans1 = std::min(dist_from_point_to_seg(a, seg2), dist_from_point_to_seg(b, seg2));
	float ans2 = std::min(dist_from_point_to_seg(c, seg1), dist_from_point_to_seg(d, seg1));
	float dist1 = dist_between_points(a, c);
	float dist2 = dist_between_points(a, d);
	float dist3 = dist_between_points(b, c);
	float dist4 = dist_between_points(b, d);
	std::cout << dist1 << ' ' << dist2 << ' ' << dist3 << ' ' << dist4 << std::endl;

	std::cout << ans1 << std::endl << ans2 << std::endl;
	system("pause");
	return 0;
}

*/