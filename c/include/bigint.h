#ifndef BIGINT_H
#define BIGINT_H
#include <stddef.h>

typedef struct {
    int *digits;
    size_t size;
    size_t capacity;
    int sign;
} BigInteger;
BigInteger *bigint_create(void);
void bigint_free(BigInteger *num);
int bigint_from_string(BigInteger *num, const char *str);
int bigint_add(const BigInteger *a, const BigInteger *b, BigInteger *result);
int bigint_read(BigInteger *num);
void bigint_print(const BigInteger *num);
size_t bigint_digit_count(const BigInteger *num);
#endif