
    /// Dependencies: Required for everything to work.
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <conio.h>
    #include <math.h>
    #include <stdbool.h>



    //- [Constants]



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



    /// Functions declaration
    void clrscr();
    void esqncs();
    void Fill();

    bool Contains();
    bool Subset();
    bool FullRow();
    bool CheckSide();

    void Swap();
    void PairSort();
    void MergeFill();
    void SingleFill();
    void UpdateFree();
    void Add();
    void Remove();
    void NextPlayerMove();
    char GameOver();

    void Typewriter();
    void Preferences();
    void PrintDivider();
    void PrintBoard();
    void PrintMenu();



    //- [Main]



    /// Start of the program
    int main(void) {

        //- Set the console code page to allow ANSI Escape Sequences and Unicodes
        esqncs();
        clrscr();

        //- Print the menu
        PrintMenu();
        clrscr();

        //- Initialize the master structure with data
        ints base;
        Fill(&base);
        
        //- Default variables
        bool aTurn = DF, over = false, ok = false, check = true;
        base.a_length = base.e_length, base.b_length = base.y_length;

        //- Intiializes set Alpha with E, and set Beta with Y
        intp Alpha[base.a_length], Beta[base.b_length];
        SingleFill(Alpha, base.arr_e, base.a_length);
        SingleFill(Beta, base.arr_y, base.b_length);

        //- Set of pairs that are unoccupied [P - (Alpha + Beta)]
        base.f_length = base.p_length - (base.a_length + base.b_length);
        intp Free[base.p_length];
        UpdateFree(Alpha, Beta, Free, &base);

        //- Set of pairs of both Alpha and Beta. (Alpha + Beta)
        base.m_length = base.a_length + base.b_length;
        intp Merge[base.m_length];
        MergeFill(Alpha, Beta, Merge, &base);
        
        //- Initializes temporary variables
        intp prev, next;
        char result;

        //- Start the game, stop once "over" is true
        while (!over) {

            //- Print the board after each round
            printf("\n\n");
            PrintBoard(RLEN, CLEN, Merge, base.m_length);
            fflush(stdout);

            //- Print accordingly based on aTurn
            if (aTurn)  {
                printf(LBLU "\n\tPlayer A's turn.\n" KRST);
            } else {
                printf(LMAG "\n\tPlayer B's turn.\n" KRST);
            }

            //- Input looper [prev]: Loops until a valid input is given
            do {
                printf("\tEnter the coordinates of the piece you want to move: " LRED);
                scanf("%d %d", &prev.x, &prev.y);
                fflush(stdin);
                
                //_ Error cases
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
            
            //- Input looper [next]: Loops until a valid input is given
            do {
                printf("\tEnter the coordinates where you want to move %s[%d, %d]%s: " LRED, aTurn ? LBLU : LMAG, prev.x, prev.y, KRST);
                scanf("%d %d", &next.x, &next.y);
                fflush(stdin);

                //_ Error cases
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

            //- Allow updates to the board
            ok = !ok;

            //- Determine the corresponding move given the input
            NextPlayerMove(prev, next, Alpha, Beta, Free, &base, &aTurn, &ok);
            //- Update the sets after determining the new board
            UpdateFree(Alpha, Beta, Free, &base);
            MergeFill(Alpha, Beta, Merge, &base);

            //- Clears screen if user allows it to
            if (CA) clrscr();

            //- Check if the game is over
            result = GameOver(&over, Alpha, Beta, base);
            check = true;
        }

        //- Print result given the winner of the game
        printf(LWHT "\n\n\tThe game is now over.\n" KRST);
        
        if (result == 'A') {
            printf(LBLU "\tAlpha won the game!\n" KRST);
        } else if (result == 'B') {
            printf(LMAG "\tBeta won the game!\n" KRST);
        } else if (result == 'T') {
            printf(LRED "\tIt's a tie!\n" KRST);
        } 
        
        //- Prevents program from abruptly closing
        getchar();
        return 0;
    }



    //- [Functions]



    /*  
        / Swaps two "intp" coordinates using pointers.
        - @param a: The initial coordinate.
        - @param b: The coordinate to swap with.
    */
    void Swap(intp* a, intp* b) {

        intp temp = *a;
        *a = *b;
        *b = temp;
    }

    /*  
        / Sorts an "intp" array of coordinates by ascending value.
        / Sorts by x-value first, then y-value.
        - @param Main: The array of coordinates to sort with.
        - @param length: The current length of the array.
    */
    void PairSort(intp* Main, int length) {

        for (int i = 0; i < length; i++) {
            for (int j = i + 1; j < length; j++) {

                if (Main[i].x > Main[j].x) 
                    Swap(&Main[i], &Main[j]);
                if (Main[i].x == Main[j].x && Main[i].y > Main[j].y) 
                    Swap(&Main[i], &Main[j]);
            }
        }
    }

    /*  
        / Function that merges two "intp" arrays into one merged
        / "intp" array. Values are stored in the "Merge" array.
        - @param Alpha: The first array to merge with.
        - @param Beta: The second array to merge with.
        - @param Merge: The array to store the merged array in.
        - @param base: The base struct to get the length of the arrays.
    */
    void MergeFill(intp* Alpha, intp* Beta, intp* Merge, ints* base) {

        base->m_length = base->a_length + base->b_length;
        for (int i = 0; i < base->a_length; i++) {
            Merge[i].x = Alpha[i].x;
            Merge[i].y = Alpha[i].y;
            Merge[i].p = 0;
        }

        for (int i = 0; i < base->b_length; i++) {
            Merge[i + base->a_length].x = Beta[i].x;
            Merge[i + base->a_length].y = Beta[i].y;
            Merge[i + base->a_length].p = 1;
        }

        PairSort(Merge, base->m_length);
    }

    /*  
        / Function that copies the elements of an "intp" array 
        / to another "intp" array of the same length.
        - @param Main: The array to store the copied values.
        - @param Source: The array to duplicate the values from.
        - @param length: The current length of both of the arrays.
        - @param base: The base struct to get the length of the arrays.
    */
    void SingleFill(intp* Main, intp* Source, int length) {

        for (int i = 0; i < length; i++) {
            Main[i].x = Source[i].x;
            Main[i].y = Source[i].y;
        }
    }

    /*  
        / Function that determines if a given "intp" coordinate is an 
        / element of a given "intp" array of coordinates.
        - @param Pair: The coordinate to check if it is in the array.
        - @param Array: The array to check if the coordinate is in.
        - @param length: The current length of the array.
        - @return "true": if the pair is in the array, "false": if not.
    */
    bool Contains(intp Pair, intp* Array, int length) {

        for (int i = 0; i < length; i++) {
            if (Array[i].x == Pair.x && Array[i].y == Pair.y) 
                return true;
        }

        return false;
    }

    /*  
        / Function that updates the "Free" array on command by removing
        / the "Alpha" or "Beta" array from the entire set of coordinates.
        - @param Alpha: The first array to ignore values from.
        - @param Beta: The second array to ignore values from.
        - @param Free: The array to store the remaining values in.
        - @param base: The base struct to get the length of the arrays.
    */
    void UpdateFree(intp* Alpha, intp* Beta, intp* Free, ints* base) {

        int j = 0;
        for (int i = 0; i < base->p_length; i++) {
            if (Contains(base->arr_p[i], Alpha, base->a_length)) continue;
            if (Contains(base->arr_p[i], Beta, base->b_length)) continue;
                Free[j] = base->arr_p[i];
                j++;
        }

        base->f_length = j;
    }

    /*  
        / Function that appends an "intp" coordinate to the
        / end of the given "intp" array.
        - @param Pair: The coordinate to add to the array.
        - @param Array: The array to add the coordinate to.
        - @param length: The current length of the array.
        - @param limit: The maximum limit of the array.
    */
    void Add(intp Pair, intp* Array, int* length, int limit) {

        if (*length < limit) {
            Array[*length] = Pair;
            (*length)++;
        }
    }

    /*  
        / Function that removes an "intp" coordinate from the given array
        / by swapping it with the last element of the array, and then
        / decrementing the length of the array.
        - @param Pair: The coordinate to remove from the array.
        - @param Array: The array to remove the coordinates from.
        - @param length: The current length of the array.
        - @param limit: The maximum limit of the array.
    */
    void Remove(intp Pair, intp* Array, int* length) {
        
        if (length <= 0) return;
        for (int i = 0; i < *length; i++) {
            if (Array[i].x == Pair.x && Array[i].y == Pair.y) {

                Swap(&Array[i], &Array[(*length) - 1]);
                (*length)--;
                return;
            }
        }
    }

    /*  
        / Function that determines the current player move based on
        / two inputs: "prev" and "next". It updates Alpha/Beta/Free
        / arrays given the case scenario.
        - @param prev: The current coordinate.
        - @param next: The coordinate to go to.
        - @param Alpha/Beta/Free: The arrays to modify the values in.
        - @param base: The base struct that contains the arrays and their lengths.
        - @param aTurn: Determines which Player's turn it is.
        - @param ok: Determines if the entered move is valid.
    */
    void NextPlayerMove(intp prev, intp next, intp* Alpha, intp* Beta, intp* Free, ints* base, bool* aTurn, bool* ok) {
        
        //- Separate the coordinates into variables
        int a = prev.x, b = prev.y;
        int c = next.x, d = next.y;
        printf("\n");

        //- 03: Alpha moves to a free tile.
        if (*ok && *aTurn && Contains(next, Free, base->f_length)) {

            if (Contains(prev, Alpha, base->a_length))
                Remove(prev, Alpha, &base->a_length);
            Add(next, Alpha, &base->a_length, base->p_length);

            *ok = !ok;
            *aTurn = !*aTurn;
            printf(!(*aTurn) ? LBLU : LMAG);
            printf("\tMoved tile [%d, %d] to tile [%d, %d].\n" KRST, a, b, c, d);
        }

        //- 04: Beta moves to a free tile.
        if (*ok && !*aTurn && Contains(next, Free, base->f_length)) {

            if (Contains(prev, Beta, base->b_length)) 
                Remove(prev, Beta, &base->b_length);
            Add(next, Beta, &base->b_length, base->p_length);

            *ok = !ok;
            *aTurn = !*aTurn;
            printf(!(*aTurn) ? LBLU : LMAG);
            printf("\tMoved tile [%d, %d] to tile [%d, %d].\n" KRST, a, b, c, d);
        }

        //- 05: Alpha cannot eat since it is not on a white tile.
        if (*ok && *aTurn && Contains(next, Beta, base->b_length) && 
            !(next.x % 2 == next.y % 2)) {  // Set S checking

            printf(KRED "\tYou cannot eat since it is not on a white tile.\n" KRST);
        }

        //- 06: Alpha moves to a tile occupied by Beta.
        if (*ok && *aTurn && Contains(next, Beta, base->b_length) && 
            (next.x % 2 == next.y % 2)) {  // Set S checking

            Remove(next, Beta, &base->b_length);
            if (Contains(prev, Alpha, base->a_length))
                Remove(prev, Alpha, &base->a_length);
            if (!Contains(next, Alpha, base->a_length))
                Add(next, Alpha, &base->a_length, base->p_length);

            *ok = !ok;
            *aTurn = !*aTurn;
            printf(KYEL "\tBeta's tile in [%d, %d] has been eaten.\n" KRST, c, d);
        }

        //- 07: Beta cannot eat since it is not on a white tile
        if (*ok && !*aTurn && Contains(next, Alpha, base->a_length) && 
            !(next.x % 2 == next.y % 2)) {  // Set S checking

            *ok = !ok;
            printf(KRED "\tYou cannot eat since it is not on a white tile.\n" KRST);
        }

        //- 08: Beta moves to a tile occupied by Alpha.
        if (*ok && !*aTurn && Contains(next, Alpha, base->a_length) && 
            (next.x % 2 == next.y % 2)) {  // Set S checking

            Remove(next, Alpha, &base->a_length);
            if (Contains(prev, Beta, base->b_length))
                Remove(prev, Beta, &base->b_length);
            if (!Contains(next, Beta, base->b_length))
                Add(next, Beta, &base->b_length, base->p_length);

            *ok = !ok;
            *aTurn = !*aTurn;
            printf(KYEL "\tAlpha's tile in [%d, %d] has been eaten.\n" KRST, c, d);
        }

        //- Cleanup
        fflush(stdin);

        //- Prompt return
        printf(LBLK "\t< Press [Enter] to continue >" KRST);
        getchar();
    }

    /*  
        / Function that determines if an "intp" array is a subset,
        / or has the elements of another "intp" array.
        - @param Main: The array to check.
        - @param Compare: The array to check against.
        - @param m_len/clen: The current length of both of the arrays.
        - @return "true": if the array is a subset, "false": if not.
    */
    bool Subset(intp* Main, intp* Compare, int m_len, int c_len) {

        for (int i = 0; i < m_len; i++) {
            if (!Contains(Main[i], Compare, c_len))
                return false;
        }

        return true;
    }

    /*  
        / Function that determines if all elements of an 
        / "intp" array are in the same, given row (x-value).
        - @param Array: The array to check.
        - @param length: The current length of the array.
        - @param row: The row (x-value) to look for.
        - @return "true": if all elements are in the row, "false": if not.
    */
    bool FullRow(intp* Array, int length, int row) {
            
        for (int i = 0; i < length; i++) {
            if (Array[i].x != row)
                return false;
        }

        return true;
    }

    /*  
        / Function that checks if at least one element of an "intp"
        / array is in the specified row (x-value), and if they're 
        / not in the Set S.
        - @param Main: The array to check.
        - @param length: The current length of the array.
        - @param row: The row (x-value) to look for.
        - @return "true": if one or more element is in the row, "false": if not.
    */
    bool CheckSide(intp* Main, int length, int row) {
        
        for (int i = 0; i < length; i++) {
            if (Main[i].x == row && (Main[i].x % 2 != Main[i].y % 2)) 
                return true;
        }

        return false;
    }

    /*  
        / Function that checks if the game is over or not
        / after each iteration. Once true, it determines who wins
        / the game by returning the winner as a character.
        - @param over: The boolean that determines if the round is over.
        - @param Alpha: The array of Alpha's coordinates.
        - @param Beta: The array of Beta's coordinates.
        - @param base: The base struct that contains the arrays and their lengths.
        - @return "char": The character of the winner.
    */
    char GameOver(bool* over, intp* Alpha, intp* Beta, ints base) {
        
        //- Alpha win condition
        if (base.b_length == 0 || (base.a_length > 0 &&
            Subset(Alpha, base.arr_y, base.a_length, base.y_length))) {

            *over = true;
            return 'A';

        //- Beta win condition
        } else if (base.a_length == 0 || (base.b_length > 0 &&
            Subset(Beta, base.arr_e, base.b_length, base.e_length))) {
            
            *over = true;
            return 'B';
        }

        //- If one player's pieces are all in the opposite row
        if (FullRow(Beta, base.b_length, RLEN) || 
            FullRow(Alpha, base.a_length, 1)) {

            *over = true;
            return 'T';
        }

        //- If both players have one piece in the opposite row, 
        //- and both pieces are not in the set S
        if (CheckSide(Alpha, base.a_length, 1) &&
            CheckSide(Beta, base.b_length, RLEN)) {

            *over = true;
            return 'T';
        }

        //- No one wins, continue the game
        return '/';
    }



    //- [Graphics]



    /*  
        / Prints a string with a typewriter effect.
        - @param delay: Time in milliseconds to wait.
        - @param s[]: String to print into.
    */
    void Typewriter(int delay, char s[]) {

        for (int i = 0; i < strlen(s); i++) {
            printf("%c", s[i]);
            usleep(delay);
            fflush(stdout);
        }

        usleep(900000);
    }

    /*  
        / Prints the preferences menu, to change global variables.
        - @param options[][]: List of menu options to choose from.
        - @param count: Number of options to choose from.
        - @param focus: The current option selected.
    */
    void Preferences(char options[][40], int count, int focus) {

        clrscr();
        bool loop = true;

        //- Loop and print until user selects exit
        while (loop) {
            
            //- Print the menu
            clrscr();
            printf("\n\n\t%s\n\n", LRED "Press [Enter] on an option to change it." KRST);
            fflush(stdout);

            //- Print options
            for (int i = 0; i < count; i++) {
                if (i == focus - 1) {
                    printf(LBLU "\t-> %s\n" KRST, options[i]);
                } else {
                    printf("\t   %s\n", options[i]);
                }
            }

            //- Prompt help
            printf("\n\tPress [W] and [S] to navigate. Select [Exit] to return to the main menu.\n");
            printf("\033[H");

            //- Get the user's input
            char t = _getch();
            fflush(stdin);

            //- Handle user input
            if (t == '\r') {
                loop = false;
            } else if (t == 'w' || t == 'W') {
                if (focus > 1) focus--;
            } else if (t == 's' || t == 'S') {
                if (focus < count) focus++;
            }
        }  

        //- Based on the user's input, change global variables and reprint the menu
        switch (focus) {
            case 1:
                BT = !BT;
                !BT ? strcpy(options[0], "Background Type: ASCII") : 
                    strcpy(options[0], "Background Type: Unicode");
                Preferences(options, count, focus);
                break;
            case 2:
                DF = !DF;
                !DF ? strcpy(options[1], "Default Starting Player: Beta") :
                    strcpy(options[1], "Default Starting Player: Alpha");
                printf("%s", options[1]);
                Preferences(options, count, focus);
                break;
            case 3:
                CA = !CA;
                !CA ? strcpy(options[2], "Clear Background After Move: No") :
                    strcpy(options[2], "Clear Background After Move: Yes");
                Preferences(options, count, focus);
                break;
        }
    }

    /*  
        / Prints a divider based on set parameters.
        - @param edge: Character to use as an edge.
        - @param fill: Character to use as a fill.
        - @param length: Width of each divider cell.
        - @param iter: Amount of cells to print.
        - @param nl: Prints a newline if true.
    */
    void PrintDivider(char* edge, char* fill, int length, int iter, int nl) {

        //- Print cells
        for (int i = 0; i < iter; i++) {
            printf("%s", edge);
            for (int i = 0; i < length; i++) 
                printf("%s", fill);
        }

        //- Print end
        printf("%s", edge);
        printf(nl ? "\n" : "   ");
    }

    /*  
        / Prints the main board, given dimensions and occupied cells.
        - @param r: Length of the board.
        - @param c: Width of the board.
        - @param Pieces: Array of ccordinates of occupied cells.
        - @param p_length: Length of Pieces.
    */
    void PrintBoard(int r, int c, intp* Pieces, int p_length) {
        
        //- Print the topmost divider
        printf("\t");
        PrintDivider(BT ? (char*)NBMU : (char*)"-", BT ? (char*)NHFT : (char*)"-", 3, CLEN, false);
        PrintDivider(BT ? (char*)NBMU : (char*)"-", BT ? (char*)NHFT : (char*)"-", 7, CLEN, true);

        //- Loop through the board
        for (int i = 0, ctr = 0; i < r; i++) {
            
            //- Print each row
            printf("\t");
            for (int x = 0; x < 2; x++) {
                for (int j = 0; j < c; j++) {

                    printf("%s", BT ? NVFT : "|");

                    //- Print the content of the cell based on Pieces
                    if (ctr < p_length && Pieces[ctr].x == i + 1 && Pieces[ctr].y == j + 1) {
                        if (Pieces[ctr].p == 0) {
                            if (x == 1) {
                                printf("%s [%d,%d] %s", LBLU, i + 1, j + 1, KRST);
                            } else { 
                                printf("%s A %s", LBLU, KRST);
                            }
                        } else if (Pieces[ctr].p == 1) {
                            if (x == 1) {
                                printf("%s [%d,%d] %s", LMAG, i + 1, j + 1, KRST);
                            } else { 
                                printf("%s B %s", LMAG, KRST);
                            }
                        }
                        ctr++;

                    //- If there are no occupants, print a blank cell
                    } else {
                        if (x == 1) {
                            printf(" [%d,%d] ", i + 1, j + 1);
                        } else if ((j + 1) % 2 == (i + 1) % 2) { 
                            printf(" - ");
                        } else { 
                            printf("   ");
                        }
                    }
                }

                printf("%s   ", BT ? NVFT : "|");
            }

            //- Print a divider for each row
            printf("\n\t");
            if (i + 1 < r) {
                PrintDivider(BT ? (char*)NALL : (char*)"-", BT ? (char*)NHFT : (char*)"-", 3, CLEN, false);
                PrintDivider(BT ? (char*)NALL : (char*)"-", BT ? (char*)NHFT : (char*)"-", 7, CLEN, true);
            }

        }

        //- Print the bottommost divider
        PrintDivider(BT ? (char*)NBMD : (char*)"-", BT ? (char*)NHFT : (char*)"-", 3, CLEN, false);
        PrintDivider(BT ? (char*)NBMD : (char*)"-", BT ? (char*)NHFT : (char*)"-", 7, CLEN, true);
    }

    /*  
        / Prints the main menu. This will be the first screen the user sees.
    */
    void PrintMenu() {

        int opt;
        clrscr();
        usleep(900000);

        //- Print the "Checkershift" Logo
        printf("\n\n");
        puts("\t" LCYN NBMU NHFT NCUR NBMU " " NBMU NBMU NHFT NCUR NBMU NHFT NCUR NBMU " " NBMU NBMU NHFT NCUR NBMU NHFT NCUR NCUL NHFT NCUR NBMU " " NBMU NBMU NBMU NHFT NCUR NCUL NBMU NCUR KRST);
        puts("\t" KBLU NVFT "  " NBMR NHFT NBML NBMR NBML " " NVFT "  " NBMR "< " NBMR NBML " " NBMR "\\" NCDR NCDL NHFT NCUR NBMR NHFT NBML NVFT NBMR NBML "  " NVFT KRST);
        puts("\t" LMAG NBMD NHFT NCDR NBMD " " NBMD NBMD NHFT NCDR NBMD NHFT NCDR NBMD " " NBMD NBMD NHFT NCDR NBMD " " NBMD NCDL NHFT NCDR NBMD " " NBMD NBMD NBMD "   " NBMD KRST);

        //- Print the introductory message
        Typewriter(30000, (char*)(LRED "\n\tWelcome to Checkershift," KRST));
        Typewriter(30000, (char*)(" a modified game of checkers,\n"));
        Typewriter(30000, (char*)("\twhere pieces behave like chess pawns.\n"));
        Typewriter(30000, (char*)(LRED "\n\tEnter an option to get started." KRST));

        //- Print the options
        printf("\n\n");
        printf("\t[1] Enter Game\n");
        printf("\t[2] Instructions\n");
        printf("\t[3] Preferences\n");
        printf("\t[4] Quit\n");

        //- Handle the user's input
        printf(LBLU "\n\t[>] ");
        scanf("%d", &opt);
        fflush(stdin);

        //- Based on the user's input, call the appropriate function
        printf(KRST);
        switch (opt) {
            case 1:     //- Start game immediately

                clrscr();
                break;

            case 2:     //- Print instructions, then return to the main menu

                clrscr();
                printf("\n\n");

                usleep(90000);
                Typewriter(30000, (char*)(LRED "\t[>] The game of Checkershift is a modified version of the game of checkers.\n"));
                Typewriter(30000, (char*)("\tPlayers take turns in moving a piece of their choosing.\n\n"));
                Typewriter(30000, (char*)("\t[>] Players can only move vertically forward from their original position,\n"));
                Typewriter(30000, (char*)("\tand horizontally to a neighboring tile.\n\n"));
                Typewriter(30000, (char*)("\t[>] They cannot move backwards or sideways.\n"));
                Typewriter(30000, (char*)("\tHence, if they reach the end of the board, they are eternally stuck.\n\n"));
                Typewriter(30000, (char*)("\t[>] The player can only eat another player if they are on a white tile [-].\n"));
                Typewriter(30000, (char*)("\tOtherwise, they aren't allowed.\n\n"));
                Typewriter(30000, (char*)("\t[>] A player wins if they manage to eat all of the opponent's players,\n"));
                Typewriter(30000, (char*)("\tor if they manage to place all their players on the same zigzag pattern\n\ton the other side of the board.\n\n"));
                Typewriter(30000, (char*)("\t[>] A tie occurs if no player is able to win due to constraints.\n\n"));
                Typewriter(30000, (char*)("\t[>] To play, select the coordinate of the piece you would like to move.\n"));
                Typewriter(30000, (char*)("\tIf it's valid, select the coordinate where you would like the piece to go to.\n\n"));
                Typewriter(30000, (char*)(LBLU "\t[>>>] May the best player win.\n" KRST));

                printf(LBLK "\n\n\n\t< Press [Enter] to continue >" KRST);
                getchar();

                PrintMenu();
                break;
                
            case 3: {   //- Print preferences, then return to the main menu
                
                clrscr();
                int count = 4, focus = 1;
                char options[count][40];

                BT ? strcpy(options[0], "Background Type: Unicode") : strcpy(options[0], "Background Type: ASCII");
                DF ? strcpy(options[1], "Default Starting Player: Alpha") : strcpy(options[1], "Default Starting Player: Beta");
                CA ? strcpy(options[2], "Clear Background After Move: Yes") : strcpy(options[2], "Clear Background After Move: No");
                strcpy(options[3], "Exit Preferences");
                Preferences(options, count, focus);

                PrintMenu();
                break;

            } case 4:   //- Exit the game immediately

                clrscr();
                exit(0);

            default:
                clrscr();
        }
    }