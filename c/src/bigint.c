#include "../include/bigint.h"
#include <stdlib.h>
BigInteger *bigint_create(void) {
    BigInteger *num = malloc(sizeof(BigInteger));

    if (num == NULL) {
        return NULL;
    }
    num->capacity = 16;
    num->size = 1;
    num->sign = 1;
    num->digits = malloc(num->capacity * sizeof(int));
    if (num->digits == NULL) {
        free(num);
        return NULL;
    }
    num->digits[0] = 0;
    return num;
}
void bigint_free(BigInteger *num) {
    if (num == NULL) {
        return;
    }
    free(num->digits);
    free(num);
}
int bigint_from_string(BigInteger *num, const char *str) {
    if (num == NULL || str == NULL || *str == '\0') {
        return 0;
    }
    size_t start = 0;
    num->sign = 1;
    if (str[0] == '-') {
        num->sign = -1;
        start = 1;
    } else if (str[0] == '+') {
        start = 1;
    }
    size_t length = 0;
    while (str[start + length] != '\0') {
        if (str[start + length] < '0' || str[start + length] > '9') {
            return 0;
        }

        length++;
    }
    if (length == 0) {
        return 0;
    }
    while (length > 1 && str[start] == '0') {
        start++;
        length--;
    }
    if (length > num->capacity) {
        size_t new_capacity = num->capacity;

        while (new_capacity < length) {
            new_capacity *= 2;
        }
        int *new_digits = realloc(
            num->digits,
            new_capacity * sizeof(int)
        );
        if (new_digits == NULL) {
            return 0;
        }
        num->digits = new_digits;
        num->capacity = new_capacity;
    }
    num->size = length;
    for (size_t i = 0; i < length; i++) {
        num->digits[i] = str[start + length - 1 - i] - '0';
    }
    if (num->size == 1 && num->digits[0] == 0) {
        num->sign = 1;
    }
    return 1;
}