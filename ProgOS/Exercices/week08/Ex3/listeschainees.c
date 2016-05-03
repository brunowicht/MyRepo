#include <stdio.h>
#include <stdlib.h>


/* deux definition utiles */
#define LISTE_VIDE (NULL)
#define est_vide(L) ((L) == LISTE_VIDE)
 
/* deux definitions pour changer facilement de type */
#define type_el int
#define affiche_el(T) printf("%d", T)


typedef struct Element_ Element;

typedef Element* ListeChainee;
struct Element_{
	type_el value;
	ListeChainee suite;
};


/* les "méthodes" */
void insere_entete(ListeChainee* liste, type_el une_valeur);
void insere_apres(Element* existant, type_el a_inserer);
void supprime_tete(ListeChainee* liste);
void supprime_suivant(Element* e);
size_t taille(ListeChainee liste);
void affiche_liste(ListeChainee liste);


int main(void) {
  ListeChainee maliste = LISTE_VIDE;
  type_el un_element = 3;
 
  printf("J'insere (en tete) "); affiche_el(un_element); putchar('\n');
  insere_entete(&maliste, un_element);
 
  printf("J'insere (en tete) 2, puis 1, 0 et -1.\n");
  insere_entete(&maliste, 2);
  insere_entete(&maliste, 1);
  insere_entete(&maliste, 0);
  insere_entete(&maliste, -1);
 
  printf("Voici la liste : \n\t");
  affiche_liste(maliste); putchar('\n');
 
  printf("Je supprime la tete de liste.\n");
  supprime_tete(&maliste);
  printf("Voici la liste : \n\t");
  affiche_liste(maliste); putchar('\n');
 
  printf("Je supprime le 4e element.\n");
  supprime_suivant(maliste->suite->suite);
  printf("Voici la liste : \n\t");
  affiche_liste(maliste); putchar('\n');
 
  printf("J'insere 156 en 3e position.\n");
  insere_apres(maliste->suite, 156);
  printf("Voici la liste : \n\t");
  affiche_liste(maliste); putchar('\n');
 
  printf("de taille %u.\n", taille(maliste));
 
  return 0;
}

void insere_entete(ListeChainee* liste, type_el une_valeur){
	const ListeChainee tmp = *liste;
	
	*liste = malloc(sizeof(Element));
	if(*liste != NULL){
		(*liste)->value = une_valeur;
		(*liste)->suite = tmp;
	}
	else{
	 *liste = tmp;
	}
	
}

void insere_apres(Element* existant,  type_el a_inserer){
	Element* e;
	
	e = malloc(sizeof(Element));
	if(e != NULL){
		e->value = a_inserer;
		e->suite = existant->suite;
		existant->suite = e;
	}	
}

void supprime_tete(ListeChainee* liste){
	if(! est_vide(*liste)){
		ListeChainee nouvelle= (*liste)->suite;
		free(*liste);
		*liste = nouvelle;
	}
}

void supprime_suivant(Element* e){
	supprime_tete(&(e->suite));
	
}

size_t taille(ListeChainee liste){
	size_t size = 0;
	while(! est_vide(liste)){
		++size;
		liste = liste->suite;
	}
	return size;
	
}

void affiche_liste(ListeChainee liste){
	putchar('(');
	while(! est_vide(liste)){
		affiche_el(liste->value);
		liste = liste->suite;
		if(!est_vide(liste)){
			putchar(',');
		}
	}
	putchar(')');
	
}
