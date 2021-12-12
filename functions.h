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

