#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "complex.h"
#include "gtest/gtest.h"

namespace {

    class Point {
        public:
        Point(double x, double y, double z) : x(x), y(y), z(z) {};
        Point() : x(0), y(0), z(0) {};

        double magnitude() const;

        double x, y, z;
    };
    bool operator<(const Point& lhs, const Point& rhs);
    double Point::magnitude() const {
    return sqrt(x*x + y*y + z*z);
    }

    bool operator<(const Point& lhs, const Point& rhs) {

        double m1 = lhs.magnitude(), 
            m2 = rhs.magnitude();

        if ( m1 < m2 ) {
            return 1;
        } else if ( m1 > m2 ) {
            return -1;
        } else {
            return 0;
        }

    } 
    std::ostream &operator<<(std::ostream &os, const Point &p) {
        os << '{' << p.x << "," << p.y << "," << p.z << '}';
        return os;
    }
    std::ostream &operator<<(std::ostream &os, const Point &p);
    TEST(TypedArray, Construction) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);
    }

    TEST(TypedArray, Defaults) {
        TypedArray<Point> x;
        Point& y = x.get(3);
        std::cout << x << "\n";
        EXPECT_DOUBLE_EQ(y.magnitude(), 0.0);
    }

    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    TEST(TypedArray,CopyElementsInSet1) {
        TypedArray<Point> b;
        Point p(1,2,3);
        b.set(0, p);
        p.x = 4;
        EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }    
    TEST(TypedArray,Pop) {
        TypedArray<double> x;
        x.set(0,0);
        x.set(1,1);
        EXPECT_DOUBLE_EQ(x.pop_front(),0.0);
        x.set(2,2);
        EXPECT_DOUBLE_EQ(x.pop_front(),1.0);
        EXPECT_DOUBLE_EQ(x.pop(),2.0);
    }
    TEST(TypedArray,Push) {
    TypedArray<double> x;
    x.push(1);
    x.push(2);
    x.push_front(0);
    EXPECT_DOUBLE_EQ(x.get(0),0.0);
    for (int i = 0;i<3;i++){
        EXPECT_DOUBLE_EQ(x.get(i),(double) i);
    }
    }
    TEST(TypedArray,Concat) {
    TypedArray<double> a;
    a.push(0);
    a.push(1);
    TypedArray<double> b;
    b.push(2);
    b.push(3);
    TypedArray<double> c;
    c.push(4);
    c.push(5);
    TypedArray<double> x = a.concat(b).concat(c);
    for (int i = 0;i<6;i++){
        EXPECT_DOUBLE_EQ(x.get(i),(double) (i));
    }
    TypedArray<double> y = a + b + c;
    for (int i = 0;i<6;i++){
        EXPECT_DOUBLE_EQ(y.get(i),(double) (i));
    }
    }
    TEST(TypedArray,Reverse) {
    TypedArray<double> x;
    x.push(3);
    x.push(2);
    x.push(1);
    x.push(0);
    x.reverse();
    for (int i = 0;i<3;i++){
        EXPECT_DOUBLE_EQ(x.get(i),(double) i);
    }
    }
    TEST(Complex,PART) {
    Complex a = Complex(2,5);
    EXPECT_DOUBLE_EQ(a.re(),2.0);
    EXPECT_DOUBLE_EQ(a.im(),5.0);
    }
    TEST(Complex,conj) {
    Complex a = Complex(2,-5);
    Complex b = a.conjugate();
    EXPECT_DOUBLE_EQ(b.re(),2.0);
    EXPECT_DOUBLE_EQ(b.im(),5.0);
    }
    TEST(Complex,equal) {
    Complex a = Complex(2,-5);
    Complex b = Complex(2,5).conjugate();
    ASSERT_EQ(a,b);
    }
    TEST(Complex,operation) {
    Complex a = Complex(2,-5);
    Complex b = Complex(2,5);
    Complex mul = Complex(29,0);
    Complex sum = Complex(4,0);
    EXPECT_DOUBLE_EQ((a+b).re(),4);
    EXPECT_DOUBLE_EQ((a+b).im(),0);    
    ASSERT_EQ(a+b,sum);
    ASSERT_EQ(a*b,mul);
    }
}