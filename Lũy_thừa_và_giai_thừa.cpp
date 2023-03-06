/*
* Cho số tự nhiên N
 và số nguyên tố P
 . Nhiệm vụ của bạn là tìm số x
 lớn nhất để N! chia hết cho px. Ví dụ với N=7, p=3 thì x=2 là số lớn nhất để 7! Chia hết cho 32.
*/
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define ll long long
#define boost ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using namespace std;

ll n, p;

int main()
{
    boost;
    //freopen("inp.INP","r",stdin);
    //freopen("out.OUT","w",stdout);
    ll t;
    cin >> t;
    while (t--) {
        cin >> n >> p;
        ll x = 0, t = 1;
        for (ll i = 1; i <= n; i++)
        {
            ll m = i;
            while (m % p == 0) x++, m /= p;
            t *= m;
        }
        //while (t%p==0) x++,t/=p;
        cout << x << endl;
    }
    return 0;
}