#include "../include/pradint.h"
#include <stdio.h>

int main(void)
{
    PradInt *number = pradint_create();

    if (number == NULL) {
        printf("Failed to create PradInt.\n");
        return 1;
    }

    printf("Enter a huge integer: ");

    if (!pradint_read(number)) {
        printf("Invalid input.\n");
        pradint_free(number);
        return 1;
    }

    printf("You entered: ");
    pradint_print(number);
    printf("\n");

    printf("Digits: %zu\n", pradint_digit_count(number));

    pradint_free(number);

    return 0;
}