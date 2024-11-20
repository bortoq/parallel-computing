/*
 * ASSEMPLER
 *
 * copyright 2022-12-21, dmitri bortoq, mit license
 */
#include "space.h"

/* read instruction from stdin */
static int read_instruction(size i)
{
  return scanf("%hu%hu%hu%*[\t -~]", &processor[i][0], &processor[i][1], &processor[i][2]);
}

/* compile next 3 numbers from stdin to a next instruction of processor */
static int compile_instruction(size_t n)
{
  switch(read_instruction(n % CHAR_BIT))
  {
    case -1:
    case 0: return 0;
    case 3: return 1;
    default: fprintf(stderr, "compilation error at instruction %lu\n", n);
      exit(n);
  }
}

/* save space to stdout and reset */
static void flush_space(int i)
{
  fwrite(space, (INSTRUCTION_SIZE * i + CHAR_BIT - 1) / CHAR_BIT, 1, stdout);
}

/* save code of the i-th instruction to space */
static void write_code(size_t n)
{
  int i = n % CHAR_BIT;
  size a;
  for(a = 0; a < sizeof s; ++a)
    bitcpy(s[a], &processor[i][a], 0, space, INSTRUCTION_SIZE * i + o[a]);
}

int main()
{
  size_t n = 0;

  do
    if(compile_instruction(n) == 1)
    {
      write_code(n);
      if(++n % CHAR_BIT == 0)
        flush_space(CHAR_BIT);
    }
  while(!feof(stdin));
  flush_space(n % CHAR_BIT);

  return 0;
}
