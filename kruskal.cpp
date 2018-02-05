 #include <cstdio>
#include <algorithm>
int pr[10101];
int in[10101];
struct ed
{
	int a, b, v;
}es[101010];
bool cmp(const ed &a, const ed &b)
{
	return a.v < b.v;
}
int getpr(int a)
{
	while (a != pr[a])
		a = pr[a];
	return a;
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &es[i].a, &es[i].b, &es[i].v);
	std::sort(es, es + m, cmp);
	for (int i = 1; i <= n; i++)
		pr[i] = i;
	long long s = 0;
	for (int i = 0; i < m; i++)
	{
		int pa = getpr(es[i].a), pb = getpr(es[i].b);
		pr[es[i].a] = pa;
		pr[es[i].b] = pb;
		if (pa != pb)
		{
			pr[pb] = pa;
			s += es[i].v;
		}
	}
	int p = getpr(1);
	for (int i = 2; i <= n; i++)
		if (getpr(i) != p)
		{
			printf("-1");
			return 0;
		}
	printf("%lld", s);
}
