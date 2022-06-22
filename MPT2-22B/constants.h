   
    /// Default Values
    #define RLEN 7
    #define CLEN 5
    #define YLIM 2
    #define ELIM 6

    /// Unicode Borders
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

    /// ANSI Escape Sequences (Light Colors)
    #define LBLK  "\x1B[30;1m"
    #define LRED  "\x1B[31;1m"
    #define LGRN  "\x1B[32;1m"
    #define LYEL  "\x1B[33;1m"
    #define LBLU  "\x1B[34;1m"
    #define LMAG  "\x1B[35;1m"
    #define LCYN  "\x1B[36;1m"
    #define LWHT  "\x1B[37;1m"

    /// ANSI Escape Sequences (Dark Colors)
    #define KBLK  "\x1B[30m"
    #define KRED  "\x1B[31m"
    #define KGRN  "\x1B[32m"
    #define KYEL  "\x1B[33m"
    #define KBLU  "\x1B[34m"
    #define KMAG  "\x1B[35m"
    #define KCYN  "\x1B[36m"
    #define KWHT  "\x1B[37m"

    /// ANSI Escape Sequences (Text Properties and Reset)
    #define HBLD  "\x1B[1m"
    #define HUND  "\x1B[4m"
    #define HRVS  "\x1B[7m"
    #define KRST  "\x1B[0m"

    /// Default Preferences
    int BT = true;
    int DF = true;
    int CA = true;

    /// Coordinate Structure
    typedef struct intp {
        int x; int y; int p;
    } intp;

    /// Set Container Structure
    typedef struct ints {
        int arr_r[RLEN];
        int arr_c[CLEN];

        intp arr_p[RLEN*CLEN];
        intp arr_s[RLEN*CLEN];
        intp arr_y[RLEN*CLEN];
        intp arr_e[RLEN*CLEN];

        int p_length;
        int s_length;
        int y_length;
        int e_length;

        int a_length;
        int b_length;
        int f_length;
        int m_length;
    } ints;



    
    /* 
        / Clears the terminal window.
    */
    void clrscr() {
        #ifdef _WIN32
            system("cls"); 
        #else
            system("clear");
        #endif
    }

    /*
        / Enables escape sequences for colors. 
    */
    void esqncs() {
        #ifdef _WIN32
            system("chcp 65001"); 
        #else
            system("clear");
        #endif
    }

    /*  
        / Function that accepts an "ints" structure and fills the 
        / elements with its corresponding values by modifying
        / constants with a specific constraint.
        - @param base: The master structure to be filled.
    */
    void Fill(ints *base) {
        
        //- Initialize Set [R]
        for (int i = 1; i <= RLEN; i++)
            base->arr_r[i-1] = i;
        
        //- Initialize Set [C]
        for (int i = 1; i <= CLEN; i++)
            base->arr_c[i-1] = i;

        //- Initialize Set [P]
        base->p_length = RLEN * CLEN;
        for (int i = 0; i < RLEN; i++) {
            for (int j = 0; j < CLEN; j++) {
                base->arr_p[i*CLEN+j].x = base->arr_r[i];
                base->arr_p[i*CLEN+j].y = base->arr_c[j];
            }
        }

        //- Initialize Set [S]
        base->s_length = ceil((double)RLEN * CLEN / 2);
        for (int i = 0, j = 0; i <= RLEN * CLEN; i++) {
            if (base->arr_p[i].x % 2 == base->arr_p[i].y % 2) {
                base->arr_s[j].x = base->arr_p[i].x;
                base->arr_s[j].y = base->arr_p[i].y;
                j++;
            }
        }

        //- Initialize Set [Y]
        base->y_length = ceil((double)CLEN / 2 * YLIM);
        for (int i = 0; base->arr_s[i].x <= YLIM; i++) {
            base->arr_y[i].x = base->arr_s[i].x;
            base->arr_y[i].y = base->arr_s[i].y;
        }

        //- Initialize Set [E]
        base->e_length = ceil((double)CLEN / 2 * (RLEN + 1 - ELIM));
        for (int i = 0, j = base->s_length - 1; base->arr_s[j].x >= ELIM; i++, j--) {
            base->arr_e[base->e_length-1-i].x = base->arr_s[j].x;
            base->arr_e[base->e_length-1-i].y = base->arr_s[j].y;
        }
    }