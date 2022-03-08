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
    FILE* entrada;                                          //Arquivo de entrada
    FILE* saida;                                            //Arquivo de saida
    int opt;
    
    //Abre o arquivo de Entrada e o de Saida
    entrada = fopen(argv[2], "r+");
    saida = fopen("saida.txt", "a+");

    //Verifica se o arquivo de Entrada existe
    if (entrada == NULL) {
        printf("\n\tErro Arquivo de entrada não encontrado\n\n");
        return 0;
    }

    //Le numero de caracteres do arquivo de entrada (Primeira linha do arquivo)
    int N;
    fscanf(entrada, "%d", &N);
    
    //Le texto (A partir da segunda linha até a ultima linha da arquivo)
    char text[N];
    fscanf(entrada, "%s", text);

    //Tira caracteres extras  de espaco em branco e quebra de linha
    char palavra[100];
    while (fscanf(entrada, "%s", palavra) != EOF){        
        strcat(text, " ");
        strcat(text, palavra);
    }

    String* texto = create_string(text);
    N = strlen(text);

    //Cria Array de Sufixos
    Suffix** aSuf = create_suf_array(texto, N);

    int contexto, count = 0;
    String* query;
    char pesquisa[1024];
    double time;
    clock_t init, fim;
    
    while ((opt = getopt(argc, argv, "aorcs")) != -1){
        switch (opt) {
            //Imprime Array de Sufixos
            case 'a':
                print_suf_array(aSuf, N);
                break;

            //Imprime Array de Sufixos Ordenadamente
            case 'o':
                //Ordena com system qsort
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
                    printf("\nEscolha o proximo algoritmo de ordenacao");
                    printf("\n[1] - bubblesort");
                    printf("\n[2] - selectionsort");
                    printf("\n[3] - insertionsort");
                    printf("\n[4] - shellsort");
                    printf("\n[5] - quicksort");
                    printf("\n[6] - heapsort");
                    printf("\nsua escolha: ");
                    scanf("%d", &escolha);

                    char alg[100];
                    init = clock();                             //pega o clock atual
                    switch (escolha){
                        //Ordena com bubblesort
                        case 1:
                            printf("\nMy sort: bubblesort\n");
                            strcpy(alg, "bubblesort");
                            bubblesort(aSuf,N);
                            break;
                        //Ordena com selectionsort
                        case 2:
                            printf("\nMy sort: selectionsort\n");
                            strcpy(alg, "selectionsort");
                            selectionsort(aSuf,N);
                            break;
                        //Ordena com insertionsort
                        case 3:
                            printf("\nMy sort: insertionsort\n");
                            strcpy(alg, "insertionsort");
                            insertionsort(aSuf,N);
                            break;
                        //Ordena com shellsort
                        case 4:
                            printf("\nMy sort: shellsort\n");
                            strcpy(alg, "shellsort");
                            shellsort(aSuf,N);
                            break;
                        //Ordena com quicksort    
                        case 5:
                            printf("\nMy sort: quicksort\n");
                            strcpy(alg, "quicksort");
                            quicksort(aSuf,0,N-1);
                            break;
                        //Ordena com heapsort 
                        case 6:
                            printf("\nMy sort: heapsort\n");
                            strcpy(alg, "heapsort");
                            heapsort(aSuf,0,N-1);
                            break;
                        default :
                            exit = 1;
                            break;
                    }
                    fim = clock();                              //pega clock final da execução do algoritmo
                    time = (double)(fim - init)/CLOCKS_PER_SEC; //numero de clocks executados dividido por qtd de clocks executados em um segundo
                
                    if(exit == 1) break;
                    else {
                        print_suf_array(aSuf, N);
                        if (estatisticas)
                            printCounters(alg, time);   //Imprime estatisticos dos algoritmos
                    }
                }
                break;

            //Imprime Array de Sufixos Ordenadamente e imprime o tempo gasto por cada um  
            case 'r':
                init = clock();                                         //pega o clock atual
                qsort((void*)aSuf, N, sizeof(char*), comp_suf_array);   //Ordena array de sufixos com system qsort
                fim = clock();                                          //pega clock final da execução do algoritmo
                time = (double)(fim - init)/CLOCKS_PER_SEC;             //numero de clocks executados dividido por qtd de clocks executados em um segundo
                printCounters("System qsort:", time);

                init = clock();                             
                bubblesort(aSuf,N);                         //Ordena array de sufixos com system qsort
                fim = clock();                              
                time = (double)(fim - init)/CLOCKS_PER_SEC; 
                printCounters("bubblesort", time);

                init = clock();                             
                selectionsort(aSuf,N);                      //Ordena array de sufixos com system qsort
                fim = clock();                              
                time = (double)(fim - init)/CLOCKS_PER_SEC; 
                printCounters("selectionsort", time);

                init = clock();                             
                insertionsort(aSuf,N);                      //Ordena array de sufixos com system qsort
                fim = clock();                              
                time = (double)(fim - init)/CLOCKS_PER_SEC; 
                printCounters("insertionsort", time);

                init = clock();                             
                shellsort(aSuf,N);                          //Ordena array de sufixos com system qsort
                fim = clock();                              
                time = (double)(fim - init)/CLOCKS_PER_SEC; 
                printCounters("shellsort", time);

                init = clock();                             
                quicksort(aSuf,0,N-1);                      //Ordena array de sufixos com system qsort
                fim = clock();                              
                time = (double)(fim - init)/CLOCKS_PER_SEC; 
                printCounters("quicksort", time);
                
                init = clock();                             
                heapsort(aSuf,0,N-1);                       //Ordena array de sufixos com system qsort
                fim = clock();                              
                time = (double)(fim - init)/CLOCKS_PER_SEC; 
                printCounters("heapsort", time);                
                break;

            //Busca uma query, previamente passada na linha de comando, e imprime suas ocorrencias
            //dentro de um contexto, tbm previamente passado na linha de comando,
            //ignorando letras maiusculas e minusculas
            case 'c':
                contexto = atoi(argv[3]);
                query = create_string(argv[4]);
                sort_suf_array(aSuf, N);    //Ordena array de sufixos
                procuraSuffix(aSuf, N, query, contexto, texto); //Busca pela query no array de sufixo e imprime dentro de um contexto
                destroy_string(query);
                break;
            
            //Busca uma query, passada dinamicamente por meio do teclado, e imprime suas ocorrencias
            //dentro de um contexto, previamente passado na linha de comando,
            //ignorando letras maiusculas e minusculas
            case 's':
                contexto = atoi(argv[3]);
                sort_suf_array(aSuf, N);
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
    //Libera memoria alocada
    destroy_string(texto);
    destroy_suf_array(aSuf, N);
    
    //Fecha os arquivos
    fclose(entrada);
    fclose(saida);

    return EXIT_SUCCESS;
}
