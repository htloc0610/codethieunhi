#include <iostream>
using namespace std;

int SoDauTien(int n)
{
    if (n / 10 == 0)
    {
        return n;
    }
    SoDauTien(n / 10);
}

int main()
{
    int n = 0;
    cin >> n;
    cout << SoDauTien(n);
    return 0;
}