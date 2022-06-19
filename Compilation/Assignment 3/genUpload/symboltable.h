#ifndef __SYMBOLTABLE_H
#define __SYMBOLTABLE_H 1

/*  interface to symbol table.  */

struct symbol { // entry in symbol table 
    char name[NSIZE];
	enum type type;
	struct symbol *next; // points to next symbol in list of symbols
	                     // having the same hash value
};

/* return pointer to entry in symbol table for 'name'.
   If 'name' is not in the table then NULL is returned
*/
struct symbol *lookup(const char *name);

/* put 'name' (and its type) in symbol table
   returns:  pointer to the new entry
             If name is already in the table then NULL is returned.
			 If insufficient memory was available then
			 the program is aborted.
*/
struct symbol *putSymbol(const char *name, enum type t);


#endif // not defined __SYMBOLTABLE_H
