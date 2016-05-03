#include <stdio.h>
#include <math.h>
#include <limits.h>

double factorielle(int);
double somme_partielle(double, int);
double cosinus(double, int);
int demander_nombre(int, int);

int main(void){
	double x = 0.0;
	printf("De quel nombre voulez vous calculer le cosinus? ");
	scanf("%lf", &x);
	printf("Et avec quelle precision?\n");
	int n = demander_nombre(1,170);
	
	double c = cosinus(x,n);
	
	printf("Le cosinus du nombre entre est : %f", c);
	
	return 0;
}

double factorielle(int n){
	double x = 1.0;
	for(int i = 1; i<=n; ++i){
		x = x*i;
	}
	return x;
}

double somme_partielle(double x, int n){
	double somme = 0;
	double k;
	for (int i = 0; i< n; ++i){
		k = pow(-1, i)*pow(x, 2*i)/factorielle(2*i);
		somme = somme + k;
	}
	
	return somme;
}

double cosinus(double x, int n){
	return somme_partielle(x,n);
}

int demander_nombre(int min, int max){
	int x = 0;
	if(min>max){
		max = LONG_MAX;
	}
		
	do{
		printf("Entrez un nombre entier entre %d et %d : ",min, max );
		scanf("%d", &x);}
		while((x<min)||(x>max));
	return x;
}
