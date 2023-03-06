/*
* Cho số tự nhiên N. Nhiệm vụ của bạn là hãy liệt kê tất cả các số có đúng ba ước số. Ví dụ n=100, ta có các số 4,9,25,49.
*/
#include<iostream>
#include<math.h>
using namespace std;

void input(int& a, int arr[])
{
	cin >> a;
	for (int i = 0; i < a; i++)
	{
		cin >> arr[i];
	}
}

bool kt_nguyento(int a)
{
	int dem = 0;
	for (int i = 2; i * i <= a; i++)
	{
		if (a % i == 0)
		{
			dem = 1;
			break;
		}
	}
	if ((dem == 1) || a < 2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void check(int a)
{
	for (int i = 1; i <= a; i++)
	{
		if (kt_nguyento(i))
			cout << i * i << " ";
	}
	cout << endl;
}

void output(int a, int arr[])
{
	for (int i = 0; i < a; i++)
	{
		check(sqrt(arr[i]));
	}
}

int main()
{
	int a = 0;
	int arr[100];
	input(a, arr);
	output(a, arr);

	return 0;
}