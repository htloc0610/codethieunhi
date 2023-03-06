/*
* Một số được coi là số đẹp khi nếu nó chia hết cho một số nguyên tố nào đó thì cũng chia hết cho bình phương của số nguyên tố đó. Viết chương trình liệt kê các số đẹp như vậy trong đoạn giữa hai số nguyên dương cho trước
*/
#include<iostream>
#include<math.h>
using namespace std;

int pt(int n)
{
	if (n == 1)
	{
		return 0;
	}
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			int dem = 0;
			while (n % i == 0)
			{
				dem++;
				n /= i;
			}
			if (dem < 2)
			{
				return false;
			}
		}

	}
	if (n != 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	// in binh phuong so nguyen to
	for (int i = n; i <= m; i++)
	{
		if (pt(i))
		{
			cout << i << " ";
		}
	}
	return 0;
}