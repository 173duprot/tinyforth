#include	"../io.h"

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
	
	/* Pointers */
	void *      QUIT = &&quit;
	void *      TEST = &&test;
	void *     RETRN = &&retrn;
	
	/* Direct Words */
	void *      quit = &QUIT;
	void *      test = &TEST;
	void *     retrn = &RETRN;

	/* Indirect Words */
	void *INDIRECT[] = { &&call, test, retrn };
	void *indirect   = &INDIRECT;
	
	/* Init */
	void *ex[] = { indirect, quit }; 
	ip = &ex;
	goto ***ip;


	/* Code */

	quit:	return 0;

	test:	puts("success");
		NEXT(++);

	call:	PUSH(rstack, ip);
		ip = *ip;	
		NEXT(++);

	retrn:	ip = POP(rstack);
		NEXT(++);
}
