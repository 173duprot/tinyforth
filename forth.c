#include <stdio.h>
#include <string.h>

// Main Memory
char memory[100000];
char *mem = memory;

// Dictionary entry type
typedef struct {
char name[100];
void* code;
} dict_t;

#define ALLOC(x)						\
	mem;							\
	memcpy(mem, (char*)&(x), sizeof(x));			\
	mem += sizeof(x);					\

#define DEFINE(x,y)						\
	(*dsp);							\
	strcpy((*dsp)->name, x);				\
	(*dsp)->code = y;					\
	(*dsp)++;						\

#define NEXT							\
	(*ip)++;						\
	goto ***(ip);						\

int main() {

	/* Pointers */

	void **instruction_pointer;
	void ***ip = (void ***)ALLOC(instruction_pointer);
	
	long *stack_pointer;
	long **sp = (long **)ALLOC(stack_pointer);
	
	void **return_stack_pointer;
	void ***rsp = (void ***)ALLOC(return_stack_pointer);
	
	dict_t *dictionary_stack_pointer;
	dict_t **dsp = (dict_t **)ALLOC(dictionary_stack_pointer);
	
	/* Stacks */
	
	long stack[10];
	*sp = (long *)ALLOC(stack);

	void *return_stack[10];
	*rsp = (void **)ALLOC(return_stack);
	
	dict_t dictionary_stack[10];
	*dsp = (dict_t *)ALLOC(dictionary_stack);
	
	/* Memory */
	char code[] = "lookup";
	char *cp = code;
	
	dict_t *bye = (dict_t *)DEFINE("bye", &&bye);
	dict_t *lookup = (dict_t *)DEFINE("lookup", &&lookup);
	
	void *word[] = { lookup->code, bye->code };
	*ip = (word)-1;

	NEXT;
	
	return 0;
	
	bye:
		puts("bye");
		return 0;
		
	lookup:
		puts("Run Code");
		NEXT;
}

// { hidden macro 1 1 + } <- test
