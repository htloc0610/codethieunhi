#include<iostream>
using namespace std;

int main()
{
	long long a;
	cin >> a;
	long long min = (a / 6) * 1 + ((a % 6) / 5) * 2 + (((a % 6) % 5) / 4) * 3 + ((((a % 6) % 5) % 4) / 3) * 4 + (((((a % 6) % 5) % 4) % 3) / 2) * 5 + ((((((a % 6) % 5) % 4) % 3) % 2) / 1) * 6;
	long long max = (a / 1) * 6 + ((a % 1) / 2) * 5 + (((a % 1) % 2) / 3) * 4 + ((((a % 1) % 2) % 3) / 4) * 3 + (((((a % 1) % 2) % 3) % 4) / 5) * 2 + ((((((a % 1) % 2) % 3) % 4) % 5) / 6) * 1;
	cout << min << " " << max;

	return 0;
}
