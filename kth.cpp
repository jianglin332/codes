#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
int v[101010];
struct o
{
	int nw;
	long long vl;
	bool operator<(const o &a) const
	{
		return vl + v[nw] > a.vl + v[a.nw];
	}
	o(long long v, int n)
	{
		vl = v, nw = n;
	}
};
int n;
long long k;
long long a[1010101], b[1010101];
void work()
{
	int n1 = n / 2, n2 = n - n1;
	int na = 1 << n1, nb = 1 << n2;
	for (int i = 0; i < na; i++)
	{
		long long s = 0;
		for (int j = 0; j < n1; j++)
			if ((i >> j) & 1)
				s += v[j];
		a[i] = s;
	}
	for (int i = 0; i < nb; i++)
	{
		long long s = 0;
		for (int j = 0; j < n2; j++)
			if ((i >> j) & 1)
				s += v[n1 + j];
		b[i] = s;
	}
	sort(a, a + na);
	sort(b, b + nb);
	long long st = 0, ed = a[na - 1] + b[nb - 1] + 1;
	k++;
	while (st + 1 < ed)
	{
		long long mid = (st + ed) / 2;
		int nt = nb - 1;
		long long nc = 0;
		for (int i = 0; i < na; i++)
		{
			if (a[na] > mid)
				break;
			while (a[i] + b[nt] >= mid)
				nt--;
			nc += nt + 1;
		}
		if (nc < k)
			st = mid;
		else
			ed = mid;
	}
	printf("%lld", st);
}
int main()
{
	scanf("%d%lld", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", v + i);
	sort(v, v + n);
	if (n <= 35)
	{
		work();
		return 0;
	}
	priority_queue<o> q;
	q.push(o(0, 0));
	long long nw = 0;
	for (int i = 0; i < k; i++)
	{
		o now = q.top();
		q.pop();
		nw = now.vl + v[now.nw];
		if (now.nw < n - 1)
		{
			q.push(o(nw, now.nw + 1));
			q.push(o(now.vl, now.nw + 1));
		}
	}
	printf("%lld", nw);
}
