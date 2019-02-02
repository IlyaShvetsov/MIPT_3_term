#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>



#define SMALL_NUM   0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)
#define norm(v)    sqrt(dot(v,v))  // norm = length of  vector
#define d(u,v)     norm(u-v)        // distance = norm of difference
#define abs(x)     ((x) >= 0 ? (x) : -(x))   //  absolute value



struct Vector
{
	double x, y, z;
	Vector operator+(const Vector& a)
	{
		Vector b;
		b.x = x + a.x;
		b.y = y + a.y;
		b.z = z + a.z;
		return b;
	}
	Vector operator-(const Vector& a)
	{
		Vector b;
		b.x = x - a.x;
		b.y = y - a.y;
		b.z = z - a.z;
		return b;
	}
	Vector operator*(double a)
	{
		Vector b;
		b.x = x*a;
		b.y = y*a;
		b.z = z*a;
		return b;
	}
	Vector(double x, double y, double z) : x(x), y(y), z(z) {}
	Vector() {}
};



struct Segment
{
	Vector P0, P1;
	Segment(Vector a, Vector b) : P0(a), P1(b) {}
};



double dist_segm_to_Segm(Segment S1, Segment S2)
{
	Vector u = S1.P1 - S1.P0;
	Vector v = S2.P1 - S2.P0;
	Vector w = S1.P0 - S2.P0;
	double  a = dot(u, u);         // always >= 0
	double  b = dot(u, v);
	double  c = dot(v, v);         // always >= 0
	double  d = dot(u, w);
	double  e = dot(v, w);
	double  D = a*c - b*b;        // always >= 0
	double  sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
	double  tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0

								  // compute the line parameters of the two closest points
	if (D <= SMALL_NUM) { // the lines are almost parallel
		sN = 0.0;         // force using point P0 on segment S1
		sD = 1.0;         // to prevent possible division by 0.0 later
		tN = e;
		tD = c;
	}
	else {                 // get the closest points on the infinite lines
		sN = (b*e - c*d);
		tN = (a*e - b*d);
		if (sN <= 0.0) {        // sc < 0 => the s=0 edge is visible
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN >= sD) {  // sc > 1  => the s=1 edge is visible
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN <= 0.0) {            // tc < 0 => the t=0 edge is visible
		tN = 0.0;
		// recompute sc for this edge
		if (-d <= 0.0)
			sN = 0.0;
		else if (-d >= a)
			sN = sD;
		else {
			sN = -d;
			sD = a;
		}
	}
	else if (tN >= tD) {      // tc > 1  => the t=1 edge is visible
		tN = tD;
		// recompute sc for this edge
		if ((-d + b) <= 0.0)
			sN = 0;
		else if ((-d + b) >= a)
			sN = sD;
		else {
			sN = (-d + b);
			sD = a;
		}
	}
	// finally do the division to get sc and tc
	sc = (abs(sN) <= SMALL_NUM ? 0.0 : sN / sD);
	tc = (abs(tN) <= SMALL_NUM ? 0.0 : tN / tD);

	// get the difference of the two closest points
	Vector dP = w + (u * sc) - (v * tc);  // =  S1(sc) - S2(tc)

	return norm(dP);   // return the closest distance
}



int main()
{
	double x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3 >> x4 >> y4 >> z4;

	Segment s1(Vector(x1, y1, z1), Vector(x2, y2, z2));
	Segment s2(Vector(x3, y3, z3), Vector(x4, y4, z4));

	double ans = dist_segm_to_Segm(s1, s2);

	std::cout << std::setprecision(10) << ans << std::endl;
	return 0;
}