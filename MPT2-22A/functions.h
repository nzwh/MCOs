    
    /*
        / Creates a menu and returns the index of the selected item.
        - @title: Name of the menu.
        - @option_names: Array of menu item names.
        - @options[]: Number of menu items.
    */
    int CreateMenu(char* title, int options, char* options_names[] ) {

        //- Initialize variables.
        int focus = 1, loop = true;

        //- Print menu.
        while (loop) {

            printf("\n\n");
            puts(LCYN "\t" NBMU NHFT NBMU NCUL NCUR NCUL NCUL NBMU NCUR NBMU NHFT NCUR NBMU NHFT NBMU NCUL NCUR NCUL NCUL NHFT NCUR NBMU " " " " NBMU NHFT NBMU NCUL NBMU NCUR NBMU NHFT NBMU KRST);
            puts(KBLU "\t" NBMR NBML " " NVFT NVFT NVFT " " NVFT " " NBMR "\\" NCDR NBMR NHFT NBML NVFT NVFT NVFT NCDL NHFT NCUR NVFT " " NBMU NBMR NHFT NBML " " NVFT " " NBMR NBML " " KRST);
            puts(LMAG "\t" NBMD NHFT NBMD NCDR NCDL NCDR " " NBMD " " NBMD " " NBMD NBMD " " NBMD NCDR NCDL NCDR NCDL NHFT NCDR NBMD NHFT NBMD NBMD " " NBMD " " NBMD " " NBMD NHFT NBMD KRST); 

            printf(LRED "\n\t%s\n\n" KRST, title);
            fflush(stdout);

            for (int i = 0; i < options; i++) {
                if (i == focus - 1) {
                    printf(LBLU "\t>  %s\n" KRST, options_names[i]);
                } else {
                    printf("\t   %s\n", options_names[i]);
                }
            }

            printf(LBLK "\n\tPress [W] and [S] to navigate. Press [Enter] to continue.\n" KRST);
            printf("\033[H");

            char t = tolower(getch());
            fflush(stdin);

            if (t == '\r') {
                loop = false;
            } else if (t == 'w') {
                if (focus > 1) focus--;
                else if (focus == 1) focus = options;
            } else if (t == 's') {
                if (focus < options) focus++;
                else if (focus == options ) focus = 1;
            }
        }

        return focus;
    }

    /*
        / Capitalizes the first letter of a string.
        - @str: String to capitalize.
        - @return: Capitalized string.
    */
    char* Capitalize(char* str) {

        str[0] = toupper(str[0]);
        return str;
    }

    /* 
        / Removes all delimiters in a given string.
        - @input: String to be cleaned.
        - @delim: String of delimiters.
    */
    void ReplaceDelim(char* input, char* delim) {

        int k = 0;
        for (int i = 0; i < strlen(input); i++) {
            if (strchr(delim, input[i]) == NULL)
                input[k++] = tolower(input[i]);
        }

        input[k] = '\0';
    }

    /* 
        / Turns input into an array separated by delimeters.
        - @init: String to be manipulated.
        - @tokens[]: Where the separated strings will be stored.
        - @length: Length of the "tokens[]" array.
        - @delim: String of delimiters.
    */
    void Tokenization(char *init, char* tokens[], int* length, char* delim) {

        //- Remove all delimiters.
        char* input = strdup(init);
        ReplaceDelim(input, delim);

        char* whitespace = " \n";
        char* token = strtok(input, whitespace);
                
        for (; token != NULL; (*length)++) {
            tokens[*length] = token;
            token = strtok(NULL, whitespace);
        }
    }

    /* 
        / Removes non-alphabetic characters from a string
        / and turns them all into lowercase.
        - @input: String to be modified.
    */
    void Alphalower(char* input) {
            
        int k = 0;
        for (int i = 0; i < strlen(input); i++) {
            if (isalpha(input[i])) 
                input[k++] = tolower(input[i]);
        }

        input[k] = '\0';
    }

    /* 
        / Processes input until a valid word is entered.
        - @str: String to be modified.
        - @message: Prompt message.
        - @limit: The maximum length of an input.
    */
    void ParseInput(char* str, char* message, int limit) {
        
        do { 
            printf(message);
            fgets(str, MAX_INPUT, stdin);
            fflush(stdout);

            Alphalower(str);
            if (strlen(str) < 1 || strlen(str) > limit) 
                printf(LRED "\t[>] Invalid input. Must be between 1 and %d characters.\n\n" KRST, limit);

        } while (strlen(str) < 1 || strlen(str) > limit);
    }

    /* 
        / Swaps two "Data" variables using pointers.
        - @a: First variable to swap.
        - @b: Second variable to swap.
    */
    void SwapData(Data* a, Data* b) {

        Data temp = *a;
        *a = *b;
        *b = temp;
    }

    /* 
        / Sorts the blocks in the entries by language.
        - @entry: The entry to sort.
    */
    void Intrasort(Entry* entry, int length) {

        //- Don't sort anymore if the length is 1 or less
        if (length <= 1) return;

        //- Sort the blocks by language
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length - 1; j++) {
                if (strcmp(entry->block[j].language, entry->block[j + 1].language) > 0) 
                    SwapData(&entry->block[j], &entry->block[j + 1]);
            }
        }
    }

    /*
        / Swaps two "Entry" variables using pointers.
        - @a: First variable.
        - @b: Second variable.
    */
    void SwapEntries(Entry* a, Entry *b) {

        Entry temp = *a;
        *a = *b;
        *b = temp;
    }

    /* 
        / Sorts the entries in the container by English,
        / and then append the rest to the end.
        - @container: The array of entries to sort.
        - @length: The length of the "Entries[]"" array.
    */
    void Intersort(Entry* Entries, int length) {
        
        //- Don't sort anymore if the length is 1 or less
        if (length <= 1) return;

        //- Declare temporary variables
        Entry Extract[length], Discard[length], Current;
        int ex_len = 0, ds_len = 0;
        bool check = false;

        //- Loop all entries
        for (int i = 0; i < length; i++) {

            //- Store current entry in Current
            Current = Entries[i];
            Intrasort(&Current, Current.length);

            //- Look for an "English" language in the block
            for (int j = 0; j < Current.length; j++) {
                if (strcmp(Current.block[j].language, "english") == 0) {
                    check = true;
                }
            }

            //- Separate entry into Extract and Discard
            if (check) {
                Extract[ex_len++] = Current;
            } else {
                Discard[ds_len++] = Current;
            }

            //- Reset check
            check = false;
        }

        //- Sort the Extract entries by the first language,
        //- then by translation.
        for (int i = 0; i < ex_len; i++) {

            for (int j = 0; j < ex_len - 1; j++) {
                if ((strcmp(Extract[j].block[0].language, Extract[j + 1].block[0].language) > 0) ||
                    (strcmp(Extract[j].block[0].language, Extract[j + 1].block[0].language) == 0 &&
                    strcmp(Extract[j].block[0].translation, Extract[j + 1].block[0].translation) > 0))
                    SwapEntries(&Extract[j], &Extract[j + 1]);
            }
        }

        //- Merge Extract and Discard into the container.
        int i = 0;
        for (; i < ex_len; i++) 
            Entries[i] = Extract[i];
        for (int j = 0; j < ds_len; j++, i++) 
            Entries[i] = Discard[j];
    }

    /*
        / Searches the container for a language-translation
        / pair and returns an array of the matching entries.
        - @container: The container to store everything.
        - @NewData: The language-translation pair to search for.
        - @return: The array of matching entries.
    */
    Container SearchContainer(Container* container, Data NewData) {

        //- Container to store matches
        Container FoundEntries;
        FoundEntries.count = 0;
        bool check = false;

        //- Look for matches
        for (int i = 0; i < container->count; i++, check = false) {
            for (int j = 0; (j < container->base[i].length) && !check; j++) {

                if (strcmp(container->base[i].block[j].translation, NewData.translation) == 0 &&
                    strcmp(container->base[i].block[j].language, NewData.language) == 0) {
                    FoundEntries.base[FoundEntries.count++] = container->base[i];
                    check = true;
                }
            }
        }

        //- Return immediately if no matches were found
        if (FoundEntries.count == 0)
            return FoundEntries;

        //- Sort all entries
        Intersort(FoundEntries.base, FoundEntries.count);
        return FoundEntries;
    }

    /* 
        / Searches the container for a specific language
        / and returns an array of the matching entries.
        - @container: The container to store everything.
        - @language: The language to search for.
        - @return: The array of matching entries.
    */
    Container SearchLanguage(Container* container, String language) {

        //- Container to store matches
        Container FoundEntries;
        FoundEntries.count = 0;

        //- Look for matches
        for (int i = 0; i < container->count; i++) {
            for (int j = 0; j < container->base[i].length; j++) {

                if (strcmp(container->base[i].block[j].language, language) == 0) {
                    FoundEntries.base[FoundEntries.count++] = container->base[i];
                    break;
                }
            }
        }

        //- Return immediately if no matches were found
        if (FoundEntries.count == 0)
            return FoundEntries;

        //- Sort all entries
        Intersort(FoundEntries.base, FoundEntries.count);
        return FoundEntries;
    }

    /* 
        / Prints the contents of an entry.
        - @entry: The entry to print.
        - @length: The length of the entry.
    */
    void PrintEntry(Entry entry, int length) {

        //- Grab the current entry based on the page
        printf(LYEL "\n\tPanel: [Displaying Current Page].\n\n" KRST);

        //- Loop and display all blocks within the entry
        for (int i = 0; i < entry.length; i++) {
            printf("\t[%02d] | %s%s%s: %s\n", i + 1, LYEL,
                Capitalize(entry.block[i].language), KRST, entry.block[i].translation);
            fflush(stdout);
        }
    }

    /* 
        / Check if a block already exists in the entry.
        - @entry: The entry to check.
        - @data: The block to look for.
        - @return "true": if the block exists, "false" if not.
    */
    bool Exists(Entry entry, Data data) {
            
        for (int i = 0; i < entry.length; i++) {
            if (strcmp(entry.block[i].language, data.language) == 0 &&
                strcmp(entry.block[i].translation, data.translation) == 0)
                return true;
        }
        return false;
    }

    /* 
        / Translates input string into a given language.
        - @container: The container to store everything.
    */
    void Translation(Container *container) {

        //- Don't allow if there are no entries
        if (container->count <= 0) {
            printf(LRED "\n\n\tNo entries found in the database." KRST);
            printf(LBLK "\n\tPress [Enter] to return back to Start Menu." KRST);
            getchar();

            StartMenu(container);
            return;
        }
        
        int choice = 0;

        do {
            clrscr();
            printf("\n\n");
            printf(LRED "\tPanel: [Translate Paragraph]\n" KRST);
            printf("\tTranslate a paragraph to a given language.\n\n\n");

            //- Input the initial language
            String language, translation;
            ParseInput(language, KRST "\tEnter the initial language: " LBLU, MAX_CHARS - 1);
            ParseInput(translation, KRST "\tEnter the translation language: " LBLU, MAX_CHARS - 1);

            //- Return all entries with the given language and translation.
            Container Results = SearchLanguage(container, language);
            
            Entry AllWords[MAX_ENTRY];
            int all_length = 0;

            //- Add all entries that correspond to the given language.
            for (int i = 0; i < Results.count; i++) {
                for (int j = 0; j < Results.base[i].length; j++) {

                    if (strcmp(Results.base[i].block[j].language, language) == 0) {
                        AllWords[all_length++] = Results.base[i];
                    }
                }
            }

            if (all_length == 0) {
                printf(LRED "\n\n\tNo entries matching [%s] in the database." KRST, language);
                printf(LBLK "\n\tPress [Enter] to return back to Start Menu." KRST);
                getchar();

                StartMenu(container);
                return;
            }

            //- Prompt for input
            printf(LBLK "\n\tEnter your sentence: \n\t" LBLU);
            char* tokens[MAX_TOKENS], input[MAX_INPUT + 1];
            int length = 0;

            fgets(input, MAX_INPUT, stdin);
            Tokenization(input, tokens, &length, ".,?!");

            bool check = false, check_again = false;
            int entry, index;
            
            //- Translate per word in the array
            printf(KRST "\n\tOutput [%d words]: \n\t" LBLU, length);
            for (int i = 0; i < length; i++, check = false, check_again = false) {

                //- Checks if the current word is in the AllWords array
                for (int j = 0; j < all_length; j++) {
                    for (int k = 0; k < AllWords[j].length; k++) {
                        if (strcmp(tokens[i], AllWords[j].block[k].translation) == 0) {
                            check = true;
                            entry = j;
                        }
                    }
                }

                //- If the word is in the AllWords array, find its translation
                if (check) {
                    for (int i = 0; i < AllWords[entry].length && !check_again; i++) {
                        if (strcmp(translation, AllWords[entry].block[i].language) == 0) {
                            check_again = true;
                            index = i;
                        }
                    }
                }

                //- If the word is in the AllWords array and has a translation, print it
                if (check_again) {
                    printf("%s ", AllWords[entry].block[index].translation);
                } else {
                    printf("%s ", tokens[i]);
                }

                fflush(stdout);
            }

            //- Prompt again
            printf("\n\n");
            printf(LYEL "\n\tTranslation complete.\n" KRST);
            printf(LBLK "\n\tWould you like to translate again?\n" KRST);
            printf("\t[1] Yes [0] No: \n\t[>] " LBLU);

            //- Recursion to loop
            scanf("%d", &choice);
            fflush(stdin);

            printf(KRST);
    
        } while (choice);

        //- Return to main menu
        printf(LBLK "\n\n\tReturning to the main menu.\n" KRST);
        printf(LBLK "\tPress [Enter] to continue.\n" KRST);
        getchar();

        StartMenu(container);
    }