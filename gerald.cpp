#pragma warning(disable:4786)
#include<time.h>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<functional>
#include<string>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<utility>
#include<fstream>
#include<sstream>
#include<cmath>
#include<stack>
#include<assert.h>
using namespace std;

#define MEM(a, b) memset(a, (b), sizeof(a))
#define CLR(a) memset(a, 0, sizeof(a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(X) ( (X) > 0 ? (X) : ( -(X) ) )
#define S(X) ( (X) * (X) )
#define SZ(V) (int )V.size()
#define FORN(i, n) for(i = 0; i < n; i++)
#define FORAB(i, a, b) for(i = a; i <= b; i++)
#define ALL(V) V.begin(), V.end()
#define IN(A, B, C)  ((B) <= (A) && (A) <= (C))

typedef pair<int,int> PII;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<PII > VP;


#define AIN(A, B, C) assert(IN(A, B, C))

//typedef int LL;
//typedef long long int LL;
//typedef __int64 LL;


#define MAXN 100005
#define LOG2_MAXN 19

int color[MAXN];

struct Heavy_Light_Decomposition
{
	int priEdgeHead[MAXN], priEdgeNext[MAXN<<1], priEdgeNode[MAXN<<1], priEdgeCount;
	int n; //node 1..n
	int priSubtreeSize[MAXN], priHeavySon[MAXN], priParent[MAXN];

	//auxPosition[x] = x node er aux e position
	//auxNode[x] = x position e node
	int auxPos, auxPosition[MAXN], auxNode[MAXN];
	int HeavyTop[MAXN], HeavyDown[MAXN];

	int dfsStart[MAXN], dfsEnd[MAXN], dfsTime;

	void add_edge(int parent, int child)
	{
		++priEdgeCount;
		priEdgeNode[priEdgeCount] = child;
		priEdgeNext[priEdgeCount] = priEdgeHead[parent];
		priEdgeHead[parent] = priEdgeCount;

		++priEdgeCount;
		priEdgeNode[priEdgeCount] = parent;
		priEdgeNext[priEdgeCount] = priEdgeHead[child];
		priEdgeHead[child] = priEdgeCount;
	}

	void set(int _n)
	{
		n = _n;

		CLR(priEdgeHead);
		priEdgeCount = 0;
		auxPos = 0;
		dfsTime = 0;
	}

	int Qlist[MAXN];

	void checkTree()
	{
		int u, v, cnt, p;
		int l, r;

		CLR(color);

		Qlist[l = 0] = 1;
		r = 1;
		color[1] = 1;
		cnt = 1;

		for(l = 0; l < r; l++)
		{
			u = Qlist[l];

			for(p = priEdgeHead[u]; p; p = priEdgeNext[p])
			{
				v = priEdgeNode[p];
				if(color[v]) continue;
				color[v] = 1;
				Qlist[r++] = v;
				++cnt;
			}
		}

		assert(cnt == n);
	}

	void decompose()
	{
		checkTree();

		/*Process Primary Tree*/
		dfs1(1, 0);
		dfs2(1, 0, 1);
	}

	void OperationChangeColor(int x)
	{
		int t, b, z1, z2, y1, y2, a;

		colorSize[x][color[x]]--;
		color[x] ^= 1;
		colorSize[x][color[x]]++;

		while(1)
		{
			t = HeavyTop[x];
			b = HeavyDown[x];

			a = findindex(1, 1, n, auxPosition[t], auxPosition[b], 1 ^ color[t], 0);
			if(a == 10000000) a = auxPosition[b] + 1;
			z1 = querySum(1, 1, n, auxPosition[t], a - 1, color[t]);

			a = findindex(1, 1, n, auxPosition[t], auxPosition[b], color[t], 0);
			if(a == 10000000) a = auxPosition[b] + 1;
			y1 = querySum(1, 1, n, auxPosition[t], a - 1, color[t] ^ 1);

			updateColor(1, 1, n, auxPosition[x]);

			a = findindex(1, 1, n, auxPosition[t], auxPosition[b], 1 ^ color[t], 0);
			if(a == 10000000) a = auxPosition[b] + 1;
			z2 = querySum(1, 1, n, auxPosition[t], a - 1, color[t]);

			a = findindex(1, 1, n, auxPosition[t], auxPosition[b], color[t], 0);
			if(a == 10000000) a = auxPosition[b] + 1;
			y2 = querySum(1, 1, n, auxPosition[t], a - 1, color[t] ^ 1);


			if(t == 1) break;

			x = priParent[t];
			colorSize[x][color[t]]     = colorSize[x][color[t]]     - z1 + z2;
			colorSize[x][color[t] ^ 1] = colorSize[x][color[t] ^ 1] - y1 + y2;
		}


	}

	int OperationCount(int x)
	{
		int a, b, ret = 0;

		while(1)
		{
//			a = findindex(1, 1, n, auxPosition[x] + 1, auxPosition[ HeavyDown[ x ] ], 1 ^ color[x], 0);
			b = findindex(1, 1, n, auxPosition[ HeavyTop[x] ], auxPosition[x] - 1, 1 ^ color[x], 1);

//			if(a == 10000000) a = auxPosition[ HeavyDown[x] ] + 1;
			if(b == -1) b = auxPosition[ HeavyTop[x] ] - 1;

//			ret += querySum(1, 1, n, b + 1, a - 1, color[x]);

			if(HeavyTop[x] == 1) break;
			if(b == auxPosition[ HeavyTop[x] ] - 1 && color[ x ] == color[ priParent[HeavyTop[x]] ]) x = priParent[ HeavyTop[x] ];
			else break;
		}


//		while(1)
		{
			a = findindex(1, 1, n, auxPosition[x] + 1, auxPosition[ HeavyDown[ x ] ], 1 ^ color[x], 0);
			b = findindex(1, 1, n, auxPosition[ HeavyTop[x] ], auxPosition[x] - 1, 1 ^ color[x], 1);

			if(a == 10000000) a = auxPosition[ HeavyDown[x] ] + 1;
			if(b == -1) b = auxPosition[ HeavyTop[x] ] - 1;

			return querySum(1, 1, n, b + 1, a - 1, color[x]);

//			if(HeavyTop[x] == 1) break;
//			if(b == auxPosition[ HeavyTop[x] ] - 1 && color[ x ] == color[ priParent[HeavyTop[x]] ]) x = priParent[ HeavyTop[x] ];
//			else break;
		}

		return ret;
	}

	int color[MAXN],colorSize[MAXN][2];
	int subtree[MAXN];

	void solve(int Q)
	{
		int i, u, p;
		int op;

		CLR(color); //color[i] = 1 if black
		CLR(subtree);

		for(i = 1; i <= n; i++) color[i] = 1, colorSize[i][0] = colorSize[i][1] = subtree[i] = 0;

		for(i = n - 1; i >= 0; i--)
		{
			u = Qlist[i];
			subtree[u] = 1;
			for(p = priEdgeHead[Qlist[i]]; p; p = priEdgeNext[p])
				if(priEdgeNode[p] != priParent[Qlist[i]])
					subtree[u] += subtree[priEdgeNode[p]];
		}

		for(i = n - 1; i >= 0; i--)
		{
			u = Qlist[i];
			colorSize[u][0] = 0, colorSize[u][1] = subtree[u];
			for(p = priEdgeHead[Qlist[i]]; p; p = priEdgeNext[p])
				if(priEdgeNode[p] == priHeavySon[Qlist[i]])
					colorSize[u][1] -= subtree[priEdgeNode[p]];
		}


		/*Process Auxiliary Tree*/
		build(1, 1, n);

		while(Q--)
		{
			scanf("%d %d", &op, &u);
			AIN(op, 0, 1);
			AIN(u, 1, n);

			if(op == 1) OperationChangeColor(u);
			else if(op == 0) printf("%d\n", OperationCount(u));
		}
	}

	void dfs1(int at, int parent)
	{
		stack<PII> S;
		PII X;
		int u, p;

		priParent[at] = parent;
		S.push(PII(at, 0));

		while(!S.empty())
		{
			X = S.top();
			at = X.first;
			S.pop();

			if(!X.second)
			{
				X.second = 1;
				S.push(X);

				dfsStart[at] = ++dfsTime;
				for(p = priEdgeHead[at]; p; p = priEdgeNext[p])
				{
					u = priEdgeNode[p];
					if(u == priParent[at]) continue;
					priParent[u] = at;
					S.push(PII(u, 0));
				}
			}
			else
			{
				priSubtreeSize[at] = 1;
				priHeavySon[at] = 0;
				for(p = priEdgeHead[at]; p; p = priEdgeNext[p])
				{
					u = priEdgeNode[p];
					if(u == priParent[at]) continue;
					priSubtreeSize[at] += priSubtreeSize[u];
					if(!priHeavySon[at] || priSubtreeSize[u] > priSubtreeSize[priHeavySon[at]])
						priHeavySon[at] = u;
				}

				dfsEnd[at] = dfsTime;
			}
		}
	}
	void dfs2(int at, int parent, int top)
	{
		int u, p;
		stack<PII> S;
		PII X;
		
		S.push(PII(at, top));
		
		while(!S.empty())
		{
			X = S.top();
			S.pop();

			at = X.first;
			top = X.second;

			if(top)
			{
				X.second = 0;
				S.push(X);

				auxNode[ auxPosition[at] = ++auxPos ] = at;
				HeavyTop[at] = top;
				
				for(p = priEdgeHead[at]; p; p = priEdgeNext[p])
				{
					u = priEdgeNode[p];
					if(u == priParent[at] || u == priHeavySon[at]) continue;
					S.push(PII(u, u));
				}

				if(priHeavySon[at]) S.push(PII(priHeavySon[at], top));
			}
			else
			{
				if(!priHeavySon[at]) HeavyDown[at] = at;
				else HeavyDown[at] = HeavyDown[ priHeavySon[at] ];
			}
		}
	}


	/*--------Auxiliary Tree-------*/
	int sum[MAXN<<2][2], last[MAXN<<2][2], first[MAXN<<2][2];

	void build(int at, int left, int right)
	{
		if(left == right)
		{
			int u = auxNode[left];

			sum[at][0] = colorSize[u][0];
			sum[at][1] = colorSize[u][1];
			last[at][ color[u] ] = first[at][ color[u] ] = left;
			last[at][ 1 ^ color[u] ] = -1, first[at][ 1 ^ color[u] ] = 10000000;
			return;
		}

		int mid = (left + right) >> 1;
		build(2*at, left, mid);
		build(2*at + 1, mid + 1, right);

		sum[at][0] = sum[at * 2][0] + sum[at * 2 + 1][0];
		sum[at][1] = sum[at * 2][1] + sum[at * 2 + 1][1];
		first[at][1] = MIN(first[at * 2][1], first[at * 2 + 1][1]);
		first[at][0] = MIN(first[at * 2][0], first[at * 2 + 1][0]);
		last[at][1] = MAX(last[at * 2][1], last[at * 2 + 1][1]);
		last[at][0] = MAX(last[at * 2][0], last[at * 2 + 1][0]);
	}

	int querySum(int at, int left, int right, int L, int R, int col)
	{
		if(R < left || right < L) return 0;
		if(L <= left && right <= R) return sum[at][col];
		int mid = (left + right) >> 1;
		return querySum(at * 2, left, mid, L, R, col) + querySum(at * 2 + 1, mid + 1, right, L, R, col);
	}

	void updateColor(int at, int left, int right, int x)
	{
		if(x < left || right < x) return;
		if(left == right) 
		{
			sum[at][0] = colorSize[auxNode[x]][0];
			sum[at][1] = colorSize[auxNode[x]][1];
			first[at][color[auxNode[x]]] = last[at][color[auxNode[x]]] = left;
			first[at][color[auxNode[x]] ^ 1] = 10000000, last[at][color[auxNode[x]] ^ 1] = -1;
			return;
		}

		int mid = (left + right) >> 1;
		updateColor(at * 2, left, mid, x);
		updateColor(at * 2 + 1, mid + 1, right, x);

		sum[at][0] = sum[at * 2][0] + sum[at * 2 + 1][0];
		sum[at][1] = sum[at * 2][1] + sum[at * 2 + 1][1];
		first[at][1] = MIN(first[at * 2][1], first[at * 2 + 1][1]);
		first[at][0] = MIN(first[at * 2][0], first[at * 2 + 1][0]);
		last[at][1] = MAX(last[at * 2][1], last[at * 2 + 1][1]);
		last[at][0] = MAX(last[at * 2][0], last[at * 2 + 1][0]);
	}

	int findindex(int at, int left, int right, int L, int R, int col, int side)
	{
		if(L <= left && right <= R) 
		{
			if(side == 0) return first[at][col];
			else return last[at][col];
		}

		if(R < left || right < L) 
		{
			if(side == 0) return 10000000;
			else return -1;
		}

		int mid = (left + right) >> 1;
		int a = findindex(at * 2, left, mid, L, R, col, side);
		int b = findindex(at * 2 + 1, mid + 1, right, L, R, col, side);
		
		if(side == 0) return MIN(a, b);
		else return MAX(a, b);
	}
};

Heavy_Light_Decomposition Tree;
/*
		Tree.set(N);

		FORAB(i, 2, N)
		{
			scanf("%d %d", &a, &b);
			a++, b++;

			AIN(a, 1, N);
			AIN(b, 1, N);
			assert(a != b);

			Tree.add_edge(a, b);
		}

		scanf("%d", &Q);

		Tree.decompose();
		Tree.solve(Q);

*/
int main()
{
	int n, i, a, b, Q;

	scanf("%d", &n);
	AIN(n, 1, 100000);
	Tree.set(n);
	for(i = 1; i < n; i++)
	{
		scanf("%d %d", &a, &b);
		AIN(a, 1, n); AIN(b, 1, n);
		assert(a != b);
		Tree.add_edge(a, b);
	}

	scanf("%d", &Q);
	AIN(Q, 1, 100000);

	Tree.decompose();
	Tree.solve(Q);

	return 0;
}
