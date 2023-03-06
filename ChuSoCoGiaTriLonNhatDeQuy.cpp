#include<iostream>
using namespace std;

int TimChuSoLonNhat(int n)
{
    if(n / 10 == 0)
    {
        return n;
    }
    return n % 10 > TimChuSoLonNhat(n / 10) ? n % 10 : TimChuSoLonNhat(n / 10);

}

int main()
{
    int n=0;
    cin>>n;
    cout<<TimChuSoLonNhat(n);
    return 0;
}