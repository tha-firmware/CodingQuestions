#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
Name: fibonacciSeq

Description: 
Using recursive method to calculate fibonacci sequence number. 

Return: (n<48) : valid result
          else : Let the user know that such input will result 
                 to overflow 32 bit unsigned interger. 
*/
uint32_t fibonacciSeq (uint32_t n) {
    uint32_t ret = 0;

    if (n >= 48) {
        printf("n = %lu causes overflow to 32 bit unsigned interger.\n", n);
        ret = 0; 
    }else if (n == 0) {
        ret = 0;
    } else if (n == 1) {
        ret = 1;
    } else {
        ret = fibonacciSeq(n-1) + fibonacciSeq(n-2);
    }
    return ret;
}

int main (void) {
    uint32_t n = 0;
    
    //Loop until user input a value that will cause the result to overflow.
    while (n < 48) {
        printf("Calculate Fibonacci Sequence (Enter 48 or greater to Exit)\n");
        printf("Enter Number: ");
        scanf("%lu", &n);

        printf("F%lu = %lu\n\n", n, fibonacciSeq(n));
    }

    system("pause");
    return 0;
}