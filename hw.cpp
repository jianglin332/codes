#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;
struct hill
{
	long long x1, y1, x2, y2;
	bool operator<(const hill & a) const
	{
		if (x2 < a.x2)
			return y2 * (a.x2 - a.x1) < a.y2 * (a.x2 - a.x1)- (a.x2 - x2) * (a.y2 - a.y1);
		return a.y2 * (x2 - x1) > y2 * (x2 - x1)- (x2 - a.x2) * (y2 - y1);
	}
}hs[101010];
bool cmp2(const int a, const int b)
{
	return hs[a].x2 < hs[b].x2;
}
bool cmp(const int a, const int b)
{
	return hs[a].x1 < hs[b].x1;
}
int iq[101010], eq[101010], ni = 1, ne, n;
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lld%lld%lld%lld", &hs[i].x1, &hs[i].y1, &hs[i].x2, &hs[i].y2), iq[i] = i, eq[i] = i;
	sort(iq + 1, iq + n, cmp);
	sort(eq, eq + n, cmp2);
	set<hill> tr;
	int ans = 1;
	hill now = hs[0];
	while (1)
	{
		while (ne < n && hs[eq[ne]].x2 <= now.x2)
			tr.erase(hs[eq[ne++]]);
		while (ni < n && hs[iq[ni]].x1 <= now.x2)
		{
			if (hs[iq[ni]].x2 > now.x2)
			{
				tr.insert(hs[iq[ni]]);
			}
			ni++;
		}
		hill ts;
		while (tr.size())
		{
			ts = *tr.rbegin();
			if (now.y2 * (ts.x2 - ts.x1) < ts.y2 * (ts.x2 - ts.x1) - (ts.x2 - now.x2) * (ts.y2 - ts.y1))
				tr.erase(ts);
			else
				break;
		}
		if (!tr.size())
			break;
		ans++;
		now = ts;
		tr.erase(ts);
	}
	printf("%d", ans);
}
