#include "functions.h"

int main(void) {

    int length = 10, height = 10, c;
    int playerCount;

    // initializes player position
    int py[4] = {0, 0, 0, 0, 0};

    srand(time(0));

    // * printing

    printf("\n\n");
    printBoard(length, height);
    printf("\n\n");

    printf("\tPlayer Sequence roll: %d\n", playerSequence(5));

    int loc;
    printf("\tEnter board location: ");
    scanf("%d", &loc);

    int new_loc = spcLocation(loc);
    printf("\tThe new location is: %d\n", new_loc);

    gradualPrint(5*10000, "\tTest sentence.\t");
    scanf("%d", &c);

}