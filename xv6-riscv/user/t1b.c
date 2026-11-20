#include "kernel/types.h"
#include "user/user.h"
#include "user/common.h"

/*
 * 1b: walk it yourself
 * Uses: int pgwalk(uint64 va, uint64 *ptes);
 */




void
show(char *name, uint64 va)
{
  uint64 ptes[3];
  int n = pgwalk(va, ptes);

  printf("%s va %p : %d valid level(s)\n", name, (void *)va, n);
  for (int i = 0; i < 3; i++) {
    if (i > n) {
      printf("   L%d  not reached\n", 2 - i);
      continue;
    }
    printf("   L%d  pte %p  ", 2 - i, (void *)ptes[i]);
    printflags(ptes[i]);
    printf("  -> %p\n", (void *)PTE2PA(ptes[i]));
  }
  if (n == 3)
    printf("   PA  %p\n", (void *)(PTE2PA(ptes[2]) + (va & (PGSIZE - 1))));
  printf("\n");
}

int
main(int argc, char *argv[])
{
  int local = 1;
  char *heap = sbrklazy(PGSIZE);   // grows sz, no page yet

  show("text      ", (uint64)&main);
  show("stack     ", (uint64)&local);
  show("heap lazy ", (uint64)heap);
  heap[0] = 1;                     // first touch: page fault maps it
  show("heap used ", (uint64)heap);
  show("trampoline", TRAMPOLINE);
  show("far away  ", 0x100000000UL);
  exit(0);
}
