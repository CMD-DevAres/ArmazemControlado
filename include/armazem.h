#ifndef ARMAZEM_H
#define ARMAZEM_H
typedef struct {
    float **matriz_sensores; //guardar peso das prateleiras
    float *vetor_medias; //guarda soma dos pesos de cada corredor
    int qtd_linhas; //guarda quantidade de corredores
    int qtd_colunas; //guarda quantidade de prateleiras
} PlantaIndustrial;

typedef struct {
    int *vetor_atuadores; //indica se cada corredor esta liberado (1) ou bloqueado (0)
    int total_alarmes; //conta as falhas de segurança detectadas
    float limite_critico; //define limite de carga
} SistemaControle;

int alocar_sistema(PlantaIndustrial *p, SistemaControle *c, int l, int c_col);

void inicializar_sensores(PlantaIndustrial *p);

void processar_dados(PlantaIndustrial *p);

void avaliar_seguranca(const PlantaIndustrial *p, SistemaControle *c);

void emitir_relatorio(const PlantaIndustrial *p, const SistemaControle *c);

void liberar_memoria(PlantaIndustrial *p, SistemaControle *c);

#endif