#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }   
    TEST(DynamicArray, MathOperation) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 6 ) {
            DynamicArray_push(da, x);  
            x += 1;
        }
        ASSERT_EQ(DynamicArray_max(da),5);
        ASSERT_EQ(DynamicArray_min(da),0);
        ASSERT_EQ(DynamicArray_sum(da),15);
        ASSERT_EQ(DynamicArray_mean(da),(double) 15/6);
        ASSERT_EQ(DynamicArray_median(da),(double) (2+3)/2);
        ASSERT_EQ(DynamicArray_last(da),5);
        ASSERT_EQ(DynamicArray_first(da),0);
        DynamicArray_destroy(da);          
    } 
    TEST(DynamicArray, Copy) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 6 ) {
            DynamicArray_push(da, x);  
            x += 1;
        }
        DynamicArray * c_da = DynamicArray_copy(da);
        for (int i = 0; i< DynamicArray_size(da);i++){
            ASSERT_EQ(DynamicArray_get(c_da,i),DynamicArray_get(da,i));
        }
        DynamicArray_destroy(da);       
        DynamicArray_destroy(c_da);      
    } 
    TEST(DynamicArray, Range) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 3 ) {
            DynamicArray_push(da, x);  
            x += 0.1;
        }
        DynamicArray * c_da = DynamicArray_range(0,3,0.1);
        for (int i = 0; i< DynamicArray_size(da);i++){
            ASSERT_EQ(DynamicArray_get(c_da,i),DynamicArray_get(da,i));
        }
        DynamicArray_destroy(da);       
        DynamicArray_destroy(c_da);      
    } 
    TEST(DynamicArray, Concat) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray * b = DynamicArray_new();
        DynamicArray * c = DynamicArray_new();
        double x = 0;
        while ( x < 3 ) {
            DynamicArray_push(a, x);  
            x += 1;
        }
        while ( x < 5 ) {
            DynamicArray_push(b, x);  
            x += 1;
        }
        x= 0;
        while ( x < 5 ) {
            DynamicArray_push(c, x);  
            x += 1;
        }
        DynamicArray * c_da = DynamicArray_concat(a,b);
        for (int i = 0; i< DynamicArray_size(c);i++){
            ASSERT_EQ(DynamicArray_get(c_da,i),DynamicArray_get(c,i));
        }
        DynamicArray_destroy(a);       
        DynamicArray_destroy(b);  
        DynamicArray_destroy(c);  
        DynamicArray_destroy(c_da);   
    } 
    TEST(DynamicArray, Take) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray * ans = DynamicArray_new();
        double x = 0;
        while ( x < 5 ) {
            DynamicArray_push(da, x);  
            x += 1;
        }
        x= 0;
        while ( x < 5 ) {
            DynamicArray_push(ans, 0);  
            x += 1;
        }
        x = 0;
        while ( x < 5 ) {
            DynamicArray_push(ans, x);  
            x += 1;
        }
        DynamicArray * c_da = DynamicArray_take(da,-10);
        for (int i = 0; i< DynamicArray_size(da);i++){
            ASSERT_EQ(DynamicArray_get(c_da,i),DynamicArray_get(ans,i));
        }
        DynamicArray_destroy(da);     
        DynamicArray_destroy(c_da);     
        DynamicArray_destroy(ans);      
    }    
}