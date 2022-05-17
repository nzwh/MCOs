#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "requisites.h"
#include "functions.h"

int main(void) {

    ints base;
    Fill(&base);

    bool aTurn = true, over = false, ok = false;
    intp* Alpha = base.arr_e;
    intp* Beta = base.arr_y;

    int f_length = base.p_length - (base.e_length + base.y_length);
    intp* Free = malloc(sizeof(intp) *f_length);
    UpdateFree(Alpha, Beta, Free, base);

    return 0;
}