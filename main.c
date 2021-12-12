#include "functions.h"
#define PL 5

int main(void) {

    int length = 10, height = 10;
    srand(time(0));

    printf("\n\n");
    printBoard(length, height);
    printf("\n\n");

    printf("\tTest roll: %d \n\n", playerSequence(PL));
    
    return 0;
}