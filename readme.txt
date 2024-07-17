\ tinyforth -- Forth in under 100 lines of GNU C99.


Run
	
	gcc -fpermissive -w forth.c


Abstract

	Forth is a extremly powerful, typeless language,
	however, imo, its elegence is offen tainted by
	small, unelegent, standard practices, which limit
	hackability in a way that simply isn't forth-like.
	
	For example, in regular forth, literals are quite
	literally baked into the interpriter, to the point
	where changing this behavior, adding debugigng 
	features, anything - would require special hooks,
	and weird hacks.
	
	To me, this is very un-forth like.

	ABLEforth solves this issue by putting parsing
	words front and center stage, there is no built-in
	literals, all data-types are handled the same way. 
	
	Tinyforth takes ABLE's formula and expands upon it,
	being unafraid to be completely non-standard in
	it's quest for simplicity and elegance.


Implimentation
	
	Forth itself is essentially a group of memory structures that create the
	illusion of a programming language.

	Tinyforth has 3 structures:
		
		long *stack[10];

			| This is the stack that holds numbers.
			|
			| Every time you type in a value, or have a value returned
			| it's off this stack.
			
			
		void *return_stack[100];

			| This is the stack that holds return addresses. 

			| Every time you run code
			|	1. Save current code-pointer on the return stack
			|	2. Jump to new code
			|	3. Run
			|	4. Jump back to code-pointer on the return stack

			
			
		void*** dict[100];

			| This is a code pointer stack
			| It has the same composition as an indirect word.

			| Every time you run any code,
			|
			|	0. Start Running the Dictionary
			|	1. When a word matches the current word
			|		- Compiled words will push their address to mem
			|		- Macro words will run immediatly
			|	2. When a \n or \0 is hit, it will close off the
			|	   memory space and then run the compiled code


Diffrences from normal Forth
	
	Dictionary stack

		Tinyforth's dictionary is far more extinsable than a traditional
		forth. It uses a code pointer stack that grows backwards,
		rather than a linked list. With a "call" word placed at the top. 

		This means that all we need to do is point `ip` to the top of the
		stack (dict), and run, and it will run lookup automatically.
		
		[][][][call][A][B][C][return]
		       ^dict

		Tinyforth also has a very diffrent method of lookup than other
		forth's. The lookup actually executes code within the words,
		allowing you to not only script the runtime, like ABLE does,
		but also allowing you to script the dictionary itself.

		The search is not performed by a singular program, but
		rather the words checking themselves, then passing onto
		the next word in the dictionary. This barely affects runtime
		performance (adding in a few extra jumps), while also allowing 
		extremely powerful meta-scripting.

		For example, you could have a word that simply ends the dictionary
		search, allowing you to have completely local scope.

		You could also pass on to a custom dictionary, allowing you to
		essentially hijack the search, completely changing the entire
		language instantly.

		This dramatically shifts the entire forth meta-programming
		experience, while also dramatically simplifying the implimentation.


INNER INTERPRITER

	NOTES

		1. Please follow along with the simplified code in ./misc/inner-interpriter.c

		2. [&&x] syntax is "lables as values" gcc exstention.

	Words
		
		Words are running code through a double redirect.

			[word] -> [&&word] -> [code]

		You run this by 
		
			> goto ***word
				
				> (code)

	Direct Threading
		
		Direct threading is an array of words.

			[a][b][c]
		
		Itterating over them using a pointer.
	
			[a][b][c]
			 ^ip

		You run this just the same, but the (code) now has
		itteration and a goto at the end.

			> goto ***ip
			
			    [a]
				> (code)
				> ++ip;		// Itterate
				> goto ***ip 	// Run B

			    [b]
				> (code)
				> ++ip;		// Itterate
				> goto ***ip;	// Run C
				
				etc...

		The NEXT(xx) macro is shorthand for the itterate-run structure.

			ie. NEXT(++) -> goto ***(++ip)


	Indirect threading 


		Indirect threading is an array of arrays.

			[a][b][c]

			[a] -> [x][y][z]


		Using a stack to keep track of instruction pointer positions.

			[a] -> [ . . . ]	
			 ^ip 			*push()

			[a] -> [ . . . ]	
			        ^ip...^ip 	*runs

			[a] -> [ . . . ]
			 ^ip 			*pop()
			
			

		By putting a special code at the beginning and end of the array.

			[a] -> [&&push] [...] [pop]
		


		You still run this just the same.

			> goto ***ip

			     [&&push]

				> PUSH(rstack, ip) // Save ip current posision
				> ip = *ip;        // Change the frame of refrence
				> NEXT(++)	   // Run [...]
				
		             [...]
				> (...)
				> (...)
				> (...)

			     [pop]
				> ip = POP(rstack) // Resets the old ip
				> NEXT(++)	   // Run B


License

	This is free and unencumbered software released into the public domain.
	
	Anyone is free to copy, modify, publish, use, compile, sell, or
	distribute this software, either in source code form or as a compiled
	binary, for any purpose, commercial or non-commercial, and by any
	means.
	
	In jurisdictions that recognize copyright laws, the author or authors
	of this software dedicate any and all copyright interest in the
	software to the public domain. We make this dedication for the benefit
	of the public at large and to the detriment of our heirs and
	successors. We intend this dedication to be an overt act of
	relinquishment in perpetuity of all present and future rights to this
	software under copyright law.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
	OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
	
	For more information, please refer to <http://unlicense.org/>
