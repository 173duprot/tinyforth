#include <stdio.h>
#include <string.h>

// Main Memory
char memory[100000];
char *mem = memory;
		
#define ALLOC(x) 	mem; mem += sizeof(x);
#define NEXT		(*ip)++; goto ****ip;
#define POP(x,ptr)	(ptr)--; x = *(ptr);
#define PUSH(x,ptr)	*(ptr) = x; (ptr)++;
		
int main() {

	/* Memory */
	
	void  ****ip = (void ****) ALLOC(void **);     // Instruction Pointer
	
	char    **cp = (char **)   ALLOC(char *);      // Character Pointer
	         *cp = (char *)    ALLOC(char [80]);   // Input Buffer
	
	long    **sp = (long **)   ALLOC(long *);      // Stack Pointer
	         *sp = (long *)	   ALLOC(long[10]);    // Stack
	
	void ****rsp = (void ****) ALLOC(void **);     // Return Stack Pointer
	        *rsp = (void ***)  ALLOC(void *[10]);  // Return Stack
	
	void  ***dsp = (void ***)  ALLOC(void **);     // Dictonary Stack Pointer
	        *dsp = (void **)   ALLOC(void * [10]); // Dictionary Stack
	
	/* Code */
	void *lookup	= && lookup;
	void *call	= && call;
	void *retrn	= && retrn;
	void *bye	= && bye;
	void *code	= && code;
	
	void **test[]	= { call, &code, &retrn };
	void ***word[]	= { &test, &bye };
	
	*ip = word;
	goto ****ip;
	
	lookup: puts("lookup");
	
	
	
	call:	puts("call");
		PUSH(*ip,*rsp);
		*ip = (**ip);
		NEXT;
	
	retrn:	puts("return");
		POP(*ip,*rsp);
		NEXT;
	
	code:	puts("run code");
		NEXT;
	
	bye:	puts("bye");
		return 0;
}
