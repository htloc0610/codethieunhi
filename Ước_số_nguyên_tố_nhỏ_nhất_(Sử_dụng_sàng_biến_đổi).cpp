/*
* Cho số tự nhiên N
. Nhiệm vụ của bạn là in ra ước số nguyên tố nhỏ nhất của các số từ 1 đến N
. Ước số nguyên tố nhỏ nhất của 1 là 1. Ước số nguyên tố nhỏ nhất của các số chẵn là 2. Ước số nguyên tố nhỏ nhất của các số nguyên tố là chính nó.
*/
#include<iostream>
using namespace std;

void sudungsangnguyento(bool sangnguyento[])
{
	for (int i = 0; i < 100001; i++)
	{
		sangnguyento[i] = 1;
	}
	sangnguyento[0] = 0;
	sangnguyento[1] = 1;
	for (int i = 2; i * i < 100001; i++)
	{
		if (sangnguyento[i])
		{
			for (int j = i * i; j < 100001; j += i)
			{
				sangnguyento[j] = 0;
			}
		}
	}
}

int main()
{
	bool sangnguyento[100001];
	sudungsangnguyento(sangnguyento);
	int n = 0, m = 0;
	cin >> n;
	while (n != 0)
	{
		cin >> m;
		for (int i = 1; i <= m; i++)
		{
			if (sangnguyento[i])
			{
				cout << i << " ";
			}
			else
			{
				for (int j = 2; j <= i / 2; ++j)
				{
					if (i % j == 0)
					{
						if (sangnguyento[j])
						{
							cout << j << " ";
							break;
						}
					}
				}
			}
		}
		cout << endl;
		--n;
	}
	return 0;
}