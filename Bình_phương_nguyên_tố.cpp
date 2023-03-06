/*
* Một số được coi là số đẹp khi nó đồng thời vừa chia hết cho một số nguyên tố và chia hết cho bình phương của số nguyên tố đó. Viết chương trình liệt kê các số đẹp như vậy trong đoạn giữa hai số nguyên dương cho trước.
*/
#include<iostream>
#include<math.h>
using namespace std;

bool isPrime(int n)
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

int main()
{
	int a = 0, b = 0, j = 0;
	cin >> a >> b;
	// in binh phuong so nguyen to
	for (int i = a; i <= b; i++)
	{
		int tmp = i;
		j = 2;
		while (j * j <= tmp)
		{
			if (isPrime(j))
			{
				if (tmp % j == 0)
				{
					if (tmp % (j * j) == 0)
					{
						cout << i << " ";
						break;
					}
					else tmp /= j;
				}
			}
			++j;
		}
	}

	return 0;
}