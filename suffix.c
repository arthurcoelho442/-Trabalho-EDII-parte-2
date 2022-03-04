#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suffix.h"

Suffix* create_suffix(String *s, int index){
    Suffix *suf = (Suffix*)malloc(sizeof(Suffix));
    suf->index = index;
    suf->s = s;
    return suf;
}

void destroy_suffix(Suffix *suf){
    free(suf);
}

void print_suffix(Suffix *suf){
    String* text = suf->s;
    print_substring(text, suf->index, text->len);
}

Suffix** create_suf_array(String *text, int N){
    Suffix** a = malloc(N * sizeof(Suffix*));
    for(int i = 0; i < N; i++)
        a[i] = create_suffix(text, i);
    
    return a;
}

void destroy_suf_array(Suffix** a, int N){
    for(int i = 0; i < N; i++)
        destroy_suffix(a[i]);
    free(a);
    return;
}

void print_suf_array(Suffix** a, int N){
    for(int i = 0; i < N; i++){
        print_suffix(a[i]);
        printf("\n");
    }
}

// Use uma (ou mais) funcoes deste tipo para ordenar
// o arry de sufixos usando o qsort e outro metodo de sua escolha
int comp_suf_array(const void *pa, const void * pb){
    //const Suffix* a = pa;
    //const Suffix* b = pb;
    
    //char* text = pa->s->c;
    //printf("\n%s\n", text);
    
    //char* str1 = text+(a->index);
    //char* str2 = text+(b->index);
    printf("\n");
    printf("%ld ||  ", (Suffix*)pa);
    printf("%ld\n", (Suffix*)pb);
    char* text = ((Suffix*)pa)->s->c;
    char* str1 = text+((Suffix*)pa)->index;
    char* str2 = text+((Suffix*)pb)->index;
    //printf("%s  //  ", str1);
    //printf("%s\n", str2);
    return strcmp(str1, str2);
}
void sort_suf_array(Suffix* *a, int N){
    char* text = a[0]->s->c;
    
    for(int i=0; i<N-1; i++){
        for(int j=i+1; j<N; j++){        
            char* str1 = text+(a[i]->index);
            char* str2 = text+(a[j]->index);
            
            if(strcmp(str1, str2) > 0){
                Suffix* aux = a[j];
                a[j] = a[i];
                a[i] = aux;
            }
        }
    }
}

void procuraSuffix(Suffix* *a, int N, String* query, int contexto, String* texto){
    int igual = 0, indice_inicio = 0, indice_final = 0;
    for(int i = 0; i < N; i++){
        igual = 0;
        String* text = a[i]->s;
        igual = equals_substring(text, a[i]->index, text->len, query);
        if(igual){
            //texto->c[query->len+a[i]->index]
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

int rank(Suffix* *a, int N, String *query);