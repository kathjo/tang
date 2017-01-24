#include <stdio.h>


typedef union{
	long int i;
	double d;
} value_t;


double pascalsround(double d){
	if (d >= 0){
 	 if (d >= 0x1.0p52){
  	  return d;
  	}
  	return d + 0x1.0p52 - 0x1.0p52;
  }
  else{
  	if (d <= -0x1.0p52){
  	  return d;
  	}
  	return d - 0x1.0p52 + 0x1.0p52;
  }
}





int main(){
	value_t x;
	x.d = -2345.15;
	double r = pascalsround(x.d);
	printf("input : %lf\n", x.d );
	printf("result: %lf\n", r );
	return 0;
}