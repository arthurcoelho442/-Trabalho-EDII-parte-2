#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "suffix.h"

// Algoritmo de ordenação bubblesort
void bubblesort(Suffix** a, int n);

// Algoritmo de ordenação selectionsort
void selectionsort(Suffix** a,int n);

// Algoritmo de ordenação insertionsort
void insertionsort(Suffix** a, int n);

// Algoritmo de ordenação shellsort
void shellsort(Suffix** a,int n);

// Algoritmo de ordenação quicksort
void quicksort(Suffix** a, int l, int r);

// Algoritmo de ordenação heapsort
void heapsort(Suffix** a, int l, int r);

//Imprime as estatisticas do algoritmo
void printCounters(char *s, double time);

//Reseta o valos dos contadores
void resetCounters();

#endif
//Finalizado