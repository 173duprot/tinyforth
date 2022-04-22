#include <stdio.h>
#include <string.h>

// Main Memory
char memory[1000000];
char *mem = memory;

// Allocating the memory using the pointer itteratively
#define ALLOC(x)					\
	mem;						\
	memcpy(mem, (char*)&(x), sizeof(x));		\
	mem += sizeof(x);				\
	

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
	
	void **dictionary_stack_pointer;
	void **dsp = (void **)ALLOC(dictionary_stack_pointer);
	
	
	/* Stacks */

	int stack[100];
	*sp = (int *)ALLOC(stack);
	
	void *return_stack[100];
	*rsp = (void **)ALLOC(return_stack);
	
	struct dictionary_entry { char name[100]; void*** code; } dictionary_stack[1000];
	*dsp = (void **)ALLOC(dictionary_stack);
	
	/* Memory */
	
	return 0;
}
