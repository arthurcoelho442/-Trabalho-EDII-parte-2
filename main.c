#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "str.h"
#include "suffix.h"

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
    char aux[1000];
    double tempo;
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
                printf("System qsort:   ");
                init = clock();                             //pega o clock atual
                qsort((void*)aSuf, N, sizeof(char*), comp_suf_array);                                       
                fim = clock();                              //pega clock final da execução do algoritmo
                tempo = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printf("%f(s)\n", tempo);
                printf("sort_algo:   ");
                aSuf = create_suf_array(texto, N);  
                init = clock();                             //pega o clock atual
                sort_suf_array(aSuf, N);
                fim = clock();                              //pega clock final da execução do algoritmo
                tempo = (double)(fim - init)/CLOCKS_PER_SEC;//numero de clocks executados dividido por qtd de clocks executados em um segundo
                printf("%f(s)\n", tempo); 
                break;
            case 'c':
                contexto = atoi(argv[3]);
                query = create_string(argv[4]);
                sort_suf_array(aSuf, N);
                procuraSuffix(aSuf, N, query, contexto, texto);
                break;
            case 's':
                contexto = atoi(argv[3]);
                sort_suf_array(aSuf, N);
                scanf("%[^\n]s", aux);
                scanf("%*[^\n]");
                scanf("%*c");
                printf("|%s|\n", aux);
                while(!isspace(aux[0]) || strlen(aux)>1) {
                    query = create_string(aux);
                    procuraSuffix(aSuf, N, query, contexto, texto);
                    scanf("%[^\n]s", aux);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("|%s|\n", aux);
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
