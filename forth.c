//----------------------------------------------------------------------------//
//#include "io.h"
#include "match.h"
#include <stdio.h>
#include <string.h>

// Main Memory
char xxxx[100000];
char *mem = xxxx;	
		
#define NEXT(xx)	goto ***(xx ip)
#define ALLOC(ptr,x) 	((ptr+=sizeof(x))-sizeof(x))
#define PUSH(ptr,x)     *(--ptr)  = x
#define POP(ptr)        *(ptr++)

int main() {
	/* Memory */
	void ***   ip;                                            // Instruction Ptr
	void ****  dict   = ALLOC(mem, void ***[100]); dict += 100;  // Dictionary
	long *     stack  = ALLOC(mem, long    [10]); stack += 10;   // Stack
	void ***   rstack = ALLOC(mem, void   *[10]); rstack+= 10;   // Return Stack
	
	/* Core Words*/
	void *       call = && call;
	void *      retrn = && retrn;
	void *       quit = && quit;
	void *      input = && input;
	void *      print = && print;
	
	/* Secondary Words */
	void **indirect[] = { call, &input, &print, &retrn };
	void **test[]     = { &indirect, &quit };
	
	/* Filling The Dictionary */
	PUSH(dict, &test);
	/* Run */
	goto parse;
        
//   defcall:   match(stack, "call") ? ALLOC(mem, ptr) : NEXT(++);
	call:	puts("-> call");	// Call -> Creates local scope.
		PUSH(rstack, ip);
		ip = *ip;
		NEXT(++);
        
	retrn:  puts("-> return");	// Retrn -> Exists local scope.
		ip = POP(rstack);
		NEXT(++);
         
	quit:   puts("-> quit");	// Quit -> Kills program.
	        return 0;
         
	def:    puts("-> def");
	        PUSH(dict, POP(stack));
	        NEXT(++);
        
        parse:  puts("-> parse");
	        ip = *dict;
	        NEXT();
         
	input:  puts("-> input");
	        gets(mem);
	        PUSH(stack, ALLOC(mem, strlen(mem)+1));
	        NEXT(++);
         
	print:  puts("-> print");
	        puts(POP(stack));
	        NEXT(++);
}
