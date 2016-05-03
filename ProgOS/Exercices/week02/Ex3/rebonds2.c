#include <stdio.h>
#include <math.h>

int main(void){
	double h0 = 10;
	double h1, v0, v1;
	double g = 9.81;
	double eps = 0.9;
	double hFin = 0.5;
	int reb = 0;
	do{
		if(h0 < hFin){
			break;
		}
		v0 = sqrt(2 * g * h0);
		v1 = eps * v0;
		h1 = (v1 * v1)/(2 * g);
		h0 = h1;
		reb += 1;
	}
		while(h0 >= hFin);
	printf("Nombre de rebonds : %d\n", reb);
	return 0;
}
