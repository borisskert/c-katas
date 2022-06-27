/*
 * https://www.codewars.com/kata/525f50e3b73515a6db000b83/train/c
 */

static char int_to_digit(unsigned char c);

char *create_phone_number(char phone_number[15], const unsigned char nums[10]) {
    phone_number[0] = '(';
    phone_number[1] = int_to_digit(nums[0]);
    phone_number[2] = int_to_digit(nums[1]);
    phone_number[3] = int_to_digit(nums[2]);
    phone_number[4] = ')';
    phone_number[5] = ' ';
    phone_number[6] = int_to_digit(nums[3]);
    phone_number[7] = int_to_digit(nums[4]);
    phone_number[8] = int_to_digit(nums[5]);
    phone_number[9] = '-';
    phone_number[10] = int_to_digit(nums[6]);
    phone_number[11] = int_to_digit(nums[7]);
    phone_number[12] = int_to_digit(nums[8]);
    phone_number[13] = int_to_digit(nums[9]);
    phone_number[14] = '\0';

    return phone_number;
}

static char int_to_digit(unsigned char c) {
    return (char) (c + '0');
}
