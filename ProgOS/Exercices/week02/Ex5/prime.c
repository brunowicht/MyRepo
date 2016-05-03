#include <stdio.h>
#include <math.h>

int main(void){
	int x = 0;
	printf("Entrez un entier suprieur a 1: ");
	scanf("%d", &x);
	
	/*contrôle si le nombre est premier*/
	
	if(x % 2 ==0){
		printf("Le nombre n'est pas premier, car il est pair! \n");
		return 0;
	}
	
	double sqr = sqrt(x);
	
	for (int i = 3; i < sqr; ++i){
		if (x % i == 0){
			printf("Le nombre n'est pas premier car il est divisible par %d ! \n", i);
			return 0;
		}
	}
	
	printf("Je crois fortement que le nombre est premier!\n");
	
	return 0;
}
