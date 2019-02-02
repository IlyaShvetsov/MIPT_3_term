#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using std::vector;
using std::make_pair;
using std::min;
using std::max;



struct Vector3D {
	int x, y, z;
	Vector3D(int x, int y, int z) : x(x), y(y), z(z) {}
	Vector3D() {}
};

Vector3D operator+(const Vector3D& v, const Vector3D& u)
{
	return Vector3D(v.x + u.x, v.y + u.y, v.z + u.z);
}

Vector3D operator-(const Vector3D& v, const Vector3D& u)
{
	return Vector3D(v.x - u.x, v.y - u.y, v.z - u.z);
}

Vector3D operator-(const Vector3D& v)
{
	return Vector3D(-v.x, -v.y, -v.z);
}

int scalar_product(const Vector3D& v, const Vector3D& u)
{
	return v.x * u.x + v.y * u.y + v.z * u.z;
}

Vector3D cross_product(const Vector3D& v, const Vector3D& u)
{
	int a = v.y * u.z - v.z * u.y;
	int b = v.z * u.x - v.x * u.z;
	int c = v.x * u.y - v.y * u.x;
	return Vector3D(a, b, c);
}



class ConvexHull {
private:

	class MatrixGraph {
	private:
		vector <vector <char> > edges;
		int verticesCount;

	public:
		explicit MatrixGraph(int verticesCount);

		void AddEdge(int from, int to);
		void DeleteEdge(int from, int to);
		char GetEdge(int from, int to);
	};

	struct Face {
		short point[3];
		Vector3D norm; // вектор нормали

		Face() {}
		Face(int first, int second, int third, const vector <Vector3D>& vertices);
		bool operator<(const Face& other);
	};

	vector <Vector3D> vertices;
	vector <Face> faces;
	MatrixGraph graph;

	void addFace(int first, int second, int third, int fourth);
	void build();

public:
	ConvexHull(vector <Vector3D>& points);
	void ShowFaces();
};



ConvexHull::MatrixGraph::MatrixGraph(int verticesCount) :
	verticesCount(verticesCount),
	edges(verticesCount - 1)
{
	for (int i = 0; i < verticesCount - 1; ++i)
		edges[i] = vector <char>(verticesCount - i - 1, 0);
}

void ConvexHull::MatrixGraph::AddEdge(int from, int to)
{
	if (from < to)
		edges[from][verticesCount - to - 1]++;
	else
		edges[to][verticesCount - from - 1]++;
}

void ConvexHull::MatrixGraph::DeleteEdge(int from, int to)
{
	if (from < to)
		edges[from][verticesCount - to - 1]--;
	else
		edges[to][verticesCount - from - 1]--;
}

char ConvexHull::MatrixGraph::GetEdge(int from, int to)
{
	if (from < to)
		return edges[from][verticesCount - to - 1];
	else
		return edges[to][verticesCount - from - 1];
}



ConvexHull::Face::Face(int first, int second, int third, const vector <Vector3D>& vertices)
{
	point[0] = min(min(first, second), third);
	point[2] = max(max(first, second), third);
	point[1] = first + second + third - point[0] - point[2];

	Vector3D v = vertices[point[1]] - vertices[point[0]];
	Vector3D u = vertices[point[2]] - vertices[point[0]];
	norm = cross_product(v, u);
}



bool ConvexHull::Face::operator<(const Face& other)
{
	if (point[0] < other.point[0])
		return true;

	if (point[0] == other.point[0] && point[1] < other.point[1])
		return true;

	if (point[0] == other.point[0] && point[1] == other.point[1] && point[2] <= other.point[2])
		return true;

	return false;
}



void ConvexHull::ShowFaces()
{
	std::cout << faces.size() << std::endl;
	for (int j = 0; j < faces.size(); ++j)
	{
		std::cout << "3 ";
		std::cout << faces[j].point[0] << ' ';
		std::cout << faces[j].point[1] << ' ';
		std::cout << faces[j].point[2] << ' ';
		std::cout << std::endl;
	}
}



ConvexHull::ConvexHull(vector <Vector3D>& points) :
	graph(points.size()),
	vertices(points)
{
	build();
}



void ConvexHull::addFace(int first, int second, int third, int fourth)
{
	Face face(first, second, third, vertices);
	Vector3D v = vertices[fourth] - vertices[face.point[0]];
	if (scalar_product(v, face.norm) > 0)
	{
		face.norm = -face.norm;
		std::swap(face.point[1], face.point[2]);
	}

	graph.AddEdge(face.point[0], face.point[1]);
	graph.AddEdge(face.point[0], face.point[2]);
	graph.AddEdge(face.point[1], face.point[2]);

	faces.push_back(face);
}



void ConvexHull::build()
{
	// строим ConvexHull по первым 4 точкам
	for (int i = 0; i < 4; ++i)
		for (int j = i + 1; j < 4; ++j)
			for (int k = j + 1; k < 4; ++k)
				addFace(i, j, k, 6 - i - j - k);

	// добавляем по одной точке
	for (int i = 4; i < vertices.size(); i++)
	{
		vector <std::pair <short, short> > updated_edges; // ребра, которые мы меняем
		for (int j = 0; j < faces.size(); ++j)
		{
			Face face = faces[j];
			Vector3D l = vertices[i] - vertices[face.point[0]];
			if (scalar_product(face.norm, l) > 0)
			{
				graph.DeleteEdge(face.point[0], face.point[1]);
				graph.DeleteEdge(face.point[0], face.point[2]);
				graph.DeleteEdge(face.point[1], face.point[2]);

				updated_edges.emplace_back(make_pair(face.point[0], face.point[1]));
				updated_edges.emplace_back(make_pair(face.point[1], face.point[2]));
				updated_edges.emplace_back(make_pair(face.point[2], face.point[0]));
				faces[j] = faces.back();
				j--;
				faces.resize(faces.size() - 1);
			}
		}
		for (int j = 0; j < updated_edges.size(); ++j)
		{
			if (graph.GetEdge(updated_edges[j].first, updated_edges[j].second) == 1)
			{
				int k;
				for (k = 0; k == i || k == updated_edges[j].first || k == updated_edges[j].second; ++k);

				addFace(updated_edges[j].first, updated_edges[j].second, i, k);
			}
		}
	}

	std::sort(faces.begin(), faces.end());
}



int main()
{
	int m, n;
	std::cin >> m;
	for (int i = 0; i < m; ++i)
	{
		std::cin >> n;
		int x, y, z;
		vector <Vector3D> points;
		for (int j = 0; j < n; ++j)
		{
			std::cin >> x >> y >> z;
			points.emplace_back(Vector3D(x, y, z));
		}
		ConvexHull hull(points);
		hull.ShowFaces();
	}

	return 0;
}