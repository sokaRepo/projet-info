#include <stdio.h>
#include <stdlib.h>

#include "src/struct.h"
#include "src/createlist.h"
#include "src/operations.h"
#include "src/printlist.h"
#include "src/debug.h"



int main ()
{
	
	dev poly1;
	dev poly2;
	dev poly3; // poly1 + poly2
	createComplexPoly(&poly1);
	createComplexPoly(&poly2);
	printf("---------------------------\n");
	red("Before operations");
	printf("---------------------------\n");
	printf("1st poly: \n");
	printComplexPoly(poly1, 1);
	printf("2nd poly: \n");
	printComplexPoly(poly2, 2);
	printf("---------------------------\n");
	red("After operations");
	printf("---------------------------\n");
	
	sortF(&poly1);
	//printComplexPoly(poly1, 1);
	//printf("------- Add Mono ----------\n");
	if(addMonomial(&poly1)) 
		printf("1st poly (with modif): \n");	
	else
		printf("1st poly: \n");
	printComplexPoly(poly1, 1);

	sortF(&poly2);
	//printf("------- Add Mono ----------\n");
	//printComplexPoly(poly2, 2);
	if(addMonomial(&poly2))
		printf("2nd poly (with modif): \n");
	else
		printf("2nd poly: \n");
	printComplexPoly(poly2, 2);

	printf("----------------------------\n");
	soustractPoly(poly1, poly2, &poly3);
	red("Result poly add:");
	printf("---------------------------\n");
	printComplexPoly(poly3, 3);
	/*
	fact poly1;
	createComplexPolyFact(&poly1);
	printf("Poly 1:\n");
	printComplexPolyFact(poly1);
	*/
	return 0;
}