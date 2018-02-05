#include <cstdio>
#include <queue>
#define o(x, y) (((x) << 7) | (y))
using namespace std;
struct state
{
	int x, y, p;
	state(){}
	state(int xx, int yy, int pp):x(xx), y(yy), p(pp){}
};
state its(int a)
{
	state ret;
	ret.p = (a & 127);
	a >>= 7;
	ret.y = (a & 127);
	a >>= 7;
	ret.x = (a & 127);
	return ret;
}
int sti(state a)
{
	int ret = a.x;
	ret <<= 7;
	ret |= a.y;
	ret <<= 7;
	ret |= a.p;
	return ret;
}
int n, m, c;
int bl[1 << 15];
bool vd[1 << 21];
int h[1 << 21];
int os[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
inline bool chk(state a)
{
	return (a.x <= n && a.y <= n && a.x > 0 && a.y > 0 && a.p > 0 && !vd[sti(a)]);
}
int main()
{
	scanf("%d%d%d", &n, &m, &c);
	for (int i = 0; i < m; i++)
	{
		int d, e, f;
		scanf("%d%d%d", &d, &e, &f);
		bl[o(d, e)] = f;
	}
	queue<int> q;
	q.push(sti(state(1, 1, c)));
	vd[sti(state(1, 1, c))] = 1;
	while (!q.empty())
	{
		state now = its(q.front());
		int nh = h[q.front()] + 1;
		for (int i = 0; i < 4; i++)
		{
			state nw(now.x + os[i][0], now.y + os[i][1], now.p - bl[o(now.x + os[i][0], now.y + os[i][1])]);
			int iw = sti(nw);
			if (!chk(nw))
				continue;
			vd[iw] = 1;
			q.push(iw);
			h[iw] = nh;
			if (nw.x == n && nw.y == n)
			{
				printf("%d", h[sti(nw)]);
				return 0;
			}
		}
		q.pop();
	}
}

