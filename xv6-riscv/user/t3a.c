#include "kernel/types.h"
#include "user/user.h"
#include "user/common.h"

/*
 * 3a: permission denied!
 * Uses: int pgperm(uint64 va, int perm);
 */
int
main(int argc, char *argv[])
{
  char *p = sbrk(PGSIZE);   // one eagerly mapped page
  int status;

  if (fork() == 0) {
    p[0] = 'A';
    printf("child : wrote '%c'\n", p[0]);
    printf("child : pgperm(R) returned old flags 0x%x\n", pgperm((uint64)p, PTE_R));
    printf("child : read back '%c'\n", p[0]);
    printf("child : writing again...\n");
    p[0] = 'B';
    printf("child : write went through! (this line should not print)\n");
    exit(0);
  }
  wait(&status);
  printf("parent: child exited with status %d\n", status);
  printf("parent: pgperm on an unmapped va   -> %d\n", pgperm(0x100000000UL, PTE_R));
  printf("parent: pgperm with W but no R     -> %d\n", pgperm((uint64)p, PTE_W));
  printf("parent: pgperm on the trampoline   -> %d\n", pgperm(TRAMPOLINE, PTE_R | PTE_X));
  exit(0);
}
