
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

        clrscr();
        char *Opts[10] = {"Add Entry", "Add Translation", "Delete Entry", "Delete Translation", "Display All Entries", "Search Word", "Search Translation", "Export", "Import", "Back"};
        int focus = CreateMenu("Main Menu", 10, Opts);

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
        case 5: {
            int page = 1;
            DisplayAllEntries(container, container->base, container->count, &page);
            ManageData(container);
            break;
        }
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
        NewEntry.length = 0; //- Maximum index is (n-1).

        int choice;
        printf("\n\n");

        //- Enter inputs
        Data NewData;
        ParseInput(NewData.language, "\tEnter a Language: ", MAX_CHARS - 1);
        ParseInput(NewData.translation, "\tEnter a Translation: ", MAX_CHARS - 1);

        //- Search for input if it exists
        Container Results = SearchContainer(container, NewData);

        //- Check for validity
        int page = 1;
        if (Results.count <= 0) {
            fprintf(stdout, "\n\t[%s, %s] does not exist yet in the database.\n\n",
                NewData.language, NewData.translation);
        } else {
            DisplayAllEntries(container, Results.base, Results.count, &page);
        }

        printf("\n\n");

        //- Ask to create
        fprintf(stdout, "\tWould you like to create a new entry?  [0] No [1] Yes \n\t[>] ");
        fscanf(stdin, "%d", &choice);
        fflush(stdin);

        //- If yes
        if (choice) {

            //- Add to entry
            strcpy(NewEntry.block[NewEntry.length].language, NewData.language);
            strcpy(NewEntry.block[NewEntry.length].translation, NewData.translation);
            NewEntry.length++;

            //- Ask for more
            do {
                //- Prompt for input
                fprintf(stdout, "\n\tAdd another translation to the entry?  [0] No [1] Yes \n\t[>] ");
                fscanf(stdin, "%d", &choice);
                fflush(stdin);
            
                if (choice) { //- If not, stop looping
                
                    //- Enter inputs
                    printf("\n");
                    ParseInput(NewData.language, "\tEnter Language: ", MAX_CHARS - 1);
                    ParseInput(NewData.translation, "\tEnter Translation: ", MAX_CHARS - 1);

                    //- Add to entry
                    strcpy(NewEntry.block[NewEntry.length].language, NewData.language);
                    strcpy(NewEntry.block[NewEntry.length].translation, NewData.translation);
                    NewEntry.length++;
                }

            } while (NewEntry.length < MAX_DATA && choice);

            if (NewEntry.length == MAX_DATA) {
                printf("\n\tMaximum amount of translations reached.\n");
            }

            //- Append to container
            container->base[container->count] = NewEntry;
            container->count++;
        }

        //- Return to Manage Data
        ManageData(container);
    }

    /* 
        / Add Translation: Add a translation to an existing entry.
        - @container: The container to store everything.
    */
    void AddTranslation(Container *container) {

        int choice = true;

        //- Enter inputs
        Data NewData;
        ParseInput(NewData.language, "Enter Language: ", MAX_CHARS - 1);
        ParseInput(NewData.translation, "Enter Translation: ", MAX_CHARS - 1);

        //- Search for input if it exists
        Container Results = SearchContainer(container, NewData);

        int page = 1;

        //- No translations found
        if (Results.count == 0) {
            fprintf(stdout, "\n\t[%s, %s] does not exist yet in the database. Use the AddEntry command first before using this command.", NewData.language, NewData.translation);
            fprintf(stdout, "\n\tPress [Enter] to return to Manage Data.\n\n");

            ManageData(container);
            return;

        //- Translations found, check for page
        } else {
            DisplayAllEntries(container, Results.base, Results.count, &page);
        }

        //- Look for the entry's original index
        bool check = true;
        for (int i = 0; i < container->count; i++) {

            for (int j = 0; j < container->base[i].length; j++) {

                if (strcmp(container->base[i].block[j].language, 
                    Results.base[page - 1].block[j].language) != 0) {
                    check = false;
                }
            }

            //- Exit once actual entry is found
            if (check) {
                page = i + 1;
            }

            check = true;
        }

        //- If maximum reached, warn user and return to Manage Data
        if (container->base[page - 1].length >= MAX_DATA) {
            printf("\n\n[%s][%s] has too many translations. \nReturning to Manage Data...\n\n",
                NewData.language, NewData.translation);
            return;

        //- If not, ask to add
        } else if (container->base[page - 1].length >= 1) {

            //- Add to current entry
            Entry NewEntry = container->base[page - 1];
            NewEntry.length = container->base[page - 1].length;

            //- Prompt for input
            fprintf(stdout, "\n\n\tYou are now adding a translation to Entry #%d.\n", page);
            while ((NewEntry.length < MAX_DATA) && choice) {
                
                //- Enter inputs
                printf("\n");
                ParseInput(NewData.language, "\tEnter Language: ", MAX_CHARS - 1);
                ParseInput(NewData.translation, "\tEnter Translation: ", MAX_CHARS - 1);

                //- Add to entry
                strcpy(NewEntry.block[NewEntry.length].language, NewData.language);
                strcpy(NewEntry.block[NewEntry.length].translation, NewData.translation);
                NewEntry.length++;

                //- Ask for more
                printf("\n\tAdd another translation to the entry? Type '1' for yes. \n\t[>] ");
                fscanf(stdin, "%d", &choice);
                fflush(stdin);
            } 

            //- Warn user if limit reached
            if (NewEntry.length == MAX_DATA) {
                printf("\n\tMaximum amount of translations reached.\n");
            }

            //- Replace index in container
            container->base[page - 1] = NewEntry;
        }

        ManageData(container);
    }

    /* 
        / Delete Entry: Delete an entry from the database.
        - @container: The container to store everything.
    */
    void DeleteEntry(Container *container) {

        //- Initialize variables
        int page = 1, index = 0;

        //- Loop until valid input is entered
        do {
            clrscr();

            //- Display all entries
            DisplayAllEntries(container, container->base, container->count, &page);

            //- Ask for entry to delete
            fprintf(stdout, "\n\tEnter the page of the entry you wish to delete. \n\tEnter [0] to show the menu again.\n\t[>] ");
            fscanf(stdin, "%d", &index);
            fflush(stdin);

        } while (index == 0);
        index--;

        fflush(stdout);
        //- If index is out of bounds, warn user and return to Manage Data
        if (index >= container->count || index < 0) {

            fprintf(stdout, "\n\tNo entry exists at this page.");
            fprintf(stdout, "\n\tPress [Enter] to return to Manage Data.\n\n");
            getchar();

        //- If index is valid, swap and delete
        } else {

            //- Delete entry
            container->base[index].length = 0;
            container->base[index] = container->base[container->count - 1];
            container->count--;

            //- Warn user if last entry was deleted
            if (container->count == 0) {
                fprintf(stdout, "\n\tLast entry deleted.");
            } else {
                fprintf(stdout, "\n\tEntry [#%d] deleted.", index + 1);
            }

            fprintf(stdout, "\n\tPress [Enter] to return to Manage Data.\n\n");
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

        //- Initialize variables
        int page = 1, index = 0;

        //- Loop until valid input is entered
        do {
            clrscr();

            //- Display all entries
            DisplayAllEntries(container, container->base, container->count, &page);

            //- Ask for the entry to delete
            fprintf(stdout, "\n\tEnter the page of the entry you wish to delete from. \n\tEnter [0] to show the menu again.\n\t[>] ");
            fscanf(stdin, "%d", &index);
            fflush(stdin);

        } while (index == 0);
        index--;

        fflush(stdout);
        //- If index is out of bounds, warn user and return to Manage Data
        if (index >= container->count || index < 0) {

            fprintf(stdout, "\n\tNo entry exists at this page.");
            fprintf(stdout, "\n\tPress [Enter] to return to Manage Data.\n\n");
            getchar();

        //- If index is valid, ask for translation to delete
        } else {

            //- Initialize variables
            Entry NewEntry = container->base[index];
            NewEntry.length = container->base[index].length;

            do {
                clrscr();
                printf("\n\n");

                //- Display all translations
                PrintEntry(NewEntry, NewEntry.length);

                //- Ask for translation to delete
                fprintf(stdout, "\n\tEnter the row of the translation you wish to delete.\n\t[>] ");
                fscanf(stdin, "%d", &index);
                fflush(stdin);
                index--;

                fflush(stdout);
                //- If index is out of bounds, warn user and return to Manage Data
                if (index >= NewEntry.length || index < 0) {
                    
                    //- Warn user if no translations exists
                    fprintf(stdout, "\n\tNo translation exists at this row.");
                    fprintf(stdout, "\n\tPress [Enter] to return to Manage Data.\n\n");
                    getchar();

                } else {

                    //- Delete translation by swapping index
                    NewEntry.block[index] = NewEntry.block[NewEntry.length - 1];
                    NewEntry.length--;

                    //- Warn user if last translation was deleted
                    if (NewEntry.length == 0) {
                        fprintf(stdout, "\n\tLast translation deleted.\n");
                    }

                    //- Re-sort container
                    Intrasort(&NewEntry, index);
                }

            } while (NewEntry.length > 0 && !(index >= NewEntry.length || index < 0));

            if (NewEntry.length == 0) {
                
                //- Delete entry
                container->base[index].length = 0;
                container->base[index] = container->base[container->count - 1];
                container->count--;

                //- Warn user if last entry was deleted
                if (container->count == 0) {
                    fprintf(stdout, "\n\tLast entry deleted.");
                } else {
                    fprintf(stdout, "\n\tNo translations left. Deleting Entry #%d.\n", index + 1);
                }
                
                fprintf(stdout, "\n\tPress [Enter] to return to Manage Data.\n\n");
                getchar();
            }

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

        //- Sort all entries
        Intersort(Entries, length);
        char page_c;

        //- Loop until user exit
        do {
            clrscr();

            //- Grab the current entry based on the page
            Entry CurrentEntry = Entries[(*page) - 1];
            printf("\n\n\tPage %02d of %02d\n\n", *page, length);

            //- Loop and display all blocks within the entry
            for (int i = 0; i < CurrentEntry.length; i++) {
                printf("\t[%02d] [%s: %s]\n", i + 1,
                    CurrentEntry.block[i].language, CurrentEntry.block[i].translation);
                fflush(stdout);
            }

            //- Pagination options
            printf("\n\n\t[N] Next Page [P] Previous Page [X] Exit Search\n\t[>] ");
            page_c = toupper(getchar());
            fflush(stdin);

            //- Change page based on "page_c" input
            switch (page_c) {
                case 'N':
                    if (*page < length)
                        (*page)++;
                    break;
                case 'P':
                    if (*page > 1)
                        (*page)--;
                    break;
            }

        } while (page_c != 'X');
    }

    /*
        / Search Word: Search for a word in the database.
        - @container: The container to store everything.
    */
    void SearchWord(Container *container) {

        //- Enter input
        String translation;
        ParseInput(translation, "Enter Translation: ", MAX_CHARS - 1);
        bool check = false;

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

            printf("\n\n[%s] not found in the database.\n\n", translation);

            //- Return to Manage Data
            ManageData(container);
            return;
        }

        //- Sort all entries
        Intersort(FoundEntries.base, FoundEntries.count);

        //- Display all entries
        int page = 1;
        DisplayAllEntries(container, FoundEntries.base, FoundEntries.count, &page);

        //- Return to Manage Data
        ManageData(container);
    }

    /* 
        / Search Translation: Search for a block in the database.
        - @container: The container to store everything.
    */
    void SearchTranslation(Container *container) {

        //- Enter input
        Data NewData;
        ParseInput(NewData.language, "Enter Language: ", MAX_CHARS - 1);
        ParseInput(NewData.translation, "Enter Translation: ", MAX_CHARS - 1);

        //- Container to store results
        Container FoundEntries = SearchContainer(container, NewData);

        //- Log if there are no results
        if (FoundEntries.count == 0) 
            printf("\n\n[%s, %s] not found in the database.\n\n", NewData.language, NewData.translation);

        //- Display all matching entries
        int page = 1;
        DisplayAllEntries(container, FoundEntries.base, FoundEntries.count, &page);

        //- Return to Manage Data
        ManageData(container);
    }

    /* 
        / Export to input text file.
        - @container: The container to store everything.
    */
    void Export(Container *container) {
        
        //- Input filename
        char filename[MAX_FILE];
        ParseInput(filename, "Enter file name: ", MAX_FILE - 5);
        strcat(filename, ".txt");

        //- Open file
        FILE *file = fopen(filename, "w");
        printf("\n\nExporting to file [%s]...\n\n", filename);

        //- Write to file
        for (int i = 0; i < container->count; i++) {
            for (int j = 0; j < container->base[i].length; j++) {
                fprintf(file, "%s: ", container->base[i].block[j].language);
                fprintf(file, "%s\n", container->base[i].block[j].translation);
            }

            fprintf(file, "\n");
        }

        //- Close file
        fclose(file);

        //- Prompt return to Manage Data
        printf("Export complete. Press [Enter] to return to Manage Data...");
        getchar();

        ManageData(container);
    }

    /* 
        / Import from input text file.
        - @container: The container to store everything.
    */
    void Import(Container *container) {

        printf("\n\n");

        //- Initialize variables
        char line[MAX_LINE];

        //- Input filename
        char filename[30];
        ParseInput(filename, "\tEnter file name: ", 25);

        //- Append .txt if no extension
        if (strcmp(&(filename[strlen(filename) - 4]), ".txt") != 0) 
            strcat(filename, ".txt");
        
        //- Open file
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            fprintf(stdout, "\tFile not found.\n");
            getchar();

            //- Return to Manage Data
            ManageData(container);
            return;
        }

        fprintf(stdout, "\tImporting from file [%s]...\n\n", filename);

        //- Declare new Entry
        Entry NewEntry;
        NewEntry.length = 0;
        int choice = 0, check = true;

        //- Loop until EOF
        while (fgets(line, MAX_LINE, file) != NULL && check) {

            //- If newline, add entry to main
            if (strcmp(line, "\n") == 0 && NewEntry.length > 0) {
                
                PrintEntry(NewEntry, NewEntry.length);
                fprintf(stdout, "\n\tParsing as Entry [#%02d]. ", container->count + 1);
                fprintf(stdout, "Keep the entry? \n\t[1] Yes [0] No\n\t[>] ");

                fscanf(stdin, "%d", &choice);
                fflush(stdin);

                if (choice == 1) {
                    container->base[container->count++] = NewEntry;
                    fprintf(stdout, "\n\tEntry added.\n\n");
                } else {
                    fprintf(stdout, "\n\tEntry discarded.\n\n");
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
                fprintf(stdout, "\n\tMaximum number of entries reached.\n\n");
                check = false;
            }
        }   

        //- Close file
        fclose(file);

        //- Prompt return to Manage Data
        printf("\n\tImporting complete. Press [Enter] to return to Manage Data.\n\n");
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