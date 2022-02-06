#include "assets.h"

// *
int isUnique(int check, int digit) {

    int n_check = 1;
    // returns true if the digit does not contains number "check".
    for(; digit > 0; digit /= 10) 
        if (check == digit%10) n_check = 0;
    return n_check;
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

enum quirks_type { na, doggos, ladders, slides, uturns };
int getQuirk(int p_pos, int position, int* quirk) {


    if (position <= 10) {
        do *quirk = (rand()%10)+1;
        while (*quirk == slides);
    } else if (position >= 91) {
        do *quirk = (rand()%10)+1;
        while (*quirk == ladders);
    } else *quirk = (rand()%10)+1;
    

    int new_pos, n_row = 0, n_col = 0;
    int x_row = 0, x_col = 0;
    int dig_o = position%10, dig_t = position/10;

    if (*quirk == uturns) {
        gradualPrint(20000, LMAG "\t[>] Player encountered a " HUND "U-turn!" KRST "\n");
        printf("\tThe %sU-turn%s leads the player back to their original position.\n" KRST, LMAG HUND, KRST);
        position -= (position - p_pos);
    }
    else {
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
                n_row = (rand()% (10-n_row)) + n_row + 1;
                n_col = (rand()%10)+1;

                gradualPrint(20000, LBLU "\t[>] Player encountered a " HUND "Ladder!" KRST "\n");
                printf("\tThe %sLadder%s leads the player to %sR[%d] C[%d].\n" KRST, LBLU HUND, KRST, KYEL, n_row, n_col);
                break;
                
            case slides:

                n_row = dig_t;
                if(position % 20 != 0)
                    n_row++;

                n_row = (rand()%(n_row-1))+1;
                n_col = (rand()%10)+1;

                gradualPrint(20000, LRED "\t[>] Player encountered a " HUND "Slide!" KRST "\n");
                printf("\tThe %sSlide%s leads the player to %sR[%d] C[%d].\n" KRST, LRED HUND, KRST, KYEL, n_row, n_col);
                break;

            default:
                printf(LBLK "\tPlayer did not encounter anything. [Q%d]\n", *quirk);
                break;
        }

        if (*quirk < uturns) {
            if (n_row % 2 == 0) 
                x_col = 11 - n_col;
            else    
                x_col = n_col;

            x_row = n_row-1;
            position = x_row*10 + x_col;
        }
    }

    //printf("\tQuirk: %d Row: %d Column: %d New Position: %d", quirk, n_row, n_col, position);
    return position;
}

// check this first before the quirk
// special 3-3 and 5-5 quirk, returns new position
int spcLocation(int position, int dice_a, int dice_b) {

    // returns the new location
    int new_pos;

    // special case 3
    if (dice_a == 3 && dice_b == 3) {
        if (position > 70)   // row 8
            new_pos = 99;
        else {
            // algorithm to grab the tile three rows above
            new_pos = ((position/10)+3)*10 + (11-(position%10));
            if (position%10 == 0) new_pos -= 20;
        }
        position = new_pos - position;

        printf(LCYN ", moving three rows up to Tile [%d].\n" KRST, new_pos);
    } 

    // special case 5: none
    if (dice_a == 5 && dice_b == 5) {
        printf(KYEL ", unfortunately missing their turn.\n" KRST);
        position = 0;
    }

    return position;
}

// moves to the new position
int rollDice(int position, int* dice_a, int* dice_b) {

    *dice_a = (rand()%10)+1;
    *dice_b = (rand()%10)+1;


    int new_pos;

    // rolls one dice if the position is on the 10th row
    if (position >= 90) {
        new_pos = *dice_a, *dice_b = 0;
        printf("[%d]", *dice_a);
    } else {

        printf("[%d][%d]", *dice_a, *dice_b);
        if (*dice_a % 2 == 0) 
            *dice_b = 11 - *dice_b;
        new_pos = ((*dice_a-1)*10 + *dice_b) - position;
    }

    if ((*dice_a == 3 && *dice_b == 3) ||
        (*dice_a == 5 && *dice_b == 5)) 
        new_pos = spcLocation(position, *dice_a, *dice_b);
    else     
        printf(KRST ", Moving %s[%d]%s spaces.\n", KYEL, new_pos, KRST);

    return position + new_pos;
}

// *
int isWin(int arr[], int size) {

    int check = 0;
    for (int i = 0; i < size; i++) 
        if(arr[i] == 100) check = 1;
    return check;
}

void overflow(int* position) {
    if (*position > 100) 
        *position = 200 - *position;
}