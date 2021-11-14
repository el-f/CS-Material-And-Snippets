/*
 * macros.h
 *
 *  Created on: Nov 7, 2018
 *      Author: efrath
 */

#ifndef MACROS_H_
#define MACROS_H_

#define HALFOF(x)  (x)/2
#define AVG5(n1, n2, n3, n4, n5)  ((n1)+(n2)+(n3)+(n4)+(n5))/5.0F
#define MAX(x, y)    (x) > (y) ? (x) : (y)
#define MIN(x, y)    (x) < (y) ? (x) : (y)
#define SQUARE(x)    (x)*(x)
#define SUM(x, y)    (x)+(y)
#define PRINT(s)    printf(#s"\n");

#endif /* MACROS_H_ */
