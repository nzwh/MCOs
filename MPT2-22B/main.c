#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "constants.h"
#include "functions.h"
#include "graphics.h"

int main(void) {

    system("CHCP 65001");
    system("cls");

    ints base;
    Fill(&base);

    bool aTurn = true, over = false, ok = false, check = true;
    base.a_length = base.e_length, base.b_length = base.y_length;

    intp Alpha[base.a_length], Beta[base.b_length];
    SingleFill(Alpha, base.arr_e, base.a_length, &base);
    SingleFill(Beta, base.arr_y, base.b_length, &base);

    base.f_length = base.p_length - (base.a_length + base.b_length);
    intp Free[base.p_length];
    UpdateFree(Alpha, Beta, Free, &base);

    base.m_length = base.a_length + base.b_length;

    intp Merge[base.m_length];
    MergeFill(Alpha, Beta, Merge, &base);

    intp prev, next;
    char result;

    while (!over) {

        PrintBoard(RLEN, CLEN, Merge, base.m_length);
        fflush(stdout);

        if (aTurn)  printf(LBLU "Player A's turn.\n" KRST);
        else        printf(LMAG "Player B's turn.\n" KRST);

        do {
            printf("Choose a piece to move: ");
            scanf("%d %d", &prev.x, &prev.y);
            fflush(stdin);
            
            if (Contains(prev, aTurn ? Beta : Alpha, aTurn ? base.b_length : base.a_length)) {
                printf(KRED "The piece you chose is not yours.\n" KRST);
            } else if (prev.x < 0 || prev.x > RLEN || prev.y < 0 || prev.y > CLEN) {
                printf(KRED "Coordinates out of range.\n" KRST);
            } else if (!Contains(prev, aTurn ? Alpha : Beta, aTurn ? base.a_length : base.b_length)) {
                printf(KRED "You don't have a piece at this location.\n" KRST);
            } 

        } while (!Contains(prev, aTurn ? Alpha : Beta, aTurn ? base.a_length : base.b_length));

        do {
            printf("Where do you want to place it: ");
            scanf("%d %d", &next.x, &next.y);
            fflush(stdin);

            if ((aTurn && prev.x != next.x + 1) || (!aTurn && next.x != prev.x + 1)) {
                printf(KRED "You can only move forward, one tile from your position.\n" KRST);
            } else if (!(next.y == prev.y || next.y == prev.y + 1 || next.y + 1 == prev.y)) {
                printf(KRED "You can only towards a neighouring tile.\n" KRST);
            } else {
                check = false;
            }

        } while (check);

        NextPlayerMove(prev, next, Alpha, Beta, Free, &base, &aTurn, &ok);
        UpdateFree(Alpha, Beta, Free, &base);
        MergeFill(Alpha, Beta, Merge, &base);

        system("cls");
        result = GameOver(&over, Alpha, Beta, base);
        check = true;
    }

    if (result == 'T') {
        printf(KGRN "It's a tie!\n" KRST);
    } else {
        printf("%s Player %c wins!\n" KRST, result == 'A' ? LBLU : LMAG, result);
    }
    
    return 0;
    getchar();
}
