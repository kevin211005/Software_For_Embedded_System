#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

/*! \breif Fraction object and method definitions
 *
 *  A fraction object is a struct with a numerator, denoted num, and
 *  a denominator, denoted den. Varions Methods that take fractions and return 
 *  fractions do arithmetical operations on them.
 */
typedef struct {
    double real;
    double im;
} Complex;

/*! Add two fractions together
 *  \param a The first summand
 *  \param b The second summand
 */
Complex add ( Complex a, Complex b );
/*! Negate  complex number 
 *  \param a The complex number
 */
Complex negate(Complex a);

/*! magnitude complex numnber  
 *  \param a The complex number
 */
double magnitude (Complex a);

/*! Multiply two complex number together 
 *  \param a The first term
 *  \param b The second term
 */
Complex multiply ( Complex a, Complex b );

#endif