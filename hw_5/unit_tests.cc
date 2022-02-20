#include <math.h>
#include <fstream>
#include <assert.h>
#include "utilities.h"
#include "gtest/gtest.h"
namespace {
    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,1);
        x.set(1,-1);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),1.0);
    }    

    TEST(Absolute_sort,Sort) {
        vector<double> a = { -10, 5, -3, 2 };
        sort_by_magnitude(a);
        EXPECT_DOUBLE_EQ(a[0],2.0); 
        EXPECT_DOUBLE_EQ(a[1],-3.0); 
        EXPECT_DOUBLE_EQ(a[2],5.0); 
        EXPECT_DOUBLE_EQ(a[3],-10.0); 
    }    
    TEST(Create_CSV,Sort) {
        create_csv();
        EXPECT_DOUBLE_EQ(0.0,0.0);
        TypedArray<TypedArray<double>> a = read_matrix_csv("bin//TEST.csv");
        EXPECT_DOUBLE_EQ(a.get(0).get(0),1.0); 
        EXPECT_DOUBLE_EQ(a.get(2).get(2),20.0); 
    }
    TEST(Map,Create) {
        create_txt();
        map<string, int> a = occurrence_map("bin//test.txt");
        EXPECT_EQ(a["are"],1); 
    }
}