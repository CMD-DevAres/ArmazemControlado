#include <stdio.h>
#include <stdlib.h>
#include "../include/armazem.h"


int alocar_sistema(PlantaIndustrial *p, SistemaControle *c, int l, int c_col) {
    p->qtd_linhas = l; //ponteiro acessa qtd de linhas e atribui l
    p->qtd_colunas = c_col; //ponteiro acessa qtd de colunas e atribui c_col

    p->matriz_sensores = malloc(l * sizeof(float *)); //ponteiro acessa matriz_sensores e aloca memoria para l

    if (p->matriz_sensores == NULL) { 
        return 0;
    }
    
    for (int i = 0; i < l; i++) {
    p->matriz_sensores[i] = malloc(c_col * sizeof(float));

    if (p->matriz_sensores[i] == NULL) {
        for (int j = 0; j < i; j++) {
            free(p->matriz_sensores[j]);
        }

        free(p->matriz_sensores);
        p->matriz_sensores = NULL;

        return 0;
    }

}
    


    return 1;
}
