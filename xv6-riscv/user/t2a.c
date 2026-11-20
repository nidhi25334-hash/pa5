#include "kernel/types.h"
#include "user/user.h"

/*
 * 2a: show me the tree
 * Uses: void vmprint(void);
 */
int
main(int argc, char *argv[])
{
  vmprint();
  exit(0);
}
