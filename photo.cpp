#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
struct ph
{
	int a, b;
	bool operator<(const ph &t) const
	{
		return a < t.a;
	}
	bool operator>(const ph &t) const
	{
		return a > t.a;
	}
}ps[101010];
int ahead[202020];
int f[202020];
int 
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
		scanf("%d%d", &ps[i].a, &ps[i].b);
	sort(ps, ps + m);
	priority_queue<ph, vector<ph>, greater<ph> > q;
	int np = 0;
	for (int i = 1; i <= n; i++)
	{
		while (np < m && ps[np].a <= i)
			q.push(ps[np++]);
		while (!q.empty() && q.top().b < i)
			q.pop();
		if (!q.empty())
			f[i] = f[q.top().a - 1];
		else
			f[i] = f[i - 1] + 1;
	}
	printf("%d", f[n]);
}
