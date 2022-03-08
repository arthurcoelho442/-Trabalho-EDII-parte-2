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
    int contexto, count = 0;
    String* query;
    char pesquisa[1024];
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

                int escolha=0, exit=0, estatisticas=0;

                printf("\nImprimrir estatisticas");
                printf("\n[1] - Nao");
                printf("\n[2] - Sim");
                printf("\nsua escolha: ");
                scanf("%d", &estatisticas);
                estatisticas--;

                while(1){
                    destroy_suf_array(aSuf,N);
                    aSuf = create_suf_array(texto, N);
                    printf("\nEscolha o proximo algoritmo de ordenacao");
                    printf("\n[1] - bubblesort");
                    printf("\n[2] - selectionsort");
                    printf("\n[3] - insertionsort");
                    printf("\n[4] - shellsort");
                    printf("\n[5] - quicksort");
                    printf("\n[6] - heapsort");
                    printf("\n[7] - exit");
                    printf("\nsua escolha: ");
                    scanf("%d", &escolha);

                    char alg[100];
                    init = clock();                             //pega o clock atual
                    switch (escolha){
                        case 1://bubblesort
                            printf("\nMy sort: bubblesort\n");
                            strcpy(alg, "bubblesort");
                            bubblesort(aSuf,N);
                            break;
                        case 2://selectionsort
                            printf("\nMy sort: selectionsort\n");
                            strcpy(alg, "selectionsort");
                            selectionsort(aSuf,N);
                            break;
                        case 3://insertionsort
                            printf("\nMy sort: insertionsort\n");
                            strcpy(alg, "insertionsort");
                            insertionsort(aSuf,N);
                            break;
                        case 4://shellsort
                            printf("\nMy sort: shellsort\n");
                            strcpy(alg, "shellsort");
                            shellsort(aSuf,N);
                            break;
                        case 5://quicksort
                            printf("\nMy sort: quicksort\n");
                            strcpy(alg, "quicksort");
                            quicksort(aSuf,0,N-1);
                            break;
                        case 6://heapsort
                            printf("\nMy sort: heapsort\n");
                            strcpy(alg, "heapsort");
                            heapsort(aSuf,0,N-1);
                            break;
                        default :
                            exit = 1;
                            break;
                    }
                    fim = clock();                              //pega clock final da execução do algoritmo
                    time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                
                    if(exit == 1) break;
                    else {
                        print_suf_array(aSuf, N);
                        if (estatisticas)
                            printCounters(alg, time);
                    }
                }
                break;
            case 'r':
                init = clock();                             //pega o clock atual
                qsort((void*)aSuf, N, sizeof(char*), comp_suf_array);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("System qsort:", time);

                destroy_suf_array(aSuf,N);
                aSuf = create_suf_array(texto, N);
                init = clock();                             //pega o clock atual
                bubblesort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("bubblesort", time);

                destroy_suf_array(aSuf,N);
                aSuf = create_suf_array(texto, N);
                init = clock();                             //pega o clock atual
                selectionsort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("selectionsort", time);

                destroy_suf_array(aSuf,N);
                aSuf = create_suf_array(texto, N);
                init = clock();                             //pega o clock atual
                insertionsort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("insertionsort", time);

                destroy_suf_array(aSuf,N);
                aSuf = create_suf_array(texto, N);
                init = clock();                             //pega o clock atual
                shellsort(aSuf,N);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("shellsort", time);

                destroy_suf_array(aSuf,N);
                aSuf = create_suf_array(texto, N);
                init = clock();                             //pega o clock atual
                quicksort(aSuf,0,N-1);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("quicksort", time);
                
                destroy_suf_array(aSuf,N);
                aSuf = create_suf_array(texto, N);
                init = clock();                             //pega o clock atual
                heapsort(aSuf,0,N-1);
                fim = clock();                              //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("heapsort", time);
                
                break;
            case 'c':
                contexto = atoi(argv[3]);
                query = create_string(argv[4]);
                qsort((void*)aSuf, N, sizeof(char*), comp_suf_array);
                procuraSuffix(aSuf, N, query, contexto, texto);
                destroy_string(query);
                break;
            case 's':
                contexto = atoi(argv[3]);
                qsort((void*)aSuf, N, sizeof(char*), comp_suf_array);
                // Pega a linha digitada
                while(1){
                    int c = fgetc(stdin);
                    pesquisa[count++] = (char)c;
                    if (c == '\n'){
                        count--;
                        break;
                    }
                }
                pesquisa[count] = '\0';
                // retorna caso não haja query
                if (count == 0)
                    return 0;
                while(1) {
                    query = create_string(pesquisa);
                    procuraSuffix(aSuf, N, query, contexto, texto);
                    printf("\n");
                    // Pega a linha digitada
                    count = 0;
                    while(1){
                        int c = fgetc(stdin);
                        pesquisa[count++] = (char)c;
                        if (c == '\n'){
                            count--;
                            break;
                        }
                    }
                    pesquisa[count] = '\0';
                    // retorna caso não haja query
                    if (count == 0)
                        return 0;
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
