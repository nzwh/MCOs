   
    #define RLEN 7
    #define CLEN 5
    #define YLIM 2
    #define ELIM 6

    typedef struct intp {
        int x; int y;
    } intp;

    typedef enum { 
        false = 0, true = !false
    } bool;

    typedef struct ints {
        int* arr_r;
        int* arr_c;

        intp* arr_p;
        intp* arr_s;
        intp* arr_y;
        intp* arr_e;

        int p_length;
        int s_length;
        int y_length;
        int e_length;
    } ints;

    //  * Function that accepts an "ints" structure and fills the 
    //  * elements with its corresponding values using constants. 
    void Fill(ints *base) {
        
        /* Array R */
        base->arr_r = malloc(sizeof(int) * RLEN);
        for (int i = 1; i <= RLEN; i++)
            base->arr_r[i-1] = i;
        
        /* Array C */
        base->arr_c = malloc(sizeof(int) * CLEN);
        for (int i = 1; i <= CLEN; i++)
            base->arr_c[i-1] = i;

        /* Array P */
        base->p_length = RLEN * CLEN;
        base->arr_p = malloc(sizeof(intp) * base->p_length);
        for (int i = 0; i < RLEN; i++) {
            for (int j = 0; j < CLEN; j++) {
                base->arr_p[i*CLEN+j].x = base->arr_r[i];
                base->arr_p[i*CLEN+j].y = base->arr_c[j];
            }
        }

        /* Array S */
        int r_limit = ceil(RLEN / 2), c_limit = ceil(CLEN / 2);
        base->s_length = (r_limit * c_limit) + (RLEN - (r_limit)) * (CLEN - c_limit);
        base->arr_s = malloc(sizeof(intp) * base->s_length);
        for (int i = 0, j = 0; i <= RLEN * CLEN; i++) {
            if (base->arr_p[i].x % 2 == base->arr_p[i].y % 2) {
                base->arr_s[j].x = base->arr_p[i].x;
                base->arr_s[j].y = base->arr_p[i].y;
                j++;
            }
        }

        /* Array Y */
        base->y_length = ceil((double)(CLEN) / 2 * YLIM);
        base->arr_y = malloc(sizeof(intp) * base->y_length);
        for (int i = 0; base->arr_s[i].x <= YLIM; i++) {
            base->arr_y[i].x = base->arr_s[i].x;
            base->arr_y[i].y = base->arr_s[i].y;
        }

        /* Array E */
        base->e_length = ceil((double)(CLEN) / 2 * (RLEN + 1 - ELIM));
        base->arr_e = malloc(sizeof(intp) * base->e_length);
        for (int i = 0, j = base->s_length - 1; base->arr_s[j].x >= ELIM; i++, j--) {
            base->arr_e[base->e_length-1-i].x = base->arr_s[j].x;
            base->arr_e[base->e_length-1-i].y = base->arr_s[j].y;
        }
    }
