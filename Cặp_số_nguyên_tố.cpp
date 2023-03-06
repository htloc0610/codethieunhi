/*
* Cho số nguyên dương chẵn N>2. Hãy liệt kê các cặp số nguyên tố p,q có tổng đúng bằng N
	Ví dụ N=6 ta có 1 cặp số nguyên tố là 3+3=6
*/
#include<iostream>
using namespace std;

bool isPrime(long long n)
{
	for (long long i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			return 0;
		}
	}
	if (n < 2)
	{
		return 0;
	}
	return 1;
}

int main()
{
	int n, m = 0;
	cin >> n;
	while (n != 0)
	{
		cin >> m;
		for (int i = 2; i <= m / 2; i++)
		{
			if (isPrime(i) && isPrime(m - i))
			{
				cout << i << " " << m - i << endl;
			}
		}
		--n;
	}

	return 0;
}