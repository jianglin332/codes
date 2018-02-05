#include <cstdio>
#include <vector>
#include <algorithm>
#define pb push_back
using namespace std;
typedef vector<int> vi;
typedef vi::iterator vt;
vi *dfs(const vi *s)
{
	vi *r = new vi;
	int n = s->size();
	if (n == 1)
	{
		r->pb((*s)[0]);
		return r;
	}
	for (int i = 1; i < (1 << n) - 1; i++)
	{
		vi x[2]; 
		for (int j = 0; j < n; j++)
			x[(i >> j) & 1].pb((*s)[j]);
		vi *t = dfs(x);
		vi *u = dfs(x + 1);
		if (t->size() && u->size())
		for (vt j = t->begin(); j != t->end(); j++)
			for (vt k = u->begin(); k != u->end(); k++)
			{
				r->pb(*j + *k);
				r->pb(*j - *k);
				r->pb(*j * *k);
				if (*k && !(*j % *k))
					r->pb(*j / *k);
			}
		delete t;
		delete u;
	}
	return r;
}
void work()
{
	vi *f = new vi;
	for (int i = 0, j; i < 4; i++, f->pb(j))
		scanf("%d", &j);
	vi *g = dfs(f);
	sort(g->rbegin(), g->rend());
	for (vt i = g->begin(); i != g->end(); i++)
		if (*i <= 24)
		{
			printf("%d\n", *i);
			return;
		}
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		work();
}
