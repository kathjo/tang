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

        double f = exp(-500);
        long double g = expl(-500);
        long double h = (long double) f;

        __uint128_t g_cast = *(__uint128_t*) &g;
        __uint128_t h_cast = *(__uint128_t*) &h;
       
        __uint128_t mask1 = 1;
        mask1 = (mask1 << 64) -1;
        printb(mask1);
        printb(g_cast);
        printb(h_cast);

        g_cast = g_cast & mask1;
        h_cast = h_cast & mask1;

        printb(g_cast);
        printb(h_cast);

        __uint128_t mask2;

        mask2 = 1;
        mask2 <<= 127;

        printb(mask2);

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
        printf("%i\n", a);
        
        printf("\n");
        printf("\n");   
        return 0;
}

//das hier ist ein guter ansatzt aber ich muss noch einen weg finden den ulp korrekt auszudrücken
