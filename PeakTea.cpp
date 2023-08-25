#include<iostream>
#include<vector>
using namespace std;

const int maxn = 1001;

vector<int> adj[maxn];
int m, n;
bool visited[maxn];
vector<pair<int, int>> dscanh;


void nhap()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
		dscanh.push_back({ x,y });
	}
}

void dfs2(int u, int s, int t)
{
	visited[u] = true;
	for (int v : adj[u])
	{
		if (u == s && v == t || u == t && v == s)
		{
			continue;
		}
		if (!visited[v])
		{
			dfs2(v, s, t);
		}
	}
}

void canhcau()
{
	int ans = 0;
	int dem = 0;
	int tplt = 0;
	memset(visited, false, sizeof(visited));
	for (int i = 1; i <= n; i++)
	{
		if (!visited[i])
		{
			++tplt;
			dfs(i);
		}
	}
	for (auto it : dscanh)
	{
		int x = it.first;
		int y = it.second;
		memset(visited, false, sizeof(visited));
		for (int j = 1; j <= n; j++)
		{
			if (!visited[j])
			{
				++dem;
				dfs2(j, x, y);
			}
		}
	}
}

void dfs(int u)
{
	visited[u] = true;
	for (int v : adj[u])
	{
		if (!visited[v])
		{
			dfs(v);
		}
	}
}

void dinhtru()
{
	int ans = 0;
	int tplt = 0;
	memset(visited, false, sizeof(visited));
	for (int i = 1; i <= n; i++)
	{
		if (!visited[i])
		{
			++tplt;
			dfs(i);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		//Loai bo dinh i
		memset(visited, false, sizeof(visited));
		visited[i] = true;
		int dem = 0;
		for (int j = 1; j <= n; j++)
		{
			if (!visited[j])
			{
				++dem;
				dfs(j);
			}
		}
		if (dem > tplt)
		{
			++ans;
		}
	}
	cout << ans;
}

int main()
{
	nhap();
	dinhtru();
	return 0;
}