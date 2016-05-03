#include <stdio.h>

#define N 5

typedef struct{
	int m;
	int n;
	double matrix[N][N];
}Matrice;

Matrice lire_matrice(void);
Matrice multiplication(const Matrice a, const Matrice b);
void affiche_matrice(const Matrice m);

int main(void){
	Matrice a = lire_matrice();
	Matrice b = lire_matrice();
	if(!(a.n == b.m)){
		printf("Multiplication des matrices impossible !");
		return 1;
	}
	Matrice c = multiplication(a,b);
	
	printf("Resultat :\n");
	affiche_matrice(c);
	
	return 0;
}

Matrice lire_matrice(void){
	Matrice m;
	printf("Saisie d'une matrice :\n");
	do{
	printf("\tNbre de lignes (<=%d): ", N);
	scanf("%d", &(m.m));
	}while(m.m>N);
	
	do{
	printf("\tNbre de colones (<=%d): ",N);
	scanf("%d", &(m.n) );
	}while(m.n>N);
		
	for(int i = 0; i<m.m; ++i){
		for(int j = 0; j<m.n; ++j){
			printf("\tM[%d, %d]=",i, j);
			scanf("%lf", &(m.matrix[i][j]));
			
		}
	}
	return m;
}

Matrice multiplication(const Matrice a, const Matrice b){
	
	Matrice c;
	c.m = a.m;
	c.n = b.n;
	
	for(int i = 0; i<a.m; ++i){
		for(int j = 0; j<b.n; ++j){
			double sum = 0;
			for(int k = 0; k<a.n; ++k){
				sum += a.matrix[i][k] * b.matrix[k][j];
			}
			c.matrix[i][j] = sum;
		}
	}
	
	return c;
}

void affiche_matrice(const Matrice m){
	for(int i = 0; i<m.m; ++i){
		for(int j = 0; j<m.n; ++j){
			printf("%.2f ", m.matrix[i][j]);
		}
		printf("\n");
	}
}

