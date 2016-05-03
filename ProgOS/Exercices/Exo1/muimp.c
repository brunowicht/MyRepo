#include <stdio.h>
#include <string.h>


//Définition des macros.
#define MAX_IMAGE_HEIGHT 100
#define MAX_IMAGE_WIDTH 100

//Définition du type Pixel.
typedef double Pixel;

//définition de la structure Image.
typedef struct {
	int height;
	int width;
	Pixel pixels[MAX_IMAGE_WIDTH][MAX_IMAGE_HEIGHT];
}Image;



//Prototypage des fonctions.
void display(FILE*, Image);
Image diamond(int h, int w, int d);
int write_to_file(char*, Image);
Image read_from_file(char*);
Image filter(Image, Image);


//fonction main.
int main(){
	
	//initialisation des variables.
	int height = 0;
	int width = 0;
	int diagonal = 0;
	
	
	
	//On demande à l'utilisateur d'entrer des données (hauteur, largeur et diagonale du losange). Et on contrôle ses entrées!
	int j = 0;
	do{
		printf("Entrez une hauteur positive et plus petite que %d, et impaire si possible: ", MAX_IMAGE_HEIGHT); fflush(stdout);
		j = scanf("%d", &height);
		if (j != 1) {
			printf("Je vous ai demandé un nombre !\n");
	
			while (!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
		}
	}while (!feof(stdin) && !ferror(stdin) && ((j!=1) || (height<1) || (height>MAX_IMAGE_HEIGHT)));
	
	do{
		printf("Entrez une largeur positive et plus petite que %d, et impaire si possible: ", MAX_IMAGE_WIDTH); fflush(stdout);
		j = scanf("%d", &width);
		if (j != 1) {
			printf("Je vous ai demandé un nombre !\n");
	
			while (!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
		}
	}while (!feof(stdin) && !ferror(stdin) && ((j!=1) || (width<1) || (width>MAX_IMAGE_WIDTH)));
	
	
	do{
		printf("Entrez une diagonale positive et plus petite que la largeur et la hauteur: ");
		j = scanf("%d", &diagonal);
		if (j != 1) {
			printf("Je vous ai demandé un nombre !\n");
	
			while (!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
		}
	}while(!feof(stdin) && !ferror(stdin) && !(diagonal > 0 && diagonal <= height && diagonal <= width && j == 1));
	
	//définitiondes variables utiles à la récupération d'un nom de fichier
	char filename[FILENAME_MAX+1] = "";
	int lg;
	
	
	//On demande à l'utilisateur un nom de fichier.
	do {
		printf("Dans quel fichier voulez vous écrire ? \n");
		
		//contrôle de la validité du nom du fichier.
		fgets(filename, FILENAME_MAX+1, stdin);
		lg = strlen(filename) - 1;
		if ((lg >= 0) && (filename[lg] == '\n')){
			filename[lg] = '\0';
		}		
	} while ((lg < 1) && !feof(stdin) && !ferror(stdin) );
	
	
	//définition de l'image.
	Image image = diamond(height,width,diagonal);
	
	//définition du masque.
	Image mask;
	mask.width = 3;
	mask.height = 3;
	for(int i = 0; i<mask.width; ++i){
		for(int j = 0; j < mask.height; ++j){
			mask.pixels[i][j] = 2 * (j-1);
		}
	}
	
	//filtrage de l'image.
	image = filter(image, mask);
	
	//écriture de l'image dans le fichier donné par l'utilisateur.
	write_to_file(filename, image);
	
	
	//lecture de l'image depuis le fichier.
	Image img_from_file = read_from_file(filename);
	
	//ouverture du fichier tampon qui nous sert à afficher l'image sans toucher au fichier dans lequel l'image est stockée.
	FILE* file = fopen("display.txt", "w");
	if (file == NULL) {
        fprintf(stderr, "ERREUR: Le fichier \"display.txt\" n'a pas pu être ouvert !\n");
    }
    
    
    //remplissage du fichier tampon.
	display(file, img_from_file);
	
	//fermeture du fichier tampon.
	fclose(file);
	
	//réouverture du fichier tampon en mode lecture pour afficher son contenu.
	file = fopen("display.txt", "r");
	if (file == NULL) {
        fprintf(stderr, "ERREUR: Le fichier \"display.txt\" ne peut pas être ouvert.\n");
    }
    
    
    //affichage du contenu du fichier tampon.
    char c;
    while((c = fgetc(file))!= EOF){
		printf("%c", c);
	}
	fclose(file);
	
	return 0;
}

Image diamond(int h, int w, int d){
	
	// on s'assure que la hauteur et la largeur soient impairs.
	w |= 1;
	h |= 1;
	
	//définition de l'image.
	Image img;
	
	img.height = h;
	img.width = w;
	
	
	//calcul des coordonées du centre.
	int xc = w/2;
	int yc = h/2;
	
	
	//initialisation de l'image avec des pixels de valeur 0.
	for(int x = 0; x < w; ++x){
		for(int y = 0; y < h; ++y){
			img.pixels[x][y] = 0.0;
		}
	}
	
	for(int y = 0; y <= yc; ++y){
		
		//les abcisses des deux pixels de chaque bord du losange.
		int x1 = xc - y + yc - d/2;
		int x2 = xc + y - yc + d/2;
		
		//On parcourt chaque ligne de la partie du haut de l'image pour créer l'image.
		for(int x = 0; x < w; ++x){
			
			// si le pixel est à l'intérieur du losange, sa valeur est 1.
			if(x >= x1 && x <= x2){
				img.pixels[x][y] = 1.0;
				img.pixels[x][h-1-y] = 1.0;
			}
		}
	}
	
	return img;	
}

void display(FILE* flot, Image img){
	
	//on parcourt l'image ligne par ligne
	for(int y = 0; y < img.height; ++y){
		for(int x = 0; x < img.width; ++x){
			
			char c;
			
			//séparation des options de caractères selon la valeur du pixel.
			if(img.pixels[x][y] == 0){
				c = '.';
			}
			else if(img.pixels[x][y] == 1){
				c = '+';
			}
			else{
				c = '*';
			}
			
			//on écrit le caractère dans le flot.
			fputc(c, flot);
		}
		//retour à la ligne à la fin d'une ligne de l'image.
		fputc('\n', flot);
	}
}

int write_to_file(char* filename, Image img){
	FILE* file = NULL;
	
	//ouverture du fichier et contrôle du bon fonctionnement de cette ouverture.
	file = fopen(filename, "w");
	if (file == NULL) {
        return 1;
    }
    
    //écriture de la hauteur et de la largeur de l'image.
    fprintf(file, "%d", img.height);
    fputc('\n', file);
    fprintf(file, "%d", img.width);
    fputc('\n', file);
    
    
    //écriture de l'image
    display(file, img);
    
    
    //fermeture du fichier.
    fclose(file);
    
	return 0;
}

Image read_from_file(char* filename){
	
	//définition de l'image.
	Image img;
	
	//ouverture du fichier.
	FILE* file = NULL;
	file = fopen(filename, "r");
	if (file == NULL) {
        fprintf(stderr, "ERREUR: Le fichier ne peut pas être ouvert.\n");
    }
    
    
    //récupération de la hauteur.
    int h = 0;
    if(fscanf(file, "%d", &h)==1){
		if(h< MAX_IMAGE_HEIGHT && h > 0){
			img.height = h;
		}
		else{
			img.height = 0;
		}
	}
	else{
		img.height = 0;
	}
	
	
	//récupération de la largeur.
	int w = 0;
    if(fscanf(file, "%d", &w)==1){
		if(w< MAX_IMAGE_WIDTH && w > 0){
			img.width = w;
		}
		else{
			img.width = 0;
		}
	}
	else{
		img.width = 0;
	}
	
	int c = fgetc(file); //on lit déjà le retour à la ligne entre la largeur et le début de l'image.
	
	//initialisation ds coordonnées.
	int x = 0;
	int y = 0;
	
	while((c = fgetc(file))!= EOF){
		
		//le cas du retour à la ligne.
		if(c == '\n'){
			++y;
			x = 0;
		}
		//le cas ou c est un point le pixel vaut 0
		else if(c == '.'){
			img.pixels[x][y] = 0.0;
			++x;
		}
		
		//le cas ou c est un "+" le pixel vaut 1
		else if(c == '+'){
			img.pixels[x][y] = 1.0;
			++x;
		}
		//dans les autres cas la valeur est arbitraire, j'ai choisi de la mettre à 2.
		else{
			img.pixels[x][y] = 10.0;
			++x;
		}
	}
	
	//fermeture  du fichier.
	fclose(file);
	
	return img;
}
//Petite fonction qui effectue x mod y.
int modulo(int x, int y){
	while(x<0){
		x += y;
	}
	return x%y;
}

Image filter(Image img, Image mask){
	//initialisation de l'image de destination.
	Image dest;
	dest.width = img.width;
	dest.height = img.height;
	
	int n = mask.width;
	
	
	//application de la formule donnée
	for(int x = 0; x < dest.width; ++x){
		for(int y = 0; y < dest.height; ++y){
			dest.pixels[x][y] = 0.0;
			for(int k = 0; k < n; ++k){
				for(int l = 0; l < n; ++l){
					dest.pixels[x][y] += (mask.pixels[k][l] * 
					img.pixels[modulo((x + n/2 - k),img.width)]
					[modulo((y + n/2 - l),img.height)]);
				}
			}
		}
	}
	
	
	return dest;
}

