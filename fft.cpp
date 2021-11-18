//
// Created by User on 18.11.2021.
//

#include "fft.h"

vcd FFT::multiplication(const vcd& num1, const vcd& num2) {
    vcd res = fft(num1);
    vcd c_vals(res.size());
    for (int i = 0; i < res.size(); i++)
        c_vals[i] = res[i] * res[i];
    vcd result = fft_rev(c_vals);
    return result;
}
