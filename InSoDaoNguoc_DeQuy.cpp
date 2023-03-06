#include<iostream>
using namespace std;

void InSoDaoNguoc(int n)
{
    if(n == 0)
    {
        return;
    }
    cout<<n%10;
    return InSoDaoNguoc(n/10);

}

int main()
{
    int n=0;
    cin>>n;
    InSoDaoNguoc(n);
    return 0;
}