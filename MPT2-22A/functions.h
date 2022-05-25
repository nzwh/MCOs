    
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

    /* given an input (string), remove all delims (char) */
    void ReplaceDelim(char* input, char* delim) {

        int k = 0;
        for (int i = 0; i < strlen(input); i++) {
            if (strchr(delim, input[i]) == NULL)
                input[k++] = input[i];
        }

        input[k] = '\0';
        // realloc(input, k + 1); sizeof returns k, so idt needed
    }

    /* turns a sentence into a word array separated by delim */
    void Tokenization(char *init, char* tokens[], int* length) {

        char* input = strdup(init);
        ReplaceDelim(input, ".,?!");

        char* delims = " \n";
        char* token = strtok(input, " \n");
                
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

