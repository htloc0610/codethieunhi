#include<iostream>
using namespace std;

int LuyThua(int x, int y)
{
    if(y==0)
    {
        return 1;
    }
    return x * LuyThua(x, y-1);
}

int main()
{
    int x, y;
    cin >> x >> y;
    cout<< LuyThua(x, y);
    return 0;
}