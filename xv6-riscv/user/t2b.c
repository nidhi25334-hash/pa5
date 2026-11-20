#include "kernel/types.h"
#include "user/user.h"

/*
 * 2b: how big is the tree?
 * Uses: int ptpages(void);
 */
#define MB (1024 * 1024)
#define GB (1024 * MB)

int
main(int argc, char *argv[])
{
  printf("start                 : sz %p  page-table pages %d\n", sbrk(0), ptpages());

  sbrk(2 * MB);                       // eager: 512 real pages
  printf("eager sbrk(2 MB)      : sz %p  page-table pages %d\n", sbrk(0), ptpages());

  char *far = sbrklazy(GB);           // lazy: only sz grows
  printf("lazy sbrk(1 GB)       : sz %p  page-table pages %d\n", sbrk(0), ptpages());

  far[GB - 1] = 1;                    // touch the very last byte
  printf("touch last byte       : sz %p  page-table pages %d\n", sbrk(0), ptpages());
  exit(0);
}
