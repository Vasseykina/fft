//
// Created by User on 18.11.2021.
//
#define _USE_MATH_DEFINES

#include <algorithm>
#include <ctime>
#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include <iomanip>

#ifndef FFT_FFT_H
#define FFT_FFT_H
typedef std::complex<double> cd;
typedef std::vector<cd> vcd;

class FFT {
private:
    static vcd fft(const vcd &as);

    static vcd fft_rev(const vcd &as);

public:
    static int power(int);

    static vcd multiplication(const vcd &num1, const vcd &num2);

    static void as_number(const vcd &v);

    static vcd as_array(int n);

};


#endif //FFT_FFT_H
