/*
 * EMULATION OF PARALLEL ADDRESS SPACE
 *
 * copyright 2022-12-17, dmitri bortoq, mit license
 */
#include "space.h"

/* return bit string of instruction argument as a number */
static inline size get_argument(size src, size n)
{
  bitcpy(n, space, src, &n, 0);
  return n;
}

/* read "i-th instruction" bit string from bit space to the processor mechanism */
static inline void fetch_instruction(size i)
{
  size a;
  for(a = 0; a < sizeof s; ++a)
    processor[i][0] = get_argument(PROCESSOR_START + i * INSTRUCTION_SIZE + o[a], s[a]);
}

/* load and run copy instructions over bit space */
static void computation()
{
  size i;
  for(i = 0; i < PROCESSOR_N; ++i)
  {
    fetch_instruction(i);
    bitcpy(processor[i][0], space, processor[i][2], space, processor[i][1]);
  }
}

/* access file f and copy byte aligned bit string. return 0 if ok */
static inline int channel(size_t (*copy)(), FILE *f, size s, size a)
{
  if(s /= CHAR_BIT > 0)
    if(copy(&space[a / CHAR_BIT], s, 1, f) != s)
      return -1;
  return 0;
}

/* copy stdin to stdout through src and dst channels. return 0 if ok */
static int channels()
{
  int code = channel(fwrite, stdout, processor[2][0], processor[2][1]);
  code |= channel(fread, stdin, processor[1][0], processor[1][1]);
  return code;
}

int main()
{
  /* prepare address space */
  uint64_t time = LIFE;
  memcpy(space, core, sizeof core);

  /* emulate computation */
  while(time-- && !channels())
    computation();

  return 0;
}

