#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "str.h"
#include "suffix.h"
#include "Algoritmos.h"

int main(int argc, char **argv){
    FILE* entrada;                                          //Arquivo de entrada para o sistema
    FILE* saida;                                            //Arquivo de saida
    int opt;
    
    //Abre o arquivo de Entrada e o de Saida
    entrada = fopen(argv[2], "r+");
    saida = fopen("saida.txt", "a+");

    //Verifica se o arquivo de Entrada é existente
    if (entrada == NULL) {
        printf("\n\tErro Arquivo de entrada não encontrado\n\n");
        return 0;
    }
    int N;
    fscanf(entrada, "%d", &N);
    
    char text[N];
    char palavra[100];
    fscanf(entrada, "%s", text);
    while (fscanf(entrada, "%s", palavra) != EOF){        
        strcat(text, " ");
        strcat(text, palavra);
    }

    String* texto = create_string(text);
    N = strlen(text);
    Suffix** aSuf = create_suf_array(texto, N);
    int contexto;
    String* query;
    char pesquisa[1000];
    double time;
    clock_t init, fim;
    while ((opt = getopt(argc, argv, "aorcs")) != -1){
        switch (opt) {
            case 'a':
                print_suf_array(aSuf, N);
                break;
            case 'o':
                printf("\nSystem qsort:\n");                                        
                qsort((void*)aSuf, N, sizeof(char*), comp_suf_array);
                print_suf_array(aSuf, N); 

                printf("\nMy_sort_algo:\n");
                aSuf = create_suf_array(texto, N);
                sort_suf_array(aSuf, N);
                print_suf_array(aSuf, N);
                break;
            case 'r':
                init = clock();                             //pega o clock atual
                qsort((void*)aSuf, N, sizeof(char*), comp_suf_array);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                print_suf_array(aSuf, N);
                printCounters("System qsort:", time);

                init = clock();                             //pega o clock atual
                bubblesort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                print_suf_array(aSuf, N);
                printCounters("bubblesort", time);

                init = clock();                             //pega o clock atual
                selectionsort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                print_suf_array(aSuf, N);
                printCounters("selectionsort", time);

                init = clock();                             //pega o clock atual
                insertionsort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                print_suf_array(aSuf, N);
                printCounters("insertionsort", time);

                init = clock();                             //pega o clock atual
                shellsort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                print_suf_array(aSuf, N);
                printCounters("shellsort", time);

                init = clock();                             //pega o clock atual
                quicksort(aSuf,0,N-1);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                print_suf_array(aSuf, N);
                printCounters("quicksort", time);

                init = clock();                             //pega o clock atual
                mergesort(aSuf,0,N-1);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                print_suf_array(aSuf, N);
                printCounters("mergesort", time);
                
                init = clock();                             //pega o clock atual
                heapsort(aSuf,0,N-1);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                print_suf_array(aSuf, N);
                printCounters("heapsort", time);
                
                break;
            case 'c':
                contexto = atoi(argv[3]);
                query = create_string(argv[4]);
                sort_suf_array(aSuf, N);
                procuraSuffix(aSuf, N, query, contexto, texto);
                destroy_string(query);
                break;
            case 's':
                contexto = atoi(argv[3]);
                sort_suf_array(aSuf, N);
                scanf("%[^\n]s", pesquisa);
                scanf("%*[^\n]");
                scanf("%*c");
                while(!isspace(pesquisa[0]) || strlen(pesquisa)>1) {
                    query = create_string(pesquisa);
                    procuraSuffix(aSuf, N, query, contexto, texto);
                    scanf("%[^\n]s", pesquisa);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    destroy_string(query);
                }
                break;
            default:
                break;
        }
    }
    destroy_string(texto);
    destroy_suf_array(aSuf, N);
    fclose(entrada);
    fclose(saida);
    return EXIT_SUCCESS;
}
