#include<iostream>
using namespace std;

//Nhe noi len
void BubleSort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = n - 2; j >= i; j--)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}

//Nang chim xuong
void BubleSort1(int a[], int n)
{
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = 0; j < i ; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}

//Ket hop vua nang vua nhe
void BubleSort2(int a[], int n)
{
	int dau = 0, cuoi = n;
	while (dau < cuoi)
	{
		//Nhe noi len
		for (int j = cuoi - 2; j >= dau; j--)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
		dau++;
		//Nang chim xuong
		for (int j = dau; j < cuoi - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
		cuoi--;
	}
}

int main()
{
	int a[] = { 1,4,5,6,3,8,9,5 };
	int n = sizeof(a) / sizeof(a[0]);
	BubleSort2(a, n);
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}