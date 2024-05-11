#pragma GCC diagnostic ignored "-Wno-incompatible-pointer-types"
#pragma GCC diagnostic ignored "-Wno-deprecated-declarations"

#include <stdio.h>
#include <string.h>

// Main Memory
char xxxx[100000];
char *mem = xxxx;
		
#define NEXT		goto ***(++ip)
#define ALLOC(x) 	((mem+=sizeof(x))-sizeof(x))
#define DEFINE(x)	*(dict--) = x
#define PUSH(ptr,x)     *(ptr++)  = x
#define POP(ptr)        *(--ptr)
		
int main() {
	
	/* Memory */
	void ***  ip; // Instruction Pointer
	void **** dict   = ALLOC(void ***[100]); dict += 100; // Dictionary
	long *    stack  = ALLOC(long    [10]);  // Stack
	void ***  rstack = ALLOC(void   *[10]);  // Return Stack
	
	/* Core Words*/
	void *      call = && call;
	void *     retrn = && retrn;
	void *       bye = && bye;
	void *     input = && input;
	void *     print = && print;
	
	/* Secondary Words */
	void **indirect[]	= { call, &input, &print, &retrn };
	void **test[]		= { &indirect, &bye };
	
	/* Filling The Dictionary */
	DEFINE(&test);
	
	/* Run */
	ip = &test;
	goto ***ip;
	
	call:	puts("call");
		PUSH(rstack, ip);
		ip = *ip;
		NEXT;
	
	retrn:	puts("return");
		ip = POP(rstack);
		NEXT;
	
	bye:	puts("bye");
		return 0;
	
	def:   puts("def");
	       DEFINE(POP(stack));
	       NEXT;
	
	input: puts("input");
	       gets(mem);
	       PUSH(stack, ALLOC( strlen(mem)+1 ) );
	       NEXT;

	print: puts("print");
	       puts(POP(stack));
	       NEXT;
	
	parse: puts("parse");
	       ip = dict;
	       NEXT;
}
