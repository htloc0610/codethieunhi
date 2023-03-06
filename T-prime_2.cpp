/*
* Cho số tự nhiên N. Nhiệm vụ của bạn là hãy đếm tất cả các số có đúng ba ước số. Ví dụ n=100, ta có số 4
*/
#include<iostream>
#include<math.h>
using namespace std;

void input(long& a)
{
	cin >> a;
}

bool kt_nguyento(long a)
{
	int dem = 0;
	for (long i = 2; i * i <= a; i++)
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

long check(long a)
{
	long dem = 0;
	for (long i = 1; i <= a; i++)
	{
		if (kt_nguyento(i))
			dem++;
	}
	return dem;
}

void output(long a)
{
	cout << check(sqrt(a));
}

int main()
{
	long a = 0;
	input(a);
	output(a);

	return 0;
}