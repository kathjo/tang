//standart exeption for pos infinity
if(x.i == 0x7FF0000000000000){				
	printf("result: %lf\n", x.d );
	return 0;
}

//standart exeption for neg infinity
if(x.i == 0xFFF0000000000000){				
	printf("result: %lf\n", 0.0 );
	return 0;
}

//minimal value for magnitude of x
value_t x_min_pos;
value_t x_min_neg;
x_min_pos.i = 0x3CA0000000000001;  
x_min_neg.i = 0xBCA0000000000001;

if((x.d < x_min_pos.d && x.d > x_min_neg.d) && x.d != 0){		
	printf("Warning: underflow!\n");
	x.d = 1 + x.d;
	printf("result: %0.16lf\n", x.d);
	return 0;
}


//maximum value for magnitude of x
value_t x_max_pos;
value_t x_max_neg;
x_max_pos.i = 0x40862E2CC5A01975;  
x_max_neg.i = 0xC0862E2CC5A01975;

if(x.d > x_max_pos.d || x.d < x_max_neg.d){					
	printf("Warning: overflow!\n\n\n");
}


//two values for reduced argument for higher accuracy
double r1, r2;

//value for range-check on n 
double pnine = 0x4080000000000000;


//values n for expanded argument representation, 
//also provides values for the look-up tables
double n = nearbyintf(x.d * inv_L.d);			
double n2 = abs(fmod(n, 32));				
double n1 = n - n2;					

//range-check on n to see if expanded representation 
//for is needed to achieve required accuracy
//also computation of reduced argument/remainder
if (n <= pnine || n >= -pnine){				
	r1 = x.d - n * l1.d;
} else {
	r1 = (x.d - n1 * l1.d) - n2 * l1.d;
}

r2 = -n * l2.d;

//converting n into indeces for look-up tables
double m = n1/32;
int j = (int)n2;

//polynomial to approximate exp(r) - 1
double r = r1 + r2;
double q = r * r * (a1.d + r * (a2.d + r * (a3.d + r * (a4.d + r * a5.d))));
double p = r1 + (r2 + q);
double s = s1[j].d + s2[j].d;

//reconstruction of final result
result.d = pow(2, m) * (s1[j].d + (s2[j].d + s * p));
