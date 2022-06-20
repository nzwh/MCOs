
    /*  
        * Prints a string with a typewriter effect.
        @param delay - Time in milliseconds to wait
        @param s[] - String to print into
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
        * Prints the preferences menu, to change global variables.
        @param options[][] - List of menu options to choose from
        @param count - Number of options to choose from
        @param focus - The current option selected
    */
    void Preferences(char options[][40], int count, int focus) {

        clrscr();
        int loop = true;

        // Loop and print until user selects exit
        while (loop) {
            
            // Print the menu
            clrscr();
            printf("\n\n\t%s\n\n", LRED "Press [Enter] on an option to change it." KRST);
            fflush(stdout);

            for (int i = 0; i < count; i++) {
                if (i == focus - 1) {
                    printf(LBLU "\t-> %s\n" KRST, options[i]);
                } else {
                    printf("\t   %s\n", options[i]);
                }
            }

            printf("\n\tPress [W] and [S] to navigate. Select [Exit] to return to the main menu.\n");
            printf("\033[H");

            // Get the user's input
            char t = _getch();
            fflush(stdin);
            // Handle user input
            if (t == '\r') {
                loop = false;
            } else if (t == 'w' || t == 'W') {
                if (focus > 1) focus--;
            } else if (t == 's' || t == 'S') {
                if (focus < count) focus++;
            }
        }  

        // Based on the user's input, change global variables and reprint the menu
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
        * Prints a divider based on set parameters.
        @param edge - Character to use as an edge
        @param fill - Character to use as a fill
        @param length - Width of each divider cell
        @param iter - Amount of cells to print
        @param nl - Prints a newline if true
    */
    void PrintDivider(char* edge, char* fill, int length, int iter, int nl) {

        for (int i = 0; i < iter; i++) {
            printf("%s", edge);
            for (int i = 0; i < length; i++) 
                printf("%s", fill);
        }

        printf("%s", edge);
        printf(nl ? "\n" : "   ");
    }

    /*  
        * Prints the main board, given dimensions and occupied cells.
        @param r - Length of the board
        @param c - Width of the board
        @param Pieces - Array of ccordinates of occupied cells
        @param p_length - Length of Pieces
    */
    void PrintBoard(int r, int c, intp* Pieces, int p_length) {
        
        // Print the topmost divider
        printf("\t");
        PrintDivider(BT ? (char*)NBMU : (char*)"-", BT ? (char*)NHFT : (char*)"-", 3, CLEN, false);
        PrintDivider(BT ? (char*)NBMU : (char*)"-", BT ? (char*)NHFT : (char*)"-", 7, CLEN, true);

        // Loop through the board
        for (int i = 0, ctr = 0; i < r; i++) {
            
            // Print each row
            printf("\t");
            for (int x = 0; x < 2; x++) {
                for (int j = 0; j < c; j++) {

                    printf("%s", BT ? NVFT : "|");

                    // Print the content of the cell based on Pieces
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

                    // If there are no occupants, print a blank cell
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

            // Print a divider for each row
            printf("\n\t");
            if (i + 1 < r) {
                PrintDivider(BT ? (char*)NALL : (char*)"-", BT ? (char*)NHFT : (char*)"-", 3, CLEN, false);
                PrintDivider(BT ? (char*)NALL : (char*)"-", BT ? (char*)NHFT : (char*)"-", 7, CLEN, true);
            }

        }

        // Print the bottommost divider
        PrintDivider(BT ? (char*)NBMD : (char*)"-", BT ? (char*)NHFT : (char*)"-", 3, CLEN, false);
        PrintDivider(BT ? (char*)NBMD : (char*)"-", BT ? (char*)NHFT : (char*)"-", 7, CLEN, true);
    }

    /*  
        * Prints the main menu. This will be the first screen the user sees.
    */
    void PrintMenu() {

        int opt;
        clrscr();
        usleep(900000);

        // Print the "Checkershift" Logo
        printf("\n\n");
        puts("\t" LCYN NBMU NHFT NCUR NBMU " " NBMU NBMU NHFT NCUR NBMU NHFT NCUR NBMU " " NBMU NBMU NHFT NCUR NBMU NHFT NCUR NCUL NHFT NCUR NBMU " " NBMU NBMU NBMU NHFT NCUR NCUL NBMU NCUR KRST);
        puts("\t" KBLU NVFT "  " NBMR NHFT NBML NBMR NBML " " NVFT "  " NBMR "< " NBMR NBML " " NBMR "\\" NCDR NCDL NHFT NCUR NBMR NHFT NBML NVFT NBMR NBML "  " NVFT KRST);
        puts("\t" LMAG NBMD NHFT NCDR NBMD " " NBMD NBMD NHFT NCDR NBMD NHFT NCDR NBMD " " NBMD NBMD NHFT NCDR NBMD " " NBMD NCDL NHFT NCDR NBMD " " NBMD NBMD NBMD "   " NBMD KRST);

        // Print the introductory message
        Typewriter(30000, (char*)(LRED "\n\tWelcome to Checkershift," KRST));
        Typewriter(30000, (char*)(" a modified game of checkers,\n"));
        Typewriter(30000, (char*)("\twhere pieces behave like chess pawns.\n"));
        Typewriter(30000, (char*)(LRED "\n\tEnter an option to get started." KRST));

        // Print the options
        printf("\n\n");
        printf("\t[1] Enter Game\n");
        printf("\t[2] Instructions\n");
        printf("\t[3] Preferences\n");
        printf("\t[4] Quit\n");

        // Get the user's input
        printf("\n");
        printf(LBLU "\t[>] ");
        // Handle the user's input
        scanf("%d", &opt);
        fflush(stdin);

        // Based on the user's input, call the appropriate function
        printf(KRST);
        switch (opt) {
            case 1:     // Start game immediately

                clrscr();
                break;

            case 2:     // Print instructions, then return to the main menu

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
                
            case 3: {   // Print preferences, then return to the main menu
                
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

            } case 4:   // Exit the game immediately

                clrscr();
                exit(0);

            default:
                clrscr();
        }
    }