%code {
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include "utilities.h"
#include "symboltable.h"

typedef int TEMP;  /* temporary variable.
                       temporary variables are named t1, t2, ... 
                       in the generated code but
					   inside the compiler they may be represented as
					   integers. For example,  temporary 
					   variable 't3' is represented as 3.
					*/
  
// number of errors 
int errors = 0;					

extern int yylex (void);
void yyerror (const char *s);

static int newtemp(), newlabel();
void emit (const char *format, ...);
void emitlabel (int label);

/* stack of "exit labels".  An "exit label" is the target 
   of a goto used to exit a statement (e.g. a while statement or a 
   switch statement.)
   The stack is used to implement 'break' statements which may appear
   in while statements and in break statements.
   A stack is needed because such statements may be nested.
   The label at the top of the stack is the "exit label"  for
   the innermost while or switch statement currently being processed.
   
   Labels are represented here by integers. For example,
   label3 is represented by the integer 3.
*/

typedef intStack labelStack;
labelStack exitLabelsStack;

enum type currentType;  // type specified in current declaration

} // %code

%code requires {
    void errorMsg (const char *format, ...);
    enum {NSIZE = 100}; // max size of variable names
    enum type {_INT, _DOUBLE };
	enum op { PLUS, MINUS, MUL, DIV, PLUS_PLUS, MINUS_MINUS };
	
	typedef int LABEL;  /* symbolic label. Symbolic labels are named
                       label1, label2, ... in the generated code 
					   but inside the compiler they may be represented as
					   integers. For example,  symbolic label 'label3' 
					   is represented as 3.
					 */
    struct exp { /* semantic value for expression */
	    char result[NSIZE]; /* result of expression is stored 
   		   in this variable. If result is a constant number
		   then the number is stored here (as a string) */
	    enum type type;     // type of expression
	};
	
	struct caselist { /* semantic value for 'caselist' */
	    char switch_result[NSIZE]; /* result variable of the switch expression */
                   /* you will probably need to add another member
                         to this structure */				   
    };			   
	
} // code requires

/* this will be the type of all semantic values. 
   yylval will also have this type 
*/
%union {
   char name[NSIZE];
   int ival;
   double dval;
   enum op op;
   struct exp e;
   LABEL label;
   const char *relop;
   enum type type;
   struct caselist cl;
}

%token <ival> INT_NUM
%token <dval> DOUBLE_NUM
%token <relop> RELOP
%token <name> ID
%token <op> ADDOP MULOP INC


%token WHILE IF ELSE FOR SWITCH  CASE DEFAULT 
%token BREAK INT DOUBLE INPUT OUTPUT

%nterm <e> expression
%nterm <label> boolexp  start_label exit_label
%nterm <type> type
%nterm <name> idlist
%nterm <name> increment
/* %nterm <cl> caselist */

/* this tells bison to generate better error messages
   when syntax errors are encountered (these error messages
   are passed as an argument to yyerror())
*/
%define parse.error verbose

/* if you are using an old version of bison use this instead:
%error-verbose */

/* enable trace option (for debugging). 
   To request trace info: assign non zero value to yydebug */
%define parse.trace
/* formatting semantic values (when tracing): */
%printer {fprintf(yyo, "%s", $$); } ID
%printer {fprintf(yyo, "%d", $$); } INT_NUM
%printer {fprintf(yyo, "%f", $$); } DOUBLE_NUM

%printer {fprintf(yyo, "result=%s, type=%s",
            $$.result, $$.type == _INT ? "int" : "double");} expression


/* token ADDOP has lower precedence than token MULOP.
   Both tokens have left associativity.

   This solves the shift/reduce conflicts in the grammar 
   because of the productions:  
      expression: expression ADDOP expression | expression MULOP expression   
*/
%left ADDOP
%left MULOP

%%
program: declarations { initStack(&exitLabelsStack); } 
         stmtlist;

declarations: declarations decl;

declarations: %empty;

decl:  type idlist ';' {
	char* temp_s = strtok($2, ","); 
	while (temp_s != NULL) {
		if (lookup(temp_s) != NULL) {
			errorMsg("The symbol %s already exists\n", temp_s);
		} else {
			putSymbol(temp_s, $1);
		}
		temp_s = strtok(NULL, ","); 
	} 
};


type: INT    { $$= _INT;} |
      DOUBLE { $$ = _DOUBLE; };
	  
idlist:  idlist ',' {strcpy($1 + strlen($1), ","); } ID {strcpy($1 + strlen($1), $4); strcpy($$, $1);  } ;

idlist:  ID {strcpy($$, $1); };
			

stmt: assign_stmt |
      while_stmt  |
	  if_stmt     |
	  for_stmt    |
	  switch_stmt |
	  break_stmt  |
	  input_stmt  |
	  output_stmt |
	  block_stmt
	  ;

assign_stmt:  ID '=' expression ';' {
	struct symbol* id = lookup($1);
	if (id == NULL) {
		errorMsg("The symbol %s doesn't exist\n" , $1);
	} else {	//add casting by the ID type
		if (id->type == _INT && $3.type == _DOUBLE) {
			emit("%s = (int)%s\n", $1, $3.result); 
		} else if(id->type == _DOUBLE && $3.type == _INT) {
			emit("%s = (double)%s\n", $1, $3.result); 
		} else {
			emit("%s = %s\n", $1, $3.result);
		}
	}
};


expression : expression ADDOP expression {
	sprintf($$.result, "t%d", newtemp()); 
	int t;
	char c;

	if ($2 == PLUS)	c = '+';
	else			c = '-';

	if ($1.type == _INT && $3.type == _DOUBLE) {
		t = newtemp();
		emit("t%d = (double)%s\n", t, $1.result);
		emit("%s = t%d <%c> %s\n", $$.result, t, c, $3.result);
		$$.type = _DOUBLE;
	} else if ($1.type == _DOUBLE && $3.type == _INT) {
		t = newtemp();
		emit("t%d = (double)%s\n", t, $3.result);
		emit("%s = %s <%c> t%d\n", $$.result, $1.result, c, t);
		$$.type = _DOUBLE;
	} else if ($1.type == _DOUBLE && $3.type == _DOUBLE) {
		emit("%s = %s <%c> %s\n", $$.result, $1.result, c, $3.result);
		$$.type = _DOUBLE;
	} else {
		emit("%s = %s %c %s\n", $$.result, $1.result, c, $3.result);
		$$.type =_INT;
	}
};


expression : expression MULOP expression {
	sprintf($$.result, "t%d", newtemp()); 
	int t;
	char c;

	if ($2 == MUL )	c = '*';
	else			c = '/';

	if ($1.type == _INT && $3.type == _DOUBLE) {
		t = newtemp();
		emit("t%d = (double)%s\n", t, $1.result);
		emit("%s = t%d <%c> %s\n", $$.result, t, c, $3.result);
		$$.type = _DOUBLE;
	} else if($1.type == _DOUBLE && $3.type == _INT) {
		t = newtemp();
		emit("t%d = (double)%s\n", t, $3.result);
		emit("%s = %s <%c> t%d\n", $$.result, $1.result, c, t);
		$$.type = _DOUBLE;
	} else if($1.type == _DOUBLE && $3.type == _DOUBLE) {
		emit("%s = %s <%c> %s\n", $$.result, $1.result, c, $3.result);
		$$.type = _DOUBLE;
	} else {
		emit("%s = %s %c %s\n", $$.result, $1.result, c, $3.result);
		$$.type =_INT;
	}
};   
                  
expression :  '(' expression ')' { $$ = $2; }

		   |  ID         
		   {
				struct symbol* id = lookup($1); 
				if (id == NULL) {
					errorMsg("The symbol %s doesn't exist\n" , $1);
				} else {
					strcpy($$.result, $1); 
					$$.type= id->type;
				} 
		   	}
		   		            
		   |  INT_NUM    { sprintf($$.result, "%d", $1); $$.type =_INT; }
		   |  DOUBLE_NUM { sprintf($$.result, "%.2f", $1); $$.type = _DOUBLE; };

while_stmt: WHILE start_label '('  boolexp { push(&exitLabelsStack, $4); } ')' 
		stmt 
		{ 
			emit("goto label%d\n", $2);
			emitlabel($4);
		};
						 
start_label: %empty { $$ = newlabel(); emitlabel($$); };

boolexp:  expression RELOP expression 
		{
			$$ = newlabel();
			emit("ifFalse %s %s %s goto label%d\n", $1.result, $2, $3.result, $$);
       	};

if_stmt:  IF exit_label '(' boolexp ')' stmt
        { 
          	emit("goto label%d\n", $2);
          	emitlabel($4);
        }				 
          ELSE stmt
		{ 
			emitlabel($2);
		};
		  
exit_label: %empty { $$ = newlabel(); };


for_stmt: FOR '(' assign_stmt start_label boolexp { push(&exitLabelsStack, $5); } ';' increment ')' stmt {
	emit("%s\n", $8);
	emit("goto label%d\n", $4);
	emitlabel($5);			  
};


increment: ID INC {
	strcpy($$, $1);
	strcpy($$ + strlen($$), " = ");
	strcpy($$ + strlen($$), $1);
	strcpy($$ + strlen($$), (($2 == PLUS) ? " + " : " - "));
	strcpy($$ + strlen($$), "1");
};

switch_stmt:  SWITCH  
              caselist 
              DEFAULT ':' stmtlist 
			  '}' /* the matching '{' is generated by 'caselist' */
			  ;

caselist: caselist CASE INT_NUM ':' stmtlist;					  

caselist: '(' expression ')' '{' ;					                  
 
break_stmt: BREAK ';' {
	if (isEmpty(&exitLabelsStack)) {
		errorMsg("Error: break statment outside the loop\n");
	} else {
		emit("goto label%d\n", pop(&exitLabelsStack));
	}
};
			
			
input_stmt: INPUT '(' ID ')' ';' { 
	struct symbol* id = lookup($3);
	if(id == NULL) {
		errorMsg("The symbol %s doesn't exist\n" , $3);
	} else {
		if (id->type == _INT)	emit("read %s\n", $3);
		else					emit("<read> %s\n", $3);
	}
};
             
output_stmt: OUTPUT '(' expression ')' ';' { emit("write %s\n", $3.result); } ;
                
block_stmt:   '{'  stmtlist '}';

stmtlist: stmtlist stmt { emit("\n"); }
        | %empty
		;				
					 
%%
int main (int argc, char **argv)
{
  extern FILE *yyin; /* defined by flex */
  extern int yydebug;
  
  if (argc > 2) {
     fprintf (stderr, "Usage: %s [input-file-name]\n", argv[0]);
	 return 1;
  }
  if (argc == 2) {
      yyin = fopen (argv [1], "r");
      if (yyin == NULL) {
          fprintf (stderr, "failed to open %s\n", argv[1]);
	      return 2;
	  }
  } // else: yyin will be the standard input (this is flex's default)
  

  yydebug = 0; //  should be set to 1 to activate the trace

  if (yydebug)
      setbuf(stdout, NULL); // (for debugging) output to stdout will be unbuffered
  
  yyparse();
  
  fclose (yyin);
  return 0;
} /* main */

/* called by yyparse() whenever a syntax error is detected */
void yyerror (const char *s)
{
  extern int yylineno; // defined by flex
  
  fprintf (stderr,"line %d:%s\n", yylineno, s);
}

/* temporary variables are represented by numbers. 
   For example, 3 means t3
*/
static
TEMP newtemp ()
{
   static int counter = 1;
   return counter++;
} 


// labels are represented by numbers. For example, 3 means label3
static
LABEL newlabel ()
{
   static int counter = 1;
   return counter++;
} 

// emit works just like  printf  --  we use emit 
// to generate code and print it to the standard output.
void emit (const char *format, ...)
{
/*  /* uncomment following line to stop generating code when errors
	   are detected */
    /* if (errors > 0) return; */ 
    printf ("    ");  // this is meant to add a nice indentation.
                      // Use emitlabel() to print a label without the indentation.    
    va_list argptr;
	va_start (argptr, format);
	// all the arguments following 'format' are passed on to vprintf
	vprintf (format, argptr); 
	va_end (argptr);
}

/* use this  to emit a label without any indentation */
void emitlabel(LABEL label) 
{
    /* uncomment following line to stop generating code when errors
	   are detected */
    /* if (errors > 0) return; */ 
	
    printf ("label%d:\n",  label);
}

/*  Use this to print error messages to standard error.
    The arguments to this function are the same as printf's arguments
*/
void errorMsg(const char *format, ...)
{
    extern int yylineno; // defined by flex
	
	fprintf(stderr, "line %d: ", yylineno);
	
    va_list argptr;
	va_start (argptr, format);
	// all the arguments following 'format' are passed on to vfprintf
	vfprintf (stderr, format, argptr); 
	va_end (argptr);
	
	errors++;
}
