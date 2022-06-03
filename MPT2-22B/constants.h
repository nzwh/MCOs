   
    // Default Values
    #define RLEN 7
    #define CLEN 5
    #define YLIM 2
    #define ELIM 6

    // Unicode Borders
    #define NCUL "\u250c"
    #define NCUR "\u2510"
    #define NCDL "\u2514"
    #define NCDR "\u2518"
    #define NHFT "\u2500"
    #define NVFT "\u2502"
    #define NBML "\u2524"
    #define NBMR "\u251c"
    #define NBMU "\u252c"
    #define NBMD "\u2534"
    #define NALL "\u253c"

    // ANSI Escape Sequences (Colors)
    #define LBLK  "\x1B[30;1m"
    #define LRED  "\x1B[31;1m"
    #define LGRN  "\x1B[32;1m"
    #define LYEL  "\x1B[33;1m"
    #define LBLU  "\x1B[34;1m"
    #define LMAG  "\x1B[35;1m"
    #define LCYN  "\x1B[36;1m"
    #define LWHT  "\x1B[37;1m"

    #define KBLK  "\x1B[30m"
    #define KRED  "\x1B[31m"
    #define KGRN  "\x1B[32m"
    #define KYEL  "\x1B[33m"
    #define KBLU  "\x1B[34m"
    #define KMAG  "\x1B[35m"
    #define KCYN  "\x1B[36m"
    #define KWHT  "\x1B[37m"

    #define HBLD  "\x1B[1m"
    #define HUND  "\x1B[4m"
    #define HRVS  "\x1B[7m"

    #define KRST  "\x1B[0m"

    // Pair Structure
    typedef struct intp {
        int x; int y; int p;
    } intp;

    // Native True/False
    typedef enum { 
        false = 0, true = !false
    } bool;

    // Set Container Structure
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

        int a_length;
        int b_length;
        int f_length;
        int m_length;
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
