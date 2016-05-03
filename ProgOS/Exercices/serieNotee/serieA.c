/* A FAIRE : complétez le début de ce programme. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N(x) (sizeof(x)/sizeof(*x))

char* copy(char* ret, const char* input){
	size_t l = strlen(input);
	ret = calloc(l , sizeof(char));
	
	size_t i = 0;
	
	while(i < l){
		char c = input[i];
		ret[i] = c;
		++i;
	}
	return ret;
}

char* to_upper_case_all_a(char* ret, const char* input){
	size_t l = strlen(input);
	ret = calloc(l , sizeof(char));
	if(ret == NULL){
		printf("erreur");
		return NULL;
	}
	size_t i = 0;
	
	while(i < l){
		char c = input[i];
		if(c == 'a'){
			ret[i] = 'A';
		}
		else{
			ret[i] = c;
		}
		++i;
	}
	
	return ret;
}

char* split_at_third_space(char* ret, const char* input){
	size_t l = strlen(input);
	ret = calloc(l , sizeof(char));
	size_t i = 0;
	int nb_space = 0;
	
	while(i < l && nb_space < 3){
		char c = input[i];
		if(isspace(c)){
			++nb_space;
			if(nb_space == 3){
				ret[i] = '\0';
				break;
			}
		}
		ret[i] = c;
		++i;
	}
	return ret;	
}

const char* append_hello(char* ret, const char* input){
	size_t l = strlen(input);
	ret = calloc(l+5 , sizeof(char));
	ret = strncpy(ret, input, l);
	ret = strcat(ret, "hello");
	
	return ret;
}

int main() {
    const char* inputs[] = {
      "Hallo Anno! Cammant ca va ? Ahlala...",
      "aaaaa",
      " a a a a a ",
      "Une phrose sons oucun o"
    };

    /* A FAIRE : définissez ici my_functions. */
     /*   my_functions
    
    iterate_over_functions(inputs      , N(inputs),
                           my_functions, N(my_functions));*/
                           
    size_t i = 0;
    while(N(inputs)>i){
		printf("\t->");
		char* ret = NULL;
		ret= copy(ret, inputs[i]);
		printf("%s\n", ret);
		free(ret);
		++i;
	}

    return 0;
}
