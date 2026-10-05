#include <stdio.h>
#include "../include/bigint.h"

int main(void) {
    BigInteger *number = bigint_create();

    if (number == NULL) {
        printf("Failed to create BigInteger.\n");
        return 1;
    }

    printf("Enter a huge integer: ");

    if (!bigint_read(number)) {
        printf("Invalid input.\n");
        bigint_free(number);
        return 1;
    }

    printf("You entered: ");
    bigint_print(number);
    printf("\n");

    printf("Digits: %zu\n", bigint_digit_count(number));

    bigint_free(number);

    return 0;
}