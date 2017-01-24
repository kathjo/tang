#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

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

        double f = exp(-212);
        long double g = expl(-212);
        long double h = (long double) f;
        double k = (double) g;
        long double j = fabsl( fabsl(g) - fabsl(h));
        long double relative = j/fabsl(g);

        __uint128_t pups = (1 << 12) -1;
        __uint128_t cast = *(__uint128_t*) & g; 

        printf("\n");
        printf("\n");
        printb(f);
        
        printb(h);
        printb(k);
        printf("\n");
        printb(g);
        printb(cast);
        printf("\n");
        printb(j);

        printf("%.20llf \n", j);
        printf("\n");
        printf("%.20llf \n", relative);

        printb(pups & cast);


        printf("\n");
        printf("\n");   
        return 0;
}

//das hier ist ein guter ansatzt aber ich muss noch einen weg finden den ulp korrekt auszudrücken