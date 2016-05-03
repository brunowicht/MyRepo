#include <stdio.h>
#include <math.h>

int main(void){
	double a0 = 0.0, a1 = 0.0, a2 = 0.0;
	double const pi = 3.14159265359;
	printf("Entrez a2 : ");
	scanf("%lf", &a2);
	printf("Entrez a1 : ");
	scanf("%lf", &a1);
	printf("Entrez a0 : ");
	scanf("%lf", &a0);
	
	double q = (3 * a1 - pow(a2, 2))/9;
	double r = (9*a2*a1 - 27*a0 - 2*pow(a2,3))/54;
	double d = pow(q, 3)+pow(r,2);
	double z1, z2, z3;
	
	if(d < 0){
		double o = acos(r / (sqrt(- pow(q, 3))));
		z1 = 2 * sqrt(- q) * cos(o) - a2/3;
		z2 = 2 * sqrt(- q) * cos((o + 2 * pi)/3) - a2/3;
		z3 = 2 * sqrt(- q) * cos((o + 4 * pi)/3) - a2/3;
		printf("les  3 solutions sont: z1 = %f , z2 = %f , z3 = %f\n", z1, z2, z3);
		return 0;	
	}
	else{
		double j = r + sqrt(d);
		double s = pow(j, 1.0/3.0);
		double t;
		double k = r - sqrt(d);
		if(k < 0){
			t = - pow(-k, 1.0/3.0);
		}
		else{
			t = pow(k , 1.0/3.0);
		}
		if((d == 0)&&(s + t != 0)){
			z1 = (- a2/3) + s + t; 
			z2 = (- a2/3) - (s+t)/2;
			printf("Les 2 solutions sont: z1 = %f , z2 = %f\n", z1, z2);
			return 0;
		}
		
		else{
			z1 = s+t-a2/3; 
			printf("La solution unique est: z1 = %f\n", z1);
			return 0;
		}
	}
}
