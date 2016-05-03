#include <stdio.h>
#include <limits.h>

int demander_nombre(int, int);

int main(void){
	
	double valeur1 = 2.0;
	double valeur2 = 4.0;
	double valeur3 = 6.0;
	
	double* choix = NULL;
	int i = demander_nombre(1,3);
	switch(i){
		case 1: choix = &valeur1;
			break;
		case 2: choix = &valeur2;
			break;
		case 3: choix = &valeur3;
			break;
	}
	
	printf("vous avez choisi %f\n", *choix);
	
	
	return 0;
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

