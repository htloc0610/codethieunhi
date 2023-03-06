/*
* Số nguyên dương N được gọi là số Sphenic nếu N
 được phân tích duy nhất dưới dạng tích của ba số khác nhau
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

int main()
{
	int n = 0, m = 0;
	cin >> n;
	while (n != 0)
	{
		cin >> m;

		if (isPrime(m))
		{
			cout << 0 << endl;
		}
		else
		{
			int count = 0;
			bool ok = true;
			for (int i = 2; i <= m; i++)
			{
				if (isPrime(i))
				{
					if (m % i == 0)
					{
						count++;
						m /= i;
						if (m % i == 0 || count > 3)
						{
							ok = false;
							break;
						}
					}
				}
			}

			if (count < 3 || !ok)
			{
				cout << 0 << endl;
			}
			else
			{
				cout << 1 << endl;
			}
		}

		--n;
	}

	return 0;
}