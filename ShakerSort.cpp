#include<iostream>
using namespace std;

//Ket hop vua nang vua nhe
void ShakerSort(int a[], int n)
{
	int dau = 0, cuoi = n, m = n;
	while (dau < cuoi)
	{
		//Nhe noi len
		for (int j = cuoi - 2; j >= dau; j--)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
				m = j;
			}
		}
		dau = m;
		//Nang chim xuong
		for (int j = dau; j < cuoi - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
				m = j;
			}
		}
		cuoi = m;
	}
}

int main()
{
	int a[] = { 1,4,5,6,3,8,9,5 };
	int n = sizeof(a) / sizeof(a[0]);
	ShakerSort(a, n);
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}