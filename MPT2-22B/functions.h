    
    bool Contains(intp* arr, int len, intp target) {

        for (int i = 0; i < len; i++)
        if (arr[i].x == target.x && arr[i].y == target.y)
            return true;
        return false;
    }

    void UpdateFree(intp* Alpha, intp* Beta, intp* Free, ints base) {

        for(int i = 0, j = 0; i < base.p_length; i++) {
        if (Contains(Alpha, base.e_length, base.arr_p[i])) continue;
        if (Contains(Beta, base.y_length, base.arr_p[i])) continue;
            Free[j] = base.arr_p[i];
            j++;
        }
    }

