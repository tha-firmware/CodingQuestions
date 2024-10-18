#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t factorial(uint32_t n);

/*
Name: factorial

Description: 
Using recursive method to calculate factorial number. 

Return: (>=1) : valid result
            0 : if n >= 13, it will overflow since result 
                can only be 32 bit unsigned interger. it
                will also let the use know its cause. 
*/
uint32_t factorial(uint32_t n) {
    uint32_t ret = 0;

    if (n == 0) {
        ret = 1; 
    } else if (n >= 13) { // it will overflow for 32 bit.
        printf("n = %i will overflow 32 bit unsigned interger\n", n);
        ret = 0;
    } else { 
        ret = n * factorial(n - 1);
    }
    return ret;
}

int main() {
    uint32_t n = 0;

    //Loop until user input a value that will cause the result to overflow.
    while (n < 13) { 
        printf("Calculate Factorial Number (Enter 13 or greater to Exit)\n");
        printf("Enter Number: ");
        scanf("%lu", &n);

        printf("%lu! = %lu\n\n", n, factorial(n));
    }

    system("pause");
    return 0;
}