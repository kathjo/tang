#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "tang.h"

//union for easy conversion between machine representation and user representation of double value
typedef union{
	long int i;
	double d;
} value_t;




double pascalsround(double d){
	if (d >= 0){
// 	 if (d >= 0x1.0p52){				dieses test sind wegen eingabe beschränkungen redundant
//  	  return d;
//  	}
  	return d + 0x1.0p52 - 0x1.0p52;
  }
  else{
//  	if (d <= -0x1.0p52){
//  	  return d;
//  	}
  	return d - 0x1.0p52 + 0x1.0p52;
  }
}


int main(){


double xa = 122;
//input argument
value_t x;
x.d = xa;




//inverse of L (32/log2)
value_t inv_L;
inv_L.i = 0x40471547652B82FE;



//l1 + l2 approximates L (log2/32)
value_t l1;
value_t l2;

l1.i    = 0x3F962E42FEF00000;
l2.i    = 0x3D8473DE6AF278ED;



//factors for polinomial approximation of exp(r) - 1, accurate for |r| < log2/64
value_t a1;
value_t a2;
value_t a3;
value_t a4;
value_t a5;

a1.i = 0x3FE0000000000000;
a2.i = 0x3FC5555555548F7C;
a3.i = 0x3FA5555555545D4E;
a4.i = 0x3F811115B7AA905E;
a5.i = 0x3F56C1728D739765;



//var for result
value_t result;



//array for look-up tables
value_t s1[32];
value_t s2[32];

s1[0].i  = 0x3FF0000000000000;
s1[1].i  = 0x3FF059B0D3158540;
s1[2].i  = 0x3FF0B5586CF98900;
s1[3].i  = 0x3FF11301D0125B40;
s1[4].i  = 0x3FF172B83C7D5140;
s1[5].i  = 0x3FF1D4873168B980;
s1[6].i  = 0x3FF2387A6E756200;
s1[7].i  = 0x3FF29E9DF51FDEC0;
s1[8].i  = 0x3FF306FE0A31B700;
s1[9].i  = 0x3FF371A7373AA9C0;
s1[10].i = 0x3FF3DEA64C123400;
s1[11].i = 0x3FF44E0860618900;
s1[12].i = 0x3FF4BFDAD5362A00;
s1[13].i = 0x3FF5342B569D4F80;
s1[14].i = 0x3FF5AB07DD485400;
s1[15].i = 0x3FF6247EB03A5580;
s1[16].i = 0x3FF6A09E667F3BC0;
s1[17].i = 0x3FF71F75E8EC5F40;
s1[18].i = 0x3FF7A11473EB0180;
s1[19].i = 0x3FF82589994CCE00;
s1[20].i = 0x3FF8ACE5422AA0C0;
s1[21].i = 0x3FF93737B0CDC5C0;
s1[22].i = 0x3FF9C49182A3F080;
s1[23].i = 0x3FFA5503B23E2540;
s1[24].i = 0x3FFAE89F995AD380;
s1[25].i = 0x3FFB7F76F2FB5E40;
s1[26].i = 0x3FFC199BDD855280;
s1[27].i = 0x3FFCB720DCEF9040;
s1[28].i = 0x3FFD5818DCFBA480;
s1[29].i = 0x3FFDFC97337B9B40;
s1[30].i = 0x3FFEA4AFA2A490C0;
s1[31].i = 0x3FFF50765B6E4540;


s2[0].i  = 0x0000000000000000;
s2[1].i  = 0x3D0A1D73E2A475B4;
s2[2].i  = 0x3CEEC5317256E308;
s2[3].i  = 0x3CF0A4EBBF1AED93;
s2[4].i  = 0x3D0D6E6FBE462876;
s2[5].i  = 0x3D053C02DC0144C8;
s2[6].i  = 0x3D0C3360FD6D8E0B;
s2[7].i  = 0x3D009612E8AFAD12;
s2[8].i  = 0x3CF52DE8D5A46306;
s2[9].i  = 0x3CE54E28AA05E8A9;
s2[10].i = 0x3D011ADA0911F09F;
s2[11].i = 0x3D068189B7A04EF8;
s2[12].i = 0x3D038EA1CBD7F621;
s2[13].i = 0x3CBDF0A83C49D86A;
s2[14].i = 0x3D04AC64980A8C8F;
s2[15].i = 0x3CD2C7C3E81BF4B7;
s2[16].i = 0x3CE921165F626CDD;
s2[17].i = 0x3D09EE91B8797785;
s2[18].i = 0x3CDB5F54408FDB37;
s2[19].i = 0x3CF28ACF88AFAB35;
s2[20].i = 0x3CFB5BA7C55A192D;
s2[21].i = 0x3D027A280E1F92A0;
s2[22].i = 0x3CF01C7C46B071F3;
s2[23].i = 0x3CFC8B424491CAF8;
s2[24].i = 0x3D06AF439A68BB99;
s2[25].i = 0x3CDBAA9EC206AD4F;
s2[26].i = 0x3CFC2220CB12A092;
s2[27].i = 0x3D048A81E5E8F4A5;
s2[28].i = 0x3CDC976816BAD9B8;
s2[29].i = 0x3CFEB968CAC39ED3;
s2[30].i = 0x3CF9858F73A18F5E;
s2[31].i = 0x3C99D3E12DD8A18B;



	//manual input
	//printf("Gives exp(x) - please enter x: \n" );
	//scanf("%lf", &x.d);
	
	


	//standart exeption for pos infinity
	if(x.i == 0x7FF0000000000000){
		//printf("result: %lf\n", x.d );
		return x.d;
	}

	//standart exeption for neg infinity
	if(x.i == 0xFFF0000000000000){
		//printf("result: %lf\n", 0.0 );
		return 0.0;
	}

	//minimal value for magnitude of x
	value_t x_min_pos;
	value_t x_min_neg;
	x_min_pos.i = 0x3CA0000000000001;  
	x_min_neg.i = 0xBCA0000000000001;

	if((x.d < x_min_pos.d && x.d > x_min_neg.d) && x.d != 0){
		//printf("Warning: underflow!\n");
		x.d = 1 + x.d;
		//printf("result: %0.16lf\n", x.d);
		return x.d;
	}


	//maximum value for magnitude of x
	value_t x_max_pos;
	value_t x_max_neg;
	x_max_pos.i = 0x40862E2CC5A01975;  
	x_max_neg.i = 0xC0862E2CC5A01975;

	if(x.d > x_max_pos.d || x.d < x_max_neg.d){
		//printf("Warning: overflow!\n\n\n");
	}

	//values n for expanded argument representation, also provides values for the look-up tables
	double n = pascalsround(x.d * inv_L.d);
	double n2 = abs(fmod(n, 32));
	double n1 = n - n2;

	

	//two values for reduced argument for higher accuracy
	double r1, r2;
	
	//value for range-check on n 
	__uint64_t pnine_int = 0x4080000000000000;
	double pnine = *(double*) & pnine_int;

	printf("%lf \n", pnine);

	//range-check on n to see if expanded representation for is needed to achieve required accuracy
	//also computation of reduced argument/remainder
	if (n <= pnine || n >= -pnine){
		r1 = x.d - n * l1.d;
	} else {
		r1 = (x.d - n1 * l1.d) - n2 * l1.d;
	}
	
	r2 = -n * l2.d;


	//converting n into indeces for look-up tables
	value_t m;
	m.d = n1/32;
	int j = (int)n2;

	//polynomial to approximate exp(r) - 1
	double r = r1 + r2;
	double q = r * r * (a1.d + r * (a2.d + r * (a3.d + r * (a4.d + r * a5.d))));
	double p = r1 + (r2 + q);
	double s = s1[j].d + s2[j].d;
	
	//reconstruction of final result
	result.d = pow(2, m.d) * (s1[j].d + (s2[j].d + s * p));



	// //debugging output
	// printf("n: %0.16lf\n", n );
	// printf("n1: %0.16lf\n", n1 );
	// printf("n2: %0.16lf\n", n2 );
	// printf("p: %0.16lf\n", p );
	// //printf("r1: %0.16lf\n", r1 );
	// //printf("r2: %0.16lf\n", r2 );
	// printf("r: %0.16lf\n\n", r );
	// //printf("s1[j].d: %0.16lf\n\n", s1[j].d );
	// //printf("s2[j].d: %0.16lf\n\n", s2[j].d );
	// printf("m: %li\n\n", m.i );
	// printf("m: %0.16lf\n\n", m.d );
	
	// printf("result: %li or %0.16lf\n\n", result.i, result.d );
	// printf("input:  %li or %0.16lf\n", x.i, x.d);


	return 0;
}