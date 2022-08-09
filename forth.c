#include <stdio.h>
#include <string.h>

// Main Memory
char memory[100000];
char *mem = memory;
		
#define ALLOC(x) 	mem; mem += sizeof(x);
#define NEXT		ip++; goto ***ip;
		
int main() {

	/* Memory */
	
	void  ***ip;                      // Instruction Pointer
	char    *cp = ALLOC(char [80]);   // Input Buffer
	long    *sp = ALLOC(long [10]);   // Stack
	void ***rsp = ALLOC(void *[10]);  // Return Stack
	void  **dsp = ALLOC(void *[10]);  // Dictionary Stack
	
	/* Code */
	void *lookup	= && lookup;
	void *call	= && call;
	void *retrn	= && retrn;
	void *bye	= && bye;
	void *code	= && code;
	
	void **test[]	= { call, &code, &retrn };
	void ***word[]	= { &test, &bye };
	
	ip = word;
	goto ***ip;
	
	lookup: puts("lookup");
	
	call:	puts("call");
		*rsp = ip; rsp++;
		ip = *ip;
		NEXT;
	
	retrn:	puts("return");
		rsp--; ip = *rsp;
		NEXT;
	
	code:	puts("run code");
		NEXT;
	
	bye:	puts("bye");
		return 0;
}
