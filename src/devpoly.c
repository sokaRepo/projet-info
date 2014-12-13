#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "devpoly.h"

void createDevPoly(dev *pl)
{
	int nombre;
	int i=0;
	//printf("BEGIN creer 1\n");
	dev l= (*pl) = malloc(sizeof(developpe));
	//printf("BEGIN creer 2\n");
	l->next=NULL;
	//printf("BEGIN creer 3\n");
	dev queue=malloc(sizeof(developpe));
	queue=l;
	queue->pow=1;
	queue->coeff=2;
	nombre=3;
	for (i=2; i<6; i++)
	{
		//printf("i = %d\n", i);
		//printf("a\n");
		queue->next=malloc(sizeof(developpe));
		queue=queue->next;
		queue->pow=i;
		queue->coeff=nombre;
		queue->next=NULL;
		nombre++;
	}
}

void printDevPoly(dev l)
{
	//int i;
	while (l != NULL)
	{
		printf ("%dX^%d+", l->coeff, l->pow);
		l=l->next;
		if(l->next == NULL) {
			printf ("%dX^%d", l->coeff, l->pow);
			l=l->next;
		}

	}
	printf("\n");
}