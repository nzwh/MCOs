
    /* 
        / Start: Prints the starting options.
        - @container: The container to store everything.
    */
    void StartMenu(Container *container) {

        clrscr();
        char *Opts[3] = {"Manage Data", "Translation Menu", "Exit"};
        int focus = CreateMenu("Main Menu", 3, Opts);

        clrscr();
        switch (focus) {
            case 1:
                ManageData(container);
                break;
            case 2:
                Translation(container);
                break;
            case 3:
                Exit();
                break;
        }
    }

    /* 
        / Manage Data: Prints the management options.
        - @container: The container to store everything.
    */
    void ManageData(Container *container) {

        int page = 1;

        clrscr();
        char *Opts[10] = {"Add Entry", "Add Translation", "Delete Entry", "Delete Translation", "Display All Entries", "Search Word", "Search Translation", "Export", "Import", "Back"};
        int focus = CreateMenu("Manage Data Menu", 10, Opts);

        clrscr();
        switch (focus) {
        case 1:
            AddEntry(container);
            break;
        case 2:
            AddTranslation(container);
            break;
        case 3:
            DeleteEntry(container);
            break;
        case 4:
            DeleteTranslation(container);
            break;
        case 5: 

            //- Don't allow if there are no entries
            if (container->count <= 0) {
                printf(LRED "\n\n\tNo entries found in the database." KRST);
                printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
                getchar();
            } else {
                DisplayAllEntries(container, container->base, container->count, &page);
            }

            ManageData(container);
            break;
        case 6: 
            SearchWord(container);
            break;
        case 7: 
            SearchTranslation(container);
            break;
        case 8:
            Export(container);
            break;
        case 9:
            Import(container);
            break;
        case 10:
            StartMenu(container);
            break;
        }
    }

    /*
        / Add Entry: Add a new entry to the database.
        - @container: The container to store everything.
    */
    void AddEntry(Container *container) {
        
        //- Define a new entry
        Entry NewEntry;
        NewEntry.length = 0;
        int choice, page = 1;

        printf("\n\n");
        printf(LRED "\tPanel: [Add Entry]\n" KRST);
        printf("\tAdd a new entry to the database.\n\n\n");

        //- Enter inputs
        Data NewData;
        ParseInput(NewData.language, KRST "\tEnter a Language: " LBLU, MAX_CHARS - 1);
        ParseInput(NewData.translation, KRST "\tEnter a Translation: " LBLU, MAX_CHARS - 1);

        //- Search for input if it exists
        Container Results = SearchContainer(container, NewData);

        //- Check for validity
        if (Results.count <= 0) {

            printf(LRED "\n\t[%s, %s] does not exist yet in the database.\n" KRST,
                NewData.language, NewData.translation);

        } else {

            printf(LYEL "\n\tFound matches. \n\tPress [Enter] to open pagination." KRST);
            getchar();

            DisplayAllEntries(container, Results.base, Results.count, &page);
        }

        printf("\n\n");

        //- Ask to create
        printf(LBLK "\tWould you like to create a new entry?  |  [1] Yes [0] No \n\t[>] " LBLU);
        scanf("%d", &choice);
        fflush(stdin);

        printf(KRST);
        if (choice) {

            //- Add to entry
            strcpy(NewEntry.block[NewEntry.length].language, NewData.language);
            strcpy(NewEntry.block[NewEntry.length].translation, NewData.translation);
            NewEntry.length++;

            printf(LBLU "\n\tEntry successfully created.\n\n" KRST);

            do {
                //- Prompt for input
                printf(LBLK "\n\tAdd another translation to the entry?  |  [1] Yes [0] No \n\t[>] " LBLU);
                scanf("%d", &choice);
                fflush(stdin);
            
                if (choice) { //- If not, stop looping

                    printf(LYEL "\n\tYou are now adding translatation [%02d/%02d].\n" KRST, NewEntry.length + 1, MAX_DATA);
                
                    //- Enter inputs
                    ParseInput(NewData.language, "\tEnter Language: ", MAX_CHARS - 1);
                    ParseInput(NewData.translation, "\tEnter Translation: ", MAX_CHARS - 1);

                    if (Exists(NewEntry, NewData)) {

                        printf(LRED "\n\t[%s: %s] already exists in the entry.\n" KRST, Capitalize(NewData.language), NewData.translation);

                    } else {

                        //- Add to entry
                        strcpy(NewEntry.block[NewEntry.length].language, NewData.language);
                        strcpy(NewEntry.block[NewEntry.length].translation, NewData.translation);
                        NewEntry.length++;

                        printf(LBLU "\n\tTranslation successfully added.\n" KRST);
                    }
                }

            } while (NewEntry.length < MAX_DATA && choice);

            if (NewEntry.length == MAX_DATA) {
                printf(LRED "\n\tMaximum amount of translations reached." KRST);
            }

            //- Append to container
            container->base[container->count] = NewEntry;
            container->count++;

            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();
        }

        //- Return to Manage Data
        ManageData(container);
    }

    /* 
        / Add Translation: Add a translation to an existing entry.
        - @container: The container to store everything.
    */
    void AddTranslation(Container *container) {
        
        //- Don't allow if there are no entries
        if (container->count <= 0) {
            printf(LRED "\n\n\tNo entries found in the database." KRST);
            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();

            ManageData(container);
            return;
        }

        int choice = true, page = 1, check = true, out = false;

        printf("\n\n");
        printf(LRED "\tPanel: [Add Translation]\n" KRST);
        printf("\tAdd translations to an existing entry.\n\n\n");

        //- Enter inputs
        Data NewData;
        ParseInput(NewData.language, KRST "\tEnter Language: " LBLU, MAX_CHARS - 1);
        ParseInput(NewData.translation, KRST "\tEnter Translation: " LBLU, MAX_CHARS - 1);

        //- Search for input if it exists
        Container Results = SearchContainer(container, NewData);

        //- No translations found
        if (Results.count == 0) {

            printf(LRED "\n\t[%s, %s] does not exist yet in the database. Use the AddEntry command first before using this command." KRST, NewData.language, NewData.translation);
            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();

            //- Return to Manage Data
            ManageData(container);
            return;

        //- Translations found, check for page
        } else {

            printf(LYEL "\n\tFound matches. \n\tPress [Enter] to open pagination." KRST);
            getchar();

            DisplayAllEntries(container, Results.base, Results.count, &page);
        }

        //- Look for the entry's original index
        for (int i = 0; i < container->count && !out; i++) {
            for (int j = 0; j < container->base[i].length; j++) {
                
                //- If not the same, disregard
                if (strcmp(container->base[i].block[j].language, 
                    Results.base[page - 1].block[j].language) != 0) {
                    check = false;
                }
            }

            //- Exit once actual entry is found
            if (check) {
                page = i + 1;
                out = true;
            }

            check = true;
        }

        //- If maximum reached, warn user and return to Manage Data
        if (container->base[page - 1].length >= MAX_DATA) {

            printf(LRED "\n\t[%s][%s] has too many translations. \n\tPress [Enter] to return to Manage Data.",
                NewData.language, NewData.translation);

            getchar();
            return;

        //- If not, ask to add
        } else {

            //- Add to current entry
            Entry NewEntry = container->base[page - 1];
            NewEntry.length = container->base[page - 1].length;

            while ((NewEntry.length < MAX_DATA) && choice) {

                //- Prompt for input
                printf(LYEL "\n\n\tYou are now adding translatation [%02d/%02d].\n" KRST, NewEntry.length + 1, MAX_DATA);
                
                //- Enter inputs
                ParseInput(NewData.language, KRST "\tEnter Language: " LBLU, MAX_CHARS - 1);
                ParseInput(NewData.translation, KRST "\tEnter Translation: " LBLU, MAX_CHARS - 1);

                if (Exists(NewEntry, NewData)) {

                    printf(LRED "\n\t[%s: %s] already exists in the entry.\n" KRST, Capitalize(NewData.language), NewData.translation);

                } else {

                    //- Add to entry
                    strcpy(NewEntry.block[NewEntry.length].language, NewData.language);
                    strcpy(NewEntry.block[NewEntry.length].translation, NewData.translation);
                    NewEntry.length++;

                    printf(LBLU "\n\tTranslation successfully added.\n" KRST);
                }

                if (NewEntry.length < MAX_DATA) {
                    printf(LBLK "\n\tAdd another translation to the entry?  |  [1] Yes [0] No \n\t[>] " LBLU);
                    scanf("%d", &choice);
                    fflush(stdin);
                }
            } 

            //- Warn user if limit reached
            if (NewEntry.length == MAX_DATA) {
                printf(LRED "\n\tMaximum amount of translations reached." KRST);
            }

            //- Replace index in container
            container->base[page - 1] = NewEntry;

            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();
        }

        ManageData(container);
    }

    /* 
        / Delete Entry: Delete an entry from the database.
        - @container: The container to store everything.
    */
    void DeleteEntry(Container *container) {

        //- Don't allow if there are no entries
        if (container->count <= 0) {
            printf(LRED "\n\n\tNo entries found in the database." KRST);
            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();  

            //- Return to Manage Data
            ManageData(container);
            return;
        }

        //- Initialize variables
        int page = 1, index = 0;

        do {
            clrscr();

            //- Display all entries
            DisplayAllEntries(container, container->base, container->count, &page);

            //- Ask for entry to delete
            printf(LRED "\n\n\tEnter the page of the entry you want to delete.%s \n\tType [0] to show the menu again.\n\t[>] " LBLU, KRST);
            scanf("%d", &index);
            fflush(stdin);

            printf(KRST);
        } while (index == 0);

        fflush(stdout);
        index--;

        //- If index is out of bounds, warn user and return to Manage Data
        if (index >= container->count || index < 0) {

            printf(LRED "\n\tNo entry exists at this page." KRST);
            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();

        //- If index is valid, swap and delete
        } else {

            //- Delete entry
            container->base[index].length = 0;
            container->base[index] = container->base[container->count - 1];
            container->count--;

            //- Warn user if last entry was deleted
            if (container->count == 0) {
                printf(LRED "\n\tLast entry deleted." KRST);
            } else {
                printf(LRED "\n\tEntry [#%d] deleted." KRST, index + 1);
            }

            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();            
            
            //- Re-sort container
            Intersort(container->base, container->count);
        }

        //- Return to Manage Data
        ManageData(container);
    }

    /* 
        / Delete Translation: Delete a translation from an existing entry.
        - @container: The container to store everything.
    */
    void DeleteTranslation(Container *container) {

        //- Don't allow if there are no entries
        if (container->count <= 0) {
            printf(LRED "\n\n\tNo entries found in the database." KRST);
            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();  

            //- Return to Manage Data
            ManageData(container);
            return;
        }

        //- Initialize variables
        int page = 1, index = 0, row = 0;

        //- Loop until valid input is entered
        do {
            clrscr();

            //- Display all entries
            DisplayAllEntries(container, container->base, container->count, &page);

            //- Ask for entry to delete
            printf(LRED "\n\n\tEnter the page of the entry you want to delete.%s \n\tType [0] to show the menu again.\n\t[>] " LBLU, KRST);
            scanf("%d", &index);
            fflush(stdin);

            printf(KRST);
            fflush(stdout);
        } while (index == 0);
        index--;

        //- If index is out of bounds, warn user and return to Manage Data
        if (index >= container->count || index < 0) {

            printf(LRED "\n\tNo entry exists at this page." KRST);
            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();

        //- If index is valid, ask for translation to delete
        } else {

            //- Initialize variables
            Entry NewEntry = container->base[index];
            NewEntry.length = container->base[index].length;

            do {
                clrscr();
                printf(KRST "\n");

                //- Display all translations
                PrintEntry(NewEntry, NewEntry.length);

                //- Ask for translation to delete
                printf(LRED "\n\n\tEnter the row of the translation you wish to delete.%s\n\tType [0] to return to Manage Data.\n\t[>] " LBLU, KRST);
                scanf("%d", &row);
                fflush(stdin);

                printf(KRST);
                row--;

                //- If index is out of bounds, warn user and return to Manage Data
                if (row == -1) {

                    printf(LYEL "\n\tReturning to Manage Data." KRST);
                    printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
                    getchar();
                    
                    //- Return to Manage Data
                    ManageData(container);
                    return;
                
                } else if (row >= NewEntry.length || row < 0) {
                    
                    //- Warn user if no translations exists
                    printf(LRED "\n\tNo translation exists at this row." KRST);
                    printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
                    getchar();

                    //- Return to Manage Data
                    ManageData(container);
                    return;

                } else {

                    //- Delete translation by swapping index
                    NewEntry.block[row] = NewEntry.block[NewEntry.length - 1];
                    NewEntry.length--;

                    //- Warn user if last translation was deleted
                    if (NewEntry.length == 0) {
                        printf(LRED "\n\tLast translation deleted.");
                    } else {
                        printf(LRED "\n\tTranslation [#%d] deleted.", row + 1);
                    }

                    printf(LBLK "\n\tPress [Enter] to continue." KRST);
                    getchar();

                    //- Re-sort container
                    Intrasort(&NewEntry, row);
                }

                container->base[index] = NewEntry;

            } while (NewEntry.length > 0 && !(row > NewEntry.length || row < 0));

            if (NewEntry.length == 0) {
                
                //- Delete entry
                container->base[index].length = 0;
                container->base[index] = container->base[container->count - 1];
                container->count--;

                //- Warn user if last entry was deleted
                if (container->count == 0) {
                    printf(LRED "\n\tLast entry deleted." KRST);
                } else {
                    printf(LRED "\n\tNo translations left. Deleting Entry #%d." KRST, index + 1);
                }
            }

            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar(); 

            //- Re-sort container
            Intersort(container->base, container->count);
        }

        //- Return to Manage Data
        ManageData(container);
    }

    /*
        / Display All Entries: Print all entries in pagination.
        - @container: The container to store everything.
    */
    void DisplayAllEntries(Container* container, Entry* Entries, int length, int* page) {
        
        //- Don't display if no entries
        if (length <= 0) return;
        
        //- Sort all entries
        Intersort(Entries, length);
        char page_c[4];

        //- Loop until user exit
        do {
            clrscr();

            //- Grab the current entry based on the page
            Entry CurrentEntry = Entries[(*page) - 1];
            printf(KRST "\n\n\tPanel: [Displaying Page %s%02d%s of %s%02d%s].\n\n", LYEL, *page, KRST, LYEL, length, KRST);

            //- Loop and display all blocks within the entry
            for (int i = 0; i < CurrentEntry.length; i++) {
                printf("\t[%02d] | %s%s%s: %s\n", i + 1, LYEL,
                    Capitalize(CurrentEntry.block[i].language), KRST, CurrentEntry.block[i].translation);
                fflush(stdout);
            }

            //- Pagination options
            printf("\n\n");
            printf(LBLK "\tType the character below to navigate.\n" LYEL);
            printf(LBLK "\tYou may also type the page number itself.\n\t" LYEL);
            printf(length > 1 ? "[N] Next Page [P] Previous Page " : "");
            printf("[X] Close Pagination%s\n\n\t[>] " LBLU, KRST);

            fgets(page_c, 3, stdin);
            fflush(stdin);

            //- Change page based on "page_c" input
            if (toupper(page_c[0]) == 'N' && *page < length) {
                (*page)++;
            } else if (toupper(page_c[0]) == 'P' && *page > 1) {
                (*page)--;
            } 
            
            int res = strtol(page_c, NULL, 10);
            if (res > 0 && res <= length) {
                (*page) = res;
            }

        } while (toupper(page_c[0]) != 'X');

        printf(KRST);
    }

    /*
        / Search Word: Search for a word in the database.
        - @container: The container to store everything.
    */
    void SearchWord(Container *container) {

        //- Don't allow if there are no entries
        if (container->count <= 0) {
            printf(LRED "\n\n\tNo entries found in the database." KRST);
            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();

            ManageData(container);
            return;
        }

        printf("\n\n");
        printf(LRED "\tPanel: [Search Word]\n" KRST);
        printf("\tLook up a word in the database.\n\n\n");

        //- Enter input
        String translation;
        ParseInput(translation, KRST "\tEnter Translation: " LBLU, MAX_CHARS - 1);

        int check = false;
        printf(KRST);

        //- Container to store translations
        Container FoundEntries;
        FoundEntries.count = 0;

        //- Look for translations
        for (int i = 0; i < container->count; i++, check = false) {
            for (int j = 0; (j < container->base[i].length) && !check; j++) {

                if (strcmp(container->base[i].block[j].translation, translation) == 0) {
                    FoundEntries.base[FoundEntries.count++] = container->base[i];
                    check = true;
                }
            }
        }

        //- Log if there are no results
        if (FoundEntries.count == 0) {

            printf(LRED "\n\t[%s] not found in the database.\n", translation);
            printf(LBLK "\tPress [Enter] to return to Manage Data." KRST);
            getchar();

            //- Return to Manage Data
            ManageData(container);
            return;
        } else {

            printf(LYEL "\n\t[%s] found in the database.\n" KRST, translation);
            printf(LBLK "\tPress [Enter] to continue." KRST);
            getchar();
        }

        //- Sort all entries
        Intersort(FoundEntries.base, FoundEntries.count);

        //- Display all entries
        int page = 1;
        DisplayAllEntries(container, FoundEntries.base, FoundEntries.count, &page);

        printf(LBLK "\n\n\tPress [Enter] to return to Manage Data." KRST);
        getchar();

        //- Return to Manage Data
        ManageData(container);
    }

    /* 
        / Search Translation: Search for a block in the database.
        - @container: The container to store everything.
    */
    void SearchTranslation(Container *container) {

        //- Don't allow if there are no entries
        if (container->count <= 0) {
            printf(LRED "\n\n\tNo entries found in the database." KRST);
            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();

            ManageData(container);
            return;
        }

        printf("\n\n");
        printf(LRED "\tPanel: [Search Translation]\n" KRST);
        printf("\tLook up a translation in the database.\n\n\n");

        //- Enter input
        Data NewData;
        ParseInput(NewData.language, KRST "\tEnter Language: " LBLU, MAX_CHARS - 1);
        ParseInput(NewData.translation, KRST "\tEnter Translation: " LBLU, MAX_CHARS - 1);

        //- Container to store results
        Container FoundEntries = SearchContainer(container, NewData);

        //- Log if there are no results
        if (FoundEntries.count == 0) {

            printf(LRED "\n\tNo matches.\n");
            printf(LBLK "\tPress [Enter] to return to Manage Data." KRST);
            getchar();

            //- Return to Manage Data
            ManageData(container);
            return;
        } else {

            printf(LYEL "\n\tFound matches.\n" KRST);
            printf(LBLK "\tPress [Enter] to continue." KRST);
            getchar();
        }

        //- Display all matching entries
        int page = 1;
        DisplayAllEntries(container, FoundEntries.base, FoundEntries.count, &page);

        printf(LBLK "\n\n\tPress [Enter] to return to Manage Data." KRST);
        getchar();

        //- Return to Manage Data
        ManageData(container);
    }

    /* 
        / Export to input text file.
        - @container: The container to store everything.
    */
    void Export(Container *container) {

        //- Don't allow if there are no entries
        if (container->count <= 0) {
            printf(LRED "\n\n\tNo entries found in the database." KRST);
            printf(LBLK "\n\tPress [Enter] to return to Manage Data." KRST);
            getchar();

            ManageData(container);
            return;
        }

        printf("\n\n");
        printf(LRED "\tPanel: [Export]\n" KRST);
        printf("\tExport the current database onto a text file.\n\n\n");
        
        //- Input filename
        char filename[MAX_FILE];
        ParseInput(filename, KRST "\tEnter file name: " LYEL, MAX_FILE - 5);

        if (strcmp(&(filename[strlen(filename) - 4]), ".txt") != 0) 
            strcat(filename, ".txt");

        //- Open file
        FILE *file = fopen(filename, "w");
        printf(LBLU "\n\n\tExporting to file [%s]...\n" KRST, filename);

        //- Write to file
        for (int i = 0; i < container->count; i++) {
            for (int j = 0; j < container->base[i].length; j++) {
                fprintf(file, "%s: ", Capitalize(container->base[i].block[j].language));
                fprintf(file, "%s\n", container->base[i].block[j].translation);
            }

            fprintf(file, "\n");
        }

        //- Close file
        fclose(file);

        //- Prompt return to Manage Data
        printf("\tPress [Enter] to return to Manage Data.");
        getchar();

        ManageData(container);
    }

    /* 
        / Import from input text file.
        - @container: The container to store everything.
    */
    void Import(Container *container) {

        printf("\n\n");
        printf(LRED "\tPanel: [Import]\n" KRST);
        printf("\tImport entries from a text file.\n\n\n");

        //- Initialize variables
        char line[MAX_LINE];
        char filename[30];
        ParseInput(filename, KRST "\tEnter file name: " LBLU, MAX_FILE - 5);

        //- Append .txt if no extension
        if (strcmp(&(filename[strlen(filename) - 4]), ".txt") != 0) 
            strcat(filename, ".txt");
        
        //- Open file
        FILE *file = fopen(filename, "r");
        if (file == NULL) {

            printf(LRED "\n\n\tFile not found." KRST); 
            printf(LBLK "\n\tPress [Enter] to return to Manage Data.\n" KRST);
            getchar();

            //- Return to Manage Data
            ManageData(container);
            return;
        }

        printf(LBLU "\tImporting from file [%s]...\n\n" KRST, filename);

        //- Declare new Entry
        Entry NewEntry;
        NewEntry.length = 0;
        int choice = 0, check = true;

        //- Loop until EOF
        while (fgets(line, MAX_LINE, file) != NULL && check) {

            //- If newline, add entry to main
            if (strcmp(line, "\n") == 0 && NewEntry.length > 0) {
                
                PrintEntry(NewEntry, NewEntry.length);
                printf(LBLU "\n\tParsing as Entry [#%02d]. " KRST, container->count + 1);
                printf("Keep the entry? \n\t[1] Yes [0] No%s\n\t[>] " LBLU, KRST);

                fscanf(stdin, "%d", &choice);
                fflush(stdin);
                printf(KRST);

                if (choice == 1) {
                    container->base[container->count++] = NewEntry;
                    printf(LBLU "\n\tEntry added.\n\n" KRST);
                } else {
                    printf(LRED "\n\tEntry discarded.\n\n" KRST);
                }

                NewEntry.length = 0;

            //- Otherwise, add to current entry
            } else {

                int length = 0;
                char *temp = strdup(line), *tokens[2];
                Tokenization(temp, tokens, &length, ":");

                strcpy(NewEntry.block[NewEntry.length].language, tokens[0]);
                strcpy(NewEntry.block[NewEntry.length].translation, tokens[1]);
                NewEntry.length++;
            }

            if (container->count == MAX_ENTRY) {
                printf(LRED "\n\tMaximum amount of translations reached." KRST);
                check = false;
            }
        }   

        //- Close file
        fclose(file);

        //- Prompt return to Manage Data
        printf(LBLU "\n\tImporting complete." KRST);
        printf(LBLK "\n\tPress [Enter] to return to Manage Data.\n\n" KRST);
        getchar();

        //- Sort all entries
        Intersort(container->base, container->count);

        //- Return to Manage Data
        ManageData(container);
    }

    /* 
        / Exit Program.
    */
    void Exit() {
        clrscr();
    }