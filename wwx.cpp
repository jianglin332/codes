#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
using namespace std;
const int Maxn=100005;
int n,AddId[Maxn],AddTot=0;
int ans[Maxn],QryTot=0;
int tx[Maxn*2],ty[Maxn*2],nx=0,ny=0;

inline int get() {
	char ch;
	while (!isdigit(ch=getchar()));
	int v=ch-48;
	while (isdigit(ch=getchar())) v=v*10+ch-48;
	return v;
}

struct Bit{
	int sum[Maxn*2],N;
	void modify(int x,int c) {
		for (;x<=N;x+=x&-x)
			sum[x]+=c;
	}
	int query(int x) {
		int ret=0;
		for (;x;x-=x&-x)
			ret+=sum[x];
		return ret;
	}
}T,T1,T2,T3,T4;

struct info{
	int opx,x1,y1,x2,y2;
}opr[Maxn];

struct PartInfo{
	int opx,x,y;
}q[Maxn],tmp[Maxn];

void solve(int l,int r) {
	if (l==r) return;
	int mid=(l+r)>>1;
	solve(l,mid);
	solve(mid+1,r);
	int p=l;
	for (int i=mid+1;i<=r;i++) {
		if (q[i].opx<=0) continue;
		for (;p<=mid&&q[p].x<=q[i].x;p++)
			if (q[p].opx<=0)
				T.modify(q[p].y,q[p].opx==0?1:-1); 
		ans[q[i].opx]+=T.query(q[i].y);
	}
	while (p-->l)
		if (q[p].opx<=0)
			T.modify(q[p].y,q[p].opx==0?-1:1);
	int t1=l,t2=mid+1;
	while (t1<=mid&&t2<=r) {
		if (q[t1].x<=q[t2].x)
			tmp[++p]=q[t1++];
		else
			tmp[++p]=q[t2++];
	}
	while (t1<=mid) tmp[++p]=q[t1++];
	while (t2<=r) tmp[++p]=q[t2++];
	memcpy(q+l,tmp+l,sizeof(PartInfo)*(r-l+1));
}

int main() {
	n=get();
	for (int i=1,cnt=0;i<=n;i++) {
		char opx;
		while (!isupper(opx=getchar()));
		if (opx=='I') {
			opr[i].opx=0;
			AddId[++AddTot]=i;
			tx[++nx]=opr[i].x1=get();
			ty[++ny]=opr[i].y1=get();
			tx[++nx]=opr[i].x2=get();
			ty[++ny]=opr[i].y2=get();
			++cnt;
		}
		if (opx=='D') {
			opr[i].opx=-AddId[get()];
			--cnt;
		}
		if (opx=='Q') {
			opr[i].opx=++QryTot;
			opr[i].x1=get();
			opr[i].y1=get();
			opr[i].x2=get();
			opr[i].y2=get();
			ans[QryTot]=cnt;
		}
	}
	
	sort(tx+1,tx+nx+1);
	nx=unique(tx+1,tx+nx+1)-tx-1;
	T1.N=T3.N=nx;
	sort(ty+1,ty+ny+1);
	ny=unique(ty+1,ty+ny+1)-ty-1;
	T2.N=T4.N=ny;
	
	for (int i=1;i<=n;i++) {
		if (opr[i].opx==0) {
			opr[i].x1=lower_bound(tx+1,tx+nx+1,opr[i].x1)-tx;
			opr[i].y1=lower_bound(ty+1,ty+ny+1,opr[i].y1)-ty;
			opr[i].x2=lower_bound(tx+1,tx+nx+1,opr[i].x2)-tx;
			opr[i].y2=lower_bound(ty+1,ty+ny+1,opr[i].y2)-ty;
			T1.modify(opr[i].x2,1);
			T2.modify(opr[i].y2,1);
			T3.modify(nx-opr[i].x1+1,1);
			T4.modify(ny-opr[i].y1+1,1);
		}
		if (opr[i].opx<0) {
			opr[i]=opr[-opr[i].opx];
			opr[i].opx=-1;
			T1.modify(opr[i].x2,-1);
			T2.modify(opr[i].y2,-1);
			T3.modify(nx-opr[i].x1+1,-1);
			T4.modify(ny-opr[i].y1+1,-1);
		}
		if (opr[i].opx>0) {
			opr[i].x1=lower_bound(tx+1,tx+nx+1,opr[i].x1)-tx;
			opr[i].y1=lower_bound(ty+1,ty+ny+1,opr[i].y1)-ty;
			opr[i].x2=upper_bound(tx+1,tx+nx+1,opr[i].x2)-tx-1;
			opr[i].y2=upper_bound(ty+1,ty+ny+1,opr[i].y2)-ty-1;
			ans[opr[i].opx]-=T1.query(opr[i].x1-1);
			ans[opr[i].opx]-=T2.query(opr[i].y1-1);
			ans[opr[i].opx]-=T3.query(nx-opr[i].x2);
			ans[opr[i].opx]-=T4.query(ny-opr[i].y2);
		}
	}
	
	T.N=ny;
	
	for (int i=1;i<=n;i++) {
		q[i].opx=opr[i].opx;
		if (opr[i].opx<=0) {
			q[i].x=opr[i].x2;
			q[i].y=opr[i].y2;
		}
		else {
			q[i].x=opr[i].x1-1;
			q[i].y=opr[i].y1-1;
		}
	}
	solve(1,n);
	
	for (int i=1;i<=n;i++) {
		q[i].opx=opr[i].opx;
		if (opr[i].opx<=0) {
			q[i].x=opr[i].x2;
			q[i].y=ny-opr[i].y1+1;
		}
		else {
			q[i].x=opr[i].x1-1;
			q[i].y=ny-opr[i].y2;
		}
	}
	solve(1,n);
	
	for (int i=1;i<=n;i++) {
		q[i].opx=opr[i].opx;
		if (opr[i].opx<=0) {
			q[i].x=nx-opr[i].x1+1;
			q[i].y=ny-opr[i].y1+1;
		}
		else {
			q[i].x=nx-opr[i].x2;
			q[i].y=ny-opr[i].y2;
		}
	}
	solve(1,n);
	
	for (int i=1;i<=n;i++) {
		q[i].opx=opr[i].opx;
		if (opr[i].opx<=0) {
			q[i].x=nx-opr[i].x1+1;
			q[i].y=opr[i].y2;
		}
		else {
			q[i].x=nx-opr[i].x2;
			q[i].y=opr[i].y1-1;
		}
	}
	solve(1,n);
	
	for (int i=1;i<=QryTot;i++)
		printf("%d\n",ans[i]);
	return 0;
}
