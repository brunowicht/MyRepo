#include <stdio.h>
#include <limits.h>

int demander_nombre(int, int);

int main(void){
	int n = demander_nombre(1,5);
	printf("Vous avez entre le nombre : %d\n", n);
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
