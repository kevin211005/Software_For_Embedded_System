#include "complex.h"
#include "math.h"

Complex add ( Complex a, Complex b ) {
  return (Complex) { a.real + b.real, a.im + b.im };
}

Complex multiply ( Complex a, Complex b ) {
  return (Complex) { a.real * b.real - a.im*b.im, a.im*b.real + a.real*b.im };
}

Complex negate ( Complex a) {
  return (Complex) { -a.real, -a.im };
}
double magnitude(Complex a){
  return (double) { sqrt((double)pow(a.real,(double) 2) + (double)pow(a.im, (double) 2) ) };
}
