#include <stdio.h>
#include <list>
using namespace std;
typedef list<pair<int, int> > lt;
lt ls;
int s[201010], ns;
int f[201010];
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		for (lt::iterator j = ls.begin(); j != ls.end(); j++)
			j->second++;
		int tp;
		scanf("%d", &tp);
		if (tp == 1)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			if (ls.empty())
				ls.insert(ls.end(), make_pair(a, b));
			else if (a < ls.begin()->first)
				ls.insert(ls.begin(), make_pair(a, b));
			else if (a > ls.rbegin()->first)
				ls.insert(ls.end(), make_pair(a, b));
			else
				for (lt::iterator j = ls.begin(); j != ls.end(); j++)
					if (a < (*j).first)
					{
						ls.insert(j, make_pair(a, b));
						break;
					}
		}
		if (tp == 2)
		{
			int pl;
			scanf("%d", &pl);
			lt::iterator t = ls.begin();
			advance(t, pl - 1);
			ls.erase(t);
		}
		ns = 0;
		f[0] = 0;
		int ans = 0;
		for (lt::iterator j = ls.begin(); j != ls.end(); j++)
			s[ns] = (*j).second, f[++ns] = 1e9;
		for (int j = 0; j < ns; j++)
		{
			int st = 0, ed = ans + 1;
			while (st + 1 < ed)
			{
				int mid = (st + ed) / 2;
				if (f[mid] < s[j])
					st = mid;
				else
					ed = mid;
			}
			if (s[j] > f[ans])
				ans++;
			st++;
			if (f[st] > s[j])
				f[st] = s[j];
		}
		printf("%d\n", ans);
	}
}
