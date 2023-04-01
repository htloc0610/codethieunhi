#include<iostream>
using namespace std;

int main()
{
	long long m = 0, n = 0;
	cin >> m >> n;
	long long** a = new long long* [m];
	for (long long i = 0; i < m; i++)
	{
		a[i] = new long long[n];
	}
	for (long long i = 0; i < m; i++)
	{
		for (long long j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}
	long long max = 0;
	for (long long i = 0; i < m; i++)
	{
		for (long long j = 0; j < n; j++)
		{
			if (a[i][j] == 1)
			{
				long long dem1 = 0, dem2 = 0;
				for (long long k = j; k < n; k++)
				{
					if (a[i][k] == 1)
					{
						++dem1;
					}
					else
					{
						break;
					}
				}
				for (long long k = i; k < m; k++)
				{
					if (a[k][j] == 1)
					{
						++dem2;
					}
					else
					{
						break;
					}
				}
				if (dem1 * dem2 > max)
				{
					max = dem1 * dem2;
				}
			}
		}
	}
	cout << max;


	for (long long i = 0; i < m; i++)
	{
		delete[] a[i];
	}
	delete[] a;
	return 0;
}