#include <stdio.h>
#include <algorithm>
using namespace std;
#define lowbit(x) ((x) & -(x))
int tree[101010];
int n;
void add(int x, int v)
{
	while (x <= n)
		tree[x] += v, x += lowbit(x);
}
int qry(int x)
{
	int r = 0;
	while (x)
		r += tree[x], x -= lowbit(x);
	return r;
}
int a[101010], b[101010], sa[101010], sb[101010], pos[101010];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i), sa[i] = a[i];
	for (int i = 1; i <= n; i++)
		scanf("%d", b + i), sb[i] = b[i];
	sort(sa + 1, sa + n + 1);
	sort(sb + 1, sb + n + 1);
	for (int i = 1; i <= n; i++)
	{
		a[i] = lower_bound(sa + 1, sa + n + 1, a[i]) - sa;
		b[i] = lower_bound(sb + 1, sb + n + 1, b[i]) - sb;
		pos[a[i]] = i;
	}
	for (int i = 1; i <= n; i++)
		b[i] = n + 1 - pos[b[i]];
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans += qry(b[i] - 1);
		add(b[i], 1);
	}
	printf("%d", int(ans % 99999997));
	return 0;
}
