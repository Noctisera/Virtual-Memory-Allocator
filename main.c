#include "vma.h"

int main(void) {
    char comm[STRING_MAX];
    arena_t* arena = NULL;
    int ok;

    while (1) {
        ok = 0;
        scanf("%s", comm);

        if (strcmp(comm, "ALLOC_ARENA") == 0) {
            ok = 1;

            uint64_t size;
            scanf("%lu", &size);
            arena = alloc_arena(size);
        }

        if (strcmp(comm, "ALLOC_BLOCK") == 0) {
            ok = 1;

            uint64_t adr_start, dim;
            scanf("%lu %lu", &adr_start, &dim);

            alloc_block(arena, adr_start, dim);
        }

        if (strcmp(comm, "PMAP") == 0) {
            ok = 1;
            pmap(arena);
        }
        if (strcmp(comm, "DEALLOC_ARENA") == 0) {
            dealloc_arena(arena);
            break;
        }
        if (strcmp(comm, "FREE_BLOCK") == 0) {
            ok = 1;

            uint64_t adr;
            scanf("%lu", &adr);
            free_block(arena, adr);
        }
        if (strcmp(comm, "WRITE") == 0) {
            ok = 1;
            uint64_t adr, dim;
            scanf("%lu %lu", &adr, &dim);

            write(arena, adr, dim);
        }
        if (strcmp(comm, "READ") == 0) {
            ok = 1;
            uint64_t adr, dim;
            scanf("%lu %lu", &adr, &dim);

            read(arena, adr, dim);
        }
        if (strcmp(comm, "MPROTECT") == 0) {
            ok = 1;

            uint64_t adr;
            scanf("%lu", &adr);
            mprotect(arena, adr);
        }
        if (ok == 0) {
            printf("Invalid command. Please try again.\n");
        }
    }
    return 0;
}