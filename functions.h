// Include all functions from "assets.h"
#include "assets.h"

/*  
    * Determines if a number contains a digit.
    Precondition: all values are nonnegative numbers.

    @param digit is a single-digit number to be checked.
    @param number is the entire number to be checked.
    @return 1 (true) if "digit" is in "number".
*/
int isUnique(int digit, int number) {

    int check = 1;
    for (; number > 0; number /= 10) 
        if (digit == number%10) check = 0;
    return check;
}

/*  
    * Generates a n-digit number with unique digits
    * from 1 to n. No repeating values.
    Precondition: "limit" is greater than 1.

    @param limit represents the length and range.
    @return a n-digit number with values from 1 to n.
*/
int playerSequence(int limit) {

    int digit = 0, temp = 0;
    for (int i = 1, p = 1; i <= limit; i++, p *= 10) {

        // Continously generate a number until it is unique
        do temp = (rand()%limit)+1;
        while (!isUnique(temp, digit));
        digit += temp * p;
    }
    return digit;
}

/*  
    * Determines the object [D,L,S,U] given the current
    * player position and their previous position.
    Precondition: all values except quirk are nonzero.

    @param pr_position is the previous player position.
    @param position is the current player position after rolling.
    @param *quirk updates the quirk with a value from 1-10.
    @return the new position of the player.
*/
enum quirks_type { na, doggos, ladders, slides, uturns };
int getQuirk(int pr_position, int position, int* quirk) {

    // No slides at the first row, roll again if slides were rolled
    if (position <= 10) {
        do *quirk = (rand()%10)+1;
        while (*quirk == slides);
    // No ladders at the last row, roll again if ladders were rolled
    } else if (position >= 91) {
        do *quirk = (rand()%10)+1;
        while (*quirk == ladders);
    // Any other row, print any quirk
    } else *quirk = (rand()%10)+1;
    
    int new_pos, n_row = 0, n_col = 0;
    int x_row = 0, x_col = 0;

    // Extract the tenth and ones of the position
    int dig_o = position%10, dig_t = position/10;

    if (*quirk == uturns) {
        gradualPrint(20000, LMAG "\t[>] Player encountered a " HUND "U-turn!" KRST "\n");
        printf("\tThe %sU-turn%s leads the player back to their original position.\n" KRST, LMAG HUND, KRST);
        position -= (position - pr_position);
    } else {
        switch (*quirk) {
            case doggos: 

                n_row = (rand()%10)+1;
                n_col = (rand()%10)+1;

                gradualPrint(20000, LCYN "\t[>] Player encountered a " HUND "Doggo!" KRST "\n");
                printf("\tThe %sDoggo%s leads the player to %sR[%d] C[%d].\n" KRST, LCYN HUND, KRST, KYEL, n_row, n_col);
                break;

            case ladders:

                n_row = dig_t;
                if (position % 20 != 0)
                    n_row++;
                n_row = (rand()% (10-n_row) ) + n_row + 1;
                n_col = (rand()%10)+1;

                gradualPrint(20000, LBLU "\t[>] Player encountered a " HUND "Ladder!" KRST "\n");
                printf("\tThe %sLadder%s leads the player to %sR[%d] C[%d].\n" KRST, LBLU HUND, KRST, KYEL, n_row, n_col);
                break;
                
            case slides:

                n_row = dig_t;
                if (position % 20 != 0)
                    n_row++;
                n_row = (rand()% (n_row-1) )+1;
                n_col = (rand()%10)+1;

                gradualPrint(20000, LRED "\t[>] Player encountered a " HUND "Slide!" KRST "\n");
                printf("\tThe %sSlide%s leads the player to %sR[%d] C[%d].\n" KRST, LRED HUND, KRST, KYEL, n_row, n_col);
                break;

            default:
                printf(LBLK "\tPlayer did not encounter anything. [Q%d]\n", *quirk);
                break;
        }

        if (*quirk < uturns) {
            if (n_row%2 == 0) x_col = 11 - n_col;
            else x_col = n_col;

            x_row = n_row-1;
            position = x_row*10 + x_col;
        }
    }

    return position;
}

/*  
    * Returns a location with a special roll: D5/D3
    Precondition: dice_a and dice_b must be equal 
                  and contain either 5 or 3.

    @param position is the current player position.
    @param dice_a is the dice that determines the row.
    @param dice_b is the dice that determines the column.
    @return the new position of the player.
*/
int spcLocation(int position, int dice_a, int dice_b) {

    int new_pos;

    // Special Case: Double 3
    if (dice_a == 3 && dice_b == 3) {
        if (position > 70)   // 8th row
            new_pos = 99;
        else {
            // Algorithm to find the tile three rows above the current
            new_pos = ((position/10)+3)*10 + (11-(position%10));
            if (position%10 == 0) new_pos -= 20;
        }
        position = new_pos - position;
        printf(LCYN ", moving three rows up to Tile [%d].\n" KRST, new_pos);
    } 

    // Special Case: Double 5
    if (dice_a == 5 && dice_b == 5) {
        position = 0;
        printf(KYEL ", unfortunately missing their turn.\n" KRST);
    }

    return position;
}

/*  
    * Rolls two die and generates a new position.
    Precondition: all values are nonnegative.

    @param position is the current player position.
    @param dice_a is the dice that determines the row.
    @param dice_b is the dice that determines the column.
    @return the new position of the player.
*/
int rollDice(int position, int* dice_a, int* dice_b) {

    *dice_a = (rand()%10)+1;
    *dice_b = (rand()%10)+1;
    int new_pos;

    // Roll one die if they are on the 10th row
    if (position >= 90) {
        new_pos = *dice_a, *dice_b = 0;
        printf("[%d]", *dice_a);
    // Otheriwse,
    } else {

        printf("[%d][%d]", *dice_a, *dice_b);
        if (*dice_a % 2 == 0) 
            *dice_b = 11 - *dice_b;
        new_pos = ((*dice_a-1)*10 + *dice_b) - position;
    }

    // Checks if the die correspond to a special combination
    if ((*dice_a == 3 && *dice_b == 3) ||
        (*dice_a == 5 && *dice_b == 5)) 
        new_pos = spcLocation(position, *dice_a, *dice_b);
    else     
        printf(KRST ", Moving %s[%d]%s spaces.\n", KYEL, new_pos, KRST);

    return position + new_pos;
}

/*  
    * Checks if there is a player with a location of 100.
    Precondition: all values are nonnegative.

    @param arr[] is an array that contains player locations.
    @param size is the amount of players.
    @return 1 (true) if there is a winning player.
*/
int isWin(int arr[], int size) {

    int check = 0;
    for (int i = 0; i < size; i++) 
        if (arr[i] == 100) check = 1;
    return check;
}

/*  
    * Computes for a player's new position if they exceed 100.
    Precondition: position is a value greater than 100.

    @param *position is the current player position.
*/
void overflow(int* position) {
    if (*position > 100) 
        *position = 200 - *position;
}