#include <iostream>
#include <algorithm>
using namespace std;
#define r(a,t) for(i=0;i<a;i+=t)
int w[10101],n,m,a,b,v,s,i;main(){cin>>n>>m;r(n,1)cin>>w[i],w[i]*=2;r(m,1)cin>>a>>b>>v,w[a-1]+=v,w[b-1]+=v;sort(w,w+n);r(n,2)s+=w[i+1]-w[i];cout<<s/2;}
