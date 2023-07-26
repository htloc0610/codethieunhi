#include <iostream>
using namespace std;

int calculate(int n) {
    int count = 0;

    while (n != 1) {
        if (n % 6 == 0) {
            n /= 6;
        }
        else if (n % 3 == 0) {
            n *= 2;
        }
        else {
            // Không thể thực hiện phép tính
            return -1;
        }
        count++;
    }

    return count;
}

int main() {
    int n = 0;
    cin >> n;
    while (n != 0) {
        int m = 0;
        cin >> m;
        cout << calculate(m) << endl;
        --n;
    }
    return 0;
}
