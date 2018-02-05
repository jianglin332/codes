#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
using namespace std;
list<int> ls[10101];
int deg[10101];
set<int> inv;
bool vd[10101];
int dfs(int nw, int fr)
{
	int ret = 1;
	vd[nw] = 1;
	for (list<int>::iterator i = ls[nw].begin(); i != ls[nw].end();)
	{
		if (inv.count(*i * 10101 + nw))
		{
			ls[nw].erase(i++);
			continue;
		}
		if (!vd[*i] && *i != fr)
			ret += dfs(*i, nw);
		i++;
	}
	return ret;
}
int main()
{
	int n, m;
	cin.sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		deg[a]++;
		deg[b]++;
		ls[a].push_back(b);
		ls[b].push_back(a);
	}
	int jd = 0;
	for (int i = 1; i <= n; i++)
		jd += deg[i] & 1;
	if (jd > 2 || (jd == 2 && !(deg[1] & 1)))
	{
		cout << -1;
		return 0;
	}
	for (int i = 1; i <= n; i++)
		ls[i].sort();
	int nw = 1, nd = n;
	for (int i = 0; i < m; i++)
	{
		for (list<int>::iterator j = ls[nw].begin(); j != ls[nw].end();)
		{
			if (inv.count(nw * 10101 + *j))
			{
				ls[nw].erase(j++);
				continue;
			}
			memset(vd, 0, sizeof(vd));
			if (deg[nw] != 1 && dfs(*j, nw) != nd)
			{
				j++;
				continue;
			}
			deg[nw]--;
			deg[*j]--;
			if (!deg[nw])
				nd--;
			inv.insert(nw * 10101 + *j);
			inv.insert(*j * 10101 + nw);
			cout << nw << ' ';
			nw = *j;
			break;
		}
	}
	cout << nw;
}
