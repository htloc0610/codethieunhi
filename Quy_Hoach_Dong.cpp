#include<iostream>
using namespace std;

int n = 0, m = 0;

bool check(int x,int a[])
{
	a[n] = a[n - 1] + 100;
	int dem = 0, index = 0;
	for (int i = 0; i <= n; i++)
	{
		if (a[index] + 2 * x < a[i])
		{
			index = i;
			++dem;
		}
	}
	return (dem <= m);
}

int main()
{
	cin >> n >> m;
	int* a = new int[n+1];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (a[i] < a[j])
			{
				swap(a[i], a[j]);
			}
		}
	}
	int l = a[0], r = a[n - 1], ans = 0;
	while (l <= r)
	{
		int mid = (r + l) / 2;
		if (check(mid,a))
		{
			r = mid - 1;
			ans = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	cout << ans;
	delete[] a;
}