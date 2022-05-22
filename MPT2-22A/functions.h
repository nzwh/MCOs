    
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

    void Tokenization(char *initial, char* tokens[], int* length) {

        char* input = strdup(initial);
        char* delims = " .,?!\n";
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

        printf("\nOutput [%d words]: \n", length);
        for (int i = 0; i < length; i++) {
            printf("[%s] ", tokens[i]);
            fflush(stdout);
        }

        /* continuation... */
    }

