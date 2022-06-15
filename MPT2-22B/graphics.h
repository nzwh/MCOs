
    void PrintDivider(char* edge, char* fill, int length, int iter, int nl) {

        for (int i = 0; i < iter; i++) {
            printf("%s", edge);
            for (int i = 0; i < length; i++) 
                printf("%s", fill);
        }

        printf("%s", edge);
        printf(nl ? "\n" : "   ");
    }

    void PrintBoard(int r, int c, intp* Pieces, int p_length) {

        // int pad = 0; // 80/2 - ((int)(41/2));
        // printf("\n\n%*s%s\n", pad, "", top_div);

        PrintDivider(NBMU, NHFT, 3, CLEN, false);
        PrintDivider(NBMU, NHFT, 7, CLEN, true);

        for (int i = 0, ctr = 0; i < r; i++) {

            for (int x = 0; x < 2; x++) {
            for (int j = 0; j < c; j++) {

                printf("%s", NVFT);
                if (ctr < p_length && Pieces[ctr].x == i + 1 && Pieces[ctr].y == j + 1) {

                    if (Pieces[ctr].p == 0) {

                        x ?
                        printf("%s [%d,%d] %s", LBLU, i + 1, j + 1, KRST) :
                        printf("%s A %s", LBLU, KRST);

                    } else if (Pieces[ctr].p == 1) {

                        x ?
                        printf("%s [%d,%d] %s", LMAG, i + 1, j + 1, KRST) :
                        printf("%s B %s", LMAG, KRST);
                    }

                    ctr++;

                } else {

                    x ?
                    printf(" [%d,%d] ", i + 1, j + 1) :
                    (j + 1) % 2 == (i + 1) % 2 ? 
                    printf(" - ") : printf("   ");
                }
            }

            printf("%s   ", NVFT);
            }

            printf("\n");
            if (i + 1 < r) {
                PrintDivider(NALL, NHFT, 3, CLEN, false);
                PrintDivider(NALL, NHFT, 7, CLEN, true);
            }

        }

        PrintDivider(NBMD, NHFT, 3, CLEN, false);
        PrintDivider(NBMD, NHFT, 7, CLEN, true);
}