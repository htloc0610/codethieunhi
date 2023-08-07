#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Edge {
	int u, v;
	int w;
};

int n, m;
int parent[100], sz[100];
vector<Edge>a;

//6 9
//1 2 12
//1 3 4
//2 3 1
//2 4 5
//2 5 3
//3 5 2
//4 5 3
//4 6 10
//5 6 8

void make_set()
{
	for (int i = 1; i <= n; i++)
	{
		parent[i] = i;
		sz[i] = i;
	}
}

int find(int v)
{
	if (v == parent[v])
	{
		return v;
	}
	return parent[v] = find(parent[v]); 
}

bool Union(int a, int b)
{
	a = find(a);
	b = find(b);
	if (a == b)
	{
		return false;
	}
	if (sz[a] < sz[b])
	{
		swap(a, b);
	}
	parent[b] = a;
	sz[a] += sz[b];
	return true;
}

void input()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		Edge x;
		cin >> x.u >> x.v >> x.w;
		a.push_back(x);
	}
}

bool cmp(Edge a, Edge b)
{
	return a.w < b.w;
}

void Kruskal()
{
	//Tao cay khung
	vector<Edge> mst;
	int d = 0;
	//Sort dsach canh theo chieu dai tang dan
	sort(a.begin(), a.end(), cmp);
	//Lap
	for (int i = 0; i < m; i++)
	{
		if (mst.size() == n - 1)
		{
			break;
		}
		Edge e = a[i];
		if (Union(e.u, e.v))
		{
			mst.push_back(e);
			d += e.w;
		}
	}
	// Tra ve ket qua
	if (mst.size() != n - 1)
	{
		cout << "Do thi khong lien thong";
	}
	else
	{
		cout << "MST: " << d << endl;
		for (auto it : mst)
		{
			cout << it.u << " " << it.v << " " << it.w << endl;
		}
	}
}

int main()
{
	input();
	make_set();
	Kruskal();
	return 0;
}