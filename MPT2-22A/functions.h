    
    void Tokenization(char *initial, str_arr* arr) {

        char* input = strdup(initial);
        char* delims = " .,?!";
        char* token = strtok(input, delims);

        arr->length = 0;
        for (; token != NULL; arr->length++) {
            arr->tokens[arr->length] = token;
            token = strtok(NULL, delims);
        }
    }

    void Translation() {

        char input[150]; 
        str_arr in;

        scanf("%[^\n]", input);
        Tokenization(input, &in);
    }