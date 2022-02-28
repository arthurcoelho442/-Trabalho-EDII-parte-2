#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "str.h"
#include "suffix.h"

int main(int argc, char **argv){
    FILE* entrada;                                          //Arquivo de entrada para o sistema
    FILE* saida;                                            //Arquivo de saida
    int opt;
    
    //Abre o arquivo de Entrada e o de Saida
    entrada = fopen(argv[3], "r+");
    saida = fopen("saida.txt", "a+");

    //Verifica se o arquivo de Entrada é existente
    if (entrada == NULL) {
        printf("\n\tErro Arquivo de entrada não encontrado\n\n");
        return 0;
    }
    while ((opt = getopt(argc, argv, "aorcs")) != -1){
        switch (opt) {
            case 'a':
                break;
            case 'o':
                break;
            case 'r':
                break;
            case 'c':
                //char texto[100], query[100];
                //int contexto = argv[3];
                //strcpy(texto, argv[1]);
                
                //strcpy(query, argv[3]);
                //printf("\nN = %s, Q = ""%s"", C = %d\n", texto, query, contexto);
                break;
            case 's':
                break;
            default:
                break;
        }
    }

    fclose(entrada);
    fclose(saida);
    return EXIT_SUCCESS;
}
