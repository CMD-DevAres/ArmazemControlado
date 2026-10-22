#include <stdio.h>
#include <stdlib.h>
#include "../include/armazem.h"


int alocar_sistema(PlantaIndustrial *p, SistemaControle *c) {
    p->qtd_linhas = 4; //ponteiro acessa qtd de linhas e atribui 4
    p->qtd_colunas = 5; //ponteiro acessa qtd de colunas e atribui 5

    p->vetor_medias = malloc(4 * sizeof(float *)); //ponteiro acessa vetor_medias e aloca memoria para 4 medias

    if (p->vetor_medias == NULL) { 
        return 0;
    }
    
    c->vetor_atuadores = malloc(4 * sizeof(int)); // ponteiro acessa vetor_atuadores e aloca memoria para 4 atuadores

    if (c->vetor_atuadores == NULL) {
        free(p->vetor_medias); // libera memoria alocada para vetor_medias
        p->vetor_medias = NULL; // atribui NULL ao ponteiro vetor_medias
        return 0;
    }

    return 1; //retorna 1 se a alocação ocorrer corretamente

}

void inicializar_sensores(PlantaIndustrial *p) {
    
}