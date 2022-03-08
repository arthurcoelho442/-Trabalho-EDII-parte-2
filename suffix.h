#ifndef SUFFIX_H
#define SUFFIX_H

#include "str.h"

typedef struct {
    String *s;
    int index;
} Suffix;

//Cria um suffixo com o id passado e a string
Suffix* create_suffix(String *s, int index);

//Libera da memoria um suffixo
void destroy_suffix(Suffix *suf);

//printda um suffixo
void print_suffix(Suffix *suf);

//Cria um vetor de suffixos
Suffix** create_suf_array(String *text, int N);

//Destroi o vetor de suffixo
void destroy_suf_array(Suffix* *a, int N);

//Printa todos os suffixo do vetor|
void print_suf_array(Suffix* *a, int N);

// Utilizado para ordenar o array de sufixos usando o qsort
int comp_suf_array(const void *pa, const void * pb);

//Procura a query no vetor de suffixos
void procuraSuffix(Suffix* *a, int N, String* query, int contexto, String* texto);

//Faz nada
int rank(Suffix* *a, int N, String *query);

#endif
