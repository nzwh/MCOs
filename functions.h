#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>

/*  
    Checks if a player is situated on a given tile. If so, 
    print the player's number. If not, print the location.

    * Create instance for multiple players situated on a
    * single tile. (ASCII Symbols)
*/ 
int checkPlayer(int location, int arr[], int size) {

    int check = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == location) {
            printf("| P%02d |", i+1);
            check = 1;
        }
    }
    return check;
}

void printBoard(int length, int height, int arr[], int size) {

    for(int i = 1; i <= height; i++) {

        printf("\t");
        if (i%2 == 0) {
            for(int j = 1; j <= length; j++) 
                if(!checkPlayer(length*height-(i*10)+j, arr, size))
                    printf("| %3d |", length*height-(i*10)+j);
        } else {
            for(int j = length; j >= 1; j--) 
                if (!checkPlayer((10-i)*10+j, arr, size))
                    printf("| %3d |", (10-i)*10+j);
        }
        printf("\n\n");
    }
}

int isUnique(int check, int digit) {

    // returns true if the digit does not contains number "check".
    for(; digit > 0; digit /= 10) 
        if (check == digit%10) return 0;
    return 1;
}

/* given the limit 'n', get an 'n' digit number with unique digits from 1 to 'n'. */
int playerSequence(int limit) {

    int digit = 0, temp = 0;
    for (int i = 1, p = 1; i <= limit; i++, p *= 10) {

        do temp = (rand()%limit)+1;
        while (!isUnique(temp, digit));
        digit += temp * p;
    }
    return digit;
}

int getPosition(int position, int dice_a, int dice_b) {

    int dice_t;

    // rolls one dice if the position is on the 10th row
    if (position >= 90) {
        dice_t = dice_a;
        printf("\t[%d]  ", dice_a);
    } else {
        dice_t = dice_a + dice_b;
        printf("\t[%d][%d]  ", dice_a, dice_b);
    }
    
    printf("Rolling: [%d]\n", dice_t);
    return dice_t;
}

int isWin(int arr[], int size) {
    for (int i = 0; i < size; i++) 
        if(arr[i] == 100) return 1;
    return 0;
}

// covert to pointer
int overflow(int position) {
    if (position > 100) 
        position = 200 - position;
    return position;
}

enum { na, doggos, ladders, slides, uturns };
int getQuirk(int p_pos, int position) {

    int quirk = (rand()%10)+1;
    int new_pos, n_row = 0, n_col = 0;
    int x_row = 0, x_col = 0;
    int dig_o = position%10, dig_t = position/10;

    if (quirk == uturns) 
        position -= (position - p_pos);

    else if (quirk < uturns) {
        switch (quirk) {
            case doggos: 

                n_row = (rand()%10)+1;
                n_col = (rand()%10)+1;
                break;

            case ladders:
  
                n_row = dig_t;
                if (position % 20 != 0)
                    n_row++;
                n_row = (rand()% (11-n_row)) + n_row;

                if (n_row == dig_t+1) {
                    if (dig_o == 0 && n_row < 10) {
                        n_row++;  // this is so brute forced
                        n_col = (rand()%10)+1;  
                    }
                    else {
                        if (n_row%2 == 1) 
                            n_col = (rand()%(10-dig_o)) + dig_o + 1;
                        else 
                            n_col = (rand()%(10-dig_o)) + 1;
                    }
                }
                else
                    n_col = (rand()%10)+1;

                break;
                
            case slides:

                n_row = dig_t;
                if(position % 20 != 0)
                    n_row++;
                n_row = (rand()%n_row)+1;

                if (n_row == dig_t+1) {
                    if (dig_o == 1 && n_row > 1) {
                        n_row--;  // this is so brute forced
                        n_col = (rand()%10)+1;  
                    }
                    else {
                        if (n_row%2 == 0) 
                            n_col = (rand()%(dig_o-1)) + (11-dig_o) + 1;
                        else 
                            n_col = (rand()%(dig_o-1)) + 1;
                    }
                }
                else
                    n_col = (rand()%10)+1;

                break;
        }

        if (n_row % 2 == 0) 
            x_col = 11 - n_col;
        else    
            x_col = n_col;

        x_row = n_row-1;
        position = x_row*10 + x_col;
    }

    printf("\tQuirk: %d Row: %d Column: %d New Position: %d", quirk, n_row, n_col, position);
    return position;
}

// check this first before the quirk
// special 3-3 and 5-5 quirk, returns new position
int spcLocation(int position, int dice_a, int dice_b) {

    // returns the new location
    int add_turn = 0, new_pos;

    // special case 3
    if (dice_a == 3 && dice_b == 3) {
        if (position > 70) // row 8
            new_pos = 99;
        else {
            // algorithm to grab the tile three rows above
            new_pos = ((position/10)+3)*10 + (11-(position%10));
            if (position%10 == 0) new_pos -= 20;
        }
        position = new_pos - position;
    } 
    // special case 5: none

    return position;
}

// moves to the new position
int rollDice(int position) {

    int dice_a = (rand()%10)+1;
    int dice_b = (rand()%10)+1;

    int new_pos;

    if ((dice_a == 3 && dice_b == 3) ||
        (dice_a == 5 && dice_b == 5)) {
        new_pos = spcLocation(position, dice_a, dice_b);
    } else {
        new_pos = getPosition(position, dice_a, dice_b);
    }

    return position + new_pos;
}

void gradualPrint(int speed, char s[]) {
    for (int i = 0; i < strlen(s); i++) {
        printf("%c", s[i]);
        usleep(speed);
    }

    printf("\b"); // erases a character
}
