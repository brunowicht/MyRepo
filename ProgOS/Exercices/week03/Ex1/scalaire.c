#include <stdio.h>

double scalaire(const double u[], const double v[], size_t taille);
double demander_vecteur(const char name, size_t taille);

int main(void){
	const int N_MAX = 3;
	double u[N_MAX];
	double v[N_MAX];
	
	for(int i = 0; i<N_MAX; ++i){
		printf("Entrez la composante u%d :", i);
		scanf("%lf", &u[i]);
	}
	for(int i = 0; i<N_MAX; ++i){
		printf("Entrez la composante v%d :", i);
		scanf("%lf", &v[i]);
	}
	
	double scal = scalaire(u, v, N_MAX);
	
	printf("Le produit scalaire des deux vecteurs est : %.2f\n", scal);
	
	return 0;
	
	
}

double scalaire(const double u[], const double v[], size_t taille){
	double result = 0;
	for(int i = 0; i<taille; ++i){
		result += u[i]*v[i];
	}
	return result;
}
