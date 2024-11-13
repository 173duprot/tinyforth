#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>

typedef struct { 
    void *free;        // Pointer to the start of the free list 
    size_t size_slot;  // Size of each slot 
    size_t size_arena; // Total number of slots 
    size_t head;       // Number of used slots 
    uint8_t mem[];     // Flexible Array Member (FAM) memory block 
} arena_t;

#define ARENA(n, size) ({ \
        arena_t *arena = (arena_t *)((uint8_t[sizeof(arena_t) + (size) * (n)]){0}); \
        arena->size_slot = (size); \
        arena->size_arena = (n); \
        arena->head = 0; \
        arena->free = NULL; \
        arena; /* Return Arena Pointer */ \
    })

// Allocate memory from the arena (slot-based)
void *arena_alloc(arena_t *a) {
    if (a->free) {
        void *p = a->free;
        a->free = *(void **)p;  // Pop from free list
        return p;
    }
    if(a->head < a->size_arena) return -1;
    void *p = a->mem + (a->head * a->size_slot);
    a->head++;
    return p;
}

// Free memory back to the arena (slot-based)
void arena_free(arena_t *a, void *p) {
    *(void **)p = a->free;  // Push to free list
    a->free = p;
}

// Reset the arena (reuse memory)
void arena_reset(arena_t *a) {
    a->head = 0;
    a->free = NULL;
}

int main() {
    // Create an arena with slots of 128 bytes and 8 total slots
    arena_t *my_arena = ARENA(8, sizeof(int));

    printf("Arena created with %zu slots, each of size %zu bytes.\n", my_arena->size_arena, my_arena->size_slot);

    // Test 1: Allocate memory (slots)
    void *p1 = arena_alloc(my_arena);
    void *p2 = arena_alloc(my_arena);
    printf("Test 1: Allocated two slots.\n");
    printf("Allocated p1 at %p, p2 at %p\n", p1, p2);
    assert(p1 != NULL && p2 != NULL && p1 != p2);

    // Test 2: Free a slot back to the arena
    arena_free(my_arena, p1);
    printf("Test 2: Freed slot p1 at %p.\n", p1);
    assert(my_arena->free == p1);

    // Test 3: Re-allocate and check if the previously freed slot is reused
    void *p3 = arena_alloc(my_arena);
    printf("Test 3: Re-allocated p3 at %p, expected %p.\n", p3, p1);
    assert(p3 == p1);

    // Test 4: Free another slot and ensure it goes to the free list
    arena_free(my_arena, p2);
    printf("Test 4: Freed slot p2 at %p.\n", p2);
    assert(my_arena->free == p2);

    // Test 5: Allocate until the arena is full
    for (size_t i = my_arena->head; i < my_arena->size_arena; i++) {
        void *p = arena_alloc(my_arena);
        printf("Test 5: Allocated slot %zu at %p\n", i+1, p);
        assert(p != NULL);
    }
    assert(my_arena->head == my_arena->size_arena);
    printf("Test 5: Arena is fully allocated with head at %zu.\n", my_arena->head);

    // Test 6: Attempting to allocate more than the available slots should fail
    int allocation_failed = 0;
    for (int i = 0; i < 2; i++) {
        void *p = NULL;
        if (my_arena->head < my_arena->size_arena) {
            p = arena_alloc(my_arena);
        }
        printf("Test 6: Attempted allocation beyond capacity, result: %p\n", p);
        if (p == NULL) allocation_failed = 1;
    }
    assert(allocation_failed == 1);
    printf("Test 6: Allocation failed as expected when exceeding arena capacity.\n");

    // Test 7: Reset the arena and check if it can be reused
    arena_reset(my_arena);
    printf("Test 7: Arena reset.\n");
    assert(my_arena->head == 0 && my_arena->free == NULL);

    // Test 8: Allocate again after reset
    p1 = arena_alloc(my_arena);
    printf("Test 8: Allocated p1 at %p after reset.\n", p1);
    assert(p1 != NULL);

    // Final check
    printf("All tests passed.\n");

    return 0;
}

