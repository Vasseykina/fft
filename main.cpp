#define _USE_MATH_DEFINES

#include <algorithm>
#include <cstdio>
#include <ctime>
#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "fft.h"

using namespace std;

typedef complex<double> cd;
typedef vector<cd> vcd;

vcd fft(const vcd &as) {
    int n = as.size();
    int k = 0; // Длина n в битах
    while ((1 << k) < n) k++;
    vector<int> rev(n);
    rev[0] = 0;
    int high1 = -1;
    for (int i = 1; i < n; i++) {
        if ((i & (i - 1)) == 0) // Проверка на степень двойки. Если i ей является, то i-1 будет состоять из кучи единиц.
            high1++;
        rev[i] = rev[i ^ (1 << high1)]; // Переворачиваем остаток
        rev[i] |= (1 << (k - high1 - 1)); // Добавляем старший бит
    }

    vcd roots(n);
    for (int i = 0; i < n; i++) {
        double alpha = 2 * M_PI * i / n;
        roots[i] = cd(cos(alpha), sin(alpha));
    }

    vcd cur(n);
    for (int i = 0; i < n; i++)
        cur[i] = as[rev[i]];

    for (int len = 1; len < n; len <<= 1) {
        vcd ncur(n);
        int rstep = roots.size() / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            for (int i = 0; i < len; i++) {
                cd val = roots[i * rstep] * cur[p1 + len];
                ncur[pdest] = cur[p1] + val;
                ncur[pdest + len] = cur[p1] - val;
                pdest++, p1++;
            }
            pdest += len;
        }
        cur.swap(ncur);
    }
    return cur;
}

vcd fft_rev(const vcd &as) {
    vcd res = fft(as);
    for (int i = 0; i < (int) res.size(); i++) res[i] /= as.size();
    reverse(res.begin() + 1, res.end());
    return res;
}

int main() {
    int n;
    cin >> n;

    vcd num1(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        num1[i] = x;
    }
    auto res = FFT::multiplication(num1, num1);
    for (int i = 0; i < n; i++)
        cout << setprecision(5) << res[i].real() << endl;
    return 0;
}