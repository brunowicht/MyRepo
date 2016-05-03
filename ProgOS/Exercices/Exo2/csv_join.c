#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define HASH_TABLE_LOAD_FACTOR 0.75

#define CSV_MAX_LINE_SIZE 1024
#define CSV_SEPARATOR ','

/* ======================================================================
 * Provided utility functions
 * ======================================================================
 */

/** ----------------------------------------------------------------------
 ** Ask for a filename
 **/
void ask_filename(const char* question, char filename[])
{
    size_t len = 0;
    do {
        fputs(question, stdout);
        fflush(stdout);
        fgets(filename, FILENAME_MAX + 1, stdin);
        filename[strcspn(filename, "\r\n")] = '\0';
        len = strlen(filename) - 1;
    } while (len < 1 && !feof(stdin) && !ferror(stdin));
}

/** ----------------------------------------------------------------------
 ** Ask for a filename to open in a given mode
 **/
FILE* ask_filename_and_open(const char* question, const char* mode)
{
    char filename[FILENAME_MAX + 1] = "";

    ask_filename(question, filename);
    FILE* retour = fopen(filename, mode);

    if (retour == NULL) {
        fprintf(stderr, "Oops, je n'ai pas réussi à ouvrir le fichier \"%s\" en mode \"%s\"!\n",
                filename, mode);
    }
    return retour;
}

/** ----------------------------------------------------------------------
 ** Ask for a size
 **/
size_t ask_size_t(const char* question)
{
    size_t v = 0;
    int res = 0;
    do {
        fputs(question, stdout);
        fflush(stdout);
        res = scanf("%u", & v);
        while (!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
    } while (!feof(stdin) && !ferror(stdin) && res != 1 && v == 0);
    return v;
}

/* ======================================================================
 * Part I -- Hashtable
 * ======================================================================
 */

/** ----------------------------------------------------------------------
 ** Hash a string for a given hashtable size.
 ** See http://en.wikipedia.org/wiki/Jenkins_hash_function
 **/
size_t hash_function(const char* key, size_t size)
{
    size_t hash = 0;
    size_t key_len = strlen(key);
    for (size_t i = 0; i < key_len; ++i) {
        hash += (unsigned char) key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash % size;
}

/* ****************************************
 * TODO : add your own code here.
 * **************************************** */
// definition of Bucket type.
typedef struct bucket_s{
	const char* key;
	const void* value;
	struct bucket_s *next;
}bucket;

//definition of Htable type.
typedef struct Htable_s{
	size_t size;
	size_t entries;
	bucket* buckets;
}Htable;




/*construit une Htable avec size alvéoles*/
Htable* construct_Htable(size_t size){
	
	//initialisation de la htable et allocation de la mémoire de ses buckets à 0
	Htable* result = NULL;
	result->buckets = calloc(size, sizeof(bucket));
	//si l'allocation s'est faite correctement, on remplit les autres champs
	if(result->buckets != NULL){
		result->size = size;
		result->entries = 0;
	}
	else{
		/*retourne NULL si on n'a pas pu allouer*/
		free(result->buckets);
		result = NULL;
	}
	//On retourne le pointeur vers la htable créée 
	return result;
}


/*Libère la mémoire associée à la htable passée en argument,
 *  ainsi que le contenu mis dans cette table.*/
void delete_Htable_and_content(Htable* htable){
	/*On contrôle que la htable à effacer existe bel et bien*/
	if(htable != NULL){
		
		/*On libère la mémoire utilisée par les buckets*/
		free(htable->buckets);
		
		/*on efface les données dans la htable*/
		htable->buckets = NULL;
		htable->entries = 0;
		
	}
}



/*add a bucket in a linked list, or modify its value if there already is a bucket
 * with the same key.*/
void add_value_linked_list(Htable* h, bucket *b, const char *key, const char *value){
	//si les valeurs d'entrées sont nulles, on ne fait rien
	if(key == NULL || value == NULL){
		return;
	}
	
	
	/*si la key passée en argument est la même que celle du bucket en argument,
	 on modifie la valeur du bucket*/
	if(strcmp(b->key, key) == 0){
		b->value = value;
		return;
	}
	
	/*si la linked list de bucket ne contient pas de prochain élément 
	 * on en crée un.*/
	if(b->next == NULL){
		b->next->key = key;
		b->next->value = value;
		b->next = NULL;
		++(h->entries);		//le nombre de buckets dans la htable doit être incrémenté.
		return;
	}
	
	//On réappelle récursivement la méthode pour ajouter le bucket plus loin dans la linked list.
	else{
		return add_value_linked_list(h, b->next, key, value);
	}
}


/*Stocke la valeur associée à la clé dans la hashtable. Si elle existe déjà,
 * la valeur est remplacée. En cas de collision de valeurs, une linked List
 * est utilisée.*/
void add_Htable_value(Htable* htable, const char* key, const char* value){
	/*Contrôle des valeurs passées en argument*/
	if(key == NULL || value == NULL){
		printf("Impossible d'ajouter une telle valeur à un tel endroit!");
		return;
	}
	
	//on détermine dans quelle alvéole placer la valeur
	size_t hash = hash_function(key, htable->size);
	
	//ajout de la valeur à l'alvéole trouvée dans la htable
	add_value_linked_list(htable, &(htable->buckets[hash]), key, value);	
}


/*récupère la valeur d'un bucket avec une certaine key*/
const void* get_bucket_value_from_linked_list(const bucket* b, const char* key){
	//si une des entrées est nulle, le retour est nul.
	if(b == NULL || key == NULL){
		return NULL;
	}
	
	//si le premier bucket de la linked liste contient la bonne key, on retourn sa valeur.
	if(strcmp(b->key, key) == 0){
		return b->value;
	}
	
	//sinon on va regarder dans le prochain bucket récursivement.
	else{
		return get_bucket_value_from_linked_list(b->next,key);
	}
	
}

/*récupère la valeur du bucket ayant la clé donnée si il existe, sinon 
 * retourn NULL.*/
const void* get_Htable_value(Htable* htable, const char* key){
	/*Si les arguments sont nuls, le retour est nul*/
	if(htable == NULL || key == NULL){
		return NULL;
	}
	
	//on trouve l'alvéole à laquelle doit se trouver le bucket avec la key donnée.
	size_t hash = hash_function(key, htable->size);
	//on retourne la valeur du bucket ayant la key donnée si elle existe.
	return get_bucket_value_from_linked_list(&(htable->buckets[hash]), key);	
}



/* ======================================================================
 * Provided: CSV file parser
 * ======================================================================
 */

typedef char* csv_row;
typedef const char* csv_const_row;

/** ----------------------------------------------------------------------
 ** Allocate and read a CSV row from a file
 **/
csv_row read_row(FILE* f)
{
    char line[CSV_MAX_LINE_SIZE + 1] = "";
    fgets(line, CSV_MAX_LINE_SIZE, f);
    line[strcspn(line, "\r\n")] = '\0'; // remove trailing '\n'
    size_t len = strlen(line);

    assert(len < CSV_MAX_LINE_SIZE); /* We should not have lines that long...
                                      * Not handled in this homework anyway!
                                      * Should be properly handled in real-life appli.
                                      */

    csv_row row;
    if ((row = calloc(len + 1, sizeof(char))) == NULL) {
        return NULL;
    }
    strncpy(row, line, len);

    return row;
}

/** ----------------------------------------------------------------------
 ** Write a CSV row to a file
 **/
void write_row(FILE* out, const csv_const_row row, size_t ignore_index)
{
    size_t len = strlen(row);
    size_t current_element = 0;
    for (size_t i = 0; i < len; ++i) {
        if (row[i] == CSV_SEPARATOR) {
            ++current_element;
        }
        if (current_element != ignore_index && (ignore_index != 0 || current_element != ignore_index + 1 || row[i] != CSV_SEPARATOR)) {
            fprintf(out, "%c", row[i]);
        }
    }
}

/** ----------------------------------------------------------------------
 ** Write 2 CSV rows side-by-side to a file
 **/
void write_rows(FILE* out, const csv_const_row row1, const csv_const_row row2, size_t ignore_index)
{
    write_row(out, row1, (size_t) -1);
    fprintf(out, "%c", CSV_SEPARATOR);
    write_row(out, row2, ignore_index);
    fprintf(out, "\n");
}

/** ----------------------------------------------------------------------
 ** Copy and return the i'th element in the row
 **/
char* row_element(const csv_const_row row, size_t index)
{
    size_t len = strlen(row);
    size_t start = 0, end = 0;
    size_t current_element = 0;
    for (size_t i = 0; i < len; ++i) {
        if (row[i] == CSV_SEPARATOR || i == len - 1) {
            ++current_element;
            if (current_element == index) {
                start = i + 1;
            } else if (current_element == index + 1) {
                end = (i == len - 1) ? len : i;
                break;
            }
        }
    }

    if (end > 0) { // success
        size_t elem_len = end - start;
        char* element;
        if ((element = calloc(elem_len + 1, sizeof(char))) == NULL) {
            return NULL;
        }
        element[elem_len] = '\0';
        strncpy(element, &row[start], elem_len);
        return element;
    } else {
        return NULL;
    }
}


/* ======================================================================
 * Part II -- Hashjoin
 * ======================================================================
 */
 
/* ****************************************
 * TODO : add your own code here.
 * **************************************** */
 
 /*Retourne la valeur de la ligne, sans la clé*/
char* row_value(const csv_const_row row, size_t index){
	//initialisation de la valeur.
	char* value = "";
	size_t i = 0;
	
	//premier element de la ligne.
	char* elem = row_element(row, i);
	while(elem != NULL){
		//ajout de l'élément si son index n'est pas celui de la clé.
		if(i != index){
			strcat(value, elem);
			strcat(value, ", ");
		}
		
		//calcul du prochain élément
		++i;
		elem = row_element(row, i);
		
	}
	//retourne la valeur.
	return value;
	
}

/*Comme son nom l'indique, on scanne la deuxieme relation et on écrit dans le fichier
 * les éléments donc l'index est déjà contenu dans la hashtable.*/
void scan_relation_two_and_print_into_file(Htable* htable, FILE* in2, FILE* out,size_t col1, size_t col2){
	
	while(1){
		//tant que la ligne peut être lue, on reste dans la boucle.
		const csv_const_row r2 = read_row(in2);
		if(r2 == NULL){
			break;
		}
		
		//on trouve la key
		char* key = row_element(r2, col2);
		//on trouve la valeur associée à cette key dans la htable, donc du coup dans la première relation.
		const char* value = get_Htable_value(htable, key);
		
		//si cette valeur a pu être trouvée, on fait la concaténation avec la clé et on écrit la ligne dans le fichier de sortie.
		if( value != NULL){
			char* val = key;
			strcat(val, value);
			csv_const_row r1 = val;
			write_rows(out, r1, r2, col2);
		}
	}
}




/*Joint les deux relations dans un nouveau fichier*/
int hash_join(FILE* in1, FILE* in2, FILE* out, size_t col1, size_t col2, size_t max_size){
	//détérmination de la taille de mémoire à allouer.
	size_t size = (max_size/sizeof(bucket));
	
	//instantiation et construction de la htable et contrôle d'erreur.
	Htable* htable;
	htable = construct_Htable(size);
	if(htable == NULL){
		return 1;
	}
	
	while(1){
		//instantiation d'une ligne de la première relation
		csv_const_row r1 = read_row(in1);
		
		//on trouve sa clé et sa valeur
		const char* key = row_element(r1, col1);
		const char* value = row_value(r1, col1);
		
		//on ajoute cette ligne à la htable.
		add_Htable_value(htable, key, value);
		
		//si la htable est pleine ou que r1 est vide (fin du fichier)...
		if((htable->size * HASH_TABLE_LOAD_FACTOR) > htable->entries || r1 == NULL){
			//on s'assure qu'on se trouve au début du deuxième fichier.
			fseek(in2, 0, SEEK_SET);
			//on scanne et on imprime la relation deux et on imprime le résultat dans le fichier de sortie.
			scan_relation_two_and_print_into_file(htable, in2, out, col1, col2);
			//on efface la htable et on 
			delete_Htable_and_content(htable);
			//contrôle que la htable est bien effacée.
			if(htable->buckets != NULL){
				return 1;
			}
			/*si on est rentré dans la condition à cause qu'on est à la fin du fichier
			il faut sortir de la boucle*/
			if(r1 == NULL){
				return 0;
			}
			//sinon c'est que la htable était pleine, donc il faut en reconstruire une pour finir la jointure.
			htable = construct_Htable(size);
			
			if(htable == NULL){
				return 1;
			}
		}
	}
	return 0;
}

/* ======================================================================
 * Provided: main()
 * ======================================================================
 */

int main(void)
{
    FILE* in1 = ask_filename_and_open("Entrez le nom du premier fichier : ", "r");
    if (in1 == NULL) {
        return EXIT_FAILURE;
    }

    FILE* in2 = ask_filename_and_open("Entrez le nom du second  fichier : ", "r");
    if (in2 == NULL) {
        fclose(in1);
        return EXIT_FAILURE;
    }

    FILE* out = ask_filename_and_open("Entrez le nom du fichier où écrire le résultat : ", "w");
    if (out == NULL) {
        fclose(in1);
        fclose(in2);
        return EXIT_FAILURE;
    }

    size_t col1 = ask_size_t("Entrez l'index de la colonne à joindre dans le premier fichier : "),
           col2 = ask_size_t("Entrez l'index de la colonne à joindre dans le second  fichier : ");

    int success = hash_join(in1, in2, out, col1, col2,ask_size_t("Entrez le budget mémoire autorisé (en octets) : "));

    fclose(in1);
    fclose(in2);
    fclose(out);

    return success;
}
