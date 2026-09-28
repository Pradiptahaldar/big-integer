#include <stdio.h>
#include "include/bigint.h"

int main(void) {
    BigInteger *num = bigint_create();

    if (num == NULL) {
        printf("Failed to create BigInteger.\n");
        return 1;
    }

    char input[1000];

    printf("Enter a huge integer: ");
    scanf("%999s", input);

    if (!bigint_from_string(num, input)) {
        printf("Invalid number.\n");
        bigint_free(num);
        return 1;
    }

    printf("Stored digits: ");

    for (size_t i = num->size; i > 0; i--) {
        printf("%d", num->digits[i - 1]);
    }

    printf("\n");
    printf("Number of digits: %zu\n", num->size);

    bigint_free(num);

    return 0;
}