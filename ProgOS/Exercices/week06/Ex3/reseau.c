#include <stdio.h>
#include <stdlib.h>

#ifndef MAX_SIZE
#define MAX_SIZE (~(size_t)0)
#endif

typedef unsigned char Ip_Addr[4];

typedef struct _node{
	Ip_Addr adresse;
	const struct _node** voisins;
	size_t nb_voisins;
}Noeud;


Noeud* creation(const unsigned char adr1,
				const unsigned char adr2,
				const unsigned char adr3,
				const unsigned char adr4);
				
void sont_voisins(Noeud* p1, Noeud* p2);
// Pointeurs car les deux vont être modifiés (ajout de voisins).
// Autre type de retour possible (e.g. code d'erreur).
 
int ajoute_voisin(Noeud* a, const Noeud* b);
// Pensez MODULAIRE !
// const pointeur pour le second, non modifié ici.
// Retour : code d'erreur (optionnel, non utilisé d'ailleurs !)
 
unsigned int voisins_communs(const Noeud* p1, const Noeud* p2);
// const pointeurs pour éviter des copies inutiles.
// int ou size_t sont aussi valables commes type de retour.
 
void affiche(const Noeud* p);
 
void affiche_simple(const Noeud* p);
// Pensez MODULAIRE !
 
void libere(Noeud* p);
// NE PAS l'oublier !!
 
/* ---------------------------------------------------------------------- */
int main()
{
  Noeud* rezo[] = {
    creation(192, 168,  1, 1),
    creation(192, 168,  1, 2),
    creation(192, 168,  1, 3),
    creation(192, 168, 10, 1),
    creation(192, 168, 10, 2),
    creation(192, 168, 20, 1),
    creation(192, 168, 20, 2)
  };
 
  for (size_t i = 0 ; i < sizeof(rezo) / sizeof(rezo[0]); ++i) {
    if (NULL == rezo[i]) {
      fprintf(stderr, "pas assez de mémoire\n");
      exit(-1);
    }
  }    
 
  sont_voisins(rezo[0], rezo[1]);
  sont_voisins(rezo[0], rezo[2]);
 
  sont_voisins(rezo[1], rezo[2]);
  sont_voisins(rezo[1], rezo[3]);
  sont_voisins(rezo[1], rezo[5]);
 
  sont_voisins(rezo[2], rezo[3]);
  sont_voisins(rezo[2], rezo[5]);
 
  sont_voisins(rezo[3], rezo[4]);
  sont_voisins(rezo[3], rezo[5]);
 
  sont_voisins(rezo[5], rezo[6]);
 
  affiche(rezo[3]);
 
  affiche_simple(rezo[0]);
  printf(" et ");
  affiche_simple(rezo[5]);
  printf(" ont %u voisins communs.\n", voisins_communs(rezo[0], rezo[5]));
 
  affiche_simple(rezo[1]);
  printf(" et ");
  affiche_simple(rezo[2]);
  printf(" ont %u voisins communs.\n", voisins_communs(rezo[1], rezo[2]));
 
  /* garbage collecting */
  for (size_t i = 0 ; i < sizeof(rezo) / sizeof(rezo[0]); ++i) {
    libere(rezo[i]);
  }
  return 0;
}

Noeud* creation(const unsigned char adr1,
				const unsigned char adr2,
				const unsigned char adr3,
				const unsigned char adr4){
	
	Noeud* bebe = calloc(1, sizeof(Noeud));
	if(bebe == NULL){
		printf("Erreur: impossible d'allouer de la mémoire pour ce noeud.\n");
		return NULL;
	}
	bebe->adresse[0] = adr1;
	bebe->adresse[1] = adr2;
	bebe->adresse[2] = adr3;
	bebe->adresse[3] = adr4;
	
	bebe->voisins = NULL;
	bebe->nb_voisins = 0;
	
	return bebe;							
}

int ajoute_voisin(Noeud* a, const Noeud* b){
	if(a != NULL){
		if(b == NULL){
			printf("Erreur (ajoute_voisin): impossible d'ajouter un voisin NULL\n");
			return 1;
		}
		
		++(a->nb_voisins);
		Noeud const ** old_content = a->voisins;
		if(a->nb_voisins > MAX_SIZE || 
			((a->voisins = realloc(a->voisins, a->nb_voisins * sizeof(Noeud*))) == NULL)){
			
			a->voisins = old_content;
			--(a->nb_voisins);
			printf("Erreur (ajoute_voisin): le noeud a déjà trop de voisins.\n");
			return 2;
		}
		
		a->voisins[a->nb_voisins - 1] = b;
		return 0;		
	}
	return 3;
}

void sont_voisins(Noeud* a, Noeud* b){
	if(0 == ajoute_voisin(a,b)){
		(void)ajoute_voisin(b,a);
	}
}

unsigned int voisins_communs(const Noeud* a, const Noeud* b){
	int voisins_commun = 0;
	
	if(a != NULL && b != NULL){
		for(size_t i = 0; i < a->nb_voisins; ++i){
			for(size_t j = 0; j < b->nb_voisins; ++j){
				if(a->voisins[i] == b->voisins[j]){
					++voisins_commun;
				}
			}
		}
	}
	return voisins_commun;			
	
}

void affiche(const Noeud* n){
	affiche_simple(n);
	printf(" a %zu voisins", n->nb_voisins);
	if(n->nb_voisins >= 1){
		printf(": ");
		for(size_t i = 0; i < n->nb_voisins - 1; ++i){
			affiche_simple(n->voisins[i]);
			printf(", ");
		}
		affiche_simple(n->voisins[n->nb_voisins-1]);
		printf(".");
	}
	printf("\n");
}


void affiche_simple(const Noeud* n){
	if(n != NULL){
		printf("%u.%u.%u.%u", n->adresse[0]
           , n->adresse[1]
           , n->adresse[2]
           , n->adresse[3]);
	}
	else{
		puts("(affiche_simple): NULL");
	}
}

void libere(Noeud* n){
	free(n->voisins);
	free(n);
}




