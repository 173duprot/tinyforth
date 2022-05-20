#include <stdio.h>
#include <string.h>

// Main Memory
char memory[100000];
char *mem = memory;
		
#define ALLOC(x)			\
		mem;			\
		mem += sizeof(x);	\
		
#define NEXT 				\
		(*ip)++;		\
		goto ***(ip);		\
		
int main() {
	
	// Instruction Pointer
	void	***ip	= (void ***)	ALLOC(void **);
	
	// Stack
	long	**sp 	= (long **)	ALLOC(long *);
		*sp 	= (long *)	ALLOC(long[10]); 
	
	// Return Stack
	void	***rsp 	= (void ***)	ALLOC(void **);
		*rsp 	= (void **)	ALLOC(void *[10]);
	
	// Dictonary Stack
	void	***dsp 	= (void ***)	ALLOC(void **);
		*dsp 	= (void **)	ALLOC(void * [10]);
	
	/* Memory */
	void *word[] = { &&lookup, &&bye };
	*ip = (word)-1;
	NEXT;
	
	lookup:
		puts("Run Code");
		NEXT;
	
	bye:
		puts("bye");
		return 0;
}
