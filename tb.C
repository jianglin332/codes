#include <cstdio>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;
#define POL 1
#define REC 2
#define pi 3.1415926535897932
#define eps 1e-8
inline bool iz(const double a)
{
	return a >= -eps && a <= eps;
}
struct vect
{
	double x, y, r, theta;
	int pol;
	void upd()
	{
		if (pol == POL)
		{
			x = r * cos(theta);
			y = r * sin(theta);
		}
		else if (pol == REC)
		{
			r = sqrt(x * x + y * y);
			theta = atan2(y, x);
			if (theta < 0)
				theta += 2 * pi;
		}
		pol = 3;
	}
	vect(){}
	vect(double a, double b, int p = REC)
	{
		pol = p;
		if (pol == REC)
			x = a, y = b;
		if (pol == POL)
			r = a, theta = b;
		upd();
	}
	bool operator<(const vect &a) const
	{
		if (y < a.y)
			return true;
		if (y > a.y)
			return false;
		if (x < a.x)
			return true;
		return false;
	}
	vect operator+(const vect &a) const
	{
		return vect(x + a.x, y + a.y);
	}
	vect operator-(const vect &a) const
	{
		return vect(x - a.x, y - a.y);
	}
}ps[12];
typedef vect point;
bool cmp(const point &a, const point &b)
{
	return a.theta < b.theta;
}
inline double dist(point a, point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		ps[i] = vect(a, b);
	}
	ps[11] = vect(10000, 10000);
	int lt = 11;
	for (int i = 0; i < n; i++)
		if (ps[i] < ps[lt])
			lt = i;
	swap(ps[0], ps[lt]);
	for (int i = 1; i < n; i++)
		ps[i] = ps[i] - ps[0];
	sort(ps + 1, ps + n, cmp);
	stack<point> sp;
	sp.push(vect(0, 0));
	sp.push(ps[1]);
	for (int i = 2; i < n; i++)
	{
		point tp = sp.top();
		point now = ps[i];
		if (iz(tp.theta - now.theta))
		{
			if (tp.r < now.r)
			{
				sp.pop();
				sp.push(now);
			}
			else
				continue;
		}
		while (1)
		{
			sp.pop();
			point ls = sp.top();
			if ((now - tp).theta < (tp - ls).theta + eps)
			{
				tp = ls;
			}
			else
			{
				sp.push(tp);
				sp.push(now);
				break;
			}
		}
	}
	point tp = vect(0, 0);
	double dt = 0;
	while (!sp.empty())
	{
		dt += dist(tp, sp.top());
		tp = sp.top();
		printf("%d %d\n", (int)((ps[0] + tp).x), (int)((ps[0] + tp).y));
		sp.pop();
	}
	printf("LENGTH=%.2lf", dt);
	return 0;
}
