
    // Dependencies: Required for everything to work.
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <conio.h>
    #include <math.h>
    #include <stdbool.h>

    // Extra headers: Contains all functions and global definitions.
    #include "constants.h"
    #include "functions.h"
    #include "graphics.h"

    // Start of the program
    int main(void) {

        // Set the console code page to allow ANSI Escape Sequences and Unicodes
        system("chcp 65001");
        clrscr();

        // Print the menu
        PrintMenu();
        clrscr();

        // Initialize the master structure with data
        ints base;
        Fill(&base);
        
        // Default variables
        bool aTurn = DF, over = false, ok = false, check = true;
        base.a_length = base.e_length, base.b_length = base.y_length;

        // Intiializes set Alpha with E, and set Beta with Y
        intp Alpha[base.a_length], Beta[base.b_length];
        SingleFill(Alpha, base.arr_e, base.a_length);
        SingleFill(Beta, base.arr_y, base.b_length);

        // Set of pairs that are unoccupied [P - (Alpha + Beta)]
        base.f_length = base.p_length - (base.a_length + base.b_length);
        intp Free[base.p_length];
        UpdateFree(Alpha, Beta, Free, &base);

        // Set of pairs of both Alpha and Beta. (Alpha + Beta)
        base.m_length = base.a_length + base.b_length;
        intp Merge[base.m_length];
        MergeFill(Alpha, Beta, Merge, &base);
        
        // Initializes the vairables to be modified
        intp prev, next;
        char result;

        // Start the game, stop once "over" is true
        while (!over) {

            // Print the board after each round
            printf("\n\n");
            PrintBoard(RLEN, CLEN, Merge, base.m_length);
            fflush(stdout);

            // Print accordingly based on aTurn
            if (aTurn)  {
                printf(LBLU "\n\tPlayer A's turn.\n" KRST);
            } else {
                printf(LMAG "\n\tPlayer B's turn.\n" KRST);
            }

            // Input looper [prev]: Loops until a valid input is given
            do {
                printf("\tEnter the coordinates of the piece you want to move: " LRED);
                scanf("%d %d", &prev.x, &prev.y);
                fflush(stdin);
                
                // Error cases
                printf(KRST);
                if (Contains(prev, aTurn ? Beta : Alpha, aTurn ? base.b_length : base.a_length)) {
                    printf(KRED "\tThis piece you chose is not yours.\n\n" KRST);
                } else if (prev.x < 0 || prev.x > RLEN || prev.y < 0 || prev.y > CLEN) {
                    printf(KRED "\tEntered coordinates are out of range.\n\n" KRST);
                } else if (!Contains(prev, aTurn ? Alpha : 
                Beta, aTurn ? base.a_length : base.b_length)) {
                    printf(KRED "\tYou don't have a piece at this location.\n\n" KRST);
                } 

            } while (!Contains(prev, aTurn ? Alpha : Beta, aTurn ? base.a_length : base.b_length));
            
            // Input looper [next]: Loops until a valid input is given
            do {
                printf("\tEnter the coordinates where you want to move %s[%d, %d]%s: " LRED, aTurn ? LBLU : LMAG, prev.x, prev.y, KRST);
                scanf("%d %d", &next.x, &next.y);
                fflush(stdin);

                // Error cases
                printf(KRST);
                if ((aTurn && prev.x != next.x + 1) || (!aTurn && next.x != prev.x + 1)) {
                    printf(KRED "\tYou can only move forward, one tile from your position.\n\n" KRST);
                } else if (!(next.y == prev.y || next.y == prev.y + 1 || next.y + 1 == prev.y)) {
                    printf(KRED "\tYou can only move towards a neighbouring tile.\n\n" KRST);
                } else if (Contains(next, aTurn ? Alpha : Beta, aTurn ? base.a_length : base.b_length)) {
                    printf(KRED "\tYou can't move to a tile that already has a piece.\n\n" KRST); 
                } else {
                    check = false;
                }

            } while (check);

            // Allow updates to the board
            ok = !ok;

            // Determine the corresponding move given the input
            NextPlayerMove(prev, next, Alpha, Beta, Free, &base, &aTurn, &ok);
            // Update the sets after determining the new board
            UpdateFree(Alpha, Beta, Free, &base);
            MergeFill(Alpha, Beta, Merge, &base);

            // Clears screen if user allows it to
            if (CA) clrscr();

            // Check if the game is over
            result = GameOver(&over, Alpha, Beta, base);
            check = true;
        }

        // Print result given the winner of the game
        printf(LWHT "\n\n\tThe game is now over.\n" KRST);
        
        if (result == 'A') {
            printf(LBLU "\tAlpha won the game!\n" KRST);
        } else if (result == 'B') {
            printf(LMAG "\tBeta won the game!\n" KRST);
        } else if (result == 'T') {
            printf(LRED "\tIt's a tie!\n" KRST);
        } 
        
        // Prevents program from abruptly closing
        getchar();
        return 0;
    }
