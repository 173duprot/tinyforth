#include <stdio.h>
#include <string.h>

// Main Memory
char memory[100000];
char *mem = memory;

#define ALLOC(x)						\
	mem;							\
	mem += sizeof(x);					\

#define NEXT							\
	(*ip)++;						\
	goto ***(ip);						\

int main() {
	
	/* Memory Structures */

	void	***ip	= (void ***)	ALLOC(void **);
	
	long	**sp 	= (long **)	ALLOC(long *);
		*sp 	= (long *)	ALLOC(long[10]); 

	void	***rsp 	= (void ***)	ALLOC(void **);
		*rsp 	= (void **)	ALLOC(void *[10]);

	void	***dsp 	= (void ***)	ALLOC(void **);
		*dsp 	= (void **)	ALLOC(void * [10]);

	/* Memory */
	
	void *word[] = { &&lookup, &&bye };
	*ip = (word)-1;
	
	NEXT;
	
	return 0;
	
	lookup:
		puts("Run Code");
		NEXT;

	bye:
		puts("bye");
		return 0;
}
