/*
* Kiểm tra số thuận nghịch.
*/
#include<iostream>
using namespace std;
int soTN(long long n) {
    long long m = n;
    long long a = 0;
    while (n) {
        a = a * 10 + n % 10;
        n /= 10;
    }
    if (m == a) return 1;
    return 0;
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        long long m;
        cin >> m;
        if (soTN(m)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}