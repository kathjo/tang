#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "tang.h"
#include <stdint.h>
#include <string.h>






#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define for_endian(size) for (int i = 0; i < size; ++i)
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define for_endian(size) for (int i = size - 1; i >= 0; --i)
#else
#error "Endianness not detected"
#endif

#define printb(value)                                   \
({                                                      \
        typeof(value) _v = value;                       \
        __printb((typeof(_v) *) &_v, sizeof(_v));       \
})

void __printb(void *value, size_t size)
{
        uint8_t byte;
        size_t blen = sizeof(byte) * 8;
        uint8_t bits[blen + 1];

        bits[blen] = '\0';
        for_endian(size) {
                byte = ((uint8_t *) value)[i];
                memset(bits, '0', blen);
                for (int j = 0; byte && j < blen; ++j) {
                        if (byte & 0x80)
                                bits[j] = '1';
                        byte <<= 1;
                }
                printf("%s", bits);
        }
        printf("\n");
}





int shifting(long double h, long double g) {

        __uint128_t g_cast = *(__uint128_t*) &g;
        __uint128_t h_cast = *(__uint128_t*) &h;
       
        __uint128_t mask1 = 1;
        mask1 = (mask1 << 64) -1;
        //printb(mask1);
        //printb(g_cast);
        //printb(h_cast);

        g_cast = g_cast & mask1;
        h_cast = h_cast & mask1;

        //printb(g_cast);
        //printb(h_cast);

        __uint128_t mask2;

        mask2 = 1;
        mask2 <<= 127;

        //printb(mask2);

        __uint128_t g_test;
        __uint128_t h_test;
        

        int a = 0;

        for (int i = 0; i <= 127; ++i)
        {
                g_test = g_cast & (mask2 >> i);
                h_test = h_cast & (mask2 >> i);
                if(g_test != h_test){
                        a = 128 - i;
                        break;
                }
        }
        return a;
}



typedef union{
	__uint64_t i;
	double d;
} value_t;

__uint128_t ulp_func(double unprecice, long double g ){

    long double h = (long double) unprecice;
    //int a = shifting(h, g);
        
	__uint128_t mask1 = 1;
	mask1 = (mask1 << 64) -1;
	//__uint128_t mask2 = (1 << a) -1;

    __uint128_t unprecice_cast = *(__uint128_t*) &unprecice;
    __uint128_t dd_ulp;
	dd_ulp = mask1 & unprecice_cast;
    

    __uint128_t difference;
    __uint128_t g_cast = *(__uint128_t*) &g;

    __uint128_t g_end = mask1 & g_cast;


    if(unprecice_cast >= g_cast ) {
        difference = unprecice_cast - g_cast;
    }else{
        difference = g_cast - unprecice_cast;
    }

    //double b,ulp;

    //b = (double) difference;
    //ulp = b * pow(2,-11);

    //return ulp;

    return difference;

}

int main(int argc, char *argv[]){

	value_t x[1000000];
	double unprecice, precice;

	__uint128_t current_ulp;
	__uint128_t max_ulp = 0;

	long double biggest_unprecice = 0, biggest_precice = 0;

	value_t maxvalue;
	maxvalue.i = 0x40862E2CC5A01975;

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
	bound[5] = maxvalue.d - 1010 * ln2;

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
			
				
				precice = expl((long double)x[i].d);
				unprecice = tang(x[i].d);
				if (precice != unprecice){
				current_ulp = ulp_func(unprecice, precice);

					if(current_ulp > max_ulp){
						max_ulp = current_ulp;
						biggest = i;
						biggest_unprecice = (long double) unprecice;
						biggest_precice = precice;
						//printf("max error in ulp is: %.16lf\n", max_ulp );
					}
				}
			
		}
		
		printf("completed bound nr.%i \n", n );

		if(biggest == -1){ 
			printf("array error\n" );
			return 0;
		}
		printf("for: %.16lf\n", x[biggest].d );
		printf("biggest: %i \n\n", biggest );

		printf("max error in ulp is: \n");
		printb(max_ulp);
		printb(biggest_unprecice);
		printb(biggest_precice);
		biggest_precice = 0;
		biggest_unprecice = 0;
		max_ulp = 0;
	}


	return 0;
}