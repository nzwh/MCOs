// Include all the header files
#include "g_logic.h"

int main(void) {

    srand(time(0));
    int length = 10, height = 10;
    int play = 1, pSize, pStruct, rCount = 0;
    int stopover, quirk;
    int dice_a = 0, dice_b = 0;

    // Gradient Codes [LRED, LMAG, LBLU, LCYN, LYEL]
    int g_arr[] = {31, 35, 34, 36, 33};

    // Starting sequence
    prDisclaimer();
    prMenu(30000);

    // Loop until the player chooses 1 or 0.
    do {

        scanf("%d", &play);
        if (play < 0 || play > 2)
            printf("\b \b");

    } while (play != 1 && play != 0);
    
    // Loop until player exits
    while (play) {

        // * Start of Prologue
        
        // Loading sequence
        loadScreen();

        // Loop until the player chooses a value between 2 and 5.
        do {
            
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");

            printf(LBLU "\t\t\t\t\tHow many players?  > " KRST);
            scanf("%d", &pSize);
            getchar();

            if (pSize < 2 || pSize > 5) {
                printf(LRED "\t\t\t\t\tPlayer count should be between 2 and 5. " KRST);
                usleep(FSCND);
            }

        } while (pSize < 2 || pSize > 5);

        // * End of Prologue
        // * Start of Initialization

        // Initializes player arrays
        int py[pSize], pp[pSize];
        int ranking_arr[pSize], new_arr[pSize];
        int pyx_move[pSize];

        // Fill all values with 0
        for (int i = 0; i < pSize; i++) {
            py[i] = 0;
            pyx_move[i] = 0;
        }

        // Initializes quirks
        int pyx[pSize][QKLMT];
        for (int i = 0; i < pSize; i++)
            for(int j = 0; j < QKLMT; j++)
            pyx[i][j] = 0;

        // Initializes quirk totals
        int pyx_total[QKLMT-1];

        // * End of initialization
        // * Start of Game

        system("cls");
        usleep(1*FSCND);
        
        // Loop until a player wins, or reaches Tile 100
        do {   
            
            // * Start of Game Intro

            // Clear ranking_arr for new values
            for (int i = 0; i < pSize; i++) 
                ranking_arr[i] = 0;

            // Typerwriter: Presequence
            printf("\n\n\n\n");
            gradualPrint(1*NSCND, LBLK "\t[>] Determining Player Sequence");
            prEllipses(1*HSCND);

            // Initializes the Player Sequence Number through a function
            int pSequence = playerSequence(pSize), iSequence = 0;
            printf(KRST "\n\n\tPlayer Sequence Integer: %s%d" KRST, LRED, pSequence);
            
            // Inverts the Player Sequence Number
            for (; pSequence != 0; pSequence /= 10) {
                iSequence *= 10;
                iSequence += pSequence % 10;
            }

            // Typewriter: Sequence
            usleep(1*FSCND);
            printf("\n\tThe current sequence of players goes as follows: \n\t");
            for (int c = iSequence, i = 0; c != 0; c /= 10, i++) {
                usleep(1*HSCND);
                printf("\x1B[%d;1m" "Player %d%s, then ", g_arr[(c%10)-1], c%10, KRST);
            }
            printf("\b \b\b \b\b \b\b \b\b \b\b \b\b \b. ");

            usleep(1*FSCND);
            printf(LBLK "\n\n\t< Press the enter key to continue >" KRST);
            getchar();

            // * End of Game Intro
            // * Start of Player Loop

            printf("\n\n");
            pStruct = iSequence;

            // Loops through the inverted sequence until it reaches zero
            for (int prev = 0; pStruct != 0 && prev != 100; pStruct /= 10) {
                
                // Extract current player
                int pCurrent = (pStruct%10)-1;
                quirk = 0;  // Reset quirk
            
                // Typewriter: Player
                usleep(1*HSCND);
                printf("\x1B[%d;1m" "\t[>] Player %02d%s's Turn!\n", g_arr[pCurrent], pCurrent+1, KRST);
                usleep(1*HSCND);
                printf("\x1B[%d;1m" "\tPlayer %02d%s rolled: " KCYN, g_arr[pCurrent], pCurrent+1, KRST);

                // Initializes the duplicate with the new location
                pp[pCurrent] = rollDice(py[pCurrent], &dice_a, &dice_b);
                // Check if the player reaches beyond Tile 100
                overflow(&pp[pCurrent]);
                
                // Typewriter: Roll
                printf(LBLK "\tLanded on Tile [%02d].\n\n" KRST, pp[pCurrent]);
                usleep(1*HSCND);

                // Does not execute if the player reaches Tile 100
                if (pp[pCurrent] < 100 && (dice_a != 5 || dice_b != 5)) {

                    // Initializes the duplicate with th new location
                    pp[pCurrent] = getQuirk(py[pCurrent], pp[pCurrent], &quirk);

                    // Typewriter: Quirk
                    printf("\x1B[%d;1m" "\tPlayer %02d%s's current location is now on %sTile [%02d]%s.\n\n", 
                            g_arr[pCurrent], pCurrent+1, KRST, KCYN  HUND, pp[pCurrent], KRST);
                    usleep(1*HSCND);
                    // Check if the player reaches beyond Tile 100
                    overflow(&pp[pCurrent]);    

                    // Initialize quirk as 0 if it is not a [D,L,S,U]
                    if (quirk > 4) quirk = 0;

                    // Computes for the farthest distance travelled from an object
                    if (abs(pp[pCurrent] - py[pCurrent]) > pyx[pCurrent][0] && quirk != 0) {
                        pyx[pCurrent][0] = abs(pp[pCurrent] - py[pCurrent]);
                        pyx_move[pCurrent] = quirk;
                    }
                    
                    // Increments the quirk total of the player
                    if (quirk <= 4 && quirk > 0) pyx[pCurrent][quirk]++;
                }

                // Store the new location in the current array
                py[pCurrent] = pp[pCurrent];

                // Typewriter: Wait
                printf(LBLK "\t< Press the enter key to continue >" KRST);
                printf(KRST "\n\n");
                getchar();

                // Stores the previous player's location
                prev = py[pCurrent];
            }

            // * End of Player Loop
            // * Start of Statistic Update

            // Computes for ranking_arr[] and new_arr[]
            determineRank(py, ranking_arr, new_arr, pSize);
            // Only runs if no one has won yet
            if (!isWin(py, pSize)) {
                
                rCount++; // Increment round count
                
                // Reset values
                for (int i = 0; i < QKLMT-1; i++)
                    pyx_total[i] = 0;

                // Totals the quirk locations of all players into one array
                for (int i = 0; i < QKLMT-1; i++)
                    for (int j = 0; j < pSize; j++)
                        pyx_total[i] += pyx[j][i+1];

                // Print the menu
                do {

                    printf(KRST "\n\t[0] Continue " LBLK "\n\t[1] View Board \n\t[2] Statistics \n\n\t" LBLU "[>] " KRST);
                    scanf(" %d", &stopover);

                    // Menu input
                    switch(stopover) {
                        case 1:

                            // View the player board
                            printf("\n\n");
                            printBoard(length, height, py, g_arr, ranking_arr, new_arr, pSize, rCount);
                            printf("\n\n");

                            getchar();
                            getchar();

                        break;
                        case 2:

                            // View the player ranking
                            printf(KRST "\n\n\n\n\n\n\n\n\n\n" LBLK);
                            centerText((char*)"*]--------------------------------------------------------------------------------------[*");

                            printf(KRST "\n\n");
                            printf(LCYN "\t\t\t     Doggos Encountered:  [%02d]\t", pyx_total[doggos-1]);
                            printf(KRST "    Closest to Finish:     " "\x1B[%d;1m" "Player %02d\n", g_arr[ranking_arr[0]-1], ranking_arr[0]);

                            printf(LBLU "\t\t\t     Ladders Escalated:   [%02d]\t", pyx_total[ladders-1]);
                            printf(KRST "    Farthest from Finish:  " "\x1B[%d;1m" "Player %02d\n", g_arr[ranking_arr[pSize-1]-1], ranking_arr[pSize-1]);

                            printf(LRED "\t\t\t     Slides Utilized:     [%02d]\n", pyx_total[slides-1]);
                            printf(LMAG "\t\t\t     U-turns Appeared:    [%02d]\t", pyx_total[uturns-1]);

                            for (int i = 0; i < pSize; i++)
                                if (ranking_arr[i] == 1)
                            printf(LRED "    Your current ranking:  [#%02d]\n", i+1);
                            printf(KRST "\n\n" LBLK);

                            centerText((char*)"*]--------------------------------------------------------------------------------------[*");
                            printf(KRST "\n\n\n\n\n\n\n\n\n\n");

                            getchar();
                            getchar();

                        break;
                    }
                
                } while (stopover != 0);
                
                getchar();
            }
            
            // * End of Statistic Update
            system("cls");

        } while(!isWin(py, pSize));

        // * Start of Summary

        // Compute digit to column number
        if (dice_a % 2 == 0 && dice_b != 0) 
            dice_b = 11 - dice_b;
        int py_winner = ranking_arr[0]-1;

        printf(LBLK "\n\n\n\n  *]---------------------------------------------------------------------------------------------------------------[*\n\n\n" KRST);

            // Header logo
            modLogo(KRST KBLU ,"____      ___  _______    ________    ____  ______   ______  __    __");
            modLogo(KRST KCYN ,"/___(\\___\\/  / /  /|  |\\__/|  ||  |\\__/|  | /  /\\  \\ |  |)  )(__(  )__)");
            modLogo(KRST LCYN ,"(   \\)___)\\__\\/__/ |__|    |__||__|    |__|/__/  \\__\\|__|\\__\\   |__|  ");
            printf(KRST "\n\n");

            // * Statistic Box

            centerText("__                                                                                            __"); 
            centerText("|                                                                                              |"); 

            printf ("\t\t\t   " "\x1B[%d;1m" HUND "Player %02d won!" KRST, g_arr[py_winner], py_winner+1);

            printf(KRST LCYN "\n\n\t\t\t   Doggos Encountered:  [%02d]" KRST, pyx[py_winner][doggos]);
            printf("\tFarthest Object Distance:  [%02d Tiles]", pyx[py_winner][0]);

            printf(LBLU "\n\t\t\t   Ladders Escalated:   [%02d]" KRST, pyx[py_winner][ladders]);
            printf("\tFarthest Object Travel:    ");

                // Prints the appropriate quirk
                switch(pyx_move[py_winner]) {
                    case doggos: printf("Doggo "); break;
                    case ladders: printf("Ladder "); break;
                    case slides: printf("Slide "); break;
                    case uturns: printf("U-turn "); break;
                    default: printf("None "); break;
                }

            printf(LRED "\n\t\t\t   Slides Utilized:     [%02d]" KRST, pyx[py_winner][slides]);
            printf(LMAG "\n\t\t\t   U-turns Appeared:    [%02d]" KRST, pyx[py_winner][uturns]);

            printf(KYEL "\tRounds Completed:          [%02d]" KRST, rCount);

                printf("\n\n\t\t\t   Player rolled a %s[%d]", LYEL, dice_a);
                if (dice_b != 0) printf("[%d]", dice_b);

                // Prints the appropriate quirk
                switch(quirk) {
                    case doggos: printf(KRST " into a %sDoggo", LCYN); break;
                    case ladders: printf(KRST " into a %sLadder", LBLU); break;
                    case slides: printf(KRST " into a %sSlide", LRED); break;
                    case uturns: printf(KRST " into a %sU-turn", LMAG); break;
                }

                printf(KRST " that led to Tile 100. \n");

            centerText("|_                                                                                            _|"); 

            // * End of Statistic Box

        printf(LBLK "\n\n  *]---------------------------------------------------------------------------------------------------------------[*\n\n\n\n" KRST);
        getchar();

        // * End of Summary
        // * Start of Re-input

        do {

            printf(KWHT "\n\t[>] Would you like to play again?\n" LBLK 
                "\t[1] Play Again\n\t[2] Return to Main Menu\n\t[0] Exit" LBLU "\n\n\t[>] " KRST);
            scanf(" %d", &play);                                                 
            
        } while (play != 1 && play != 0 && play != 2);

        // * End of Re-input
        // * Optional: Return to Main Menu

        if (play == 2) {
            system("cls");
            prMenu(30000);
            do {
                scanf("%d", &play);
                if (play < 0 || play > 2)
                    printf("\b \b");
            } while (play != 1 && play != 0);
        }

        // * End of Optional
    }

    // Prints the ending screen
    endGame();
}