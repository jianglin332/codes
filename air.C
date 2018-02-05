#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
double dis[160][160];
double px[160], py[160];
double d[160];
bool vd[160] = {0};
int n;
double di, c;
double work(int a)
{
	memset(vd, 0, sizeof(vd));
	double ans = 0;
	for (int i = 0; i <= n; i++)
		d[i] = dis[1][i];
	int t = 1;
	vd[1] = 1;
	long double ans = 0.;
	while (t < n + a)
	{
		long double k = 1e50;
		int p;
		for (int i = 0; i <= n; i++)
		{
			if (!vd[i])
			{
				if (d[i] < k)
				{
					k = d[i];
					p = i;
				}
			}
		}
		vd[p] = 1;
		ans += k;
		for (int i = 0; i <= n; i++)
			d[i] = min(d[i], dis[i][p]);
		t++;
	}
	return ans;
}
int main()
{

	cin>>n;
	for (int i = 1; i <= n; i++)
		cin>>px[i];
	for (int i = 1; i <= n; i++)
		cin>>py[i];

	cin>>di>>c;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dis[i][j] = sqrt((px[i] - px[j]) * (px[i] - px[j]) + (py[i] - py[j]) * (py[i] - py[j])) * di;
	for (int i = 1; i <= n; i++)
		dis[i][0] = dis[0][i] = 1e10;
	dis[0][0] = 0.;
	double ans = work(0);
	for (int i = 1; i <= n; i++)
		dis[i][0] = dis[0][i] = c;
	ans = min(work(1), ans);
	printf("%.2lf", double(ans));
}
