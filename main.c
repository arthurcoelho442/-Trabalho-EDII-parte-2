#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
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
    /*char text[N];
    fgetc(entrada);
    int cont = 0;
    while (!feof(entrada)){        
        char c = fgetc(entrada);
        if(cont>1){
            char ant = text[cont-1];
            if(c == ' ' &&  ant != ' ')
                text[cont++] = c;
            else if(c == '\n' &&  ant != '\n')
                text[cont++] = c;
        }else if(c != '\n' && c != ' ')
            text[cont++] = c;
    }*/
    //printf("%s\n", text);
    String* texto = create_string(text);
    Suffix** aSuf = create_suf_array(texto, N);
    
    while ((opt = getopt(argc, argv, "aorcs")) != -1){
        switch (opt) {
            case 'a':
                print_suf_array(aSuf, N);
                break;
            case 'o':
                sort_suf_array(aSuf, N);
                print_suf_array(aSuf, N);
                break;
            case 'r':
                break;
            case 'c':
                break;
            case 's':
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
