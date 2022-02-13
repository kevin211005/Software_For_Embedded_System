#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(real*real + imag*imag);

}
double Complex::re() const {
    return real;
}
double Complex::im() const {
    return imag;
}
Complex Complex::conjugate(){
    return Complex(re(),-im());
}
Complex operator + (const Complex& a, const Complex& b) {
    return Complex(a.re()+b.re(),a.im()+b.im());
}
Complex operator * (const Complex& a, const Complex& b) {
    return Complex(a.re()*b.re()-a.im()*b.im(),a.im()*b.re()+a.re()*b.im());
}
bool operator == (const Complex& a, const Complex& b) {
    if (a.re() == b.re() && a.im() == b.im())
    {
        return true;        
    }
    else{
        return false;
    }

}