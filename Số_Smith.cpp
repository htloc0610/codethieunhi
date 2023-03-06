/*
* Cho số tự nhiên N
. Nhiệm vụ của bạn là hãy kiểm tra N
 có phải là số Smith hay không. Một số được gọi là số Smith nếu N
 không phải là số nguyên tố và có tổng các chữ số của N
 bằng tổng các chữ số của các ước số nguyên tố của N
. Ví dụ N = 666 có các ước số nguyên tố là 2, 3, 3, 37 có tổng các chữ số là 18.
*/
#include<iostream>
using namespace std;

int isPrime(int n)
{
	for (int i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			return 0;
		}
	}

	return n > 1;
}

int sumDigits(int n)
{
	int s = 0;
	while (n != 0)
	{
		s += n % 10;
		n /= 10;
	}

	return s;
}

int sumDivisor(int n)
{
	int s = 0;
	while (n != 1)
	{
		for (int i = 2; i <= n; i++)
		{
			if (isPrime(i))
			{
				if (n % i == 0)
				{
					while (n % i == 0)
					{
						s += sumDigits(i);
						n /= i;
					}
				}
			}
		}
	}
	return s;
}



int main()
{
	int n = 0, m = 0;
	cin >> n;
	while (n != 0)
	{
		cin >> m;
		if ((isPrime(m) == 0) && (sumDigits(m) == sumDivisor(m)))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
		--n;
	}

	return 0;
}