    
    void Swap(intp* a, intp* b) {
        intp temp = *a;
        *a = *b;
        *b = temp;
    }

    void PairSort(intp* Array, int length) {

        intp temp;
        for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {

            if (Array[i].x > Array[j].x) 
                Swap(&Array[i], &Array[j]);
            if (Array[i].x == Array[j].x && Array[i].y > Array[j].y) 
                Swap(&Array[i], &Array[j]);
        }};
    }

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

    void SingleFill(intp* Main, intp* Source, int Len, ints* base) {
        for (int i = 0; i < Len; i++) {
            Main[i].x = Source[i].x;
            Main[i].y = Source[i].y;
        }
    }

    bool Contains(intp target, intp* arr, int len) {

        for (int i = 0; i < len; i++)
        if (arr[i].x == target.x && arr[i].y == target.y)
            return true;
        return false;
    }

    void UpdateFree(intp* Alpha, intp* Beta, intp* Free, ints* base) {

        int j = 0;
        for(int i = 0; i < base->p_length; i++) {
        if (Contains(base->arr_p[i], Alpha, base->a_length)) continue;
        if (Contains(base->arr_p[i], Beta, base->b_length)) continue;
            Free[j] = base->arr_p[i];
            j++;
        }

        base->f_length = j;
    }

    void Add(intp target, intp* arr, int* len, int limit) {

        if (*len < limit) {
            arr[*len] = target;
            *len += 1;
        }
    }

    void Remove(intp target, intp* arr, int* len, int limit) {
        
        for (int i = 0; i < *len; i++) {
            if (arr[i].x == target.x && arr[i].y == target.y) {

                intp temp = arr[i];
                arr[i] = arr[*len - 1];
                arr[*len - 1] = temp;

                *len -= 1;
                return;
            }
        }
    }

    void PrintInline(intp* arr, int len, char* name) {
        
        printf("%s", name);
        for (int i = 0; i < len; i++) {
            printf("[%d, %d] ", arr[i].x, arr[i].y);
            fflush(stdout);
        }
        printf("\n");
    }

    void NextPlayerMove(intp prev, intp next, intp* Alpha, intp* Beta, intp* Free, ints* base, bool* aTurn, bool* ok) {

        int a = prev.x, b = prev.y;
        int c = next.x, d = next.y;

        *ok = !*ok;

        //  * 03: Player A moves to a free tile.
        if (*ok && *aTurn && Contains(next, Free, base->f_length)) {

            if (Contains(prev, Alpha, base->a_length))
                Remove(prev, Alpha, &base->a_length, base->p_length);
            Add(next, Alpha, &base->a_length, base->p_length);
            *aTurn = !*aTurn;
            *ok = !*ok;
        }

        //  * 04: Player B moves to a free tile.
        if (*ok && !*aTurn && Contains(next, Free, base->f_length)) {

            if (Contains(prev, Beta, base->b_length)) 
                Remove(prev, Beta, &base->b_length, base->p_length);
            Add(next, Beta, &base->b_length, base->p_length);
            *aTurn = !*aTurn;
            *ok = !*ok;
        }

        //  * 05: Player A cannot eat since it is not on a white tile.
        if (*ok && *aTurn && Contains(next, Beta, base->b_length) && 
            !Contains(next, base->arr_s, base->s_length)) {

            *ok = !*ok;
            printf(KRED "You cannot eat since it is not on a white tile.\n" KRST);
        }

        //  * 06: Player A moves to a tile occupied by Player B.
        if (*ok && *aTurn && Contains(next, Beta, base->b_length) && 
            Contains(next, base->arr_s, base->s_length)) {

            Remove(next, Beta, &base->b_length, base->p_length);
            if (Contains(prev, Alpha, base->a_length))
                Remove(prev, Alpha, &base->a_length, base->p_length);
            if (!Contains(next, Alpha, base->a_length))
                Add(next, Alpha, &base->a_length, base->p_length);

            *aTurn = !*aTurn;
            *ok = !*ok;
            printf(KYEL "Player B's tile in [%d, %d] has been eaten.\n" KRST, c, d);
        }

        //  * 07: Player B cannot eat since it is not on a white tile
        if (*ok && !*aTurn && Contains(next, Alpha, base->a_length) && 
            !Contains(next, base->arr_s, base->s_length)) {

            *ok = !*ok;
            printf(KRED "You cannot eat since it is not on a white tile.\n" KRST);
        }

        //  * 08: Player B moves to a tile occupied by Player A.
        if (*ok && !*aTurn && Contains(next, Alpha, base->a_length) && 
            Contains(next, base->arr_s, base->s_length)) {

            Remove(next, Alpha, &base->a_length, base->p_length);
            if (Contains(prev, Beta, base->b_length))
                Remove(prev, Beta, &base->b_length, base->p_length);
            if (!Contains(next, Beta, base->b_length))
                Add(next, Beta, &base->b_length, base->p_length);

            *aTurn = !*aTurn;
            *ok = !*ok;
            printf(KYEL "Player A's tile in [%d, %d] has been eaten.\n" KRST, c, d);
        }

        fflush(stdin);
        getchar();
    }

    bool Subset(intp* Main, intp* Compare, int x_len, int y_len) {

        for (int i = 0; i < x_len; i++) {
            if (!Contains(Main[i], Compare, y_len))
                return false;
        }
        return true;
    }

    bool FullRow(intp* Main, int len, int row) {
            
        for (int i = 0; i < len; i++) {
            if (Main[i].x != row)
                return false;
        }
        return true;
    }

    bool CheckSide(intp* Main, int len, int side) {

        for (int i = 0; i < len; i++) {
            if (Main[i].x == side) 
                return true;
        }
        return false;
    }

    char GameOver(bool* over, intp* Alpha, intp* Beta, ints base) {

        if (FullRow(Beta, base.b_length, RLEN) || 
            FullRow(Alpha, base.a_length, 1)) {

            *over = true;
            return 'T';
        }

        if (CheckSide(Alpha, base.a_length, 1) && 
            CheckSide(Beta, base.b_length, RLEN)) {

            *over = true;
            return 'T';
        }

        if (base.b_length == 0 || 
            Subset(Alpha, base.arr_y, base.a_length, base.y_length)) {

            *over = true;
            return 'A';

        } else if (base.a_length == 0 || 
            Subset(Beta, base.arr_e, base.b_length, base.e_length)) {
            
            *over = true;
            return 'B';

        } else {
            return '/';
        }

    }
