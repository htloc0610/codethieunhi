/*
* Viết chương trình nhập hai số nguyên dương a,b thỏa mãn 2<a<b<100. Một cặp số (i,j) được gọi là nguyên tố cùng nhau nếu i≠j và ước số chung lớn nhất của i với j là 1. Hãy liệt kê các cặp số nguyên tố cùng nhau trong đoạn [a,b] theo thứ tự từ nhỏ đến lớn.
*/
#include<iostream>
#include<math.h>
using namespace std;

int USCLN(int a, int b)
{
	int r = 0;
	while (a % b != 0)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return b;
}

int main()
{
	int a = 0, b = 0;
	cin >> a >> b;
	for (int i = a; i <= b; i++)
	{
		for (int j = i + 1; j <= b; j++)
		{
			if (i != j)
			{
				if (USCLN(i, j) == 1)
				{
					cout << "(" << i << "," << j << ")" << endl;
				}
			}
		}
	}

	return 0;
}