#include<iostream>
#include<set>
#include<stack>
#include<vector>
using namespace std;

int n, m;
set<int> adj[10001];
int degree[10001];

void nhap()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		adj[x].insert(y);
		adj[y].insert(x);
	}
}

void euler(int x)
{
	stack<int> st;
	vector<int> EC;
	st.push(x);
	while (!st.empty())
	{
		int v = st.top();
		if (!adj[v].empty())
		{
			int u = *adj[v].begin();
			st.push(u);
			//Xoa (u,v)
			adj[v].erase(u);
			adj[u].erase(v);
		}
		else
		{
			st.pop();
			EC.push_back(v);
		}
	}
	reverse(begin(EC), end(EC));
	for (int x : EC)
	{
		cout << x << " ";
	}
}

int main()
{
	nhap();
	euler(1);
	return 0;
}