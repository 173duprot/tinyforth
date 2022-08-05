#include <stdio.h>
#include <string.h>

// ha

// Main Memory
char memory[100000];
char *mem = memory;
		
#define ALLOC(x)			\
		mem;			\
		mem += sizeof(x);	\

#define NEXT 				\
		(*ip)=(*nip);		\
		(*nip)++;		\
		goto **(*ip);		\

#define PUSH(x,sp)	*(sp) = (x); (sp)++;
#define POP(sp)		*((sp)--);
		
int main() {
	
	// Instruction Pointer
	void	****ip	= (void ****)	ALLOC(void ***);
	void	****nip	= (void ****)	ALLOC(void ***);
	
	// Stack
	long	**sp 	= (long **)	ALLOC(long *);
		*sp 	= (long *)	ALLOC(long[10]); 
	
	// Return Stack
	void	***rsp 	= (void ***)	ALLOC(void **);
		*rsp 	= (void **)	ALLOC(void *[10]);
	
	// Dictonary Stack
	void	***dsp 	= (void ***)	ALLOC(void **);
		*dsp 	= (void **)	ALLOC(void * [10]);
	
	/* Memory */
	void *bye		= &&bye;
	void *code		= &&code;
	void *exit		= &&exit;
	void **subword[]	= { &&docol, &code, &exit };
	void **word[]		= { &&docol, &subword, &bye };
	*nip = word;
	NEXT;
	
	docol:
		PUSH(*nip, *rsp);

		/* set nip to the next thing and run it */
		(*nip)	= *(*ip + 1); 
		NEXT;

	exit:
		*nip = POP(*rsp);
		NEXT;
	
	code:
		puts("Run Code");
		NEXT;
	
	bye:
		puts("bye");
		return 0;
}
