// Libraries used
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

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

// USleep Values
#define FSCND 999999
#define HSCND 500000
#define MSCND 100000
#define NSCND 50000

// Terminal Width
#define CAP 120

// Quirk Limit
#define QKLMT 5

// * Formatting

/*  
    * Prints an animated ellipses given a delay.
    Precondition: "delay" is a positive value in milliseconds.

    @param delay is the number of milliseconds to wait.
*/
void prEllipses(int delay) {

    usleep(delay*3);
    for (int i = 0; i < 3; i++) {
        printf(".");
        usleep(delay);
    }
}

/*  
    * Prints a given string gradually with animation.
    Precondition: "delay" is a positive value in milliseconds.

    @param delay is the number of milliseconds to wait.
    @param s[] is the string to be printed gradually.
*/
void gradualPrint(int delay, char s[]) {

    for (int i = 0; i < strlen(s); i++) {
        printf("%c", s[i]);
        usleep(delay);
        fflush(stdout);     // OnlineGDB Dependency
    }
}

/*  
    * Appends spaces to the start of a string to center it.
    Precondition: "*text" is a string with a length less than "CAP".

    @param *test is the string to be centered.
*/
void centerText(char *text) {
    printf("%.*s%s \n", (int)((CAP/2) - (strlen(text)/2)), 
        "                                                                              ", text);
}

// * End of Formatting
// * Board Printing

/*  
    * Checks if a player is situated on a given tile. If so, 
    * print the player's number. If not, print the location.
    Preconditions: all values are within the valid bounds.

    @param location is a tile on the board.
    @param arr[] is an array of player locations.
    @param size is the amount of players.
    @param ranking_arr[] is an array of sorted indices of arr[].
    @param g_arr[] is an array of player colors.
    @return 1 (true) if there is player on the tile; false otherwise.
*/ 
int checkPlayer(int location, int arr[], int size, int ranking_arr[], int g_arr[]) {
    
    // Loop through all player locations
    int check = 0, occupant = 0, loc_arr[size];
    for (int i = 0; i < size; i++) {

        // If a player is on a specific tile
        if (arr[i] == location) {
            
            // Adds the player number into loc_arr[]
            loc_arr[occupant] = i;
            occupant++;
            // Return true
            check = 1;
        }
    }

    // If there is one occupant, print with color
    if (occupant == 1)
        printf("\x1B[%d;1m" "|  P%d  |" KRST, g_arr[loc_arr[0]], loc_arr[0]+1);
    // If there are more than one occupants, print without color
    if (occupant == 2) 
        printf(KWHT "| P%dP%d |" KRST, loc_arr[0]+1, loc_arr[1]+1);
    if (occupant == 3) 
        printf(KWHT "| P%d%d%d |" KRST, loc_arr[0]+1, loc_arr[1]+1, loc_arr[2]+1);
    if (occupant == 4) 
        printf(KWHT "| %d%d%d%d |" KRST, loc_arr[0]+1, loc_arr[1]+1, loc_arr[2]+1, loc_arr[3]+1);
    if (occupant == 5) 
        printf(KWHT "| FULL |" KRST);

    // If the tile is 100, print FL [Finish Line] instead
    if (location == 100 && occupant == 0)
        printf(KWHT "|  FL  |" KRST);

    return check;
}

/*  
    * Prints the right side portion of the board.
    Preconditions: all values are within the valid bounds.

    @param row is the row of the board.
    @param round_num is the current number of rounds completed.
    @param arr[] is an array of player locations.
    @param size is the amount of players.
    @param ranking_arr[] is an array of sorted indices of arr[].
    @param new_arr[] is an array of sorted values of arr[].
    @param g_arr[] is an array of player colors.
*/ 
void checkInstance(int row, int round_num, int arr[], int size, int ranking_arr[], int new_arr[], int g_arr[]) {
    
    // Prints either a short or long divider depending on the row.
    if (row % 2 == 1) 
        printf("     %s|%s    ", LBLK, KRST);
    else if (row != 20)
        printf("                                                                                             %s|%s    ", LBLK, KRST);

    // Print given the corresponding row number
    if (row == 2) printf(HBLD "[///] Round %02d:" KRST, round_num);

    // Prints the player ranking
    if ((row >= 4 && row <= 8) && row-4 < size)
        printf("\x1B[%d;1m" "[0%d] " "\x1B[%d;1m" "P-%02d " "\x1B[%d;1m" "[T-%02d]" KRST, 
            g_arr[row-4], row-3, g_arr[ranking_arr[row-4]-1], ranking_arr[row-4], g_arr[row-4], new_arr[row-4]);

    if (row == 10) printf(LBLK "---" KRST);

    if (row == 12) printf("Tiles needed to");
    if (row == 13) printf("reach 1st Place:");
    if (row == 14) printf(HBLD HUND "[%d Tiles]" KRST, arr[ranking_arr[0]-1] - arr[0]);

    if (row == 17) printf(LBLK "Press enter" KRST);
    if (row == 18) printf(LBLK "to continue: " KRST);

    printf("\n");
}

/*  
    * Checks if the player already exists in the array.
    Preconditions: ranking_arr[] is initialized as 0.

    @param player is the current player number.
    @param size is the amount of players.
    @return 0 (false) if the player exists; true otherwise.
*/ 
int nonExisting(int ranking_arr[], int player, int size) {

    int check = 1;
    for (int i = 0; i < size; i++)
        if (ranking_arr[i] == player) check = 0;
    return check;
}

/*  
    * Computes for a sorted arr[] and sorted indices of arr[].
    Preconditions: arr[] contains valid player locations.

    @param arr[] is an array of player locations.
    @param ranking_arr[] is an array of sorted indices of arr[].
    @param new_arr[] is an array of sorted values of arr[].
    @param size is the amount of players.
*/ 
void determineRank(int arr[], int* ranking_arr, int* new_arr, int size) {

    // Duplicate the values arr[] into new_arr[]
    for (int k = 0; k < size; k++) 
        new_arr[k] = arr[k];
    
    // Sort new_arr[] by ascending
    for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
        if (new_arr[j] > new_arr[i]) {
            int temp = new_arr[i];
            new_arr[i] = new_arr[j];
            new_arr[j] = temp;
        }
    }
    }

    // Compares values of new_arr[] and arr[] and stores the index
    for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) 
        if (new_arr[i] == arr[j] && nonExisting(ranking_arr, j+1, size)) 
            ranking_arr[i] = j+1;
    }
}

/*  
    * Prints the current state of the board.
    Preconditions: all values are within the valid bounds.

    @param length is the length of the board.
    @param height is the height of the board.
    @param arr[] is an array of player locations.
    @param g_arr[] is an array of player colors.
    @param size is the amount of players.
    @param ranking_arr[] is an array of sorted indices of arr[].
    @param new_arr[] is an array of sorted values of arr[].
    @param size is the amount of players.
    @param round_num is the current number of rounds completed.
*/ 
void printBoard(int length, int height, int arr[], int g_arr[], int* ranking_arr, int* new_arr, int size, int round_num) {

    int row_iterator = 1, k = 0;
    printf(LBLK "\n\n  *]----------------------------------------------------------------------------------------]*[--------------------[*\n\n" KRST);

    // Loops through all rows
    for (int i = 1; i <= height; i++) {

        // Determine if the column should be printed forwards or backwards.
        printf("\t");
        if (i%2 == 0) {
            for (int j = 1; j <= length; j++)  
                if (!checkPlayer(length*height-(i*10)+j, arr, size, ranking_arr, g_arr))
                    printf(LBLK "|  %02d  |" KRST, length*height-(i*10)+j);
        } else {
            for (int j = height; j >= 1; j--) 
                if (!checkPlayer((10-i)*10+j, arr, size, ranking_arr, g_arr) && (10-i)*10+j != 100)
                    printf(LBLK "|  %02d  |" KRST, (10-i)*10+j);
        }
    
        // Appends the rightmost row
        checkInstance(row_iterator, round_num, arr, size, ranking_arr, new_arr, g_arr);
        row_iterator++;
        checkInstance(row_iterator, round_num, arr, size, ranking_arr, new_arr, g_arr);
        row_iterator++;
    }

    printf(LBLK "  *]----------------------------------------------------------------------------------------]*[--------------------[*\n\n" KRST);
}

// * End of Board Printing
// * Game Design & Intermissions

/*  
    * Prints the starting disclaimer.
    Preconditions: N/A
*/ 
void prDisclaimer() {

    system("cls");

    printf(LBLK);
    usleep(2*MSCND);

    printf("\n\n\n\n\n");
    centerText((char*)"*      D I S C L A I M E R     *");
    usleep(1*NSCND);

    printf("\n\n");
    centerText((char*)"This rendition of Snake and Ladders entitled 'Doggos, Ladders, Snakes and U-turns'");
    usleep(1*NSCND);
    centerText((char*)"was created as a Machine Project in the class CCPROG1 during the");
    usleep(1*NSCND);
    centerText((char*)"First Year of the 1st Term of AY '21 - '22.");
    usleep(1*NSCND);

    printf("\n");
    centerText((char*)"Inspired by the original game 'Snake and Ladders', this version contains modifications");
    usleep(1*NSCND);
    centerText((char*)"to the original game that can both hinder or uplift the player into success.");
    usleep(1*NSCND);

    printf("\n");
    centerText((char*)"This game is to be played in single-player mode, with the player up against one to four");
    usleep(1*NSCND);
    centerText((char*)"computers; depending on the player's choice. ASCII Art belongs to their respective owners. ");
    usleep(1*NSCND);

    printf("\n\n");
    centerText((char*)"Good luck and enjoy the game.");
    usleep(1*FSCND);

    printf("\n\n\n\n" KWHT);
    centerText((char*)"<  Press the enter key to continue  >");

    printf(KRST);

    getchar();
    system("cls");
}

/*  
    * Takes a string and centers and colors it.
    Preconditions: A valid ANSI Color string.
    @param *color is a ANSI Color Escape Sequence.
    @param *text is the string to be centered.
*/ 
void modLogo(char* color, char* text) {

    printf(color);
    centerText(text);
    usleep(1*MSCND);
}

/*  
    * Prints the game logo.
    Preconditions: N/A
*/ 
void prLogo() {

    modLogo(KRST LCYN, (char*)"     __                            __        __   __                  ");
    modLogo(KRST KCYN, (char*)" ___/ /__  ___ ____ ____  ___     / /__ ____/ /__/ /__ _______        ");
    modLogo(KRST LBLU, (char*)"/ _  / _ \\/ _ `/ _ `/ _ \\(_-<_   / / _ `/ _  / _  / -_) __(_-<_       ");
    modLogo(KRST KBLU, (char*)"\\_,_/\\___/\\_, /\\_, /\\___/___( ) /_/\\_,_/\\_,_/\\_,_/\\__/_/ /___( )      ");
    modLogo(KRST LCYN, (char*)"         /___//___/ ___ _/ /|/___ ___     __ __/ /___ _______|/  ___  ");
    modLogo(KRST KCYN, (char*)"          (_-</ _ \\/ _ `/  '_/ -_|_-<_   / // / __/ // / __/ _ \\(_-<_ ");
    modLogo(KRST LBLU, (char*)"         /___/_//_/\\_,_/_/\\_\\\\__/___( )  \\_,_/\\__/\\_,_/_/ /_//_/___( )");
    modLogo(KRST KBLU, (char*)"                                    |/                             |/ ");

    printf(KRST);
}

/*  
    * Prints the main menu.
    Preconditions: "delay" is a positive value in milliseconds.

    @param delay is the number of milliseconds to wait.
*/ 
void prMenu(int delay) {

    usleep(1*HSCND);
    printf("\n\n\n\n");

    prLogo();
    printf("\n\n\n\n");

    gradualPrint(delay, HBLD KWHT "\t\t\t\t\t\t  [1] Start Game     \n\n");
    gradualPrint(delay, KBLU "\t\t\t\t\t\t  [0] Exit     \n\n");
    gradualPrint(delay, "\n\n\t\t\t\t\t\t  [>] " KRST);
}

/*  
    * Prints a standalone loading screen.
    Preconditions: N/A
*/ 
void loadScreen() {

    system("cls");
    usleep(1*FSCND);
    
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n" LBLK);

        printf("%*.sLoading: ", 52);
        fflush(stdout);
        
        for (int i = 0; i <= 100; i++) {
            printf("[%02d%%]", i);
            
            usleep(1*NSCND);
            fflush(stdout);     // OnlineGDB Dependency
            
            if (i != 100) printf("\b \b\b \b\b \b\b \b\b \b");
        }
    
    usleep(1*FSCND);
}

/*  
    * Prints the endgame screen.
    Preconditions: N/A
*/ 
void endGame() {

    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n");
    modLogo(KRST KBLU, "      _______ _     _ _______ __   _ _     _      __   __  _____  _     _        ");
    modLogo(KRST KCYN, "         |    |_____| |_____| | \\  | |____/         \\_/   |     | |     |        ");
    modLogo(KRST LCYN, "         |    |     | |     | |  \\_| |    \\_         |    |_____| |_____|        ");
    modLogo(KRST KBLU, " _______  _____   ______       _____         _______ __   __ _____ __   _  ______");
    modLogo(KRST KCYN, " |______ |     | |_____/      |_____] |      |_____|   \\_/     |   | \\  | |  ____");
    modLogo(KRST LCYN, " |       |_____| |    \\_      |       |_____ |     |    |    __|__ |  \\_| |_____|");
    printf("\n\n\n\n\n\n\n\n\n\n\n" KRST);

    usleep(1*FSCND);
}

// * End of Game Design & Intermissions