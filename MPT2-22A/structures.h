
    #define MAX_TOKENS 75

    typedef struct str_arr {
        char* tokens[MAX_TOKENS];
        int length;
    } str_arr;

    typedef enum { 
        false = 0, true = !false
    } bool;
