#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "tang.h"
#include <stdlib.h>

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

int main(void) {




        srand(time(NULL));

        __uint64_t maxvalue_cast = 0x40862E2CC5A01975;
        double maxvalue = *(double*) &maxvalue_cast;
        double ln2 = log(2.0);

        double bound[6];
        bound[0] = 0x1.0p-14;
        bound[1] = ln2/64;
        bound[2] = 2 * ln2 - ln2/64;
        bound[3] = 20 * ln2 - 2 * ln2/64;
        bound[4] = 1010 * ln2 - 20 * ln2;
        bound[5] = maxvalue - 1010 * ln2;

        double offset[6];
        offset[0] = 0;
        offset[1] = 0;
        offset[2] = ln2/64;
        offset[3] = 2 * ln2/64;
        offset[4] = 20 * ln2;
        offset[5] = 1010 * ln2;

        double f = 0, max_difference_float = 0;
        long double g = 0, h = 0;

        __uint128_t g_cast = 0, h_cast = 0, g_cast_test = 0, h_cast_test = 0, difference = 0, max_difference = 0, mask = 1;


        mask = (mask << 64) - 1;


        double x = 0;
        int i_test = 0;

        double c = 0;

        for(int n = 0; n<6; n++){
                for(int i = 0; i<40000000; i++){
                        if(i < 20000000){
                                x = (((double)rand()/(double)(RAND_MAX)) * bound[n]) + offset[n];
                        } else{
                                x = - (((double)rand()/(double)(RAND_MAX)) * bound[n]) - offset[n];
                        }

                        f = tang(x);
                        h = (long double) f;
                        g = expl((long double)x);

                        g_cast = *(__uint128_t*) &g;
                        h_cast = *(__uint128_t*) &h;

                        g_cast = g_cast & mask;
                        h_cast = h_cast & mask;


                        if(g_cast != h_cast){
                                if(g_cast > h_cast){
                                        difference = g_cast - h_cast;
                                }else{
                                     difference = h_cast - h_cast;
                                }
                        }


                                max_difference_float = (double) difference;
                                max_difference_float = max_difference_float/2048;
                                if(max_difference_float > 0.5){
                                        c = c + 1;

                                }
                        

                        
                        g_cast = 0;
                        h_cast = 0;
                }
        c = (c/40000000)*100;

        printf("Stufe: %i\n", n);
        printf("\n");
        
        printf("Prozent mit Fehler größer als 0.5 ULP: %lf\n", c);
        printf("\n");

        
        printf("\n");

        g_cast_test = 0;
        h_cast_test = 0;
        difference = 0;
        max_difference = 0;
        max_difference_float = 0;
        i_test = 0;

        }

        return 0;
}