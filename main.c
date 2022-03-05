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
    double time = 0.000;
    while ((opt = getopt(argc, argv, "aorcs")) != -1){
        switch (opt) {
            case 'a':
                print_suf_array(aSuf, N);
                break;
            case 'o':
                //printf(" ");
                sort_suf_array(aSuf, N);
                print_suf_array(aSuf, N);
                break;
            case 'r':
                bubblesort(aSuf,N);
                print_suf_array(aSuf, N);
                printCounters("bubblesort", time);

                selectionsort(aSuf,N);
                print_suf_array(aSuf, N);
                printCounters("selectionsort", time);

                insertionsort(aSuf,N);
                print_suf_array(aSuf, N);
                printCounters("insertionsort", time);

                shellsort(aSuf,N);
                print_suf_array(aSuf, N);
                printCounters("shellsort", time);

                quicksort(aSuf,0,N-1);
                print_suf_array(aSuf, N);
                printCounters("quicksort", time);

                mergesort(aSuf,0,N-1);
                print_suf_array(aSuf, N);
                printCounters("mergesort", time);
                
                heapsort(aSuf,0,N-1);
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
                    printf("|%s|\n", pesquisa);
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
