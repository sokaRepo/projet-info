#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "printlist.h"

void printComplexPoly(dev l, int nb)
{
	//int i;
	printf("P%d(Z) = ", nb);

	if(!l) {
		printf("0\n");
		return ;
	}

	while (l != NULL)
	{
		
		if(l->next == NULL) {
			printf ("(%lf - %lfi)Z^%d", l->real, l->img, l->pow);
			l=l->next;
		}else {
			printf ("(%lf - %lfi)Z^%d + ", l->real, l->img, l->pow);
			l=l->next;
		}

	}
	printf("\n\n");
}


void printComplexPolyFact(fact l)
{
	//int i;
	while (l != NULL)
	{
		
		if(l->real > 0 && l->img > 0) 
			printf ("(%lfz + %lfi + %lf)", l->real, l->img, l->coeff);
		else if(l->real < 0 && l->img < 0)
			printf ("(%lfz - %lfi - %lf)", l->real, l->img, l->coeff);
		else if(l->real > 0 && l->img < 0)
			printf ("(%lfz - %lfi + %lf)", l->real, l->img, l->coeff);
		else if(l->real < 0 && l->img > 0)
			printf ("(%lfz + %lfi - %lf)", l->real, l->img, l->coeff);
		else
			printf ("(%lfz)", l->coeff);
		l = l->next;
	}
	printf("\n");
}
