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

                int escolha, exit=0;
                while(escolha){
                    printf("\nEscolha o proximo algoritmo de ordenacao");
                    printf("\n[1] - bubblesort");
                    printf("\n[2] - selectionsort");
                    printf("\n[3] - insertionsort");
                    printf("\n[4] - shellsort");
                    printf("\n[5] - quicksort");
                    printf("\n[6] - heapsort\n");
                    scanf("%d", &escolha);
                    switch (escolha){
                        case 1://bubblesort
                            printf("\nMy sort: bubblesort\n");
                            bubblesort(aSuf,N);
                            break;
                        case 2://selectionsort
                            printf("\nMy sort: selectionsort\n");   
                            selectionsort(aSuf,N);
                            break;
                        case 3://insertionsort
                            printf("\nMy sort: insertionsort\n");
                            insertionsort(aSuf,N);
                            break;
                        case 4://shellsort
                            printf("\nMy sort: shellsort\n");
                            shellsort(aSuf,N);
                            break;
                        case 5://quicksort
                            printf("\nMy sort: quicksort\n");
                            quicksort(aSuf,0,N-1);
                            break;
                        case 6://heapsort
                            printf("\nMy sort: heapsort\n");
                            heapsort(aSuf,0,N-1);
                            break;
                        default :
                            exit = 1;
                            break;
                    }
                    if(exit == 1) break;
                    else print_suf_array(aSuf, N);
                }
                break;
            case 'r':
                init = clock();                             //pega o clock atual
                qsort((void*)aSuf, N, sizeof(char*), comp_suf_array);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("System qsort:", time);

                init = clock();                             //pega o clock atual
                bubblesort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("bubblesort", time);

                init = clock();                             //pega o clock atual
                selectionsort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("selectionsort", time);

                init = clock();                             //pega o clock atual
                insertionsort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("insertionsort", time);

                init = clock();                             //pega o clock atual
                shellsort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("shellsort", time);

                init = clock();                             //pega o clock atual
                quicksort(aSuf,0,N-1);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("quicksort", time);
                
                init = clock();                             //pega o clock atual
                heapsort(aSuf,0,N-1);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
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
