#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
/* gen.tab.h is required because it contains definitions
   that should appear before 'struct symbol' is defined in symboltable.h */
#include "gen.tab.h"  
#include "symboltable.h"

/* This file contains an implementation of a symbol table using 
   hashing. */

enum h {HASH_SIZE = 101 };

static
struct symbol *symboltable[HASH_SIZE];

/*  the hash function is from Kernighan and Ritchie's
    book "The C Programming Language".
*/
static  
unsigned hash(const char *s)
{
    unsigned hashval;
	for(hashval = 0; *s; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASH_SIZE;
}

/* return pointer to entry in symbol table for 'name'.
   If 'name' is not in the table then NULL is returned
*/
struct symbol *lookup(const char *name)
{
    for (struct symbol *sym = symboltable[hash(name)]; sym; sym = sym->next)
        if (!strcmp(name, sym->name))
            return sym;

    return NULL; 		
}

/* put 'name' (and its type) in symbol table
   returns:  pointer to the new entry
             If name is already in the table then NULL is returned.
			 If insufficient memory was available then
			 the program is aborted.
*/
struct symbol *putSymbol(const char *name, enum type t)
{
    struct symbol *sym = lookup(name);
 
    if (sym	!= NULL)
		return NULL;  // name is already in the table
	sym = (struct symbol *)malloc(sizeof(struct symbol));
	assert(sym != NULL);
	strcpy (sym->name, name);
	sym->type = t;
	
	unsigned hashval = hash(name);
    sym->next = symboltable[hashval];
    symboltable[hashval] = sym;
    return sym;	
}

