#include "kernel/types.h"
#include "user/user.h"
#include "user/common.h"

/*
 * 1a: slice and dice
 * No kernel changes needed. Replace each 0 below with the
 * shift-and-mask expression that extracts that field from va.
 */
#define L2(va)  (va >> 30) & 0x1FF   // TODO: bits 38..30
#define L1(va) (va >> 21) & 0x1FF  // TODO: bits 29..21
#define L0(va)  (va >> 12) & 0x1FF // TODO: bits 20..12
#define OFF(va) (va >> 0) & 0xFFF// TODO: bits 11..0

int global = 7;

void
show(char *name, uint64 va)
{
  printf("%s %p -> L2 %d  L1 %d  L0 %d  offset 0x%x\n", name, (void *)va,
         (int)L2(va), (int)L1(va), (int)L0(va), (int)OFF(va));
}

int
main(int argc, char *argv[])
{
  int local = 1;

  show("text       ", (uint64)&main);
  show("global     ", (uint64)&global);
  show("stack      ", (uint64)&local);
  show("example    ", 0x40403ABCUL);
  show("trapframe  ", TRAPFRAME);
  show("trampoline ", TRAMPOLINE);
  exit(0);
}
