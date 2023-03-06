#include<iostream>
using namespace std;

void Input(int* a, int p)
{
	for (int i = 0; i < p; i++)
	{
		cin >> a[i];
	}
}

void FirstPrint(int* a, int p)
{
	for (int i = p - 1; i >= 0; i--)
	{
		bool check = 1;
		for (int j = i; j < p; j++)
		{
			if (i == j)
			{
				continue;
			}
			if (a[i] == a[j])
			{
				check = 0;
				break;
			}
		}
		if (check)
		{
			cout << a[i] << endl;
		}
	}
}

void SecondPrint(int* a, int n, int p)
{
	for (int i = 1; i <= n; i++)
	{
		bool check = 1;
		for (int j = 0; j < p; j++)
		{
			if (a[j] == i)
			{
				check = 0;
				break;
			}
		}
		if (check)
		{
			cout << i << endl;
		}
	}
}

int main()
{
	int n = 0, p = 0;
	cin >> n >> p;	
	int* a = new int[p];
	Input(a, p);
	FirstPrint(a, p);
	SecondPrint(a, n, p);
	delete[] a;

	return 0;
}