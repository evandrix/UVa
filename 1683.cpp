#include <bits/stdc++.h>

using namespace std;

#define eps 1e-8
#define MAXN (1048576)
#define MAXV 262144
struct Point
{
	double x, y;
	int id;
	Point(double a = 0, double b = 0, int c = -1) : x(a), y(b), id(c) {}
	Point operator-(const Point &a) const
	{
		return Point(x - a.x, y - a.y);
	}
	Point operator+(const Point &a) const
	{
		return Point(x + a.x, y + a.y);
	}
	Point operator*(const double a) const
	{
		return Point(x * a, y * a);
	}
	Point operator/(const double a) const
	{
		return Point(x / a, y / a);
	}
	bool operator<(const Point &a) const
	{
		if (fabs(x - a.x) > eps)
			return x < a.x;
		if (fabs(y - a.y) > eps)
			return y < a.y;
		return false;
	}
	bool operator==(const Point &a) const
	{
		return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	}
	bool operator!=(const Point &a) const
	{
		return !(fabs(x - a.x) < eps && fabs(y - a.y) < eps);
	}
	void read(int id = -1)
	{
		this->id = id;
	}
	double dist(Point b)
	{
		return hypot(x - b.x, y - b.y);
	}
	double dist2(Point b)
	{
		return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
	}
	void print()
	{
		printf("point (%lf, %lf)\n", x, y);
	}
};
struct Point3D
{
	double x, y, z;
	Point3D(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) {}
	Point3D(Point p)
	{
		x = p.x, y = p.y, z = p.x * p.x + p.y * p.y;
	}
	Point3D operator-(const Point3D &a) const
	{
		return Point3D(x - a.x, y - a.y, z - a.z);
	}
	double dot(Point3D a)
	{
		return x * a.x + y * a.y + z * a.z;
	}
};
struct Edge
{
	int id;
	list<Edge>::iterator twin;
	Edge(int id = 0)
	{
		this->id = id;
	}
};

int cmpZero(double v)
{
	if (fabs(v) > eps)
		return v > 0 ? 1 : -1;
	return 0;
}

double cross(Point o, Point a, Point b)
{
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
Point3D cross(Point3D a, Point3D b)
{// normal vector
	return Point3D(a.y * b.z - a.z * b.y, -a.x * b.z + a.z * b.x, a.x * b.y - a.y * b.x);
}
int inCircle(Point a, Point b, Point c, Point p)
{
	if (cross(a, b, c) < 0)
		swap(b, c);
	Point3D a3(a), b3(b), c3(c), p3(p);
	//	printf("%lf %lf %lf\n", a3.x, a3.y, a3.z);
	//	printf("%lf %lf %lf\n", b3.x, b3.y, b3.z);
	//	printf("%lf %lf %lf\n", c3.x, c3.y, c3.z);
	//	printf("%lf %lf %lf\n", p3.x, p3.y, p3.z);
	b3 = b3 - a3, c3 = c3 - a3, p3 = p3 - a3;
	Point3D f = cross(b3, c3);// normal vector
	return cmpZero(p3.dot(f));// check same direction, in: < 0, on: = 0, out: > 0
}
int intersection(Point a, Point b, Point c, Point d)
{// seg(a, b) and seg(c, d)
	return cmpZero(cross(a, c, b)) * cmpZero(cross(a, b, d)) > 0 && cmpZero(cross(c, a, d)) * cmpZero(cross(c, d, b)) > 0;
}
class Delaunay
{
public:
	list<Edge> head[MAXV];// graph
	Point p[MAXV];
	int n, rename[MAXV];
	void init(int n, Point p[])
	{
		for (int i = 0; i < n; i++)
			head[i].clear();
		for (int i = 0; i < n; i++)
			this->p[i] = p[i];
		sort(this->p, this->p + n);
		for (int i = 0; i < n; i++)
			rename[p[i].id] = i;
		this->n = n;
		divide(0, n - 1);
	}
	void addEdge(int u, int v)
	{
		head[u].push_front(Edge(v));
		head[v].push_front(Edge(u));
		head[u].begin()->twin = head[v].begin();
		head[v].begin()->twin = head[u].begin();
	}
	void divide(int l, int r)
	{
		if (r - l <= 2)
		{// #point <= 3
			for (int i = l; i <= r; i++)
				for (int j = i + 1; j <= r; j++)
					addEdge(i, j);
			return;
		}
		int mid = (l + r) / 2;
		divide(l, mid);
		divide(mid + 1, r);

		list<Edge>::iterator it;
		int nowl = l, nowr = r;

		//		printf("divide %d %d\n", l, r);
		for (int update = 1; update;)
		{// find left and right convex, lower common tangent
			update = 0;
			Point ptL = p[nowl], ptR = p[nowr];
			for (it = head[nowl].begin(); it != head[nowl].end(); it++)
			{
				Point t = p[it->id];
				double v = cross(ptR, ptL, t);
				if (cmpZero(v) > 0 || (cmpZero(v) == 0 && ptR.dist2(t) < ptR.dist2(ptL)))
				{
					nowl = it->id, update = 1;
					break;
				}
			}
			if (update)
				continue;
			for (it = head[nowr].begin(); it != head[nowr].end(); it++)
			{
				Point t = p[it->id];
				double v = cross(ptL, ptR, t);
				if (cmpZero(v) < 0 || (cmpZero(v) == 0 && ptL.dist2(t) < ptL.dist2(ptR)))
				{
					nowr = it->id, update = 1;
					break;
				}
			}
		}

		addEdge(nowl, nowr);// add tangent
		//		printf("add base %d %d\n", nowl, nowr);
		for (int update = 1; true;)
		{
			update = 0;
			Point ptL = p[nowl], ptR = p[nowr];
			int ch = -1, side = 0;
			for (it = head[nowl].begin(); it != head[nowl].end(); it++)
			{
				//				ptL.print(), ptR.print(), p[it->id].print();
				if (cmpZero(cross(ptL, ptR, p[it->id])) > 0 && (ch == -1 || inCircle(ptL, ptR, p[ch], p[it->id]) < 0))
					ch = it->id, side = -1;
				//				printf("test L %d %d %d\n", nowl, it->id, inCircle(ptL, ptR, p[ch], p[it->id]));
			}
			for (it = head[nowr].begin(); it != head[nowr].end(); it++)
			{
				if (cmpZero(cross(ptR, p[it->id], ptL)) > 0 && (ch == -1 || inCircle(ptL, ptR, p[ch], p[it->id]) < 0))
					ch = it->id, side = 1;
				//				printf("test R %d %d %d\n", nowr, it->id, inCircle(ptL, ptR, p[ch], p[it->id]));
			}
			if (ch == -1)
				break;// upper common tangent
			//			printf("choose %d %d\n", ch, side);
			if (side == -1)
			{
				for (it = head[nowl].begin(); it != head[nowl].end();)
				{
					if (intersection(ptL, p[it->id], ptR, p[ch]))
					{
						head[it->id].erase(it->twin);
						head[nowl].erase(it++);
					}
					else
						it++;
				}
				nowl = ch;
				addEdge(nowl, nowr);
			}
			else
			{
				for (it = head[nowr].begin(); it != head[nowr].end();)
				{
					if (intersection(ptR, p[it->id], ptL, p[ch]))
					{
						head[it->id].erase(it->twin);
						head[nowr].erase(it++);
					}
					else
						it++;
				}
				nowr = ch;
				addEdge(nowl, nowr);
			}
		}
	}

	vector<pair<int, int>> getEdge()
	{
		vector<pair<int, int>> ret;
		list<Edge>::iterator it;
		for (int i = 0; i < n; i++)
		{
			for (it = head[i].begin(); it != head[i].end(); it++)
			{
				if (it->id < i)
					continue;
				//				printf("DG %d %d\n", i, it->id);
				ret.push_back(make_pair(p[i].id, p[it->id].id));
			}
		}
		return ret;
	}
} tool;
#define INF (1LL << 60)
Point p[MAXV];
long long ret[MAXV];
int main()
{
	int testcase, n;
	long long x, y;
	scanf("%d", &testcase);
	while (testcase--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			scanf("%lld %lld", &x, &y);
			p[i] = Point(x, y, i);
		}
		tool.init(n, p);
		vector<pair<int, int>> DG = tool.getEdge();
		for (int i = 0; i < n; i++)
		{
			ret[i] = INF;
		}
		for (int i = 0; i < DG.size(); i++)
		{
			x = DG[i].first, y = DG[i].second;
			long long v = (long long)(p[x].x - p[y].x) * (long long)(p[x].x - p[y].x) +
										(long long)(p[x].y - p[y].y) * (long long)(p[x].y - p[y].y);
			ret[x] = min(ret[x], v);
			ret[y] = min(ret[y], v);
		}
		for (int i = 0; i < n; i++)
		{
			printf("%lld\n", ret[i]);
		}
	}
	return 0;
}
/*
 2
 10
 17 41
 0 34
 24 19
 8 28
 14 12
 45 5
 27 31
 41 11
 42 45
 36 27
 15
 0 0
 1 2
 2 3
 3 2
 4 0
 8 4
 7 4
 6 3
 6 1
 8 0
 11 0
 12 2
 13 1
 14 2
 15 0
 */
