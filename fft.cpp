//
// Created by User on 18.11.2021.
//

#include "fft.h"

using namespace std;

vcd FFT::fft(const vcd &as) {
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

vcd FFT::fft_rev(const vcd &as) {
    vcd res = fft(as);
    for (auto &re: res) re /= as.size();
    reverse(res.begin() + 1, res.end());
    return res;
}

vcd FFT::multiplication(const vcd &num1, const vcd &num2) {
    vcd res = fft(num1);
    vcd res2 = fft(num2);
    vcd c_vals(res.size());
    for (int i = 0; i < res.size(); i++)
        c_vals[i] = res[i] * res2[i];
    vcd result = fft_rev(c_vals);
    for (auto i = 0; i < result.size() - 1; i++) {
        if (result[i].real() >= 10) {
            auto tmp = static_cast<int>(result[i].real()) / 10;
            result[i + 1] += tmp;
            result[i] -= tmp * 10;
        }
    }
    return result;
}

int FFT::power(int n) {
    n = 2 * n;
    int i = 2;
    while (pow(2, i) < n) {
        i++;
    }
    return pow(2, i);
}

void FFT::as_number(const vcd &res) {
    auto rev = res;
    reverse(rev.begin(), rev.end());
    bool flag = false;
    for (auto &re: rev) {
        if (!flag && int(re.real()) != 0) {
            flag = true;
        }
        if (flag) {
            cout << setprecision(5) << static_cast<int>(re.real());
        }
    }
}

vcd FFT::as_array(int n) {
    int tmp =n;
    int count=0;
    while(tmp>0){
        tmp/=10;
        count++;
    }
    vcd array(power(count));
    tmp =n;
    int i=0;
    while(tmp>0){
        array[i]=tmp%10;
        tmp/=10;
        i++;
    }
    return array;
}
