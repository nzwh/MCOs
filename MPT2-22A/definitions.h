    
    /// DefaultMax characters for a string
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