// Shared constants for the walk-the-walk test programs.
// User programs cannot include kernel/riscv.h, so we copy what we need.
#define PGSIZE      4096
#define MAXVA       (1L << (9 + 9 + 9 + 12 - 1))
#define TRAMPOLINE  (MAXVA - PGSIZE)
#define TRAPFRAME   (TRAMPOLINE - PGSIZE)
#define PGROUNDDOWN(a) (((uint64)(a)) & ~(PGSIZE - 1))

#define PTE_V (1L << 0)
#define PTE_R (1L << 1)
#define PTE_W (1L << 2)
#define PTE_X (1L << 3)
#define PTE_U (1L << 4)
#define PTE2PA(pte) (((pte) >> 10) << 12)

// Print the flag bits of a PTE as "VRWXU", with '-' for a clear bit.
static inline void
printflags(uint64 pte)
{
  printf("%c%c%c%c%c",
         (pte & PTE_V) ? 'V' : '-', (pte & PTE_R) ? 'R' : '-',
         (pte & PTE_W) ? 'W' : '-', (pte & PTE_X) ? 'X' : '-',
         (pte & PTE_U) ? 'U' : '-');
}
