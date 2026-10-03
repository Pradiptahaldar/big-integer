#include "../include/bigint.h"
#include <stdlib.h>
#include<stdio.h>
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
int bigint_add(const BigInteger *a, const BigInteger *b, BigInteger *result) {
    if (a == NULL || b == NULL || result == NULL) {
        return 0;
    }
    if (a->sign != b->sign) {
        return 0;
    }
    size_t max_size = a->size > b->size ? a->size : b->size;
    if (max_size + 1 > result->capacity) {
        size_t new_capacity = result->capacity;
        while (new_capacity < max_size + 1) {
            new_capacity *= 2;
        }
        int *new_digits = realloc(
            result->digits,
            new_capacity * sizeof(int)
        );
        if (new_digits == NULL) {
            return 0;
        }
        result->digits = new_digits;
        result->capacity = new_capacity;
    }
    int carry = 0;
    for (size_t i = 0; i < max_size; i++) {
        int digit_a = i < a->size ? a->digits[i] : 0;
        int digit_b = i < b->size ? b->digits[i] : 0;
        int sum = digit_a + digit_b + carry;
        result->digits[i] = sum % 10;
        carry = sum / 10;
    }
    result->size = max_size;
    if (carry > 0) {
        result->digits[result->size] = carry;
        result->size++;
        }
    result->sign = a->sign;
    return 1;
}
void bigint_print(const BigInteger *num) {
    if (num == NULL) {
        return;
    }
    if (num->sign < 0) {
        printf("-");
    }
    for (size_t i = num->size; i > 0; i--) {
        printf("%d", num->digits[i - 1]);
    }
}
int bigint_read(BigInteger *num) {
    if (num == NULL) {
        return 0;
    }
    size_t capacity = 16;
    size_t length = 0;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char *new_buffer = realloc(buffer, capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }
            buffer = new_buffer;
        }
        buffer[length++] = (char)ch;
    }
    buffer[length] = '\0';
    int success = bigint_from_string(num, buffer);
    free(buffer);
    return success;
}
size_t bigint_digit_count(const BigInteger *num) {
    if (num == NULL) {
        return 0;
    }
    return num->size;
}