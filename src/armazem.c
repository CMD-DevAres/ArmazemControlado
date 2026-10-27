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

    for (i = 0; i < p->qtd_linhas; i++) { //percore as linhas da matriz
        for (j = 0; j < p->qtd_colunas; j++) { //percorre as colunas colunas de cada linha
            p->matriz_sensores[i][j] = 0.0; //iniciar peso da prateleira com zero
        }
    }
    
}

void inicializar_atuadores(SistemaControle *c, int l) {
    int i; //contador utilizado no ciclo

    c->total_alarmes = 0; //inicia o contador de alarmes em zero
    c->limite_critico = 400.0; //define o limite critico de carga

    for (i = 0; i < l; i++) { //percorre todos os atuadores
        c->vetor_atuadores[i] = 1; //inicia cada atuador como liberado
    }
}


void processar_dados(PlantaIndustrial *p) {
    int i, j; //contadores utilizados nos ciclos
    float soma; //guarda a soma dos pesos de cada corredor

    for (i = 0; i < p->qtd_linhas; i++) { //percorre todas as linhas da matriz
        soma = 0.0; //reinicia a soma para cada corredor

        for (j = 0; j < p->qtd_colunas; j++) { //percorre todas as colunas de cada linha
            printf("Digite o peso do corredor %d, prateleira %d: ", i + 1, j + 1);
            scanf("%f", &p->matriz_sensores[i][j]); //le o peso informado pelo usuario

            soma += p->matriz_sensores[i][j]; //adiciona o peso a soma do corredor
        }

        p->vetor_medias[i] = soma; //calcula os pesos do corredor
    }
}

void avaliar_seguranca(const PlantaIndustrial *p, SistemaControle *c) {
    int i; //contador utilizado no ciclo

    c->total_alarmes = 0; //reinicia o contador de alarmes

    for (i = 0; i < p->qtd_linhas; i++) { //percorre todos os corredores
        if (p->vetor_medias[i] > c->limite_critico) {
            c->vetor_atuadores[i] = 0; //bloqueia o atuador do corredor
            c->total_alarmes++; //incrementa o contador de alarmes
        } else {
            c->vetor_atuadores[i] = 1; //mantem o atuador liberado
        }
    }
}


void emitir_relatorio(const PlantaIndustrial *p, const SistemaControle *c) {
    int i, j; //contadores utilizados nos ciclos

    printf("\n=== RELATORIO DO ARMAZEM ===\n");

    for (i = 0; i < p->qtd_linhas; i++) { //percorre todos os corredores
        printf("\nCorredor %d:\n", i + 1);

        for (j = 0; j < p->qtd_colunas; j++) { //percorre todas as prateleiras do corredor
            printf("Prateleira %d: %.2f\n", j + 1, p->matriz_sensores[i][j]); //exibe o peso da prateleira
        }

        printf("Somatorio do corredor: %.2f\n", p->vetor_medias[i]);
        
        if (c->vetor_atuadores[i] == 1) {
            printf("Atuador: LIBERADO\n"); //informa que o atuador esta liberado
        } else {
            printf("Atuador: BLOQUEADO\n"); //informa que o atuador esta bloqueado
        }
    }

    printf("\nTotal de alarmes: %d\n", c->total_alarmes); //exibe o total de alarmes
    printf("Limite critico: %.2f\n", c->limite_critico); //exibe o limite critico de carga
}


void liberar_memoria(PlantaIndustrial *p, SistemaControle *c) {
    int i; //contador utilizado no ciclo

    for (i = 0; i < p->qtd_linhas; i++) { //percorre todas as linhas da matriz
        free(p->matriz_sensores[i]); //libera a memoria de cada linha
    }

    free(p->matriz_sensores); //libera a memoria dos ponteiros das linhas
    p->matriz_sensores = NULL; //indica que a matriz nao possui memoria alocada

    free(p->vetor_medias); //libera a memoria do vetor de medias
    p->vetor_medias = NULL; //indica que o vetor nao possui memoria alocada

    free(c->vetor_atuadores); //libera a memoria do vetor de atuadores
    c->vetor_atuadores = NULL; //indica que o vetor nao possui memoria alocada
}
