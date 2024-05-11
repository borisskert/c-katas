/*
 * https://www.codewars.com/kata/55e7280b40e1c4a06d0000aa/train/c
 */

static int go(int max, int k, int list[], int size, int sum, int index);

int chooseBestSum(int t, int k, int ls[], int szls) {
    return go(t, k, ls, szls, 0, 0);
}

int go(int max, int k, int list[], int size, int sum, int index) {
    if (k == 0 && sum <= max) {
        return sum;
    }

    if (sum > max || index >= size) {
        return -1;
    }

    int a = go(max, k - 1, list, size, sum + list[index], index + 1);
    int b = go(max, k, list, size, sum, index + 1);

    if (a == -1) {
        return b;
    }

    if (b == -1) {
        return a;
    }

    return a > b ? a : b;
}
