#define _USE_MATH_DEFINES

#include <algorithm>
#include <cstdio>
#include <ctime>
#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include <iomanip>
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
    cin>> n;

    vcd as(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin>>x;
        as[i] = x;
    }

    //clock_t stime = clock();
    vcd res = fft(as);

    vcd c_vals(res.size());

    for (int i = 0; i < res.size(); i++)
        c_vals[i] = res[i] * res[i];


    cout<<"Result:"<<endl;
//    stime = clock();
    vcd as2 = fft_rev(c_vals);
    for (int i = 0; i < n; i++)
        cout<<setprecision(5)<< as2[i].real()<< endl;
    return 0;
}