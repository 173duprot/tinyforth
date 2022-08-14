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
	void ***      ip = ALLOC(void **[20]);  // Instruction Pointer
	char *        in = ALLOC(char   [80]);  // Input Buffer
	long *     stack = ALLOC(long   [10]);  // Stack
	void ***  rstack = ALLOC(void  *[10]);  // Return Stack
	void **     dict = ALLOC(void  *[10]);  // Dictionary Stack
	
	/* Core Words*/
	void *      call = && call;
	void *     retrn = && retrn;
	void *       bye = && bye;
	void *     shell = && shell;
	void *    lookup = && lookup;
	
	/* Secondary Words */
	void **end[]	= { call, &lookup };
	void **test[]	= { call, &shell, &retrn };
	
	/* Filling The Dictionary */
	PUSH(dict, test);
	
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
	
	bye:	puts("bye");
		return 0;

	shell:	putchar('>');
		PUSH(rstack, in);
		do {
			in++;
			*in = getchar();
		} while(*in != '\n');
		POP(rstack, in);
		NEXT;

	lookup:	puts("lookup");
		NEXT;
}
