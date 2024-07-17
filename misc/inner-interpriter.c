//----------------------------------------------------------------------------//
#include "io.h"

// Main Memory
char xxxx[100000];
char *mem = xxxx;

#define NEXT(xx)	goto ***(xx ip)
#define ALLOC(x) 	((mem+=sizeof(x))-sizeof(x))
#define PUSH(ptr,x)     *(ptr++)  = x
#define POP(ptr)        *(--ptr)

int main() {
	
	/* Memory */
	void ***  ip;						// Instruction Ptr
	long *    stack  = ALLOC(long    [10]);			// Stack
	void ***  rstack = ALLOC(void   *[10]);			// Return Stack
	
	/* Direct Words*/
	void *      call = && call;
	void *     retrn = && retrn;
	void *      quit = && quit;
	void *     input = && input;
	void *     print = && print;
	
	/* Indirect Words */
	void **indirect[]	= { call, &input, &print, &retrn };
	
	/* Init */

	void **array[]		= { &indirect, &quit };
	ip =  &array;
	goto ***ip;

	/* Code */

	call:	puts("-> call");	// Call -> Creates local scope.
		PUSH(rstack, ip);
		ip = *ip;
		NEXT(++);
	
	retrn:	puts("-> return");	// Retrn -> Exists local scope.
		ip = POP(rstack);
		NEXT(++);
	
	quit:	puts("-> quit");	// Quit -> Kills program.
		return 0;

	input: puts("-> input");
	       gets(mem);
	       PUSH(stack, ALLOC( strlen(mem)+1 ) );
	       NEXT(++);

	print: puts("-> print");
	       puts(POP(stack));
	       NEXT(++);
	
}
