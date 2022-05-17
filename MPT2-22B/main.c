#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "requisites.h"
#include "functions.h"

int main(void) {

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

    return 0;
}