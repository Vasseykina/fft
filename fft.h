//
// Created by User on 18.11.2021.
//
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
public:
    static vcd multiplication(const vcd& num1, const vcd& num2);

};


#endif //FFT_FFT_H
