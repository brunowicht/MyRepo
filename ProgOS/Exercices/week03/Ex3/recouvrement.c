#include <stdio.h>

#define DIM 10

typedef struct{
	char g[DIM][DIM];
}Grille;

typedef struct{
	Grille grille;
	int valide;
}Placement;

Placement remplitGrille(Grille grille, size_t ligne, size_t colonne, char direction, size_t longueur);



int main(void){
	
	Grille grille;
	Placement p;
	for(int i = 0; i< DIM; ++i){
		for(int j = 0; j< DIM; ++j){
			grille.g[i][j] = '.';
		}
	}
	
	size_t ligne = 0;
	size_t colonne = 0;
	char direction = 'E';
	size_t longueur = 0;
	
	while(ligne >= 0){
		printf("Entrez coord. x: ");
		scanf("%d", &ligne);
		if(ligne > DIM){break;}
		
		printf("Entrez coord. y: ");
		scanf("%d", &colonne);
		
		printf("Entrez une direction (N, S, E, O):");
		scanf(" %c", &direction);
		
		printf("Entrez longueur: ");
		scanf("%d", &longueur);
		
		p = remplitGrille(grille, ligne, colonne, direction, longueur);
		if(p.valide == 1){
			printf("Placement en (%d, %d) direction %c longueur %d -> succes\n", ligne, colonne, direction, longueur);
		}
		else{
			printf("Placement en (%d, %d) direction %c longueur %d -> ECHEC\n", ligne, colonne, direction, longueur);
		}
		grille = p.grille;
		printf("%c\n", grille.g[ligne][colonne]);
	}
	
	printf("Resultat des placements: \n");
	
	for(int i = 0; i<DIM; ++i){
		for(int j = 0; j<DIM; ++j){
			printf("%c", grille.g[i][j]);
		}
		printf("\n");
	}
	return 0;
}

Placement remplitGrille(Grille grille, size_t ligne, size_t colonne, char direction, size_t longueur){
	Placement p;
	p.grille = grille;
	p.valide = 0;
	if(direction == 'N'){
		if(ligne-longueur+1 > DIM){
			return p;
		}
		for(int i = ligne; i>ligne-longueur; --i){
			if(grille.g[i][colonne] == '#'){
				return p;
			}
			grille.g[i][colonne] = '#';
			p.grille= grille;
			p.valide = 1;
			
		}
		return p;
	}
	else if(direction == 'S'){
		if(ligne+longueur > DIM){
			return p;
		}
		for(int i = ligne; i<ligne+longueur; ++i){
			if(grille.g[i][colonne] == '#'){
				return p;
			}
			grille.g[i][colonne] = '#';
			p.grille= grille;
			p.valide = 1;
		}
		return p;
	} 
	else if(direction == 'E'){
		if(colonne+longueur > DIM){
			return p;
		}
		for(int i = colonne; i<colonne+longueur; ++i){
			if(grille.g[ligne][i] == '#'){
				return p;
			}
			grille.g[ligne][i] = '#';
			p.grille= grille;
			p.valide = 1;
		}
		return p;
	}
	else if(direction == 'O'){
		if(colonne-longueur+1 > DIM){
			return p;
		}
		for(int i = colonne; i>colonne-longueur; --i){
			if(grille.g[ligne][i] == '#'){
				return p;
			}
			grille.g[ligne][i] = '#';
			p.grille= grille;
			p.valide = 1;
		}
		return p;
	}
	else{
		return p;
	}
}
