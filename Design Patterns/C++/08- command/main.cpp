#include "calculator.h"

void main()
{
	Calculator calc;

	calc.compute('+' , 5);	
	calc.compute('*' , 2.5);
	calc.compute('-' , 4);
	calc.compute('/' , 2);

	calc.undo(2);
	calc.undo(1);
	calc.redo(3);
	calc.redo(1);
}