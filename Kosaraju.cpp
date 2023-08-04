#include<iostream>
#include<vector>
#include<stack>
using namespace std;

const int maxn = 100;
int n, m;
vector<int> adj[maxn], r_adj[maxn];
bool used[maxn];
stack<int> st;

void inp()
{
	cin >> n >> m;
	while (m != 0)
	{
		int k, l;
		cin >> k >> l;
		adj[k].push_back(l);
		r_adj[l].push_back(k);
		--m;
	}
}

void DFS1(int u)
{
	used[u] = true;
	for (int v : adj[u])
	{
		if (!used[v])
		{
			DFS1(v);
		}
	}
	st.push(u);
}

void DFS2(int u)
{
	used[u] = true;
	cout << u << " ";
	for (int v : r_adj[u])
	{
		if (!used[v])
		{
			DFS2(v);
		}
	}
}

void SCC()
{
	memset(used, false, sizeof(used));
	for (int i = 1; i <= n; i++)
	{
		if (!used[i])
		{
			DFS1(i);
		}
	}
	memset(used, false, sizeof(used));
	while (!st.empty())
	{
		int u = st.top();
		if (!used[u])
		{
			DFS2(u);
			cout << endl;
		}
		st.pop();
	}
}

int main()
{
	inp();
	SCC();
	return 0;
}