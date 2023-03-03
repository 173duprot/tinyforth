#pragma GCC diagnostic ignored "-Wno-incompatible-pointer-types"
#pragma GCC diagnostic ignored "-Wno-deprecated-declarations"

#include <stdio.h>
#include <string.h>

// Main Memory
char xxxx[100000];
char *mem = xxxx;
		
#define NEXT		ip++; goto ***ip;
#define ALLOC(x) 	mem; mem += sizeof(x);
#define DEFINE(x)	({ *dict = x; dict--; })
#define PUSH(ptr,x)     ({ *ptr  = x; ptr ++; })
#define POP(ptr)        ({ ptr--; *ptr; })
		
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
	
	/* Secondary Words */
	void **indirect[]	= { call, &input, &retrn };
	void **test[]		= { &indirect, &bye };
	
	/* Filling The Dictionary */
	DEFINE(test);
	
	/* Run */
	ip = &test;
	goto ***ip;
	
//	name:	puts("name");
//		{
//		    int flag = 1;
//		    char name[]="test";
//		    char *in = POP(stack);
//		    for(int i=0; in[i]!=' ' && in[i]!='\0'; i++){
//		    	if(in[i] != name[i]) {
//		    	    flag = 0;
//		    	}
//		        putchar(in[i]);
//		    }
//		}	

	call:	puts("call");
		PUSH(rstack, ip);
		ip = *ip;
		NEXT;
	
	retrn:	puts("return");
		ip = POP(rstack);
		NEXT;

	bye:	puts("bye");
		return 0;

	compile:puts("compile");

	def:   puts("def");
	       DEFINE(POP(stack));

	input: puts("input");
	       gets(mem);
	       mem += sizeof(strlen(mem)+1);
	       NEXT;

	parse: puts("parse");
	       ip = dict;
	       goto ***ip;


}
