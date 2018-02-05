#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<vector>
const double eps=1e-8;
using namespace std;
struct point{
    double x,y;int u;
    bool operator <(const point&ths)const{
        return x<ths.x||x-ths.x<=-eps&&y<ths.y;
    }point operator -(const point &rhs)const{
        return (point){x-rhs.x,y-rhs.y};
    }
}P[200],T2[200],go[200];
inline double cha(point x,point y){return x.x*y.y-x.y*y.x;}
int H[200],top;
double ans=1e99;
inline double area(){
    double x=0.0;
    int N=top;
    for(int i=0;i<N;i++)x+=cha(T2[H[i]],T2[H[(i+1)%N]]);
    x/=2.0;
    ans=min(ans,x);
    return x;
}
int n;
bool in[200];
inline void getTu(){
    sort(T2+1,T2+1+n);
    H[0]=1;top=1;
    for(int i=2;i<=n;i++)
    {
        in[i]=0;
        if(top==1)H[top]=i,in[i]=1,top++;
        else{
            while(top>1&&cha(T2[H[top-1]]-T2[H[top-2]],T2[i]-T2[H[top-1]])<=eps)in[H[top-1]]=0,top--;
            in[i]=1;H[top]=i;top++;
        }
    }in[1]=0;
    for(int i=n;i>=1;i--)
    if(!in[i]){
        if(top==1)H[top]=i,in[i]=1,top++;
        else{
            while(top>1&&cha(T2[H[top-1]]-T2[H[top-2]],T2[i]-T2[H[top-1]])<=eps)in[H[top-1]]=0,top--;
            in[i]=1;H[top]=i;top++;
        }
    }
}
double T,Height,G,v[200];
inline double dis(point x,point y)
{
    return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}
inline int ini(){int u;char ch=0;while(!(ch>='0'&&ch<='9'))ch=getchar();u=ch-'0';while((ch=getchar())&&ch>='0'&&ch<='9')u=u*10+ch-'0';return u;}
int main(){
    scanf("%lf%lf",&Height,&G);
    T=sqrt(2.0*Height/G);
    n=ini();
    for(int i=1;i<=n;i++)
    {
        P[i].x=ini();P[i].y=ini();
        go[i].x=ini()-P[i].x,go[i].y=ini()-P[i].y;
    }int S=100/n+1;
    double seg=T/(double)S;
    for(int i=1;i<=S;i++)
    {
        double left=(double)(i-1)*seg,right=(double)i*seg;
        for(int j=1;j<=n;j++)
                T2[j]=(point){P[j].x+go[j].x*left/T,P[j].y+go[j].y*left/T,j};
        getTu();area();
        while(right-left>=eps)
        {
            double m1=(right-left)/3.0+left;
            double m2=(right-left)*2.0/3.0+left;
            double a1,a2;
            for(int j=1;j<=n;j++)
                    T2[j]=(point){P[T2[j].u].x+go[T2[j].u].x*m1/T,P[T2[j].u].y+go[T2[j].u].y*m1/T,T2[j].u};
            getTu();a1=area();
            for(int j=1;j<=n;j++)
                    T2[j]=(point){P[T2[j].u].x+go[T2[j].u].x*m2/T,P[T2[j].u].y+go[T2[j].u].y*m2/T,T2[j].u};
            getTu();a2=area();
            if(a1<a2)right=m2;
            else left=m1;
        }
    }printf("%.4f\n",ans);
}
