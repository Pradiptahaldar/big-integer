#include <stdio.h>
#include "include/bigint.h"

int main(void) {
    BigInteger *a = bigint_create();
    BigInteger *b = bigint_create();
    BigInteger *result = bigint_create();

    if (a == NULL || b == NULL || result == NULL) {
        printf("Memory allocation failed.\n");

        bigint_free(a);
        bigint_free(b);
        bigint_free(result);

        return 1;
    }

    bigint_from_string(a, "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
    bigint_from_string(b, "888888888888888888888888888888888888888888");

    if (!bigint_add(a, b, result)) {
        printf("Addition failed.\n");

        bigint_free(a);
        bigint_free(b);
        bigint_free(result);

        return 1;
    }

    printf("Result: ");

    for (size_t i = result->size; i > 0; i--) {
        printf("%d", result->digits[i - 1]);
    }

    printf("\n");

    bigint_free(a);
    bigint_free(b);
    bigint_free(result);

    return 0;
}