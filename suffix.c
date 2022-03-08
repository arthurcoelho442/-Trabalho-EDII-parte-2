#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suffix.h"

//Cria um suffixo com o id passado e a string
Suffix* create_suffix(String *s, int index){
    Suffix *suf = (Suffix*)malloc(sizeof(Suffix));
    suf->index = index;
    suf->s = s;
    return suf;
}

//Libera da memoria um suffixo
void destroy_suffix(Suffix *suf){
    free(suf);
}

//printda um suffixo
void print_suffix(Suffix *suf){
    String* text = suf->s;
    print_substring(text, suf->index, text->len);
}

//Cria um vetor de suffixos
Suffix** create_suf_array(String *text, int N){
    Suffix** a = malloc(N * sizeof(Suffix*));
    for(int i = 0; i < N; i++)
        a[i] = create_suffix(text, i);
    
    return a;
}

//Destroi o vetor de suffixo
void destroy_suf_array(Suffix** a, int N){
    for(int i = 0; i < N; i++)
        destroy_suffix(a[i]);
    free(a);
    return;
}

//Printa todos os suffixo do vetor|
void print_suf_array(Suffix** a, int N){
    for(int i = 0; i < N; i++){
        print_suffix(a[i]);
        printf("\n");
    }
}

// Utilizado para ordenar o array de sufixos usando o qsort
int comp_suf_array(const void *pa, const void * pb){
    char* str1 = (*(Suffix**)pa)->s->c + (*(Suffix**)pa)->index;
    char* str2 = (*(Suffix**)pb)->s->c + (*(Suffix**)pb)->index;
    return strcmp(str1, str2);
}

//Procura a query no vetor de suffixos
void procuraSuffix(Suffix* *a, int N, String* query, int contexto, String* texto){
    int igual = 0, indice_inicio = 0, indice_final = 0;
    for(int i = 0; i < N; i++){
        igual = 0;
        String* text = a[i]->s;
        igual = equals_substring(text, a[i]->index, text->len, query);
        if(igual){
            if(a[i]->index - contexto <=0){
                indice_inicio = 0;
            } else {
                indice_inicio = a[i]->index - contexto;
            }
            if(a[i]->index + contexto >= texto->len){
                indice_final = texto->len - 1;
            } else {
                indice_final = a[i]->index + query->len + contexto;
            }
            print_substring(texto, indice_inicio, indice_final);
            printf("\n"); 
        } 
    }
}

//Faz nada
int rank(Suffix* *a, int N, String *query);