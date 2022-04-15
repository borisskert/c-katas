/**
 * https://www.codewars.com/kata/555624b601231dc7a400017a/train/c
 * @param n amount of people in a circle
 * @param k every kth person is going to be eliminated until one remains
 * @return the last surviving person
 */
int josephus_survivor(int n, int k) {
    int x = 2;
    int i = 0;

    while (i < n) {
        i = i + 1;

        x = x + k - 1;
        x = x % i + 1;
    }

    return x;
}
