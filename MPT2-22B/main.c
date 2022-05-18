#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "requisites.h"
#include "functions.h"

int main(void) {

    srand(time(0));

    ints base;
    Fill(&base);

    bool aTurn = true, over = false, ok = false;
    base.a_length = base.e_length, base.b_length = base.y_length;

    intp* Alpha = malloc(sizeof(intp) * base.p_length);
    intp* Beta = malloc(sizeof(intp) * base.p_length);
    Alpha = base.arr_e, Beta = base.arr_y;

    base.f_length = base.p_length - (base.a_length + base.b_length);
    intp* Free = malloc(sizeof(intp) * base.f_length); 
    UpdateFree(Alpha, Beta, Free, &base);

    char result;
    intp prev = (intp){0, 0}, next;

    for (int i = 1; !over; i++) {
        
        printf("\nRound %02d\n", i);
        intp next = base.arr_s[rand() % base.s_length];

        printf("Previous: [%d, %d]\n", prev.x, prev.y);
        printf("Next: [%d, %d]\n\n", next.x, next.y);
        fflush(stdout);

        printf("Turn: %s", aTurn ? "Alpha\n" : "Beta\n");
        fflush(stdout);

        PrintInline(Alpha, base.a_length, "Alpha: ");
        PrintInline(Beta, base.b_length, "Beta: ");
        fflush(stdout);

        NextPlayerMove(prev, next, Alpha, Beta, Free, &base, &aTurn, &ok);
        UpdateFree(Alpha, Beta, Free, &base); 
        result = GameOver(&over, Alpha, Beta, base);
        prev = next;
    }

    printf("\nWinner: Player %c !\n", result);
    Freer(Alpha, Beta, Free, &base);

    return 0;
}