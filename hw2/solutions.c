#include "solutions.h"

int running_total(int num) {
    static int total = 0;
    total += num;
    return total;
}
int* reverse(int array[], int len) {
    int* reverse_arr = (int*) calloc(len,sizeof(int));
    for (int i = 0; i < len; i++) {
        reverse_arr[i] = array[len-i-1];
    }
    return reverse_arr;
}
void reverse_in_place(int array[],int len){
    for (int i = 0;i < len/2; i++ ){
        int pre = array[i];
        array[i] = array[len-i-1];
        array[len-i-1] = pre;
    }
}
int num_occurences(int array[],int len, int target){
    int count = 0;
    for (int i =0; i < len; i++){
        if(target == array[i]){
            count++;
        }
    }
    return count;
}