\ tinyforth

	Forth in under 100 lines of GNU C99.

Abstract

	Forth is a extremly powerful, typeless language, however, imo, its elegence
	is offen tainted by small, unelegent standard peices of code, which limit
	hackability in a way that simply isn't forth-like.
	
	For example, in regular forth, literals are quite literally baked into the
	interpriter, to the point where changing this behavior, adding debugigng 
	features, anything - would require special hooks, weird hacks, and general
	inconvient, uncomfortable and akward hacking.
	
	To me, this is very un-forth like.

	ABLEforth solves this issue by putting parsing words front and center stange,
	there is no built-in literals, all data-types are handled the same way. 
	
	Tinyforth takes ABLE's formula and expands upon it drastically - being
	unafraid to be completely non-standard in it's quest for simplicity and
	grockability.

Implimentation
	
	Forth itself is essentially a group of memory structures that create the
	illusion of a programming language.

	Tinyforth has 3 structures:
		|
		| long stack[100];
		| 	|
		| 	| This is the stack that holds numbers.
		| 	|
		| 	| Every time you type in a value, or have a value returned
		| 	| it's off this stack.
		| 	
		| 	
		| void *return_stack[100];
		| 	|
		| 	| This is the stack that holds return addresses. 
		| 	| 
		| 	| Every time you run code
		| 	|	1. Save current code-pointer on the return stack
		| 	|	2. Jump to new code
		| 	|	3. Run
		| 	|	4. Jump back to code-pointer on the return stack
		| 	
		| 	
		| dict_t dictionary_stack[50];
		| 	|
		| 	| This is a key:value namespace stack.
		| 	| 
		| 	| It follows this structure
		| 	|	---------------
		| 	|	char name[100];
		| 	|	void* code; 
		| 	|	---------------
		| 	| 
		| 	| Every time you run any code,
		| 	|
		| 	|	0. Look up the {name:code}
		| 	|
		| 	|	1. Save current code pointer on the return stack
		| 	|	2. Jump to new {*code}
		| 	|	3. Run
		| 	|	4. Jump back to code-pointer on the return stack
