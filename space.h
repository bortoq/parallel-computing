/*
 * ADDRESS SPACE DEFINITIONS
 *
 * copyright 2024-10-31, dmitri bortoq, mit license
 */
#ifndef SPACE_H_
#define SPACE_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/* address space settings */
enum {
  SPACE_SIZE = 0xFFF0,            /* user defined: SPACE_SIZE. version limit [% 8, % INSTRUCTION_SIZE] */
  LIFE = 0x10,                    /** user defined: number of processor executions (> 1) */
  PROCESSOR_N = 64,               /** number of instructions in processor (> 2), version limit [% 8] */
  N_SIZE = 16,                    /* number of bits in instruction's "n" */
  ADDRESS_SIZE = 16,              /* number of bits in instruction's "dst" ("src" has same size) */
  INSTRUCTION_SIZE = 16 + 2 * 16, /* number of bits in instruction "copy n, dst, src" (> 10) */
  PROCESSOR_START = 0,            /** bit index of the first processor's instruction */
};

/* types */
typedef uint16_t  size;           /* large enough for instruction argument */

/* copy bits from one array to another (n, src, s, dst, d) */
void bitcpy();

/* GLOBALS */
size processor[PROCESSOR_N][3];     /* parsed copy instructions */
char space[SPACE_SIZE / CHAR_BIT];  /* data bits of the bit space */

/* format of the instruction */
const size o[] = {0, N_SIZE, N_SIZE + ADDRESS_SIZE};
const size s[] = {N_SIZE, ADDRESS_SIZE, ADDRESS_SIZE};

/* TODO: core */
const size core[] = {                       \
  0x0008, 0x0020, 0x0c00,  /* channel in */ \
  0x0008, 0x0c08, 0x0,    /* channel out */ \
  0x0BD0, 0x0BD0, 0x0C00,      /* loader */ \
};

#endif /* SPACE_H_ */

