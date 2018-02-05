#include <stdio.h>
#include <string.h>
const int upp = 1;
const int downn = 2;
char s[101010];
struct node
{
	int num[26];
	int l, r;
	node *lch, *rch;
	int lazy;
	void down()
	{
		if (!lazy || !lch)
			return;
		memset(rch->num, 0, sizeof(rch->num));
		memset(lch->num, 0, sizeof(lch->num));
		if (lazy == upp)
		{
			int ln = lch->r - lch->l + 1;
			int i = 0;
			for (; i < 26; i++)
			{
				if (ln >= num[i])
					lch->num[i] = num[i], ln -= num[i];
				else
				{
					lch->num[i] = ln, rch->num[i] = num[i] - ln;
					i++;
					break;
				}
			}
			for (; i < 26; i++)
				rch->num[i] = num[i];
			lch->lazy = rch->lazy = upp;
		}
		if (lazy == downn)
		{
			int rn = rch->r - rch->l + 1;
			int i = 0;
			for (; i < 26; i++)
			{
				if (rn >= num[i])
					rch->num[i] = num[i], rn -= num[i];
				else
				{
					rch->num[i] = rn, lch->num[i] = num[i] - rn;
					i++;
					break;
				}
			}
			for (; i < 26; i++)
				lch->num[i] = num[i];
			lch->lazy = rch->lazy = downn;
		}
		lazy = 0;
	}
	void up()
	{
		if (!lch)
			return;
		for (int i = 0; i < 26; i++)
			num[i] = rch->num[i] + lch->num[i];
	}
} *root;
void setup(int l, int r, int *state, node *rt = root)
{
	if (l <= rt->l && rt->r <= r)
	{
		int nl = rt->r - rt->l + 1;
		memset(rt->num, 0, sizeof(rt->num));
		for (int i = 0; i < 26; i++)
			if (nl >= state[i])
				rt->num[i] = state[i], nl -= state[i], state[i] = 0;
			else
			{
				rt->num[i] = nl, state[i] -= nl;
				break;
			}
		rt->lazy = upp;
		return;
	}
	rt->down();
	if (l <= rt->lch->r)
		setup(l, r, state, rt->lch);
	if (r >= rt->rch->l)
		setup(l, r, state, rt->rch);
	rt->up();
}
void setdown(int l, int r, int *state, node *rt = root)
{
	if (l <= rt->l && rt->r <= r)
	{
		int nl = rt->r - rt->l + 1;
		memset(rt->num, 0, sizeof(rt->num));
		for (int i = 0; i < 26; i++)
			if (nl >= state[i])
				rt->num[i] = state[i], nl -= state[i], state[i] = 0;
			else
			{
				rt->num[i] = nl, state[i] -= nl;
				break;
			}
		rt->lazy = downn;
		return;
	}
	rt->down();
	if (r >= rt->rch->l)
		setdown(l, r, state, rt->rch);
	if (l <= rt->lch->r)
		setdown(l, r, state, rt->lch);
	rt->up();
}
void maketree(int l, int r, node *&rt = root)
{
	rt = new node;
	rt->l = l;
	rt->r = r;
	rt->lazy = 0;
	if (l == r)
	{
		rt->lch = rt->rch = 0;
		memset(rt->num, 0, sizeof(rt->num));
		rt->num[s[l] - 'a'] = 1;
		return;
	}
	maketree(l, (l + r) / 2, rt->lch);
	maketree((l + r) / 2 + 1, r, rt->rch);
	rt->up();
}
void disp(node *rt = root)
{
	if (!rt->lch)
	{
		for (int i = 0; i < 26; i++)
			if (rt->num[i])
			{
				putchar(i + 'a');
				return;
			}
	}
	if (rt->lazy == upp)
	{
		for (int i = 0; i < 26; i++)
			for (int j = 0; j < rt->num[i]; j++)
				putchar(i + 'a');
	}
	if (rt->lazy == downn)
	{
		for (int i = 25; i >= 0; i--)
			for (int j = 0; j < rt->num[i]; j++)
				putchar(i + 'a');
	}
	if (rt->lazy == 0)
	{
		rt->down();
		disp(rt->lch), disp(rt->rch);
	}
}
void qry(int l, int r, int *state, node *rt = root)
{
	if (l <= rt->l && rt->r <= r)
	{
		for (int i = 0; i < 26; i++)
			state[i] += rt->num[i];
		return;
	}
	rt->down();
	if (r >= rt->rch->l)
		qry(l, r, state, rt->rch);
	if (l <= rt->lch->r)
		qry(l, r, state, rt->lch);
}
void c1p(int a, char t, node *rt = root)
{
	if (!rt->lch)
	{
		memset(rt->num, 0, sizeof(rt->num));
		rt->num[t] = 1;
		return;
	}
	rt->down();
	if (a <= rt->lch->r)
		c1p(a, t, rt->lch);
	else
		c1p(a, t, rt->rch);
	rt->up();
}
void chg(int l, int r)
{
	int state[26] = {0};
	qry(l, r, state);
	char flg = -1;
	for (int i = 0; i < 26; i++)
		if (state[i] & 1)
			if (flg >= 0)
				return;
			else
				flg = i;
	if (flg >= 0)
		c1p((r + l) / 2, flg);
	int all = 0;
	for (int i = 0; i < 26; i++)
	{
		state[i] >>= 1;
		all += state[i];
	}
	int s2[26];
	memcpy(s2, state, sizeof(s2));
	setup(l, l + all - 1, state);
	setdown(r - all + 1, r, s2);
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	scanf("%s", s + 1);
	maketree(1, n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		chg(a, b);
	}
	disp();
}
