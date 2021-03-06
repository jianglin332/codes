#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define maxn 2100000 + 5
#define inf 1000000000
#define maxfv 2005

int was[maxn], n, i, j, f[maxn], t[maxn], p[maxn], a[maxfv][maxfv], fc[maxfv][maxfv];
int yw[maxn], xw[maxn], zw[maxn], xb[maxn], yb[maxn], zb[maxn], pr[maxn], ii;
int ff[maxn], ft[maxn], fp[maxn], fl[maxn], o[maxn], carry[maxn], q1, q2, queue[maxn], vn, q, x, y, ii2, up[maxn][20];
int g[maxn], groups, m1, m2, all, k, deleted[maxn], fail, cc[maxn], sum1, tin[maxn], tout[maxn], lcb[maxfv], lcw[maxfv], timer;
int F[maxfv][maxfv], c[maxfv][maxfv];

inline bool anc (int x, int y) {
	return (tin[x] <= tin[y] && tout[y] <= tout[x]);
}

int lca (int x, int y) {
	if (anc(x, y)) return x;
	for(int i = 19; i >= 0; i--) if (!anc(up[x][i], y)) x = up[x][i];
	return up[x][0];
}

void addedge (int x, int y) {
	t[++ii] = y;
	p[ii] = f[x];
	f[x] = ii;
}

inline void addfedge (int x, int y, int z) {
	fc[x][y] = z;
	a[x][++cc[x]] = y;
	a[y][++cc[y]] = x;
}

void dfs (int k) {
	tin[k] = ++timer;
	was[k] = 1;
	int q = f[k];
	while (q > 0) {
		if (was[t[q]] != 1) {
			up[t[q]][0] = k;
			for(int j = 1; j < 20; j++) up[t[q]][j] = up[up[t[q]][j - 1]][j - 1];
			dfs(t[q]);
		}
		q = p[q];
	}
	tout[k] = ++timer;
}

void mdfs (int k) {
	g[k] = groups;
	int q = f[k];
	if (deleted[k] != i)
		while (q > 0) {
			if (!g[t[q]] && deleted[t[q]] != i) mdfs(t[q]);
			q = p[q];
		}
}

int h[maxfv], e[maxfv];

inline void push (int u, int v) {
	fail = 0;
	int d = min (e[u], fc[u][v]);
	fc[u][v] -= d;
	fc[v][u] += d;
	e[u] -= d;
	e[v] += d;
}

inline void lift (int k) {
	h[k] = n + n;
	for(int i = 1; i <= cc[k]; i++) if (fc[k][a[k][i]] > 0 && h[a[k][i]] + 1 < h[k]) h[k] = h[a[k][i]] + 1;
}

int get_mf () {
	n = 2 + m1 + m2;
	h[1] = n;
	while (true) {
		fail = 1;
		for(i = 2; i < n; i++) {
			lift(i);
			j = 1;
			while (e[i]) {
				if (j > cc[i]) {
					lift(i);
					j = 1;
				}
				k = a[i][j];
				if (fc[i][k] > 0 && h[i] == h[k] + 1) push(i, k);
				++j;
			}
		}
		if (fail == 1) break;
	}
	return sum1 - e[1];
}

bool anc2 (int x, int y) {
	return anc(y, x);
}

bool cross (int x1, int y1, int l1, int x2, int y2, int l2){
	if(anc(l1, l2) && anc(l2, x1)) return true;
	if(anc(l1, x2) && anc(x2, x1)) return true;
	if(anc(l1, y2) && anc(y2, x1)) return true;	
	if(anc(l1, l2) && anc(l2, y1)) return true;
	if(anc(l1, x2) && anc(x2, y1)) return true;
	if(anc(l1, y2) && anc(y2, y1)) return true;	
	if(anc(l2, l1) && anc(l1, x2)) return true;
	if(anc(l2, x1) && anc(x1, x2)) return true;
	if(anc(l2, y1) && anc(y1, x2)) return true;	
	if(anc(l2, l1) && anc(l1, y2)) return true;
	if(anc(l2, x1) && anc(x1, y2)) return true;
	if(anc(l2, y1) && anc(y1, y2)) return true;
	return false;
	
}

int main (int argc, char * const argv[]) {
	scanf("%d %d %d", &n, &m1, &m2);
	for(i = 1; i < n; i++) {
		scanf("%d %d", &x, &y);
		addedge(x, y);
		addedge(y, x);
	}
	for(i = 0; i < 20; i++) up[1][i] = 1;
	dfs(1);
	for(i = 1; i <= m1; i++) {
		scanf("%d %d %d", &xw[i], &yw[i], &zw[i]);
		lcw[i] = lca(xw[i], yw[i]);
		e[1 + i] = zw[i];
		addfedge(1, 1 + i, 0);
		addfedge(1 + i, 1, zw[i]);
		--cc[1];
		--cc[1 + i];
		all += zw[i];
	}
	sum1 = all;
	for(i = 1; i <= m2; i++) {
		scanf("%d %d %d", &xb[i], &yb[i], &zb[i]);
		lcb[i] = lca(xb[i], yb[i]);
		addfedge(1 + m1 + i, 2 + m1 + m2, zb[i]);
		all += zb[i];
	}
	for(i = 1; i <= m1; i++) 
		for(j = 1; j <= m2; j++) if (cross(xw[i], yw[i], lcw[i], xb[j], yb[j], lcb[j])) {
			addfedge(1 + i, 1 + m1 + j, inf);
//			cerr << i << " and " << j << " crosses" << endl;
		}
	printf("%d\n", all - get_mf());
	return 0;
}
