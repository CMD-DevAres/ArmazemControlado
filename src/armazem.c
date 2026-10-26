#include <stdio.h>
#include <stdlib.h>
#include "../include/armazem.h"


int alocar_sistema(PlantaIndustrial *p, SistemaControle *c, int l, int c_col) {
    int i, j; //contadores utilizados nos ciclos

    p->qtd_linhas = l; //ponteiro acessa qtd de linhas e atribui l
    p->qtd_colunas = c_col; //ponteiro acessa qtd de colunas e atribui c_col

    p->matriz_sensores = malloc(l * sizeof(float *)); //aloca memoria para os ponteiros das linhas da matriz

    if (p->matriz_sensores == NULL) {
        return 0; //retorna 0 se a alocacao da matriz falhar
    }

    for (i = 0; i < l; i++) { //percorre todas as linhas da matriz
        p->matriz_sensores[i] = malloc(c_col * sizeof(float)); //aloca memoria para as colunas de cada linha

        if (p->matriz_sensores[i] == NULL) {
            for (j = 0; j < i; j++) { //percorre as linhas que foram alocadas anteriormente
                free(p->matriz_sensores[j]); //libera memoria da linha alocada
            }

            free(p->matriz_sensores); //libera memoria dos ponteiros das linhas
            p->matriz_sensores = NULL; //atribui NULL ao ponteiro da matriz

            return 0; //retorna 0 se a alocacao de alguma linha falhar
        }
    }

    p->vetor_medias = malloc(l * sizeof(float)); //ponteiro acessa vetor_medias e aloca memoria para l medias

    if (p->vetor_medias == NULL) {
        for (i = 0; i < l; i++) { //percorre todas as linhas da matriz
            free(p->matriz_sensores[i]); //libera memoria de cada linha
        }

        free(p->matriz_sensores); //libera memoria dos ponteiros das linhas
        p->matriz_sensores = NULL; //atribui NULL ao ponteiro da matriz

        return 0; //retorna 0 se a alocacao do vetor de medias falhar
    }

    c->vetor_atuadores = malloc(l * sizeof(int)); //ponteiro acessa vetor_atuadores e aloca memoria para um atuador por linha

    if (c->vetor_atuadores == NULL) {
        free(p->vetor_medias); //libera memoria alocada para vetor_medias
        p->vetor_medias = NULL; //atribui NULL ao ponteiro vetor_medias

        for (i = 0; i < l; i++) { //percorre todas as linhas da matriz
            free(p->matriz_sensores[i]); //libera memoria de cada linha
        }

        free(p->matriz_sensores); //libera memoria dos ponteiros das linhas
        p->matriz_sensores = NULL; //atribui NULL ao ponteiro da matriz

        return 0; //retorna 0 se a alocacao dos atuadores falhar
    }

    return 1; //retorna 1 se todas as alocacoes ocorrerem corretamente
}


void inicializar_sensores(PlantaIndustrial *p) {
    int i, j;

    for (i = 0; i < p->qtd_linhas; i++) { //percore 4 linhas da matriz
        for (j = 0; j < p->qtd_colunas; j++) { //percorre 5 colunas de cada linha
            p->matriz_sensores[i][j] = 0.0; //iniciar peso da prateleira com zero
        }
    }
    
}