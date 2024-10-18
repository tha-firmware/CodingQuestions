#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned char BYTE;

bool StretchOrShrink(BYTE* destBuffer, int destWidth, BYTE* srcBuffer, int srcWidth);
void printBuffer(BYTE *buffer, int size);
void ShrinkTest (void);
void StretchTest (void);

/*
Name: StretchOrShrink

Description:
If destination is greater than source, we stretch, otherwise we shrink.

If the stretch is not whole multiple (meaning there's remainders), then
we use the remainder to fill up starting from first cell. 

For shrinking, there are many possibly ways of shrinking. However, we 
must able to get the original resoluation from stretched image, when 
we shrink. Thus the shrink is done by undoing what we would normally
do when we stretch. 

Return: false - invalid inputs, otherwise it is true.
*/
bool StretchOrShrink(BYTE* destBuffer, int destWidth, BYTE* srcBuffer, int srcWidth) {
    bool ret = false;
    int divNum = 0;
    int remainder = 0;
    int duplicate = 0;
    int k = 0;

    if ((destBuffer != NULL) && 
        (destWidth > 0) && 
        (srcBuffer != NULL) && 
        (srcWidth > 0)) {

        if (destWidth > srcWidth) {
            remainder = destWidth % srcWidth;
            divNum = destWidth / srcWidth;

            for (int i = 0; i < srcWidth; i++) {
                if (remainder) {
                    duplicate = divNum + 1;
                    remainder--;
                } else {
                    duplicate = divNum;
                }
                for (int j = 0; j < duplicate; j++) {
                    destBuffer[k++] = srcBuffer[i];
                }
            }
        } else if (destWidth <= srcWidth) {
            remainder = srcWidth % destWidth; 
            divNum = srcWidth / destWidth;

            for (int i = 0; i < destWidth; i++){
                if (remainder) {
                    duplicate = divNum + 1;
                    remainder--;
                } else {
                    duplicate = divNum;
                }
                destBuffer[i] = srcBuffer[k];
                k += duplicate;
            }
        }
        ret = true;
    }
    return ret;
}

/*
Name: printBuffer

Description: Print the provided buffer.
*/
void printBuffer(BYTE *buffer, int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%i ", buffer[i]);
    }
    printf("]\n");
}

/*
Name: ShrinkTest

Description: test code to shrink 1D buffer. destination buffer 
must be smaller than source.
*/
void ShrinkTest (void) {
    BYTE src[] = {254, 254, 254, 43, 43, 43, 36, 36, 23, 23, 12, 12};
    BYTE dst[5];
    int dstSize = sizeof(dst)/sizeof(BYTE);
    int srcSize = sizeof(src)/sizeof(BYTE);

    printf("\n---Shrink Test---\n");

    if (StretchOrShrink(dst, dstSize, src, srcSize)) {
        printf("source:\n");
        printBuffer (src, srcSize);

        printf("destination:\n");
        printBuffer(dst, dstSize);
    }
}

/*
Name: StretchTest

Description: test code to stretch 1D buffer. destination buffer 
must be larger than source.
*/
void StretchTest (void) {
    BYTE src[] = {254,43,36,23,12};
    BYTE dst[12];
    int dstSize = sizeof(dst)/sizeof(BYTE);
    int srcSize = sizeof(src)/sizeof(BYTE);

    printf("\n---Stretch Test---\n");

    if (StretchOrShrink(dst, dstSize, src, srcSize)) {
        printf("source:\n");
        printBuffer (src, srcSize);

        printf("destination:\n");
        printBuffer(dst, dstSize);
    }
}

int main (void) {
    StretchTest();
    ShrinkTest();

    system("pause");
    return 0; 
}