#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void printBoard(int length, int height) {

    // create board
    for(int i = 1; i <= height; i++) {

        printf("\t");
        if (i%2 == 0) 
            for(int j = 1; j <= length; j++) 
                printf("[ %3d ]", length*height-(i*10)+j);
        else    
            for(int j = length; j >= 1; j--) 
                printf("[ %3d ]", (10-i)*10+j);
        
        printf("\n");
    }
}

int isUnique(int check, int a, int b, int c, int d, int e) {

    if (check != a && check != b && check != c && check != d && check != e)
        return 1;
    else    
        return 0;
}

int playerSequence(int limit) {

    int digit = 0, temp = 0;
    for (int i = 1; i <= limit; i++) {
        temp = (rand()%limit)+1;
        int exit = 0;
        
        if (digit == 0)
            digit += temp * pow(10, i-1);
        else if (digit > 0) {
            while(!exit) {
                if (isUnique(temp, digit%10, (digit/10)%10, (digit/100)%10, (digit/1000)%10, digit/10000)) {
                    digit += temp * pow(10, i-1);
                    exit = 1;
                }
                else temp = (rand()%limit)+1;
            }
        }
        exit = 0;
    }

    return digit;
}