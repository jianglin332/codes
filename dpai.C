#include<stdio.h>
#include<string.h>
#include<algorithm>
#define HASH 10007
#define MAXD 10010
int N, M, pre[65][MAXD];
char g[10][10], op[65][MAXD];
struct HashMap
{
    int head[HASH], size, next[MAXD], st[MAXD], col[MAXD], dp[MAXD];
    void init()
    {
        memset(head, -1, sizeof(head)), size = 0;    
    }
    void push(int _st, int _col, int _dp, int id, int k, char ch)
    {
        int i, h = ((_st << 6) + _col) % HASH;
        for(i = head[h]; i != -1; i = next[i])
            if(st[i] == _st && col[i] == _col)
            {
                dp[i] += _dp;
                return ;    
            }
        st[size] = _st, col[size] = _col, dp[size] = _dp;
        pre[id][size] = k, op[id][size] = ch;
        next[size] = head[h], head[h] = size ++;
    }
}hm[2];
int code[10], h[10];
int encode(int *code, int m)
{
    int i, st = 0, cnt = -1;
    memset(h, -1, sizeof(h));
    for(i = 0; i < m; i ++)
    {
        if(h[code[i]] == -1) h[code[i]] = ++ cnt;
        st = st << 3 | h[code[i]];    
    }
    return st;
}
void decode(int *code, int m, int st)
{
    for(int i = m - 1; i >= 0; i --) code[i] = st & 7, st >>= 3;    
}
void init()
{
    int i;
    scanf("%d%d", &N, &M);
    for(i = 0; i < N; i ++) scanf("%s", g[i]);    
}
void dp(int i, int j, int c, int cur)
{
    int k;
    for(k = 0; k < hm[cur].size; k ++)
    {
        int col = hm[cur].col[k], u = i ? (col >> j & 1) == c : 0, l = j ? (col >> j - 1 & 1) == c : 0, lu = (col >> M) == c;    
        if(u && l && lu) continue;
        if(i == N - 1 && j == M - 1 && !u && !l && lu) continue;
        decode(code, M, hm[cur].st[k]);
        if(i && !u)
        {
            int s1 = 0, s2 = 0;
            for(int t = 0; t < M; t ++)
            {
                if(code[t] == code[j]) ++ s1;
                if((col >> t & 1) != c) ++ s2;    
            }
            if(s1 == 1)
            {
                if(s2 > 1) continue;
                if(i < N - 1 || j < M - 2) continue;    
            }
        }
        if(u && l)
        {
            if(code[j] != code[j - 1])
                for(int t = 0, x = code[j]; t < M; t ++)
                    if(code[t] == x) code[t] = code[j - 1];    
        }
        else if(!u && l) code[j] = code[j - 1];
        else if(!u && !l) code[j] = M;
        
        if(col & 1 << j) col |= 1 << M;
        else col &= ~(1 << M);
        if(c) col |= 1 << j;
        else col &= ~(1 << j);
        
        hm[cur ^ 1].push(encode(code, M), col, hm[cur].dp[k], i * M + j, k, c ? '#' : 'o');
    }
}
void print(int k)
{
    int i, j;
    for(i = N - 1; i >= 0; i --)
        for(j = M - 1; j >= 0; j --)
            g[i][j] = op[i * M + j][k], k = pre[i * M + j][k];
    for(i = 0; i < N; i ++) puts(g[i]);
}
void solve()
{
    int i, j, k, cur = 0, ans = 0;
    hm[0].init();
    hm[0].push(0, 0, 1, 0, 0, 0);
    for(i = 0; i < N; i ++)
        for(j = 0; j < M; j ++)
        {
            hm[cur ^ 1].init();
            if(g[i][j] != '#') dp(i, j, 0, cur);
            if(g[i][j] != 'o') dp(i, j, 1, cur);
            cur ^= 1;
        }
    for(i = 0; i < hm[cur].size; i ++)
    {
        int max = 0;
        decode(code, M, hm[cur].st[i]);
        for(j = 0; j < M; j ++) max = std::max(max, code[j]);
        if(max > 1) continue;
        ans += hm[cur].dp[i], k = i;
    }
    printf("%d\n", ans);
    if(ans != 0) print(k);
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t --)
    {
        init();
        solve();
        printf("\n");
    }
    return 0;    
}
