#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    cin >> n;

    vector<int> primes;
    int m = ceil(pow(n / pow(2, 3), 1.0 / 3));
    for (int i = 2; i <= m; ++i) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }

    int count = 0;
    for (int i = 0; i < primes.size(); ++i) {
        for (int j = i + 1 ; j < primes.size(); ++j) {
            long long s = (long long)primes[i] * primes[i] * primes[i] * primes[j] * primes[j] * primes[j];
            if (s <= n) {
                count ++;
            }
        }
    }

    cout << count;
    return 0;
}
