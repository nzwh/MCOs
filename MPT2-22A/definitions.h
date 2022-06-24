    
    /// Max characters for a string
    #define MAX_CHARS 20

    /// Max blocks in a single entry
    #define MAX_DATA 10

    /// Max entries in a container
    #define MAX_ENTRY 150

    /// Max user input for translation
    #define MAX_INPUT 150

    /// Max user input for filename
    #define MAX_FILE 30

    /// Max elements in the word array
    #define MAX_TOKENS 75

    /// Max characters in a line
    #define MAX_LINE 50

    /// String datatype
    typedef char String[MAX_CHARS + 1];

    /// Language & Translation Structure
    typedef struct Data {
        String language;
        String translation;
    } Data;

    /// Entry Structure [Max 10]
    typedef struct Entry {
        Data block[MAX_DATA];
        int length;
    } Entry;

    /// Main Structure [Max 150]
    typedef struct Container {
        Entry base[MAX_ENTRY];
        int count;
    } Container;

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



    /*
        / Function definitions.
    */
    void Exit();

    void StartMenu();
    void ManageData();
    void Translation();

    void AddEntry();
    void AddTranslation();
    void DeleteEntry();
    void DeleteTranslation();

    void DisplayAllEntries();
    void SearchWord();
    void SearchTranslation();

    void Export();
    void Import();

    void Tokenization();
    Container SearchLanguage();

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