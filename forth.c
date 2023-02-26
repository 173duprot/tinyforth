#pragma GCC diagnostic ignored "-Wno-deprecated-declarations"
#pragma GCC diagnostic ignored "-Wno-incompatible-pointer-types"

#include <stdio.h>
#include <string.h>

// Main Memory
char xxxx[100000];
char *mem = xxxx;
		
#define NEXT		ip++; goto ***ip;
#define ALLOC(x) 	mem; mem += sizeof(x);
#define PUSH(ptr,x)     *ptr = x; ptr++;
#define POP(ptr,x)      ptr--; x = *ptr;
		
int main() {
	
	/* Memory */
	void ***  ip;   // Instruction Pointer
	void *    dict; // Dictionary Pointer
	long *    stack =  ALLOC(long   [10]);  // Stack
	void ***  rstack = ALLOC(void  *[10]);  // Return Stack
	
	/* Core Words*/
	void *      call = && call;
	void *     retrn = && retrn;
	void *       bye = && bye;
	void *     input = && input;
	
	/* Secondary Words */
	void **indirect[]	= { call, &input, &retrn };
	void **test[]		= { &indirect, &bye };
	
	/* Starting The Dictionary */
	dict = test;
	
	/* Run */
	ip = &test;
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
	       gets(mem);
	       mem += sizeof(strlen(mem)+1);
	       NEXT;

	parse: puts("parse");

	bye:	puts("bye");
		return 0;
}
