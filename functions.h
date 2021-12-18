#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>

#define LM 5

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void printBoard(int length, int height) {

    int location = 0;

    // create board
    for(int i = 1; i <= height; i++) {

        printf("\t");
        if (i%2 == 0) {
            for(int j = 1; j <= length; j++) 
                if (location == length*height-(i*10)+j) printf("|     |");
                else printf("| %3d |", length*height-(i*10)+j);
        } else {
            for(int j = length; j >= 1; j--) 
                if (location == (10-i)*10+j) printf("|     |");
                else printf("| %3d |", (10-i)*10+j);
        }
        printf("\n\n");
    }
}

int isUnique(int check, int digit, int limit) {

    // note: if arrays are allowed, implement an array check function for isUnique() instead.
    if (check != digit%10 && check != (digit/10)%10 && check != (digit/100)%10 
    && check != (digit/1000)%10 && check != digit/10000)
        return 1;
    else    
        return 0;
}

int playerSequence(int limit) {

    int digit = 0, temp = 0, exit = 0;
    for (int i = 1; i <= limit; i++) {
        temp = (rand()%limit)+1;
        
        if (digit == 0) 
            digit += temp * pow(10, i-1);
        else if (digit > 0) {
            while (!exit) {
                if (isUnique(temp, digit, limit)) {
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

int rollDice() {
    int dice_a = rand() % 10;
    int dice_b = rand() % 10;

    printf("\tRolling: [%d] [%d]\n", dice_a, dice_b);

    return dice_a + dice_b;
}

// only if obstacle roll is >= 5, includes special 3-3 quirk
int newLocation(int dice_a, int dice_b, int position) {

    // returns the new location
    int add_turn = 0, new_pos;

    // special case
    if (dice_a == 3 && dice_b == 3) {
        if (position > 70) // row 8
            new_pos = 99;
        else {
            // algorithm to grab the box three rows above
            new_pos = ((position/10)+3)*10 + (11-(position%10));
            if (position%10 == 0) new_pos -= 20;
        }
        position = new_pos;
    } 
    else if (dice_a != 5 && dice_b != 5) 
        position += dice_a + dice_b;

    return position;
}

void gradualPrint(int speed, char s[]) {
    for (int i = 0; i < strlen(s); i++) {
        printf("%c", s[i]);
        usleep(speed);
    }
}