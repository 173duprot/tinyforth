#include <stdio.h>

// WARNING: I will be using this for hacky-stuff. In C, we will never be using
// a ptr->0 so we can use STRCPY and null-terminate it to copy

#define STRCPY(a1, a2) for(int i=0; a1[i] != 0; i++) { a2[i] = a1[i]; } 

#define PUSH(stack, pointer, val)  \
    pointer++;                     \
    stack[pointer] = val;

#define POP(stack, pointer, val)   \
    val = stack[pointer];          \
    pointer--;

#define BUILTIN(ptr,nam,cod)          \
    printf("def builtin: %s\n", nam); \
    dp++;                             \
    void* ptr = &dict[dp].code[0];    \
    STRCPY(nam, dict[dp].name)        \
    STRCPY(cod, dict[dp].code)

// This is put at the end of asm primatives
#define NEXT                \
    ip = nip;               \
    nip++;                  \
    printf("goto **%p -> %p\n", ip, **ip);\
    goto ***ip;

/* structures */
    // core
        void*** ip;  // Instruction Pointer
        void*** nip; // Next Instruction Pointer
    // buffers
        char    input[1000];
        void*** code[100];
    // stack
        int    sp =  -1; // sp:  Stack ptr (First push will push from [-1] to [0])
        int    stack[10];
    // return stack
        int    rsp = -1; // rsp: Return Stack ptr
        void*  rstack[20];
    // dictionary
        int    dp =  -1; // dp:  Dict ptr (instead of linked list, dict is an array of structs)
        struct entry { char name[40]; void** code[200]; } dict[1000];

int main(void)
{
    printf("\n--- init ---\n");
    /* --- builtin --- */
    void* docol = &&docol;

    char  bye_n[]  = "bye";
    void* bye_a[]  = { &&bye, 0 };
    BUILTIN(bye, bye_n, bye_a)

    char  exit_n[] = "exit";
    void* exit_a[] = { &&exit, 0};
    BUILTIN(exit, exit_n, exit_a)

    char  test_n[] = "test";
    void* test_a[] = { docol, exit, 0 };
    BUILTIN(test, test_n, test_a)

    /* --- Start the program --- */
    code[0] = test;
    code[1] = bye;
    nip = &code[0];
    NEXT
    /* --- builtin code --- */
    docol:
        printf("\ndocol:\n");
        printf("pushing %p to rstack\n", nip);
        PUSH(rstack, rsp, nip)
        nip = *ip + 1;
        NEXT
    exit:
        printf("\nexit\n");
        printf("poping %p from rstack\n", rstack[rsp]);
        POP(rstack, rsp, nip)
        NEXT
    bye:
        printf("\nbye:\n");
        return 0;
};
