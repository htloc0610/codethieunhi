#include<iostream>
#include<queue>
using namespace std;

int m, n;
char a[100][100];
bool visit[100][100];
int dx[4] = { -1, 0, 0, 1 };
int dy[4] = { 0, -1, 1, 0 };

//6 6
//x x x o o o
//o o x o o o
//o x x x x o
//o o o o o x
//x x o x o x
//x o x x o x

void DFS(int i, int j)
{
	visit[i][j] = true;
	for (int k = 0; k < 4; k++)
	{
		int i1 = i + dx[k];
		int j1 = j + dy[k];
		if (i1 >= 1 && i1 <= m && j1 >= 1 && j1 <= n && !visit[i1][j1] && a[i][j] == 'x')
		{
			DFS(i1, j1);
		}
	}
}

void BFS(int i, int j)
{
	queue<pair<int, int>> q;
	q.push({ i, j });
	visit[i][j] = true;
	while (!q.empty())
	{
		pair<int, int> top = q.front();
		q.pop();
		for (int k = 0; k < 4; k++)
		{
			int i1 = top.first + dx[k];
			int j1 = top.second + dy[k];
			if (i1 >= 1 && i1 <= m && j1 >= 1 && j1 <= n && !visit[i1][j1] && a[i1][j1] == 'x')
			{
				q.push({ i1, j1 });
				visit[i1][j1] = true;
			}
		}
	}
}


int main()
{
	cin >> m >> n;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> a[i][j];
		}
	}
	memset(visit, false, sizeof(visit));
	int count = 0;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (!visit[i][j] && a[i][j] == 'x')
			{
				++count;
				BFS(i, j);
			}
		}
	}
	cout << count;
	return 0;
}