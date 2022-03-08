#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Algoritmos.h"

#define key(A) (A)
#define less(A, B) strLess(A,B)
#define exch(A, B) { Suffix* t = A; A = B; B = t; exchCount++;} 
#define copy(A, B) { A = B; copyCount++; }
#define compexch(A, B) if (less(B, A)) exch(A, B)

/***** contadores das operações ********/
int compCount = 0;//Comparações
int exchCount  = 0;//Trocas
int copyCount  = 0;//Copias

/***** (re)inicialização dos contadores *****/
void resetCounters(){ 
    compCount = 0;
    exchCount = 0;
    copyCount = 0;
}
    
/****    comparaçãdo de dois Suffixos    ****/
/****  e contagem das comparações  ****/
int strLess(Suffix *a, Suffix *b){
    char* text = a->s->c;
    int idA = a->index;
    int idB = b->index;
    
    compCount++;
    for(;;){
        if(text[idA] == '\0')  return (text[idB] != '\0');
        if(text[idB] == '\0')  return 0;
        if(text[idA] < text[idB]) return 1;
        if(text[idA++] > text[idB++]) return 0;

    }
}

/****    impressao das estatisticas dos algoritmos    ****/
void printCounters(char *s, double time){
  printf("\n|%s                               %0.6lf (s)|\n", s, time);
  printf("|%s comparacoes: %d, trocas %d, atribuicoes: %d|", s,compCount, exchCount, copyCount);
  resetCounters();   
}
    
/*****************************************************
*********            bubblesort             **********
*****************************************************/

void bubblesort(Suffix** a, int n){
    int i, j; 
    for(i = 1; i < n; i++)
        for(j = i; j > 0; j--) 
            compexch(a[j-1], a[j]);
}



/*****************************************************
*********          selectionsort            **********
*****************************************************/

void selectionsort(Suffix** a,int n) { 
    int i, j;
    for(i = 0; i < (n-1); i++){ 
        int min = i;
        for(j = i+1; j < n; j++) 
        if (less(a[j], a[min])) copy(min,j);
        exch(a[i], a[min]);
    } 
}
 
/*****************************************************
*********         insertionsort             **********
*****************************************************/

void insertionsort(Suffix** a, int n){ 
    int i;
    for(i = 1; i < n; i++) compexch(a[0], a[i]);
    for(i = 2; i < n; i++){ 
        int j = i; Suffix* v; copy(v,a[i]); 
        while(less(v, a[j-1])) { copy(a[j],a[j-1]); j--; }
        copy(a[j],v); 
    } 
}

/*****************************************************
*********             shellsort             **********
*****************************************************/
   
void shellsort(Suffix** a,int n){ 
    int i, j, h; 
    for(h = 1; h <= (n-2)/3; h = 3*h+1) ;

    for( ; h > 0; h /= 3) 
        for(i = h; i < n; i++){
        int j = i; Suffix* v; copy(v,a[i]); 
        while (j >= h && less(v, a[j-h])){ 
            copy(a[j],a[j-h]); j -= h; 
        }
        copy(a[j],v);
        }       
}

/*****************************************************
*********           quicksort               **********
*****************************************************/

int partition(Suffix** a, int l, int r) { 
    int i = l-1, j = r; Suffix* v = a[r];
    for(;;){ 
        while (less(a[++i], v)) ;
        while (less(v, a[--j])) if (j == l) break;
        if (i >= j) break;
        exch(a[i], a[j]);
    }
    exch(a[i], a[r]);
    return i;
}


void quicksort(Suffix** a, int l, int r){
    int i;
    if (r <= l) return;
    i = partition(a, l, r);
    quicksort(a, l, i-1);
    quicksort(a, i+1, r);
}

/*****************************************************
*******              heapsort                 ********
*****************************************************/

void fixDown(Suffix** a, int k, int N){
    int j;
    while (2*k <= N){
        j = 2*k;
        if (j < N && less(a[j], a[j+1])) j++;
        if (!less(a[k], a[j])) break;
        exch(a[k], a[j]); k = j;
    }
}

#define pq(A) a[l-1+A]

void heapsort(Suffix** a, int l, int r){
    int k, n = r-l+1;
        for (k = n/2; k >= 1; k--) 
        fixDown(&pq(0), k, n);
        while (n > 1){
            exch(pq(1),pq(n)); 
            fixDown(&pq(0), 1, --n); 
        }
}
/****************************************************/