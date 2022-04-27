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

int main() {

	/* Pointers */

	void ***instruction_pointer;
	void ****ip = (void ****)ALLOC(instruction_pointer);

	void ***next_instruction_pointer;
	void ****nip = (void ****)ALLOC(next_instruction_pointer);

	int *stack_pointer;
	int **sp = (int **)ALLOC(stack_pointer);
	
	void **return_stack_pointer;
	void ***rsp = (void ***)ALLOC(return_stack_pointer);
	
	dict_t *dictionary_stack_pointer;
	dict_t **dsp = (dict_t **)ALLOC(dictionary_stack_pointer);
	
	
	/* Stacks */

	int stack[100];
	*sp = (int *)ALLOC(stack);
	
	void *return_stack[100];
	**rsp = (void **)ALLOC(return_stack);
	
	dict_t dictionary_stack[50];
	*dsp = (dict_t *)ALLOC(dictionary_stack);
	
	/* Memory */
	dict_t *test = (dict_t *)DEFINE("test", &&test);
	goto *(test->code);

	return 0;

	test:
		puts("Hello World!");
		return 0;
}
