#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "functions.h"
#include "graphics.h"

int main(void) {

    system("cls");

    ints base;
    Fill(&base);

    bool aTurn = true, over = false, ok = false;
    base.a_length = base.e_length, base.b_length = base.y_length;

    intp *Alpha = malloc(sizeof(intp) * base.p_length);
    intp *Beta = malloc(sizeof(intp) * base.p_length);
    Alpha = base.arr_e, Beta = base.arr_y;

    base.f_length = base.p_length - (base.a_length + base.b_length);
    intp *Free = malloc(sizeof(intp) * base.f_length);
    UpdateFree(Alpha, Beta, Free, &base);

    base.m_length = base.a_length + base.b_length;
    intp* Merge = malloc(sizeof(intp) * base.m_length);
    MergeFill(Alpha, Beta, Merge, &base);

    intp prev, next;
    char result;

    while (!over) {

        PrintBoard(RLEN, CLEN, Merge);
        fflush(stdout);

        if (aTurn)  printf(LBLU "Player A's turn.\n" KRST);
        else        printf(LMAG "Player B's turn.\n" KRST);

        printf("Choose a piece to move: ");
        scanf("%d %d", &prev.x, &prev.y);
        printf("Where do you want to place it: ");
        scanf("%d %d", &next.x, &next.y);

        NextPlayerMove(prev, next, Alpha, Beta, Free, &base, &aTurn, &ok);
        UpdateFree(Alpha, Beta, Free, &base);
        MergeFill(Alpha, Beta, Merge, &base);

        system("cls");
        result = GameOver(&over, Alpha, Beta, base);
    }

    printf("\nWinner: %s Player %c !\n", result == 'A' ? LBLU : LMAG, result);
    Freer(Alpha, Beta, Free, &base);

    return 0;
}
