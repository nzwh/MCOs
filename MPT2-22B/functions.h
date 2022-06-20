    
    /*  
        * Swaps two "intp" coordinates using pointers.
        @param a - The initial coordinate.
        @param b - The coordinate to swap with.
    */
    void Swap(intp* a, intp* b) {

        intp temp = *a;
        *a = *b;
        *b = temp;
    }

    /*  
        * Sorts an "intp" array of coordinates by ascending value.
        * Sorts by x-value first, then y-value.
        @param Main - The array of coordinates to sort with.
        @param length - The current length of the array.
    */
    void PairSort(intp* Main, int length) {

        for (int i = 0; i < length; i++) {
            for (int j = i + 1; j < length; j++) {

                if (Main[i].x > Main[j].x) 
                    Swap(&Main[i], &Main[j]);
                if (Main[i].x == Main[j].x && Main[i].y > Main[j].y) 
                    Swap(&Main[i], &Main[j]);
            }
        }
    }

    /*  
        * Function that merges two "intp" arrays into one merged
        * "intp" array. Values are stored in the "Merge" array.
        @param Alpha - The first array to merge with.
        @param Beta - The second array to merge with.
        @param Merge - The array to store the merged array in.
        @param base - The base struct to get the length of the arrays.
    */
    void MergeFill(intp* Alpha, intp* Beta, intp* Merge, ints* base) {

        base->m_length = base->a_length + base->b_length;
        for (int i = 0; i < base->a_length; i++) {
            Merge[i].x = Alpha[i].x;
            Merge[i].y = Alpha[i].y;
            Merge[i].p = 0;
        }

        for (int i = 0; i < base->b_length; i++) {
            Merge[i + base->a_length].x = Beta[i].x;
            Merge[i + base->a_length].y = Beta[i].y;
            Merge[i + base->a_length].p = 1;
        }

        PairSort(Merge, base->m_length);
    }

    /*  
        * Function that copies the elements of an "intp" array 
        * to another "intp" array of the same length.
        @param Main - The array to store the copied values.
        @param Source - The array to duplicate the values from.
        @param length - The current length of both of the arrays.
        @param base - The base struct to get the length of the arrays.
    */
    void SingleFill(intp* Main, intp* Source, int length) {

        for (int i = 0; i < length; i++) {
            Main[i].x = Source[i].x;
            Main[i].y = Source[i].y;
        }
    }

    /*  
        * Function that determines if a given "intp" coordinate is an 
        * element of a given "intp" array of coordinates.
        @param Pair - The coordinate to check if it is in the array.
        @param Array - The array to check if the coordinate is in.
        @param length - The current length of the array.
        @return "true" if the pair is in the array, "false" if not.
    */
    bool Contains(intp Pair, intp* Array, int length) {

        for (int i = 0; i < length; i++) {
            if (Array[i].x == Pair.x && Array[i].y == Pair.y) 
                return true;
        }

        return false;
    }

    /*  
        * Function that updates the "Free" array on command by removing
        * the "Alpha" or "Beta" array from the entire set of coordinates.
        @param Alpha - The first array to ignore values from.
        @param Beta - The second array to ignore values from.
        @param Free - The array to store the remaining values in.
        @param base - The base struct to get the length of the arrays.
    */
    void UpdateFree(intp* Alpha, intp* Beta, intp* Free, ints* base) {

        int j = 0;
        for (int i = 0; i < base->p_length; i++) {
            if (Contains(base->arr_p[i], Alpha, base->a_length)) continue;
            if (Contains(base->arr_p[i], Beta, base->b_length)) continue;
                Free[j] = base->arr_p[i];
                j++;
        }

        base->f_length = j;
    }

    /*  
        * Function that appends an "intp" coordinate to the
        * end of the given "intp" array.
        @param Pair - The coordinate to add to the array.
        @param Array - The array to add the coordinate to.
        @param length - The current length of the array.
        @param limit - The maximum limit of the array.
    */
    void Add(intp Pair, intp* Array, int* length, int limit) {

        if (*length < limit) {
            Array[*length] = Pair;
            (*length)++;
        }
    }

    /*  
        * Function that removes an "intp" coordinate from the given array
        * by swapping it with the last element of the array, and then
        * decrementing the length of the array.
        @param Pair - The coordinate to remove from the array.
        @param Array - The array to remove the coordinates from.
        @param length - The current length of the array.
        @param limit - The maximum limit of the array.
    */
    void Remove(intp Pair, intp* Array, int* length) {
        
        if (length <= 0) return;
        for (int i = 0; i < *length; i++) {
            if (Array[i].x == Pair.x && Array[i].y == Pair.y) {

                Swap(&Array[i], &Array[(*length) - 1]);
                (*length)--;
                return;
            }
        }
    }

    /*  
        * Function that determines the current player move based on
        * two inputs: "prev" and "next". It updates Alpha/Beta/Free
        * arrays given the case scenario.
        @param prev - The current coordinate.
        @param next - The coordinate to go to.
        @param Alpha/Beta/Free - The arrays to modify the values in.
        @param base - The base struct that contains the arrays and their lengths.
        @param aTurn - Determines which Player's turn it is.
        @param ok - Determines if the entered move is valid.
    */
    void NextPlayerMove(intp prev, intp next, intp* Alpha, intp* Beta, intp* Free, ints* base, bool* aTurn, bool* ok) {
        
        // Separate the coordinates into variables
        int a = prev.x, b = prev.y;
        int c = next.x, d = next.y;
        printf("\n");

        //  * 03: Alpha moves to a free tile.
        if (*ok && *aTurn && Contains(next, Free, base->f_length)) {

            if (Contains(prev, Alpha, base->a_length))
                Remove(prev, Alpha, &base->a_length);
            Add(next, Alpha, &base->a_length, base->p_length);

            *ok = !ok;
            *aTurn = !*aTurn;
            printf(!(*aTurn) ? LBLU : LMAG);
            printf("\tMoved tile [%d, %d] to tile [%d, %d].\n" KRST, a, b, c, d);
        }

        //  * 04: Beta moves to a free tile.
        if (*ok && !*aTurn && Contains(next, Free, base->f_length)) {

            if (Contains(prev, Beta, base->b_length)) 
                Remove(prev, Beta, &base->b_length);
            Add(next, Beta, &base->b_length, base->p_length);

            *ok = !ok;
            *aTurn = !*aTurn;
            printf(!(*aTurn) ? LBLU : LMAG);
            printf("\tMoved tile [%d, %d] to tile [%d, %d].\n" KRST, a, b, c, d);
        }

        //  * 05: Alpha cannot eat since it is not on a white tile.
        if (*ok && *aTurn && Contains(next, Beta, base->b_length) && 
            !(next.x % 2 == next.y % 2)) {  // Set S checking

            printf(KRED "\tYou cannot eat since it is not on a white tile.\n" KRST);
        }

        //  * 06: Alpha moves to a tile occupied by Beta.
        if (*ok && *aTurn && Contains(next, Beta, base->b_length) && 
            (next.x % 2 == next.y % 2)) {  // Set S checking

            Remove(next, Beta, &base->b_length);
            if (Contains(prev, Alpha, base->a_length))
                Remove(prev, Alpha, &base->a_length);
            if (!Contains(next, Alpha, base->a_length))
                Add(next, Alpha, &base->a_length, base->p_length);

            *ok = !ok;
            *aTurn = !*aTurn;
            printf(KYEL "\tBeta's tile in [%d, %d] has been eaten.\n" KRST, c, d);
        }

        //  * 07: Beta cannot eat since it is not on a white tile
        if (*ok && !*aTurn && Contains(next, Alpha, base->a_length) && 
            !(next.x % 2 == next.y % 2)) {  // Set S checking

            *ok = !ok;
            printf(KRED "\tYou cannot eat since it is not on a white tile.\n" KRST);
        }

        //  * 08: Beta moves to a tile occupied by Alpha.
        if (*ok && !*aTurn && Contains(next, Alpha, base->a_length) && 
            (next.x % 2 == next.y % 2)) {  // Set S checking

            Remove(next, Alpha, &base->a_length);
            if (Contains(prev, Beta, base->b_length))
                Remove(prev, Beta, &base->b_length);
            if (!Contains(next, Beta, base->b_length))
                Add(next, Beta, &base->b_length, base->p_length);

            *ok = !ok;
            *aTurn = !*aTurn;
            printf(KYEL "\tAlpha's tile in [%d, %d] has been eaten.\n" KRST, c, d);
        }

        // Cleanup
        fflush(stdin);
        printf(LBLK "\t< Press [Enter] to continue >" KRST);
        getchar();
    }

    /*  
        * Function that determines if an "intp" array is a subset,
        * or has the elements of another "intp" array.
        @param Main - The array to check.
        @param Compare - The array to check against.
        @param m_len/clen - The current length of both of the arrays.
        @return "true" if the array is a subset, "false" if not.
    */
    bool Subset(intp* Main, intp* Compare, int m_len, int c_len) {

        for (int i = 0; i < m_len; i++) {
            if (!Contains(Main[i], Compare, c_len))
                return false;
        }

        return true;
    }

    /*  
        * Function that determines if all elements of an 
        * "intp" array are in the same, given row (x-value).
        @param Array - The array to check.
        @param length - The current length of the array.
        @param row - The row (x-value) to look for.
        @return "true" if all elements are in the row, "false" if not.
    */
    bool FullRow(intp* Array, int length, int row) {
            
        for (int i = 0; i < length; i++) {
            if (Array[i].x != row)
                return false;
        }

        return true;
    }

    /*  
        * Function that checks if at least one element of an "intp"
        * array is in the specified row (x-value), and if they're 
        * not in the Set S.
        @param Main - The array to check.
        @param length - The current length of the array.
        @param row - The row (x-value) to look for.
        @return "true" if one or more element is in the specified row, "false" if not.
    */
    bool CheckSide(intp* Main, int length, int row) {
        
        for (int i = 0; i < length; i++) {
            if (Main[i].x == row && (Main[i].x % 2 != Main[i].y % 2)) 
                return true;
        }

        return false;
    }

    /*  
        * Function that checks if the game is over or not
        * after each iteration. Once true, it determines who wins
        * the game by returning the winner as a character.
        @param over - The boolean that determines if the round is over.
        @param Alpha - The array of Alpha's coordinates.
        @param Beta - The array of Beta's coordinates.
        @param base - The base struct that contains the arrays and their lengths.
        @return "char", The character of the winner.
    */
    char GameOver(bool* over, intp* Alpha, intp* Beta, ints base) {
        
        // Alpha win condition
        if (base.b_length == 0 || 
            Subset(Alpha, base.arr_y, base.a_length, base.y_length)) {

            *over = true;
            return 'A';

        // Beta win condition
        } else if (base.a_length == 0 || 
            Subset(Beta, base.arr_e, base.b_length, base.e_length)) {
            
            *over = true;
            return 'B';

        // If one player's pieces are all in the opposite row
        if (FullRow(Beta, base.b_length, RLEN) || 
            FullRow(Alpha, base.a_length, 1)) {

            *over = true;
            return 'T';
        }

        // If both players have one piece in the opposite row, 
        // and both pieces are not in the set S
        if (CheckSide(Alpha, base.a_length, 1) && 
            CheckSide(Beta, base.b_length, RLEN)) {

            *over = true;
            return 'T';
        }

        // No one wins, continue the game
        } else {
            return '/';
        }
    }