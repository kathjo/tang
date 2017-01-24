#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tang.h"

typedef union{
	unsigned long long int i;
	long double d;
} value_l;

int main(){
	long double c;
	long double e;
	double f,g;
	long double fl;
	value_l a;
	f  = -0.0129538740849641;
	fl = (long double) f;
	e = expl(fl);
	g = tang(f);;
	c = fabsl(fabsl(e) - (long double)fabsl(g));
	a.d = c;
	//d.i = a.i - b.i;
	//printf("%lx\n", c.i);
	printf("%.18llf\n", a.d);
	printf("%llx\n", a.i);
	//printf("%lx\n", d.i);

}

//something is wrong, maybe you need a new conversion method


//vieleicht kannst du double zu long double casten, die position müsste ja erhalten bleiben, 
//das  sollte dir auch die richtige differenz berechnen können