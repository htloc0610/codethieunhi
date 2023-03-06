#include<iostream>
using namespace std;

int main()
{
	int m, n;
	cin >> m >> n;
	int** a = new int * [m];
	for (int i = 0; i < m; i++)
	{
		a[i] = new int[n];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < m; i++)
	{
		delete[] a[i];
	}
	delete[] a;
	return 0;
}