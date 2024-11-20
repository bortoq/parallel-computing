/*
 * DISASSEMPLER
 *
 * copyright 2024-10-31, dmitri bortoq, mit license
 */
#include "space.h"

/* read code of i-th instruction */
static inline void read_code(size i)
{
  size a;
  for(a = 0; a < sizeof s; ++a)
    bitcpy(s[a], space, INSTRUCTION_SIZE * i + o[a], &processor[i][a], 0);
}

/* decompile code from stdin to the processor */
static size_t read_codes()
{
  size i;
  size_t n = fread(space, 1, sizeof space, stdin) * CHAR_BIT / INSTRUCTION_SIZE;

  for(i = 0; i < n; ++i)
    read_code(i);
  return n;
}

/* write instruction to stdout */
static void write_instruction(size i)
{
  printf("%#4X %#4X %#4X\n", processor[i][0], processor[i][1], processor[i][2]);
}

/* save n instructions from processor to stdout */
static void write_instructions(size_t n)
{
  size i;
  for(i = 0; i < n; ++i)
    write_instruction(i);
}

int main()
{
  size_t n = 0;

  do {
    n = read_codes();
    write_instructions(n);
  } while(!feof(stdin));

  return 0;
}

