#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;
struct ed
{
	int nx, to;
}es[1010101];
int hd[10101], ne;
int ans;
bool can[10101][10101];
int dfs(int t, int a)
{
	can[t][a] = 1;
	for (int i = hd[a]; i != -1; i = es[i].nx)
		if (!can[t][es[i].to])
			dfs(t, es[i].to);
}
int main(int argc, char ** argv)
{
	freopen(argv[1], "r", stdin);
	freopen(argv[2], "w", stdout);
	memset(hd, -1, sizeof(hd));
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		es[ne].to = b;
		es[ne].nx = hd[a];
		hd[a] = ne++;
	}
	for (int i = 1; i <= n; i++)
	{
		dfs(i, i);
	}
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (can[i][j] && can[j][i])
				ans++;
	printf("%d\n", ans);
	fclose(stdout);
}
