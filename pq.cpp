#include <cstdio>
#include <queue>
using namespace std;
struct num
{
	int v;
	int p;
	num(int _v, int _p)
	{
		v = _v;
		p = _p;
	}
};
struct cmp
{
	bool operator()(const num &a, const num &b)
	{
		return a.v > b.v;
	}
};
int ns[101010];
int main()
{
	priority_queue<num, vector<num>, cmp> pn;
	int n;
	scanf("%d", &n);
	int now = 0, from = 0;
	for (int i = 0; i < n; i++)
	{
		int t;
		scanf("%d", &t);
		if (t == 1)
		{
			int tmp;
			scanf("%d", &tmp);
			ns[now] = tmp;
			pn.push(num(tmp, now++));
		}
		else if (t == 2)
		{
			printf("%d ", ns[from++]);
		}
		else if (t == 3)
		{
			while ((!pn.empty()) && pn.top().p < from)
				pn.pop();
			if (nclude <cstdio>
#include <queue>
					using namespace std;
					struct num 
					{
					        int v;
						        int p;
							        num(int _v, int _p) 
								        {   
									                v = _v; 
											                p = _p; 
													        }   
														};
														struct cmp 
														{
														        bool operator()(const num &a, const num &b) 
															        {
																                return a.v > b.v;
																		        }
																			};
																			int ns[101010];
																			int main()
																			{
																				        priority_queue<num, vector<num>, cmp> pn; 
																					        int n;
																						        scanf("%d", &n);
																							        int now = 0, from = 0;
																								        for (int i = 0; i < n; i++)
																										        {
																												                int t;
																														                scanf("%d", &t);
																																                if (t == 1)
																																			                {
																																						                        int tmp;
																																									                        scanf("%d", &tmp);
																																												                        ns[now] = tmp;
																																															                        pn.push(num(tmp, now++));
																																																		                }   
																																		                else if (t == 2)
																																					                {   
																																								                        printf("%d ", ns[from++]);
																																											                }
																																				                else if (t == 3)
																																							                {
																																										                        while ((!pn.empty()) && pn.top().p < from)
																																														                                pn.pop();
																																													                        if (pn.empty())
																																																	                                printf("-1 ");
																																																                        else
																																																				                                printf("%d", pn.top().v);
																																																			                }
																																						        }
																									        return 0;
																			}
																			~                                                                                                        
																				~                                                                                                        
																				~                                                                                                        
																				~                                                                                                        
																				~                                                                                                        
																				~                                                                                                        
																				:set nonumber                                                                          20,2         全部
																				pn.empty())
				printf("-1 ");
			else
				printf("%d ", pn.top().v);
		}
	}
	return 0;
}
