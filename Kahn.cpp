#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<int>a[10];
int point[10] = {};
queue<int> kahn;
int n = 0, m = 0;

//7 7
//1 2
//2 3
//2 4
//4 5
//3 5
//7 6
//1 6

void KAHN()
{
	for (int i = 1; i <= n; i++)
	{
		if (point[i] == 0)
		{
			kahn.push(i);
		}
	}
	while (!kahn.empty())
	{
		int u = kahn.front();
		cout << u << " ";
		for (int x : a[u])
		{
			point[x]--;
			if (point[x] == 0)
			{
				kahn.push(x);
			}
		}
		kahn.pop();
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int k, l;
		cin >> k >> l;
		a[k].push_back(l);
		point[l]++;
	}
	KAHN();
	return 0;
}