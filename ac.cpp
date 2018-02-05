#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct node
{
	node *son[128];
	node *next;
	vector<int> *end;
	bool vd;
	int tms;
	node()
	{
		memset(son, 0, sizeof(son));
		next = 0;
		tms = 0;
		vd = 0;
		end = new vector<int>;
	}
} *root;
bool ts[501010];
char buf[1010101];
long long ans[1010101];
void insert(int n)
{
	node *now = root;
	int l = strlen(buf);
	for (int i = 0; i < l; i++)
	{
		if (buf[i] > 126 || buf[i] < 32)
			break;
		if (!now->son[buf[i]])
			now->son[buf[i]] = new node;
		now = now->son[buf[i]];
	}
	now->tms++;
	now->end->push_back(n);
}
void mkfail()
{
	root->next = root;
	queue<node *> q;
	for (int i = 0; i < 128; i++)
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
		for (int i = 0; i < 128; i++)
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
void qry(int n)
{
	int l = strlen(buf);
	long long an = 0;
	node *now = root;
	for (int i = 0; i < l; i++)
	{
		now = now->son[buf[i]];
		an += now->tms;
		node *tmp = now;
		while (!tmp->vd)
		{
			tmp->vd = 1;
			for (vector<int>::iterator j = tmp->end->begin(); j != tmp->end->end(); j++)
				ts[*j] = 1;
			tmp = tmp->next;
		}
	}
	ans[n] = an;
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
		insert(i);
	}
	mkfail();
	for (int i = 0; i < m; i++)
	{
		gets(buf);
		qry(i);
	}
	for (int i = 0; i < n; i++)
		printf("%d", ts[i] ? 1 : 0);
	printf("\n");
	for (int i = 0; i < m; i++)
		printf("%I64d ", ans[i]);
	printf("\n");
}
