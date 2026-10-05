#include "../include/pradint.h"
#include <stdlib.h>
#include <stdio.h>

struct PradInt {
    int *digits;
    size_t size;
    size_t capacity;
    int sign;
};
/* Create a new PradInt initialized to 0 */
PradInt *pradint_create(void)
{    PradInt *num = malloc(sizeof(PradInt));
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
/* Free a PradInt */
void pradint_free(PradInt *num)
{
    if (num == NULL) {
        return;
    }
    free(num->digits);
    free(num);
}

/* Create a PradInt from a string */
int pradint_from_string(PradInt *num, const char *str)
{
    if (num == NULL || str == NULL || *str == '\0') {
        return 0;
    }
    size_t start = 0;
    int sign = 1;
    /* Handle sign */
    if (str[0] == '-') {
        sign = -1;
        start = 1;
    }
    else if (str[0] == '+') {
        start = 1;
    }
    /* Validate digits */
    size_t length = 0;
    while (str[start + length] != '\0') {
        if (str[start + length] < '0' ||
            str[start + length] > '9') {
            return 0;
        }
        length++;
    }
    if (length == 0) {
        return 0;
    }
    /* Remove leading zeros */
    while (length > 1 && str[start] == '0') {
        start++;
        length--;
    }
    /* Increase capacity if necessary */
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
    /* Store digits in reverse order. */
    for (size_t i = 0; i < length; i++) {
        num->digits[i] =
            str[start + length - 1 - i] - '0';
    }
    /* Store sign */
    num->sign = sign;
    /* Normalize negative zero */
    if (num->size == 1 && num->digits[0] == 0) {
        num->sign = 1;
    }
    return 1;
}
/*Compare magnitudes. */
static int compare_magnitude(
    const PradInt *a,
    const PradInt *b
)
{
    if (a->size > b->size) {
        return 1;
    }
    if (a->size < b->size) {
        return -1;
    }
    for (size_t i = a->size; i > 0; i--) {
        if (a->digits[i - 1] > b->digits[i - 1]) {
            return 1;
        }
        if (a->digits[i - 1] < b->digits[i - 1]) {
            return -1;
        }
    }
    return 0;
}
/* Subtract magnitude:*/
static void subtract_magnitude(
    const PradInt *larger,
    const PradInt *smaller,
    PradInt *result
)
{
    int borrow = 0;
    for (size_t i = 0; i < larger->size; i++) {
        int digit_larger = larger->digits[i];
        int digit_smaller =
            i < smaller->size
            ? smaller->digits[i]
            : 0;
        int difference =
            digit_larger - digit_smaller - borrow;
        if (difference < 0) {
            difference += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result->digits[i] = difference;
    }
    result->size = larger->size;
    /* Remove leading zeros */
    while (
        result->size > 1 &&
        result->digits[result->size - 1] == 0
    ) {
        result->size--;
    }
}
/* Add two arbitrary-precision integers. */
int pradint_add(
    const PradInt *a,
    const PradInt *b,
    PradInt *result
)
{
    if (a == NULL || b == NULL || result == NULL) {
        return 0;
    }
    size_t max_size =
        a->size > b->size
        ? a->size
        : b->size;
    /* Make sure result has enough capacity.*/
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
    if (a->sign == b->sign) {
        int carry = 0;
        for (size_t i = 0; i < max_size; i++) {
            int digit_a =
                i < a->size
                ? a->digits[i]
                : 0;
            int digit_b =
                i < b->size
                ? b->digits[i]
                : 0;
            int sum =
                digit_a + digit_b + carry;
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
    int comparison = compare_magnitude(a, b);
    if (comparison == 0) {
        result->digits[0] = 0;
        result->size = 1;
        result->sign = 1;
        return 1;
    }
    if (comparison > 0) {
        subtract_magnitude(
            a,
            b,
            result
        );
        result->sign = a->sign;
    }
    else {
        subtract_magnitude(
            b,
            a,
            result
        );
        result->sign = b->sign;
    }
    return 1;
}

/* Print a PradInt */
void pradint_print(const PradInt *num)
{
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
/* Read a PradInt from user input */
int pradint_read(PradInt *num)
{
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
            char *new_buffer =
                realloc(buffer, capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }
            buffer = new_buffer;
        }
        buffer[length++] = (char)ch;
    }
    buffer[length] = '\0';
    int success =
        pradint_from_string(
            num,
            buffer
        );
    free(buffer);
    return success;}
/* Return number of digits */
size_t pradint_digit_count(const PradInt *num)
{
    if (num == NULL) {
        return 0;
    }

    return num->size;
}