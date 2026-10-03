#include <stdio.h>
#include "include/bigint.h"

int main(void) {
    BigInteger *num = bigint_create();
    if (num == NULL) {
        printf("Failed to create BigInteger.\n");
        return 1;
    }
    printf("Enter a huge integer: ");
    if (!bigint_read(num)) {
        printf("Invalid input.\n");
        bigint_free(num);
        return 1;
    }
    printf("Stored number: ");
    bigint_print(num);
    printf("\n");
    printf("Number of digits: %zu\n", bigint_digit_count(num));
    bigint_free(num);
    return 0;
}