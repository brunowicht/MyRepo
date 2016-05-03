#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define VECTOR_PADDING 128

typedef int type_el;

typedef struct {
	size_t size;
	size_t allocated;
	type_el* content;
}vector;




int main(void){
	return 0;
}


vector* vector_construct(vector* v){
	vector* result = v;
	if(result != NULL){
		result->content = calloc(VECTOR_PADDING, sizeof(type_el));
		if(result->content != NULL){
			result->size = 0;
			result->allocated = VECTOR_PADDING;
		}
		else{
			return NULL;
		}
	}
	return result;
}

void vector_delete(vector* v){
	if(v != NULL && v->content != NULL){
		free(v->content);
		v->content = NULL;
		v->size = 0;
		v->allocated = 0;
	}	
}

vector* vector_enlarge(vector* v){
	vector* result = v;
	if(result != NULL){
		type_el* const oldcontent = result->content;
		result->allocated += VECTOR_PADDING;
		if(result->allocated > SIZE_MAX/sizeof(type_el)
		|| (result->content = realloc(result->content, result->allocated * sizeof(type_el))) == NULL){
			result->content = oldcontent;
			result->allocated -= VECTOR_PADDING;
			result = NULL;
		}
	}
	return result;
	
}

size_t vector_push(vector* v, type_el val){
	if(v != NULL){
		while(v->size >= v->allocated){
			if(vector_enlarge(v) == NULL){
				return 0;
			}
		}
		v->content[v->size] = val;
		++(v->size);
		return v->size;
	}
	return 0;
}
