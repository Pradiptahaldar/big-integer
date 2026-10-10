#ifndef PRADINT_H
#define PRADINT_H
#include <stddef.h>

typedef struct PradInt PradInt;

PradInt *pradint_create(void);
void pradint_free(PradInt *num);

int pradint_from_string(PradInt *num, const char *str);
int pradint_read(PradInt *num);
void pradint_print(const PradInt *num);

size_t pradint_digit_count(const PradInt *num);

int pradint_add(
    const PradInt *a,
    const PradInt *b,
    PradInt *result
);
int pradint_subtract(
    const PradInt *a,
    const PradInt *b,
    PradInt *result 
);

#endif