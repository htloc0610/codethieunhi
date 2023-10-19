#include<iostream>
#include<math.h>
using namespace std;

int main()
{
    long long L = 0, R = 0;
    cin >> L >> R;

    int k = ceil(log2(R / L));

    cout << k;

	return 0;
}
