#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "operations.h"
#include "debug.h"
#include "printlist.h"


/*
@ Nom: getPolyLength
@ Objectif: retourne le nombre de maillon d'une LSC

*/

int getPolyLength(dev poly) {
	int count = 0;
	while(poly) {
		count++;
		poly = poly->next;
	}
	return count;
}

/*
@ Nom: swap_p
@ Objectif: échange de place les 2 monômes passés en argument

*/
void swap_p(dev *p1, dev *p2) {
	int tmp_pow;
	float tmp_real, tmp_img;
	// On sauvegarde la puissance, la partie réelle et img du 1er monôme
	tmp_pow = (*p1)->pow;
	tmp_img = (*p1)->img;
	tmp_real = (*p1)->real;

	// On place le 1er monome à la place du 2nd
	(*p1)->pow = (*p2)->pow;
	(*p1)->img = (*p2)->img;
	(*p1)->real = (*p2)->real;

	// On place le 2nd à la place du 1er
	(*p2)->pow = tmp_pow;
	(*p2)->img = tmp_img;
	(*p2)->real = tmp_real;

}

/*
@ Nom: sortF
@ Objectif: trie les monômes d'un polynôme afin d'avoir les monômes en ordre croissant
			Le trie se base sur la puissance du monôme: (1 + 2i)Z^4 + (3 - i)Z^1 => on inverse

*/
void sortF(dev *poly) {
	dev tmp = *poly;
	int len = getPolyLength(tmp);
	int i, n;

	// On conserve l'adresse du 1er monôme/maillon
	dev save = *poly;

	// Le monôme à comparer avec son précédent (stocké dans tmp plus haut)
	dev cmp = tmp->next;

	/*
		On effectue 2 boucles (basé sur la longueur de la LSC) pour être sûr d'effectuer un tri complet
	*/
	for(i=0; i<len-1; i++) {
		for(n=0; n<len-1; n++) {
			if(cmp->pow < tmp->pow) {
				//printf("[DEBUG] Change %d and %d\n", cmp->pow, tmp->pow);
				swap_p(&cmp, &tmp);
			}
			// On compare les 2 monômes suivant
			cmp = cmp->next;
			tmp = tmp->next;
		}
		/*
			On est arrivé à la fin de la LSC, on se replace au début pour effectuer un nouveau tri
		*/
		tmp = save;
		cmp = tmp->next;
	}

	/*
		Les monômes du polynome sont ordonnés croissant !
	*/
}


/*
@ Nom: addMonomial, retourne 1 si une modification a été apportée au polynome
@ Objectif: si 2 monômes ont la même puissance on les additionne
			Ex: (2 + 3i)Z^2 + (1 + 2i)Z^2 => (3 + 5i)Z^2

*/
int addMonomial(dev *poly) {
	// monôme courrant
	dev curr = *poly;
	int len = getPolyLength(curr);

	// monôme suivant
	dev cmp = curr->next;
	dev save = *poly;
	int i;
	int flag=0;
	for(i=0; i<len; i++) {
		while(curr->next) {
			if(curr->pow == cmp->pow) {
				//printf("OK %d - %d\n", curr->pow, cmp->pow);
				curr->img += cmp->img;
				curr->real += cmp->real;
				curr->next = cmp->next;
				free(cmp);
				flag = 1;
				//printComplexPoly(save, 0);
			}
			if(curr->next) {
			curr = curr->next;
			cmp = curr->next;
			}
			else break;
			//printf("OK\n");
		}
		//printf("OK\n");
		//if(getPolyLength(save) == 1) break;
		curr = save;
		cmp = curr->next;
		i++;
	}
	return flag;
}



/*
@ Nom: cleanNullMonomial
@ Objectif: supprime les monômes nuls <=> si partie img == 0 et partie réelle == 0 on supprime le monôme

*/
void cleanNullMonomial(dev *poly) {
	dev tmp = *poly;
	dev curr = *poly;
	dev next = curr->next;

	if(!tmp) return ;
	if(tmp->img == 0 && tmp->real == 0) {
		*poly = tmp->next;
		tmp = *poly;
	}
	if(!tmp) return ;
	while(next->next) {
		if(next->img == 0 && next->real == 0) {
			curr = curr->next = next->next;
			free(next);
			next = curr->next;
		}
		else {
			curr = curr->next;
			next = next->next;
		}

	}
	
}


void addPoly(dev poly1, dev poly2, dev * result) {
	dev polyResult = (*result) = malloc(sizeof(dev));
	polyResult->next = NULL;
	*result = polyResult;

	while(poly1 && poly2) {
		if(poly1->pow > poly2->pow) {
			polyResult->pow = poly1->pow;
			polyResult->img = poly1->img;
			polyResult->real = poly1->real;
			poly1 = polyResult->next;
		}
		else if(poly1->pow < poly2->pow) {
			polyResult->pow = poly2->pow;
			polyResult->img = poly2->img;
			polyResult->real = poly2->real;
			poly2 = polyResult->next;	
		}
		else {
			polyResult->pow = poly1->pow;
			if(poly1->img + poly2->img == 0)
				polyResult = NULL;
			else
				polyResult->img = poly1->img + poly2->img;
			polyResult->real = poly1->real + poly2->real;
			poly1 = poly1->next;
			poly2 = poly2->next;
		}

		if(poly1 && poly2) {
            polyResult = polyResult->next = malloc(sizeof(dev));
            polyResult->next = NULL;
        }
	}
	//printf("OK\n");
	cleanNullMonomial(&polyResult);

	
}

void multiplyPoly(dev poly1, dev poly2, dev * result) {
	dev polyResult = (*result) = malloc(sizeof(dev));
	polyResult->next = NULL;
	*result = polyResult;

	while(poly1 && poly2) {
		if(poly1->pow > poly2->pow) {
			polyResult->pow = poly1->pow;
			polyResult->img = poly1->img;
			polyResult->real = poly1->real;
			poly1 = polyResult->next;
		}
		else if(poly1->pow < poly2->pow) {
			polyResult->pow = poly2->pow;
			polyResult->img = poly2->img;
			polyResult->real = poly2->real;
			poly2 = polyResult->next;	
		}
		else {
			polyResult->pow = poly1->pow;
			polyResult->img = poly1->img * poly2->img;
			polyResult->real = poly1->real * poly2->real;
			poly1 = poly1->next;
			poly2 = poly2->next;
		}

		if(poly1 && poly2) {
            polyResult = polyResult->next = malloc(sizeof(dev));
            polyResult->next = NULL;
        }
	}
	cleanNullMonomial(&polyResult);
	
}

void soustractPoly(dev poly1, dev poly2, dev * result) {
	dev polyResult = (*result) = malloc(sizeof(dev));
	polyResult->next = NULL;
	*result = polyResult;

	while(poly1 && poly2) {

		if(poly1->pow > poly2->pow) {
			polyResult->pow = poly1->pow;
			polyResult->img = poly1->img;
			polyResult->real = poly1->real;
			poly1 = poly1->next;
		}
		else if(poly1->pow < poly2->pow) {
			polyResult->pow = poly2->pow;
			polyResult->img = poly2->img;
			polyResult->real = poly2->real;
			poly2 = poly2->next;	
		}
		else {
			polyResult->pow = poly1->pow;
			polyResult->img = poly1->img - poly2->img;
			polyResult->real = poly1->real - poly2->real;
			poly1 = poly1->next;
			poly2 = poly2->next;
		}
		if(poly1 && poly2) {
            polyResult = polyResult->next = malloc(sizeof(dev));
            polyResult->next = NULL;
        }

	}
	printComplexPoly(polyResult, 0);
	cleanNullMonomial(&(*result));
	
}



void dividePoly(dev poly1, dev poly2, dev * result) {
	dev polyResult = (*result) = malloc(sizeof(dev));
	polyResult->next = NULL;
	*result = polyResult;

	while(poly1 && poly2) {
		if(poly1->pow > poly2->pow) {
			polyResult->pow = poly1->pow;
			polyResult->img = poly1->img;
			polyResult->real = poly1->real;
			poly1 = polyResult->next;
		}
		else if(poly1->pow < poly2->pow) {
			polyResult->pow = poly2->pow;
			polyResult->img = poly2->img;
			polyResult->real = poly2->real;
			poly2 = polyResult->next;	
		}
		else {
			polyResult->pow = poly1->pow;
			polyResult->img = poly1->img / poly2->img;
			polyResult->real = poly1->real / poly2->real;
			poly1 = poly1->next;
			poly2 = poly2->next;
		}

		if(poly1 && poly2) {
            polyResult = polyResult->next = malloc(sizeof(dev));
            polyResult->next = NULL;
        }
	}
	cleanNullMonomial(&polyResult);
	
}