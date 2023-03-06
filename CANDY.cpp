#include<iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int* a = new int [n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (int i = n-2; i >= 0; i--)
	{
		a[i] += a[i + 1] / 2;
	}
	cout << a[0];
	delete[] a;
	return 0;
}