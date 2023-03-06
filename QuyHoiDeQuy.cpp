#include<iostream>
using namespace std;

int ToHop(int n, int k)
{
    if ( k == 0 || k == n)
    {
        return 1;
    }
    if ( k == 1 || k == n-1)
    {
        return n;
    }
    return ToHop(n-1,k) + ToHop(n-1,k-1);
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for( int j = 0; j <= i ;j++)
        {
            cout << ToHop(i,j) << " ";
        }
        cout<<endl;
    }
    return 0;
}