 #include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
#define N 15
#define M 15
#define __int64 long long
#define MAX_STATE 200000
#define HASH_LIMIT 200000
int n,m,nn,mm;
bool map[N][M];
unsigned __int64 state[2][MAX_STATE],dp[2][MAX_STATE];//滚动数组
int Hash[HASH_LIMIT],nstate[2];
inline bool canGo(int i,int j)
{
 if(i<=0 || i>n || j<=0 || j>m) return false;
 if(map[i][j]) return true;
 return false;
}
inline unsigned __int64 shift(unsigned __int64 a,int index) { return a<<((m+1-index)<<1); }
inline int get(int index,unsigned __int64 st) { return (int)((st>>((m+1-index)*2))&3); }
inline void clr(int kk)
{    
 memset(Hash,-1,sizeof(Hash));
 memset(dp[kk],0,sizeof(dp[kk]));
 memset(state[kk],-1,sizeof(state[kk]));
 nstate[kk]=0;
}
void add(int kk,unsigned __int64 data,unsigned __int64 st)
{
 int pos=st%HASH_LIMIT;
 while(Hash[pos]!=-1)
 {
  if(state[kk][Hash[pos]]==st)
  {
   dp[kk][Hash[pos]]+=data;
   return;
  }
  pos=(pos+1)%HASH_LIMIT;
 }
 Hash[pos]=(++nstate[kk]);
 state[kk][Hash[pos]]=st;
 dp[kk][Hash[pos]]=data;
}
unsigned __int64 work()
{
 int i,j,u,v,k=0;
 unsigned __int64 ts,ans=0;
 clr(k); add(k,1,0);//此处为初始化，千万别漏
 for(i=1;i<=n;i++)
 {
  for(j=1;j<=m;j++)
  {
   k^=1;
   clr(k);
   for(u=1;u<=nstate[k^1];u++)
   {
    unsigned long long s=state[k^1][u];
    unsigned long long data=dp[k^1][u];
    int left=get(j,s);
    int up=get(j+1,s);
    if(!canGo(i,j))//如果该格子为障碍
    {
     if(left==0 && up==0) add(k,data,s);
    }
    else
    {
     if(left==0 && up==0)
     {
      if(canGo(i+1,j) && canGo(i,j+1))
      {
       ts=s+shift(1,j)+shift(2,j+1);
       add(k,data,ts);
      }
     }
     else if(left==0 && up>0)
     {
      if(canGo(i,j+1)) add(k,data,s);
      if(canGo(i+1,j))
      {
       int b=get(j+1,s);
       ts=s-shift(b,j+1)+shift(b,j);
       add(k,data,ts);
      }
     }
     else if(left>0 && up==0)
     {
      if(canGo(i+1,j)) add(k,data,s);
      if(canGo(i,j+1))
      {
       int b=get(j,s);
       ts=s-shift(b,j)+shift(b,j+1);
       add(k,data,ts);
      }
     }
     else if(left==1 && up==1)
     {
      int p=1;
      for(v=j+2;v<=m+1;v++)//匹配括号
      {
       int ss=get(v,s);
       if(ss==1) p++;
       if(ss==2) p--;
       if(p==0)
       {
        ts=s-shift(2,v)+shift(1,v);
        break;
       }
      }
      ts=ts-shift(1,j)-shift(1,j+1);
      add(k,data,ts);
     }
     else if(left==2 && up==2)
     {
      int p=1;
      for(v=j-1;v>=1;v--)//匹配括号
      {
       int ss=get(v,s);
       if(ss==1) p--;
       if(ss==2) p++;
       if(p==0)
       {
        ts=s-shift(1,v)+shift(2,v);
        break;
       }
      }
      ts=ts-shift(2,j)-shift(2,j+1);
      add(k,data,ts);
     }
     else if(left==2 && up==1)
     {
      ts=s-shift(2,j)-shift(1,j+1);
      add(k,data,ts);
     }
     else if(left==1 && up==2)
     {
      if(i==nn && j==mm) ans+=data;
     }
    }
   }
  }
  for(int ii=1;ii<=nstate[k];ii++) state[k][ii]=(state[k][ii]>>2);//做完一行，整个状态前移一格（即两位）
 }
 return ans;
}
int main()
{
 int i,j;
 char str[15];
 cin>>n>>m;
 for(i=1;i<=n;i++)
 {
  cin>>str;
  for(j=1;j<=m;j++)
  {
   map[i][j]=(str[j-1]=='.');
   if(map[i][j]) nn=i,mm=j;
  }
 }
 cout<<work()<<endl;
return 0;
}
