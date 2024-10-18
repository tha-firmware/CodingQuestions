#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t divide(uint32_t dividend, uint32_t divisor);
void userInteractive(void);

/*
Name: divide

Description: 
Using long division to optimize process of division calculation.
The long division is done on binary.

Return: result of division
*/
uint32_t divide(uint32_t numerator, uint32_t denominator) {
    uint32_t ret = 0;
    uint32_t shift_pos = 0;
    uint32_t div = numerator;

    if (denominator == 0) {
        printf("Invalid Entry: denominator is 0\n");
    } else if (numerator >= denominator) {
        // We want to know where to start long divsion
        while (div >= denominator) {
            div >>= 1;
            shift_pos++;
        }
        // Start value used to subtract from numerator. 
        div = denominator << (--shift_pos);

        //Performing long division in binary. 
        while (div >= denominator) {
            ret <<= 1;
            if (numerator >= div) {
                numerator -= div;

                ret |= 0x1;
            }
            div >>= 1;
        }
    }
    return ret;
}

/*
Name: userInteractive

Description: 
User interactive code where the user can input what they want to 
divide. If they set the denominator 0, it exists the loop and 
program. 
*/
void userInteractive(void) {
    uint32_t numerator;
    uint32_t denominator = 1;

    while (denominator != 0) {
        printf("Enter numerator: ");
        scanf("%lu", &numerator);
        printf("Enter denominator (type 0 to exit): ");
        scanf("%lu", &denominator);

        if (denominator != 0)
            printf("%u = %u / %u\n\n", divide(numerator, denominator), numerator, denominator);
    }
}

int main () {

    uint32_t numerator = 0xFFFFFFFF;
    uint32_t denominator = 3;
    uint32_t result;
    
    //For demo purposes.
    result = divide(numerator, denominator);

    if (result != (numerator/denominator)) {
        printf("Error\n");
        return 1;
    }
    printf("Demo:\n");
    printf("%u = %u / %u\n\n", result, numerator, denominator);

    userInteractive();

    system("pause");
    return 0;
}