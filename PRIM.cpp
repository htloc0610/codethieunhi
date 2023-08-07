#include<iostream>
#include<vector>
using namespace std;

//B1 : Khoi tao
//6 8
//1 2 9
//1 3 4
//2 3 1
//2 4 6
//3 5 2
//4 5 3
//4 6 10
//5 6 8

struct canh {
	int x, y, w;
};

int n, m;
vector<pair<int, int>> adj[100];
bool used[100];//used[i] = true -> V (MST), used[i] = false : i thuoc tap V

void nhap()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y, z;
		cin >> x >> y >> z;
		adj[x].push_back({ y, z });
		adj[y].push_back({ x, z });
	}
	memset(used, false, sizeof(used));
}

void prim(int u)
{
	vector<canh> MST;
	int d = 0;
	used[u] = true;
	while (MST.size() < n - 1)
	{
		// e = (x, y) x thuoc V, y thuoc V (MST)
		int min_w = INT_MAX;
		int X, Y;
		for (int i = 1; i <= n; i++)
		{
			if (used[i] == true) // i thuoc V (MST)
			{
				// Duyet danh sach ke
				for (auto it : adj[i])
				{
					int j = it.first;
					int trongso = it.second;
					if (!used[j] && trongso < min_w)
					{
						min_w = trongso;
						X = j;
						Y = i;
					}
				}

			}
		}
		MST.push_back({ X,Y,min_w });
		d += min_w;
		used[X] = true;
	}
	cout << d << endl;
	for (canh e : MST)
	{
		cout << e.x << " " << e.y << " " << e.w << endl;
	}
}

int main()
{
	nhap();
	prim(1);
	return 0;
}