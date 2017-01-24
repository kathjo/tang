#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "tang.h"

typedef union{
	unsigned long int i;
	double d;
} value_t;

double besseresfabs(double a){
	if(a >= 0.0){
		return a;
	} else {
		return -a;
	}
}

int main(int argc, char *argv[]){

	value_t x[1000000];
	value_t a;
	value_t b;
	value_t current_error;

	int errors = 0;
	double max_error = 0;
	int biggest = -1;
	//double current_error;

	srand(time(NULL));

	double ln2 = log(2.0);

	double bound[6];
	bound[0] = 0x1.0p-14;
	bound[1] = ln2/64;
	bound[2] = 2 * ln2 - ln2/64;
	bound[3] = 20 * ln2 - 2 * ln2/64;
	bound[4] = 1010 * ln2 - 20 * ln2;
	bound[5] = 1024 * ln2 - 1010 * ln2;

	double offset[6];
	offset[0] = 0;
	offset[1] = 0;
	offset[2] = ln2/64;
	offset[3] = 2 * ln2/64;
	offset[4] = 20 * ln2;
	offset[5] = 1010 * ln2;


	for(int n = 0; n<6; n++){
		for(int i = 0; i<1000000; i++){
			if(i < 500000){
				x[i].d = (((double)rand()/(double)(RAND_MAX)) * bound[n]) + offset[n];
			} else{
				x[i].d = - (((double)rand()/(double)(RAND_MAX)) * bound[n]) - offset[n];
			}
			if(exp(x[i].d) != tang(x[i].d)){
				//printf("%.16lf\n%.16lf\n%.16lf\n\n", x[i].d, exp(x[i].d), tang(x[i].d));
				//a.d = exp(x[i].d);
				//b.d = tang(x[i].d);
				//printf("%lf\n%lx\n%lx\n\n", x[i].d, a.i, b.i);
				//return 0;
				current_error.d = fabs(fabs(exp(x[i].d)) - fabs(tang(x[i].d)));

				if(current_error.d > max_error){
					max_error = current_error.d;
					biggest = i;	
				}
				//printf("current error is: %.16lf\n\n\n", current_error.d );
				errors++;
			}
		}
		
		printf("completed bound nr.%i \n", n );
		printf("%i errors \n", errors );
		printf("max error is: %.16lf\n", max_error );
		if(biggest == -1){ return 0;}
		printf("for: %.16lf\n", x[biggest].d );
		printf("biggest: %i \n\n", biggest );
		printf("exp: %.16lf\n\n", exp(x[biggest].d) );
		printf("tang: %.16lf\n\n\n", tang(x[biggest].d) );
		a.d = exp(x[biggest].d);
		b.d = tang(x[biggest].d);
		printf("exp : %.16lx\n\n", a.i );
		printf("tang: %.16lx\n\n\n\n", b.i );
		max_error = 0;
		errors = 0;
	}


	return 0;
}