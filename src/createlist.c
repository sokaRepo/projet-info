#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "struct.h"
#include "createlist.h"



float genRandNb() {
	srand(time(NULL));
	return (float)(rand() % 10);
}

void createComplexPoly(dev *pl)
{
	int i=0;
	time_t t;
	srand((unsigned) time(&t));
	//printf("BEGIN creer 1\n");
	dev l= (*pl) = malloc(sizeof(developpe));
	//printf("BEGIN creer 2\n");
	l->next=NULL;
	//printf("BEGIN creer 3\n");
	dev queue=malloc(sizeof(developpe));
	queue=l;
	queue->pow=(rand() % 1);
	queue->img = (float)(rand() % 1);
	queue->real=(float)(rand() % 1);
	for (i=2; i<6; i++)
	{
		queue->next=malloc(sizeof(developpe));
		queue=queue->next;
		queue->pow=(rand() % 1);
		queue->img=(float)(rand() % 1);
		queue->real=(float)(rand() % 1);
		queue->next=NULL;
	}
	sleep(1);
}
/*
void createComplexFromCmd(fact *poly) {
	fact queue, l;
	dev tmp = *poly;
	int i;
	int nbMonomes;
	printf("Enter number of monome");
	scanf("%d", &nbMonomes);
	if(nbMonomes <= 0) {
		printf("Un polynome vide a bien été créé\n");
		return ;
	}
	if(nbMonomes >= 1) {
		fact = (*poly) = malloc(sizeof(factorise));

	}
	for(i=0; i<nbMonomes; i++) {

	}
	
	if(x >= 0) {
		l = (*pl) = malloc(sizeof(node));
		l->info = x;
		l->next = NULL;
		queue = l;
	}
	printf("> ");
	scanf("%d", &x);
	while(x >= 0) {
		queue = queue->succ = malloc(sizeof(node));
		queue->info = x;
		queue->succ = NULL;
		printf("> ");
		scanf("%d", &x);
	}
	
}
*/

void createComplexPolyFact(fact *pl)
{
	int nombre;
	int i=0;
	//printf("BEGIN creer 1\n");
	fact l= (*pl) = malloc(sizeof(fact));
	//printf("BEGIN creer 2\n");
	l->next=NULL;
	//printf("BEGIN creer 3\n");
	fact queue=malloc(sizeof(fact));
	queue=l;
	queue->coeff=1;
	queue->img = 1;
	queue->real=2;
	nombre=3;
	for (i=2; i<6; i++)
	{
		//printf("i = %d\n", i);
		//printf("a\n");
		queue->next=malloc(sizeof(fact));
		queue=queue->next;
		queue->coeff=i;
		queue->img=nombre;
		queue->real=nombre;
		queue->next=NULL;
		nombre++;
	}
}