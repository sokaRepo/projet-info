#ifndef POLY
#define POLY

	
typedef struct developpe{
	float img;
	float real;
	int coeff;
	int pow;
	struct developpe *next;
}developpe;

typedef developpe * dev;

typedef struct factorise{
	float img;
	float real;
	float coeff;
	struct factorise *next;
}factorise;

typedef factorise * fact;

typedef struct polynome{
	struct factorise factorise;
	struct developpe developpee;
}polynome;

#endif