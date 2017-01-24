#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef union{
	long int i;
	double d;
} value_t;



int main(){

	value_t x;
	x.i = 0x40862E2CC5A01975;

	value_t inv_L;
	inv_L.i = 0x40471547652B82FE;

	if (x.d * inv_L.d >= 0x1.0p52 || x.d * inv_L.d <= -0x1.0p52){
		printf("is not in bounds\n");
	}else{
		printf("is in bounds\n");
	}
	return 0;
}