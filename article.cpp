#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int nn;
struct node;
node *ns[111];
struct node
{
	node *son[26];
	node *next;
	int label;
	bool vd;
	int tms;
	node()
	{
		memset(son, 0, sizeof(son));
		next = 0;
		tms = 0;
		vd = 0;
		label = nn;
		ns[nn++] = this;
	}
} *root;
char buf[101];
int f[101010][111];
void insert()
{
	node *now = root;
	int l = strlen(buf);
	for (int i = 0; i < l; i++)
	{
		if (buf[i] > 'z' || buf[i] < 'a')
			break;
		if (!now->son[buf[i] - 'a'])
			now->son[buf[i] - 'a'] = new node;
		now = now->son[buf[i] - 'a'];
	}
	now->tms++;
}
void mkfail()
{
	root->next = root;
	queue<node *> q;
	for (int i = 0; i < 26; i++)
		if (!root->son[i])
			root->son[i] = root;
		else
		{
			root->son[i]->next = root;
			q.push(root->son[i]);
		}
	while (!q.empty())
	{
		node *now = q.front();
		q.pop();
		for (int i = 0; i < 26; i++)
			if (now->son[i])
			{
				now->son[i]->next = now->next->son[i];
				now->son[i]->tms += now->next->son[i]->tms;
				q.push(now->son[i]);
			}
			else
				now->son[i] = now->next->son[i];
	}
}
int main()
{
	root = new node;
	int n, m;
	scanf("%d%d", &n, &m);
	gets(buf);
	for (int i = 0; i < n; i++)
	{
		gets(buf);
		insert();
	}
	mkfail();
	memset(f, 0xCC, sizeof(f));
	f[0][0] = 0;
	for (int i = 0; i < m; i++)
	{
		int *fn = f[i];
		int *fp = f[i + 1];
		for (int j = 0; j < nn; j++)
			if (fn[j] >= 0)
				for (int k = 0; k < 26; k++)
					fp[ns[j]->son[k]->label] = max(fp[ns[j]->son[k]->label], fn[j] + ns[j]->son[k]->tms);
	}
	int ans = 0;
	for (int i = 0; i < nn; i++)
		ans = max(ans, f[m][i]);
	printf("%d", ans);
	return 0;
}
