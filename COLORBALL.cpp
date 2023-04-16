#include<iostream>
using namespace std;

int main()
{
	int m = 0, n = 0, k = 0;
	cin >> m >> n >> k;
	int** a = new int* [m];
	for (int i = 0; i < m; i++)
	{
		a[i] = new int[n];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = 0;
		}
	}
	while (k != 0)
	{
		int o = 0, p = 0;
		cin >> o >> p;
		o--;
		p--;
		for (int i = o - 1; i <= o + 1; i++)
		{
			if (i >= 0 && i < m)
			{
				for (int j = p - 1; j <= p + 1; j++)
				{
					if (j >= 0 && j < n)
					{
						if (a[i][j] == 1)
						{
							continue;
						}
						else
						{
							a[i][j] += 1;
						}
					}
				}
			}
		}
		cin >> o >> p;
		o--;
		p--;
		for (int i = o - 1; i <= o + 1; i++)
		{
			if (i >= 0 && i < m)
			{
				for (int j = p - 1; j <= p + 1; j++)
				{
					if (j >= 0 && j < n)
					{
						if (a[i][j] == -1)
						{
							continue;
						}
						else
						{
							a[i][j] -= 1;
						}
					}
				}
			}
		}
		k--;
	}
	int x = 0, y = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 1)
			{
				x++;
			}
			else if (a[i][j] == -1)
			{
				y++;
			}
		}
	}
	cout << x << " " << y;
	for (int i = 0; i < m; i++)
	{
		delete[] a[i];
	}
	delete[] a;
	return 0;
}