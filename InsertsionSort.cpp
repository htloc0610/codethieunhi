#include<iostream>
using namespace std;

void InsertsionSort(int a[], int n)
{
	int key;
	for (int i = 1; i < n; i++)
	{
		key = a[i];
		int j = i - 1;
		/* Di chuyển các phần tử có giá trị lớn hơn giá trị
	    key về sau một vị trí so với vị trí ban đầu
	    của nó */
		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

int main()
{
	int a[] = { 1, 5, 6, 7, 4, 9, 2, 3 };
	int n = sizeof(a) / sizeof(a[0]);
	InsertsionSort(a, n);
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}