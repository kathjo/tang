#include <stdio.h>
#include <math.h>

//const double LN2 = log(2);



int fm(int k, int pl){
	printf("in fm: \n");
	printf("k: %i\n", k );
	printf("pl: %i\n", pl );
	int m1, m2, m;
	m1 = k/pl;
	m2 = (k >= 0) ? m1+1 : m1-1;
	printf("m1: %i\n", m1 );
	printf("m2: %i\n", m2 );
	m  = (abs(k-m1*pl)<= pl/2) ? m1 : m2;
	return m;
}



float give_t(float i, float w){
	float t = pow(2, i/(pow(2, w)));
	printf("i: %f\n", i );
	printf("w: %f\n", w );
	return t;
}



int main(){
	double x, z, y;
	double ln2 = log(2);
	//TODO: mehrstufige ln als rangevariable einführen
	double euler = 2.718281828459045235360287471352662497757247093699959574966;
	int e, m, k, l, w1, w2, i1, i2, pl, pw1, pw2;

	w1 = w2 = 3;
	l  = w1 + w2;

	pl = (int)pow(2, l);
	pw1 = (int)pow(2, w1);
	pw2 = (int)pow(2, w2);

	x = 80;

	e = (int) (x/ln2);
	z = fmod(x, ln2);
	k = round(z*(pow(2,l)/ln2));
	y = z - k * (ln2 / pl);
	//printf("k =");
	//scanf(" %i", &k);
	//printf("k: %i\n", k );
	//m = (k >= pow(2,l/2)) ? 1 : 0;
	//i2 = k

	/**if(k >= 0){
		if(k >= pow(2,l/2)){
			m = 1;
			i2 = fi2(m,k);
			i1 = m * (int)pow(2,l) + i2 * (int)pow(2,w1) 
		}
	}**/

	m  = fm(k, pl);
	k  = k - m*pl;
	i2 = fm(k, pw1);
	i1 = k - i2*pw1;



	float t1 = give_t(i2, w1);
	float t2 = give_t(i1, l);


	float result = pow(2, m+e) * t1 * t2 * pow(euler, y);

	
	//printf("ln2: %f\n", ln2 );
	//printf("%f = %i*ln2 + %f\n", x, e, z);
	printf("\n\n\n");
	printf("m: %i\n", m );
	printf("i2: %i\n", i2 );
	printf("i1: %i\n", i1 );
	printf("t1: %f\n", t1 );
	printf("t2: %f\n", t2 );
	printf("y: %f\n", y );
	printf("\n\n");
	printf("result: %f\n", result );
	
	return 0;
}
