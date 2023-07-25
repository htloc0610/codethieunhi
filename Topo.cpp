#include<iostream>
#include<stack>
#include<vector>
using namespace std;

vector<int>a[10];
bool visit[10];
vector<int> topo;

void DFS(int u)
{
	visit[u] = true;
	for (int x : a[u])
	{
		if (!visit[x])
		{
			DFS(x);
		}
	}
	topo.push_back(u);
}

int main()
{
	int n = 0, m = 0;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int k, l;
		cin >> k >> l;
		a[k].push_back(l);
	}
	memset(visit, false, sizeof(visit));
	for (int i = 1; i <= n; i++)
	{
		if (!visit[i])
		{
			DFS(i);
		}
	}
	reverse(topo.begin(), topo.end());
	for (int x : topo)
	{
		cout << x << " ";
	}
	return 0;
}