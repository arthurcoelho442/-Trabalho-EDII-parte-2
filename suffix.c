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

int rank(Suffix* *a, int N, String *query);