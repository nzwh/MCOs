#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>

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

#define BBLK  "\x1B[40m"
#define BRED  "\x1B[41m"
#define BGRN  "\x1B[42m"
#define BYEL  "\x1B[43m"
#define BBLU  "\x1B[44m"
#define BMAG  "\x1B[45m"
#define BCYN  "\x1B[46m"
#define BWHT  "\x1B[47m"

#define HBLD  "\x1B[1m"
#define HUND  "\x1B[4m"
#define HRVS  "\x1B[7m"

#define KRST  "\x1B[0m"

#define CAP 120
#define FSCND 999999
#define HSCND 500000
#define MSCND 100000
#define NSCND 50000

#define QKLMT 5

void prEllipses(int delay) {
    usleep(delay*3);
    for(int i = 0; i < 3; i++) {
        printf(".");
        usleep(delay);
    }
}
/*  
    Checks if a player is situated on a given tile. If so, 
    print the player's number. If not, print the location.

    * Create instance for multiple players situated on a
    * single tile. (ASCII Symbols)
*/ 
int checkPlayer(int location, int arr[], int size, int ranking_arr[], int g_arr[]) {
    
    int check = 0, occupant = 0, loc_arr[size];
    for (int i = 0; i < size; i++) {

        // check if a player is on a specific tile
        if (arr[i] == location) {
            
            // add the player into the loc_arr array
            loc_arr[occupant] = i;
            occupant++;
            // return true if there is an occupant
            check = 1;
        }
    }

    // if a player occupies the specific tile
    if (occupant == 1) {
    
        // print current player with their color
        printf("\x1B[%d;1m" "|  P%d  |" KRST, g_arr[loc_arr[0]], loc_arr[0]+1);
    } 
    if (occupant == 2) 
        printf(KWHT "| P%dP%d |" KRST, loc_arr[0]+1, loc_arr[1]+1);
    if (occupant == 3) 
        printf(KWHT "| P%d%d%d |" KRST, loc_arr[0]+1, loc_arr[1]+1, loc_arr[2]+1);
    if (occupant == 4) 
        printf(KWHT "| %d%d%d%d |" KRST, loc_arr[0]+1, loc_arr[1]+1, loc_arr[2]+1, loc_arr[3]+1);
    if (occupant == 5) 
        printf(KWHT "| FULL |" KRST);

    if (location == 100 && occupant == 0)
        printf(KWHT "|  FL  |" KRST);

    return check;
}
void checkInstance(int row, int round_num, int arr[], int size, int ranking_arr[], int new_arr[], int g_arr[]) {
    
    if (row % 2 == 1) 
        printf("     %s|%s    ", LBLK, KRST);
    else if (row != 20)
        printf("                                                                                             %s|%s    ", LBLK, KRST);

    if (row == 2) printf(HBLD "[///] Round %02d:" KRST, round_num);

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

// *
int nonExisting(int ranking_arr[], int player, int size) {

    int check = 1;
    for (int i = 0; i < size; i++)
        if (ranking_arr[i] == player) check = 0;
    return check;
}

// compute ranking_arr
void determineRank(int arr[], int* ranking_arr, int* new_arr, int size) {

    // duplicate array into a new array
    for (int k = 0; k < size; k++) 
        new_arr[k] = arr[k];
    
    // sort the new array into ascending
    for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
        if (new_arr[j] > new_arr[i]) {
            int temp = new_arr[i];
            new_arr[i] = new_arr[j];
            new_arr[j] = temp;
        }
    }
    }

    // ! re-sort
    // get the indices based on original array from greatest
    for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) 
        if (new_arr[i] == arr[j] && nonExisting(ranking_arr, j+1, size)) 
            ranking_arr[i] = j+1;
    }
}

void printBoard(int length, int height, int arr[], int g_arr[], int* ranking_arr, int* new_arr, int size, int round_num) {

    // gradient codes [LRED, LMAG, LBLU, LCYN, LYEL]
    int row_iterator = 1, k = 0;
    printf(LBLK "\n\n  *]----------------------------------------------------------------------------------------]*[--------------------[*\n\n" KRST);

    for(int i = 1; i <= height; i++) {

        // print board
        printf("\t");
        if (i%2 == 0) {
            for(int j = 1; j <= length; j++)  
                if(!checkPlayer(length*height-(i*10)+j, arr, size, ranking_arr, g_arr))
                    printf(LBLK "|  %02d  |" KRST, length*height-(i*10)+j);
        } else {
            for(int j = height; j >= 1; j--) 
                if (!checkPlayer((10-i)*10+j, arr, size, ranking_arr, g_arr) && (10-i)*10+j != 100)
                    printf(LBLK "|  %02d  |" KRST, (10-i)*10+j);
        }
    
        // appends the right row
        checkInstance(row_iterator, round_num, arr, size, ranking_arr, new_arr, g_arr);
        row_iterator++;
        checkInstance(row_iterator, round_num, arr, size, ranking_arr, new_arr, g_arr);
        row_iterator++;
    }

    printf(LBLK "  *]----------------------------------------------------------------------------------------]*[--------------------[*\n\n" KRST);
}

void gradualPrint(int speed, char s[]) {

    for (int i = 0; i < strlen(s); i++) {
        printf("%c", s[i]);
        usleep(speed);
        // fflush(stdout);
    }
}
void centerText(char *text) {
    printf("%.*s%s \n", (int)((CAP/2) - (strlen(text)/2)), "                                                                              ", text);
}

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

    // ! find alternative
    getchar();
    system("cls");
}

// todo: change function names
void modLogo(char* color, char* text) {
    printf(color);
    centerText(text);
    usleep(1*MSCND);
}
void prLogo() {

    /* // todo: replace logo
    modLogo(LWHT, (char*)"    ___  ____ ____ ____ ____ ____    _    ____ ___  ___  ____ ____ ____      "); 
    modLogo(KWHT, (char*)"    |  \\ |  | | __ | __ |  | [__     |    |__| |  \\ |  \\ |___ |__/ [__      ");
    modLogo(LBLK, (char*)"    |__/ |__| |__] |__] |__| ___]    |___ |  | |__/ |__/ |___ |  \\ ___]     ");
    modLogo(LWHT, (char*)"       ____ _  _ ____ _  _ ____ ____    _  _ ___ _  _ ____ _  _ ____         ");
    modLogo(KWHT, (char*)"       [__  |\\ | |__| |_/  |___ [__     |  |  |  |  | |__/ |\\ | [__         ");
    modLogo(LBLK, (char*)"       ___] | \\| |  | | \\_ |___ ___]    |__|  |  |__| |  \\ | \\| ___]        "); */

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

void prMenu(int delay) {

    usleep(1*HSCND);
    printf("\n\n\n\n");

    prLogo();
    printf("\n\n\n\n");

    gradualPrint(delay, HBLD KWHT "\t\t\t\t\t\t  [1] Start Game     \n\n");
    gradualPrint(delay, KBLU "\t\t\t\t\t\t  [0] Exit     \n\n");
    gradualPrint(delay, "\n\n\t\t\t\t\t\t  [>] " KRST);
}

void printDiceDigit(int dice) {

    if (dice == 10) printf(KCYN "1 0");
    else printf(KCYN "0 %d", dice);   
}
void printDice(int dice_a, int dice_b) {

    printf("\n\n\n\n" LBLK);

    printf("\t                             .:      -#=:                        \n");
    printf("\t                       #====+##      *-*:===.                    \n");
    printf("\t               .#=====:   .=:=-      # .*   :==-.                \n");
    printf("\t          .====:        .=-  #       #  .*      -==-             \n");
    printf("\t         -#-     ::    =-   :=       #    *.  ::   .-#-          \n");
    printf("\t        =-=:         ==     *       .*     *.       ==*.         \n");
    printf("\t        * *=---:.  -=      .+       :=  :: .#=-----=*  #         \n");
    printf("\t       =:-=    .:-+-   ::  +.       =-    .*        #  #         \n");

    printf("\t       *.*         *       *        +:   .*   ");
    printDiceDigit(dice_b);
    printf(LBLK "   *. #         \n");

    printf("\t      -=*    ");
    printDiceDigit(dice_a);
    printf(LBLK "   =:     --        :%%=--#:         :+ #         \n");
        
    printf("\t      *+.           *  .::#          .*:  -+:        # #         \n");
    printf("\t     :#=         .--=-=++-             -==: :+=      *:*         \n");
    printf("\t     ##      :-=++----:                   .==-:==.   :**         \n");
    printf("\t    .%%  .=+#*=--.                             -==*+:  %%*         \n");
    printf("\t    +#+*+-.                                      :=##-*+         \n");
    printf("\t                                                    .=*=         \n");

    printf("\n\n\n\n");
}

void loadScreen() {

    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n" LBLK);

        printf("%*.sLoading: ", 52);
        fflush(stdout);
        
        for(int i = 0; i <= 100; i++) {
            printf("[%02d%%]", i);
            
            usleep(1*NSCND);
            fflush(stdout);
            
            if (i != 100) printf("\b \b\b \b\b \b\b \b\b \b");
        }
    
    usleep(1*FSCND);
}
