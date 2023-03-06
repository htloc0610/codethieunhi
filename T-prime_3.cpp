/*
* Cho hai số L,R. Nhiệm vụ của bạn là hãy đếm tất cả các số có đúng ba ước số trong khoảng [L,R]. Ví dụ L=1,R=10, ta có kết quả là 2 vì chỉ có số 4 và 9 là có đúng 3 ước số.
*/
#include <bits/stdc++.h>
using namespace std;

bool isSquare(long long x) {
    long long canX = sqrt(x);
    return (canX * canX == x);
}
bool isPrime(long long x) {
    if (x < 2) return false;
    for (int i = 2; i <= sqrt(x); i++)
        if (x % i == 0) return false;
    return true;
}


int main() {
    int T; cin >> T;
    while (T--) { // for (int i = 1; i <= T; i++) {
        long long l, r;
        cin >> l >> r;
        int dem = 0;
        for (long long x = sqrt(l); 1LL * x * x <= r; x++) {
            if ((long long)x * x < l) continue;
            if (isPrime(x) == true) {
                dem++;
            }
        }
        cout << dem << endl;
    }

    return 0;
}