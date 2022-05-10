/**
 * https://www.codewars.com/kata/51e04f6b544cf3f6550000c1/train/c
 * @return number of complete beeramid levels
 */
int beeramid(double bonus, double price) {
    int amount = (int) (bonus / price);

    int level = 0;
    int sum = 0;

    do {
        level += 1;
        sum += level * level;
    } while (sum <= amount);

    return level - 1;
}
