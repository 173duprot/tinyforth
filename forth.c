#include <stdio.h>
#include <string.h>

// Main Memory
char memory[100000];
char *mem = memory;
		
#define ALLOC(x) 	mem; mem += sizeof(x);
#define NEXT		ip++; goto ***ip;
#define PUSH(ptr,x)     *ptr = x; ptr++;
#define POP(ptr,x)      ptr--; x = *ptr;
		
int main() {
	
	/* Memory */
	void *        dp;                       // Dictionary Pointer
	void ***      ip = ALLOC(void **[20]);  // Instruction Pointer
	long *     stack = ALLOC(long   [10]);  // Stack
	void ***  rstack = ALLOC(void  *[10]);  // Return Stack
	
	/* Core Words*/
	void *      call = && call;
	void *     retrn = && retrn;
	void *       bye = && bye;
	void *     input = && input;
	
	/* Secondary Words */
	void **test[]	= { call, &input, &retrn };
	
	/* Starting The Dictionary */
	dp = test;
	
	/* Run */
	PUSH(rstack, ip);
	 PUSH(ip, &test);
	 PUSH(ip, &bye);
	POP(rstack, ip);
	goto ***ip;
	
	
	call:	puts("call");
		PUSH(rstack, ip);
		ip = *ip;
		NEXT;
	
	retrn:	puts("return");
		POP(rstack, ip);
		NEXT;

	input: puts("input");
	       putchar('>');
	       do {
	               *mem = getchar();
	                mem += sizeof(char);
               } while (*(mem-1) != '\n');
	       NEXT;

	parse: puts("parse");

	bye:	puts("bye");
		return 0;
}
