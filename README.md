# Big Integer Library in C

A custom arbitrary-precision integer library implemented in **C**, designed to handle integers far beyond the limits of C's built-in integer data types.

## Project Overview

C provides fixed-size integer types such as:

* `int`
* `long`
* `long long`

These types have finite ranges. When a value exceeds the supported range, integer overflow can occur.

Python, on the other hand, provides arbitrary-precision integers through its built-in `int` type.

This project aims to explore how arbitrary-precision integers can be implemented in C by creating our own **Big Integer library** using dynamic memory and digit-based representation.

The project will allow a C programmer to work with integers containing far more digits than can be represented by standard C integer types.

---

## Main Objectives

1. Implement a Big Integer data type in C.
2. Store integers dynamically without relying on fixed-size C integer types.
3. Accept extremely large integer input.
4. Preserve every digit of the input without overflow or loss of precision.
5. Provide a reusable C API that other programs can use.
6. Implement arithmetic operations for Big Integers.
7. Test the implementation using very large inputs.
8. Compare the implementation with Python's arbitrary-precision integer support.
9. Develop an additional implementation/feature of our own as part of the project.

---

## Core Concept

Instead of storing a huge integer inside a normal C variable, the number is represented using dynamically allocated memory.

For example:

```text
12345678901234567890
```

can internally be represented as individual decimal digits:

```text
[0, 9, 8, 7, 6, 5, 4, 3, 2, 1]
```

The digits are stored in reverse order so that arithmetic operations can process the least significant digit first.

The amount of memory allocated can grow when the number becomes larger.

---

## Current Big Integer Structure

The project currently uses a structure conceptually containing:

```c
typedef struct {
    int *digits;
    size_t size;
    size_t capacity;
    int sign;
} BigInteger;
```

### Fields

| Field      | Purpose                                           |
| ---------- | ------------------------------------------------- |
| `digits`   | Dynamically allocated array containing the digits |
| `size`     | Number of digits currently used                   |
| `capacity` | Allocated capacity of the digit array             |
| `sign`     | Represents positive or negative values            |

---

## Reusable Library

The project is being designed as a **reusable C library**, rather than only as a standalone calculator.

The intended usage will be:

```c
#include "bigint.h"

int main(void) {
    BigInteger *number = bigint_create();

    bigint_read(number);
    bigint_print(number);

    bigint_free(number);

    return 0;
}
```

The user program should interact with the Big Integer implementation through a public API while the internal representation remains inside the library implementation.

---

## Planned Public API

The library will provide functions such as:

```c
BigInteger *bigint_create(void);

void bigint_free(BigInteger *num);

int bigint_read(BigInteger *num);

void bigint_print(const BigInteger *num);

size_t bigint_digit_count(const BigInteger *num);
```

Additional arithmetic functions will be added as development progresses.

---

## Planned Arithmetic Operations

The project is planned to support:

* Addition
* Subtraction
* Multiplication
* Division
* Comparison
* Sign handling
* Other useful Big Integer operations where appropriate

Each operation will be implemented without converting the entire number into a standard C integer type.

---

## Large Integer Input

The library is designed to accept numbers whose length is not restricted by the range of `int`, `long`, or `long long`.

The input mechanism uses dynamically growing memory instead of a fixed-size input buffer.

For example, the implementation can already accept and reproduce numbers such as:

```text
12345678901234567890123456789012345678901234567890
```

without converting the number into a built-in C integer.

---

## Current Testing

The current implementation has successfully demonstrated:

* Big Integer object creation
* Dynamic memory allocation
* Large integer input
* Exact storage of individual digits
* Exact printing of the stored number
* 50-digit input testing
* 100-digit input testing

Further large-scale tests will be added during development.

---

## C vs Python

A major part of the project is understanding the difference between fixed-width integer handling in C and arbitrary-precision integer handling in Python.

The project will compare:

```text
C built-in integer
        │
        └── Fixed range

Our Big Integer library
        │
        └── Dynamically sized representation

Python int
        │
        └── Arbitrary precision
```

The comparison will focus on representation, arithmetic, memory usage, execution time, and practical limitations.

---

## Original Contribution

In addition to implementing the fundamental Big Integer functionality, the project will contain at least one **additional implementation designed by the project team**.

The exact feature will be selected after the core library has been completed and evaluated.

The goal is to make the contribution technically meaningful and clearly distinguish it from the standard Big Integer concept.

---

## Project Structure

The planned project structure is:

```text
big-integer-project/
│
├── c/
│   ├── include/
│   │   └── bigint.h
│   │
│   ├── src/
│   │   └── bigint.c
│   │
│   └── examples/
│       └── demo.c
│
├── python/
│
├── tests/
│
├── docs/
│
├── README.md
│
└── .gitignore
```

The structure may evolve as development continues.

---

## Technology

### C

Used for:

* Big Integer representation
* Dynamic memory management
* Core arithmetic algorithms
* Library/API implementation

### Python

Used for:

* Comparison with Python's built-in arbitrary-precision integers
* Test generation
* Performance experiments
* Supporting analysis

### Tools

* GCC
* MSYS2 UCRT64
* Visual Studio Code
* Git
* GitHub

---

## Development Status

### Completed

* [x] Project structure
* [x] C compiler environment
* [x] BigInteger structure
* [x] Dynamic memory allocation
* [x] Large integer input
* [x] Exact large integer output
* [x] Initial large-number testing
* [x] Initial Big Integer API

### In Progress

* [ ] Reusable library/demo architecture
* [ ] Robust input and edge-case handling
* [ ] Addition
* [ ] Subtraction
* [ ] Multiplication
* [ ] Division
* [ ] Comparison
* [ ] Extensive testing
* [ ] Python comparison
* [ ] Performance analysis
* [ ] Original project contribution
* [ ] Final documentation

---

## Goal

The final project should demonstrate that a programmer can use our C implementation to create and manipulate integers far beyond the limits of standard C integer types, while also understanding how arbitrary-precision arithmetic can be implemented internally.

The project is intended to be both:

1. A working Big Integer implementation in C.
2. A reusable library that can be integrated into another C program.
$env:Path += ";C:\msys64\ucrt64\bin"
gcc c\main.c c\src\bigint.c -o c\bigint.exe
.\c\bigint.exe
123456789012345678901234567890123456789012345678901234567890