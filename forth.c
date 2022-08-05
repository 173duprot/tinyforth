#include <stdio.h>
#include <string.h>

// Main Memory
char memory[100000];
char *mem = memory;
		
#define ALLOC(x) 	mem; mem += sizeof(x);
#define NEXT 		(*ip)++; goto **(*ip-1);
		
int main() {

	/* Memory */
	void  ***ip = (void ***) ALLOC(void **);     // Instruction Pointer

	long   **sp = (long **)	 ALLOC(long *);	     // Stack Pointer
	        *sp = (long *)	 ALLOC(long[10]);    // Stack

	void ***rsp = (void ***) ALLOC(void **);     // Return Stack Pointer
	       *rsp = (void **)	 ALLOC(void *[10]);  // Return Stack

	void ***dsp = (void ***) ALLOC(void **);     // Dictonary Stack Pointer
	       *dsp = (void **)  ALLOC(void * [10]); // Dictionary Stack
	
	/* Code */
	void *test[] = { &&code, &&retrn };
	void *word[] = { &&call, &test, &&code, &&bye};
	*ip = (word);
	NEXT;
	
	call:
		puts("Call");
		**rsp = *ip+1; (*rsp)++; // Push ip+1 onto return stack
		*ip = (**ip);
		NEXT;
	
	retrn:
		puts("Return");
		(*rsp)--; *ip = **rsp;
		NEXT;

	code:
		puts("Run Code");
		NEXT;
	
	bye:
		puts("bye");
		return 0;
}
