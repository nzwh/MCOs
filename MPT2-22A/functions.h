    
    int CreateMenu(char* title, int options, char* options_names[] ) {

        int focus = 1, loop = true;
        while (loop) {

            printf("\n%s\n\n", title);
            fflush(stdout);

            for (int i = 0; i < options; i++) {
                if (i == focus - 1) {
                    printf("-> %s\n", options_names[i]);
                } else {
                    printf("   %s\n", options_names[i]);
                }
            }

            printf("\nPress [W] and [S] to navigate. Press [Enter] to continue.\n");
            printf("\033[H");

            char t = _getch();
            if (t == '\r') {
                loop = false;
            } else if (t == 'w') {
                if (focus > 1) focus--;
            } else if (t == 's') {
                if (focus < options) focus++;
            }
        }

        return focus;
    }

    char* ReplaceDelim(char* input, char* delim, char new) {

        char* new_input = (char*) malloc(strlen(input) + 1);
        int push = 0, l = 0;
    
        for (int i = 0; i < strlen(input); i++, push = 0) {
            for (int j = 0; j < strlen(delim); j++) 
                if (input[i] == delim[j]) 
                    push = 1;

            if (push == 0) {
                new_input[l] = input[i];
                l++;
            }
        }

        new_input[l] = '\0'; // is this necessary
        realloc(new_input, l + 1);
        return new_input;
    }

    void Tokenization(char *initial, char* tokens[], int* length) {
        char* init = strdup(initial);
        char* input = ReplaceDelim(init, ".,?!", ' ');

        char* delims = " \n";
        char* token = strtok(input, delims);
                
        for (; token != NULL; (*length)++) {
            tokens[*length] = token;
            token = strtok(NULL, delims);
        }
    }

    void Translation() {

        clrscr();
        printf("Enter your sentence: \n\n");
        
        char* tokens[MAX_TOKENS], input[MAX_INPUT + 1];
        int length = 0;

        fgets(input, MAX_INPUT, stdin);
        Tokenization(input, tokens, &length);

        printf("\nOutput [%d words]: \n\n", length);
        for (int i = 0; i < length; i++) {
            printf("[%s] ", tokens[i]);
            fflush(stdout);
        }

        getchar();

        /* continuation... */
    }

