#include<iostream>
#include<vector>
using namespace std;

void Merge(int a[], int l, int m, int r)
{
	vector<int>x(a + l, a + m + 1);
	vector<int>y(a + m + 1, a + r + 1);
	int i = 0, j = 0;
	while (i < x.size() && j < y.size())
	{
		if (x[i] <= y[j])
		{
			a[l++] = x[i++];
		}
		else
		{
			a[l++] = y[j++];
		}
	}
	while (i < x.size())
	{
		a[l++] = x[i++];
	}
	while (j < y.size())
	{
		a[l++] = y[j++];
	}
}

void MergerSort(int a[], int l, int r)
{
	if (l >= r)
	{
		return;
	}
	int m = (l + r) / 2;
	MergerSort(a, l, m);
	MergerSort(a, m + 1, r);
	Merge(a, l, m, r);
}

int main()
{
	int a[] = { 1, 5, 6, 3, 8, 6, 9, 4 };
	int n = sizeof(a) / sizeof(a[0]);
	MergerSort(a, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}