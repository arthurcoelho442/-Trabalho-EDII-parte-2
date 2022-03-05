#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "suffix.h"

void bubblesort(Suffix** a, int n);
void selectionsort(Suffix** a,int n);
void insertionsort(Suffix** a, int n);
void shellsort(Suffix** a,int n);
void quicksort(Suffix** a, int l, int r);
void mergeAB(Suffix** a,Suffix** b,Suffix** c,int N,int M);
void mergesort(Suffix** a, int l, int r);
void heapsort(Suffix** a, int l, int r);

void printCounters(char *s);
void resetCounters();

#endif
