    
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

        //  * Conditional 01
        if (*aTurn && Contains(prev, Alpha, base->a_length) &&
            a == c + 1 && (d == b || d == b + 1 || d + 1 == b)) {

            *ok = !*ok;
        }

        //  * Conditional 02
        if (!*aTurn && Contains(prev, Beta, base->b_length) &&
            c == a + 1 && (d == b || d == b + 1 || d + 1 == b)) {

            *ok = !*ok;
        }

        //  * Conditional 03
        if (*ok && *aTurn && Contains(next, Free, base->f_length)) {

            if (Contains(prev, Alpha, base->a_length))
                Remove(prev, Alpha, &base->a_length, base->p_length);
            Add(next, Alpha, &base->a_length, base->p_length);
            *aTurn = !*aTurn;
            *ok = !*ok;
        }

        //  * Conditional 04
        if (*ok && !*aTurn && Contains(next, Free, base->f_length)) {

            if (Contains(prev, Beta, base->b_length)) 
                Remove(prev, Beta, &base->b_length, base->p_length);
            Add(next, Beta, &base->b_length, base->p_length);
            *aTurn = !*aTurn;
            *ok = !*ok;
        }

        //  * Conditional 05
        if (*ok && *aTurn && Contains(next, Beta, base->b_length) && 
            !Contains(next, base->arr_s, base->s_length)) {

            *ok = !*ok;
        }

        //  * Conditional 06
        if (*ok && *aTurn && Contains(next, Beta, base->b_length) && 
            Contains(next, base->arr_s, base->s_length)) {

            Remove(next, Beta, &base->b_length, base->p_length);
            if (Contains(prev, Alpha, base->a_length))
                Remove(prev, Alpha, &base->a_length, base->p_length);
            if (!Contains(next, Alpha, base->a_length))
                Add(next, Alpha, &base->a_length, base->p_length);
            *aTurn = !*aTurn;
            *ok = !*ok;
        }

        //  * Conditional 07
        if (*ok && !*aTurn && Contains(next, Alpha, base->a_length) && 
            !Contains(next, base->arr_s, base->s_length)) {

            *ok = !*ok;
        }

        //  * Conditional 08
        if (*ok && !*aTurn && Contains(next, Alpha, base->a_length) && 
            Contains(next, base->arr_s, base->s_length)) {

            Remove(next, Alpha, &base->a_length, base->p_length);
            if (Contains(prev, Beta, base->b_length))
                Remove(prev, Beta, &base->b_length, base->p_length);
            if (!Contains(next, Beta, base->b_length))
                Add(next, Beta, &base->b_length, base->p_length);
            *aTurn = !*aTurn;
            *ok = !*ok;
        }
    }

    bool Subset(intp* x, intp* y, int x_len, int y_len) {

        // for (int i = 0; i < x_len; i++) {
        // for (int j = 0; j < y_len; j++) {

        //     if (x[i].x == y[j].x && x[i].y == y[j].y)
        //         break;
        //     if (j == y_len)
        //         return false;
        // }};

        // return true;

        return false;
    }

    char GameOver(bool* over, intp* Alpha, intp* Beta, ints base) {

        if ((base.a_length > 0 && base.b_length > 0)
        && !Subset(Alpha, base.arr_y, base.a_length, base.y_length)
        && !Subset(Beta, base.arr_e, base.b_length, base.e_length))
            return '/';
        
        *over = true;
        char result;

        if (base.b_length == 0 || Subset(Alpha, base.arr_y, base.a_length, base.y_length)) {
            result = 'A';
        } else if (base.a_length == 0 || Subset(Beta, base.arr_e, base.b_length, base.e_length)) {
            result = 'B';
        }
        return result;
    }

    void Freer(intp* Alpha, intp* Beta, intp* Free, ints* base) {
        
        free(Alpha);
        free(Beta);
        free(Free);

        free(base->arr_r);
        free(base->arr_c);
        free(base->arr_p);
        free(base->arr_s);
        free(base->arr_y);
        free(base->arr_e);
    }

