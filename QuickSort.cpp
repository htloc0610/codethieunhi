#include<iostream>
using namespace std;

int LomutoPartition(int a[], int l, int r)
{
	int x = a[r];
	int i = l - 1;
	for (int j = l; j < r; j++)
	{
		if (a[j] <= x)
		{
			i++;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[r]);
	return i + 1;
}

int HoarePartition(int a[], int l, int r)
{
	int x = a[l];
	int i = l;
	int j = r;
	while (true)
	{
		while (a[j] > x)
		{
			j--;
		}
		while (a[i] < x)
		{
			i++;
		}
		if (i < j)
		{
			swap(a[i], a[j]);
		}
		else
		{
			return j;
		}
	}
}

void QuickSort(int a[], int l, int r)
{
	if (l < r)
	{
		int p = HoarePartition(a, l, r);
		QuickSort(a, l, p - 1);
		QuickSort(a, p + 1, r);
	}
}

int main()
{
	int a[] = { 1, 3, 5, 4, 2, 9, 6 };
	int n = sizeof(a) / sizeof(a[0]);
	QuickSort(a, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}