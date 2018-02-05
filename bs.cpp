#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
using namespace std;
int bit[16][133333];
char bf[11];
int a[505050], na;
int dd[505050];
map<int, int> mp;
#define lb(x) ((x) & -(x))
void add(int b, int a, int t)
{
	a++;
	int lm = (1 << b + 2) + 5;
	int *it = bit[b];
	while (a <= lm)
		it[a] += t, a += lb(a);
}
int qry(int b, int a)
{
	a++;
	int *it = bit[b], r = 0;
	while (a)
		r += it[a], a -= lb(a);
	return r;
}
int main()
{
	int n;
	scanf("%d", &n);
	int pl = 0;
	for (int i = 0; i < n; i++)
	{
		int t;
		scanf("%s%d", bf, &t);
		if (bf[0] == 'I')
		{
			t -= pl;
			mp[t]++;
			for (int i = 0; i < 16; i++)
			{
				add(i, t & ((1 << i + 1) - 1), 1);
				add(i, (t & ((1 << i + 1) - 1)) + (1 << i + 1), 1);
			}
		}
		else if (bf[0] == 'Q')
		{
			int q = (1 << (t + 1)) - 1;
			q -= pl;
			q &= (1 << (t + 1)) - 1;
			if (q < (1 << t))
				q += (1 << t + 1);
			int ans = qry(t, q) - qry(t, q - (1 << t));
			printf("%d\n", ans);
		}
		else if (bf[0] == 'A')
		{
			pl += t;
		}
		else
		{
			t -= pl;
			int f = mp[t];
			for (int i = 0; i < 16; i++)
			{
				add(i, t & ((1 << i + 1) - 1), -f);
				add(i, (t & ((1 << i + 1) - 1)) + (1 << i + 1), -f);
			}
			mp[t] = 0;
		}
	}
	return 0;
}
