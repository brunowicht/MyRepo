#include <stdio.h>
#include <string.h>

typedef void (*Cmd)(void* data);

void print(void* data);
void quit(void* data);
void push(void* data);
void pop(void* data);
void add(void* data);

Cmd interprete(const char* nom_comande);

int main(void){
	double registres[] = { 0.0, 0.0 };
	Cmd cmd = quit;
	
	do{
		char lu[] = "nom de la plus longue commande";
		printf("Entrez une commande (print, add, push, pop, quit) : ");
		scanf("%s", lu);
		(cmd = interprete(lu))(registres);
	}while(cmd != quit);
	
	return 0;
}

Cmd interprete(const char* nom){
	if (nom == NULL) return quit;
 
  if ( ! strcmp(nom, "print") ) {
    return print;
  } else
  if ( ! strcmp(nom, "add") ) {
    return add;
  } else
  if ( ! strcmp(nom, "push") ) {
    return push;
  } else
  if ( ! strcmp(nom, "pop") ) {
    return pop;
  } 
  return quit;
}

void quit(void* data){
	puts("Bye!");
}

void add(void* data){
	double * const regs = data;
  regs[0] += regs[1];
}
 
void push(void* data)
{
  double * const regs = data;
  regs[1] = regs[0];
  printf("Valeur ? ");
  scanf("%lf", regs);
}

void print(void* data)
{
  const double * const px = data;
  printf("-> %g\n", *px);
}

void pop(void* data)
{
  double * const regs = data;
  regs[0] = regs[1];
}
