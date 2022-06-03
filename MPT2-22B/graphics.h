
    void PrintBoard(int r, int c, intp* Pieces) {
        
        char* top_div = NBMU NHFT NHFT NHFT NHFT NHFT NHFT NHFT NBMU NHFT NHFT NHFT NHFT NHFT NHFT NHFT NBMU NHFT NHFT NHFT NHFT NHFT NHFT NHFT NBMU NHFT NHFT NHFT NHFT NHFT NHFT NHFT NBMU NHFT NHFT NHFT NHFT NHFT NHFT NHFT NBMU;
        char* mid_div = NBMR NHFT NHFT NHFT NHFT NHFT NHFT NHFT NALL NHFT NHFT NHFT NHFT NHFT NHFT NHFT NALL NHFT NHFT NHFT NHFT NHFT NHFT NHFT NALL NHFT NHFT NHFT NHFT NHFT NHFT NHFT NALL NHFT NHFT NHFT NHFT NHFT NHFT NHFT NBML;
        char* bot_div = NBMD NHFT NHFT NHFT NHFT NHFT NHFT NHFT NBMD NHFT NHFT NHFT NHFT NHFT NHFT NHFT NBMD NHFT NHFT NHFT NHFT NHFT NHFT NHFT NBMD NHFT NHFT NHFT NHFT NHFT NHFT NHFT NBMD NHFT NHFT NHFT NHFT NHFT NHFT NHFT NBMD;
        char* pipe = NVFT;

        int pad = 0; // 80/2 - ((int)(41/2));
        printf("\n\n%*s%s\n", pad, "", top_div);
        for (int i = 0, ctr = 0; i < r; i++) {

            printf("%*s", pad, "");
            printf("%s", pipe);
            for (int j = 0; j < c; j++) {

                if (Pieces[ctr].x == i + 1 && Pieces[ctr].y == j + 1) {

                    if (Pieces[ctr++].p == 0) {
                        printf("%s [%d,%d] %s", LBLU, i + 1, j + 1, KRST);
                    } else {
                        printf("%s [%d,%d] %s", LMAG, i + 1, j + 1, KRST);
                    }

                } else {
                    printf(" [%d,%d] ", i + 1, j + 1);
                }

                printf("%s", pipe);
            }

            if (i + 1 < r) printf("\n%*s%s\n", pad, "", mid_div);
        }

        printf("\n%*s%s\n", pad, "", bot_div);
}