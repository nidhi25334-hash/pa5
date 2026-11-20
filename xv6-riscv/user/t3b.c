#include "kernel/types.h"
#include "user/user.h"
#include "user/common.h"

/*
 * 3b: mind the gap
 * Uses: int pgwalk(uint64 va, uint64 *ptes);  (from 1b)
 */
void
leaf(char *name, uint64 va)
{
  uint64 ptes[3];
  int n = pgwalk(va, ptes);

  printf("%s %p : valid levels %d, leaf flags ", name, (void *)va, n);
  printflags(ptes[2]);
  printf("\n");
}

int
main(int argc, char *argv[])
{
  int local = 1;
  uint64 stack = PGROUNDDOWN(&local);
  uint64 guard = stack - PGSIZE;
  int status;

  leaf("stack page", stack);
  leaf("guard page", guard);

  if (fork() == 0) {
    printf("child : reading the guard page...\n");
    volatile char c = *(char *)guard;
    printf("child : read %d (this line should not print)\n", c);
    exit(0);
  }
  wait(&status);
  printf("parent: child exited with status %d\n", status);
  exit(0);
}
