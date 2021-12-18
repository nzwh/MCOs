#include "functions.h"

int main(void) {

    int length = 10, height = 10, c;
    int playerCount;

    // initializes player position
    int p_1, p_2, p_3, p_4, p_5;
    /* int p[LM]; */

    srand(time(0));

    // * printing

    printf("\n\n");
    printBoard(length, height);
    printf("\n\n");

    printf("\tPlayer Sequence roll: %d\n", playerSequence(5));

    int loc;
    printf("\tEnter board location: ");
    scanf("%d", &loc);

    int new_loc = newLocation(3, 3, loc);
    printf("\tThe new location is: %d\n", new_loc);

    int move = rollDice();
    gradualPrint(5*10000, "\tTest sentence.\t");
    scanf("%d", &c);

}