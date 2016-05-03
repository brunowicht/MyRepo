#include <stdio.h>
#include <math.h>

int main(void){
	double s = 30000.0;
	double r = 1300;
	double ir = 0.01;
	double somme = 0;
	int nMois = 0;
	
	while(s > 0){
		somme = somme + (ir * s);
		s = s - r;
		nMois += 1;
	}
	
	printf("Somme des interets encaisses: %f  (sur %d mois)\n", somme, nMois);
	return 0;
}
