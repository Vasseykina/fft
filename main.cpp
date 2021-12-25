#include <complex>
#include <iostream>
#include <vector>
#include "fft.h"

using namespace std;
typedef complex<double> cd;
typedef vector<cd> vcd;

int main() {
    int n;
    cout<<"Enter number 1"<<endl;
    cin >> n;
    vcd num1 = FFT::as_array(n);
    cout<<"Enter number 2"<<endl;
    cin >> n;
    vcd num2 = FFT::as_array(n);
    cout<<"Result:"<<endl;
    auto res = FFT::multiplication(num1, num2);
    FFT::as_number(res);
    return 0;
}