#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
 
using namespace std;
 
int a[300000];
int toAdd[300000];
 
long long S[300000];
long long C[300000];
long long D[300000];
long long Begins[300000];
int c[300000];
int prefSum[300000];
 
long long md = 1000000007;
 
const int magic = 300;
//const int magic = 0;
 
long long fpow(long long a, long long b){
     long long ans = 1;
     while (b){
           if (b % 2) ans = (ans * a) % md;
           a = (a * a) % md;
           b /= 2;
     }
     return ans;
}
 
vector<int> positions[200000];
 
int fenv[300000];
 
void f_up(int v, int val){
     if (val < 0) val += md;
     while (v <= 100000){
           fenv[v] += val;
           if (fenv[v] >= md) fenv[v] -= md;
           
           v = (v | (v + 1));
     }
}
 
int f_get(int v){
    int val = 0;
    while (v > 0){
          val += fenv[v];
          if (val >= md) val -= md;
          v = (v & (v + 1)) - 1;
    }
    
    return val;
}
 
int main(){
    int n;
    
    scanf("%d", &n);
    
    long long Ans = 0;
    
    for (int i = 1; i <= n; i++){
        scanf("%d", a + i);
//        a[i]   = rand()%10+1;
        c[a[i]]++;
        positions[a[i]].push_back(i);
    }
    
    for (int N = 1; N <= 100000; N++){
        if (c[N] > magic){
           int toSet = c[N];
           
           for (int i = 1; i <= n; i++){
               if (a[i] == N){
                  toSet--;
                  toAdd[i] = toSet;
               } else toAdd[i] = 0;
           }
           
           for (int Num = 1; Num <= 100000; Num++){
               S[Num] = 0;
               D[Num] = 0;
               C[Num] = 0;
           }
           
           long long sumS = 0;
           long long sumC = 0;
           long long last = c[N];
           
           for (int i = 1; i <= n; i++){
               if (a[i] == N){
                  sumS += toAdd[i];
                  sumC++;
                  last = toAdd[i];
               } else {
                 long long temp = sumS * C[a[i]] - S[a[i]] - (sumC * C[a[i]] - D[a[i]]) * last;                
                 Ans = (Ans + temp) % md;
                 D[a[i]] += sumC;
                 C[a[i]]++;
                 S[a[i]] += sumS;
               }
           }
        }
    }
 
    for (int i = 1; i <= n; i++){
        if (c[a[i]] <= magic){
           int j = positions[a[i]].size() - 1;
           long long temp = 0;
           int intervals = 0;
           while (positions[a[i]][j] > i){
                 intervals++;
                 temp += f_get(positions[a[i]][j]);
                 f_up(positions[a[i]][j], -1);
//                 cout << i << " " << a[i] << " " << positions[a[i]][j] << " " << temp << endl;
                 j--;
           }
           temp %= md;
           f_up(i, intervals);
                     
           Ans = (Ans + temp) % md;
           
           j--;
           
           intervals = 0;
           while (j >= 0){
                 intervals++;
                 f_up(positions[a[i]][j], -1);
                 j--;
           }           
           f_up(i, intervals);
        }
    }
    
    
    for (int Num = 1; Num <= 100000; Num++)
        if (c[Num] <= magic){
             int temp = c[Num];
             temp = (temp * (c[Num] - 1)) % md;
             temp = (temp * (c[Num] - 2)) % md;
             temp = (temp * (c[Num] - 3)) % md;                
             temp = (temp * fpow(24, md - 2)) % md;
             Ans = (Ans - temp % md + md) % md;
        }
 
/*    Ans = 0;
    for (int Num = 1; Num <= 100000; Num++){        
           if (c[Num] == 0) continue;
        //if (c[Num] > magic){        
           prefSum[0] = 0;
           for (int i = 1; i <= n; i++){
              prefSum[i] = prefSum[i - 1];
              if (a[i] == Num) prefSum[i]++;
           }
        
           for (int Little = 1; Little <= 100000; Little++){
               //if (c[Little] <= magic){
               if (Little != Num){
                  int lastPos = 0;
                  long long Ssum = 0;
                  for (int i = 0; i < positions[Little].size(); i++){
                      Ans = (Ans + Ssum * (prefSum[n] - prefSum[positions[Little][i]]));
                      Ssum = (Ssum + prefSum[positions[Little][i]]) % md;
                  }                                    
               }
           }
        //}
    }    */
 
    for (int Num = 1; Num <= 100000; Num++){        
        if (c[Num] > magic){        
           prefSum[0] = 0;
           for (int i = 1; i <= n; i++){
               prefSum[i] = prefSum[i - 1];
               if (a[i] == Num) prefSum[i]++;
           }
        
           for (int Little = 1; Little <= 100000; Little++){
               if (c[Little] <= magic){
                  int lastPos = 0;
                  long long Ssum = 0;
                  for (int i = 0; i < positions[Little].size(); i++){
                      Ans = (Ans + Ssum * (prefSum[n] - prefSum[positions[Little][i]]));
                      Ssum = (Ssum + prefSum[positions[Little][i]]) % md;
                  }                                    
               }
           }
        }
    }
 
  
    for (int Num = 1; Num <= 100000; Num++){
        C[Num] = 0;        
    }
       
    
    Begins[0] = 0;
    for (int i = 1; i <= n; i++){
        Begins[i] = Begins[i - 1] + C[a[i]];
        C[a[i]]++;
    }
    
    for (int Num = 1; Num <= 100000; Num++){
        C[Num] = 0;        
    }
    
    long long Ends = 0;
    for (int i = n; i >= 1; i--){
        Ends = C[a[i]];        
        C[a[i]]++;     
           
        Ans += (Begins[i - 1] % md) * (Ends % md);
        Ans %= md;
    }
   
    for (int Num = 1; Num <= 100000; Num++){
        int temp = C[Num];
        temp = (temp * (C[Num] - 1)) % md;
        temp = (temp * (C[Num] - 2)) % md;
        temp = (temp * (C[Num] - 3)) % md;                
        temp = (temp * fpow(24, md - 2)) % md;
        Ans = (Ans - temp % md + md) % md;
    }
    
    Ans = (md - Ans) % md;
    
    long long All = 0;
    for (int Num = 1; Num <= 100000; Num++){
        Ans += All * ((C[Num] * (C[Num] - 1) / 2) % md);        
        Ans %= md;        
        All += C[Num] * (C[Num] - 1) / 2;
        All %= md;
    }
        
    cout << Ans << endl;
    
    system("pause");
    
    return 0;
}