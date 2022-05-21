    
    #define MAX_TOKENS 75
    #define MAX_CHARS 20
    #define MAX_ROWS 10

    #define MAX_NAME 25
    #define MAX_INPUT 150
    #define CAP 120

    void clrscr() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    typedef struct Lang_tr {
        char lang[MAX_CHARS];
        char tran[MAX_CHARS];
    } Lang_tr;

    typedef struct Entry {
        Lang_tr row[MAX_ROWS];
        int length;
    } Entry;

    typedef enum { 
        false = 0, true = !false
    } bool;



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

    void Tokenization(char *initial, char* tokens[], int* length);

