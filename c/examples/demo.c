#include "../include/pradint.h"
#include <stdio.h>

int main(void)
{
    PradInt *a = pradint_create();
    PradInt *b = pradint_create();
    PradInt *result = pradint_create();

    if (a == NULL || b == NULL || result == NULL) {
        printf("Failed to create PradInt.\n");

        pradint_free(a);
        pradint_free(b);
        pradint_free(result);

        return 1;
    }

    printf("Enter first huge integer: ");
    if (!pradint_read(a)) {
        printf("Invalid input.\n");

        pradint_free(a);
        pradint_free(b);
        pradint_free(result);

        return 1;
    }

    printf("Enter second huge integer: ");
    if (!pradint_read(b)) {
        printf("Invalid input.\n");

        pradint_free(a);
        pradint_free(b);
        pradint_free(result);

        return 1;
    }

    printf("\nA: ");
    pradint_print(a);

    printf("\nB: ");
    pradint_print(b);

    if (!pradint_subtract(a, b, result)) {
        printf("\nAddition failed.\n");

        pradint_free(a);
        pradint_free(b);
        pradint_free(result);

        return 1;
    }

    printf("\nA - B: ");
    pradint_print(result);
    printf("\n");

    pradint_free(a);
    pradint_free(b);
    pradint_free(result);

    return 0;
}