
    void StartMenu() {

        clrscr();
        char* Opts[3] = { "Manage Data", "Translate Menu", "Exit" };
        int focus = CreateMenu("Main Menu", 3, Opts);

        clrscr();
        switch (focus) {
            case 1: ManageData();
                break;
            case 2: Translation();
                break;
            case 3: Exit();
                break;
        }
    }

    void ManageData() {

        clrscr();
        char* Opts[10] = { "Add Entry", "Add Translation", "Delete Entry", "Delete Translation", "Display All Entries", "Search Word", "Search Translation", "Export", "Import", "Back" };
        int focus = CreateMenu("Main Menu", 10, Opts);

        clrscr();
        switch (focus) {
            case 1: AddEntry();
                break;
            case 2: AddTranslation();
                break;
            case 3: DeleteEntry();
                break;
            case 4: DeleteTranslation();
                break;
            case 5: DisplayAllEntries();
                break;
            case 6: SearchWord();
                break;
            case 7: SearchTranslation();
                break;
            case 8: Export();
                break;
            case 9: Import();
                break;
            case 10: StartMenu();
                break;
        }
    }



    /* unfinished areas */

    void AddEntry() {

    }

    void AddTranslation() {

    }

    void DeleteEntry() {

    }

    void DeleteTranslation() {

    }

    void DisplayAllEntries() {

    }

    void SearchWord() {

    }

    void SearchTranslation() {

    }

    void Export() {

    }

    void Import() {

    }

    void Exit() {

    }