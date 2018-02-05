#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct tp
{
	int tm, num;
	bool ud;
	bool operator < (const tp &a) const
	{
		return tm < a.tm;
	}
}ps[1111], rs[1111];
int main()
{
	int cas = 0;
	while (1)
	{
		int w;
		scanf("%d", &w);
		if (!w)
			break;
		memset(ps, 0, sizeof(ps));
		memset(rs, 0, sizeof(rs));
		printf("Trial %d: ", ++cas);
		for (int i = 0; i < w; i++)
			scanf("%d%d", &ps[i].num, &ps[i].tm);
		int r;
		scanf("%d", &r);
		for (int i = 0; i < r; i++)
		{
			int h, m;
			scanf("%d%d:%d", &rs[i].num, &h, &m);
			rs[i].tm = (h - 14) * 60 + m;
		}
		sort(ps, ps + w);
		sort(rs, rs + r);
		int lim = 0;
		for (int i = 0; i < r; i++)
		{
			int tm = rs[i].tm, num = rs[i].num;
			while (lim < w && ps[lim].tm <= tm)
				lim++;
			int mx = 0, tg = -1;
			for (int j = 0; j < lim; j++)
				if (ps[j].num <= num && !ps[j].ud)
				{
					if (ps[j].num > mx)
					{
						mx = ps[j].num;
						tg = j;
					}
				}
			if (tg != -1)
				ps[tg].ud = 1;
		}
		int nc = 0, np = 0;
		for (int i = 0; i < w; i++)
			if (!ps[i].ud)
				nc++, np += ps[i].num;
		printf("%d %d\n", nc, np);
	}
}
