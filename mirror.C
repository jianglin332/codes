#include <cstdio>
#include <cstring>
#define NE 0
#define NW 1
#define SE 2
#define SW 3
const int os[4][2] = 
{
	{-1, 1},
	{-1, -1},
	{1, 1},
	{1, -1}
};
const int hs = 150001;
const long long mu = 70001;
struct node
{
	long long v;
	node *nx;
	node(){}
	node(int vv, node *n):v(vv), nx(n){}
};
struct hash_table
{
	node *ns[hs];
	hash_table()
	{
		memset(ns, 0, sizeof(ns));
	}
	void ins(long long v)
	{
		int t = (v * mu) % hs;
		ns[t] = new node(v, ns[t]);
	}
	bool operator[](int a)
	{
		int t = (v * mu) % hs;
		for (node *i = ns[t]; i; i = i->nx)
			if (i->v == a)
				return 1;
		return 0;
	}
}ht;
int main()
{
}
