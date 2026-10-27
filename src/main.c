#include <stdio.h>
#include <stdlib.h>
#include "../include/armazem.h"

int main(void) {
    int sistema_inicializado = 0; //indica se o sistema ja foi inicializado
    int opcao; //guarda o numero escolhido pelo usuario no menu
    PlantaIndustrial planta = {0}; //representa o armazem, matriz de pesos e as medias por corredor
    SistemaControle controle = {0}; //representa o sistema de seguranca, os atuadores e o limite critico

    do {
        printf("\n=== SISTEMA DE ARMAZEM AUTOMATIZADO ===\n");
        printf("1 - Inicializar sistema\n");
        printf("2 - Processar dados dos sensores\n");
        printf("3 - Avaliar seguranca\n");
        printf("4 - Emitir relatorio\n");
        printf("0 - Encerrar programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (sistema_inicializado == 0) {
                    if (alocar_sistema(&planta, &controle, 4, 5)) {
                        inicializar_sensores(&planta);
                        inicializar_atuadores(&controle, planta.qtd_linhas);
                        sistema_inicializado = 1;
                        printf("Sistema inicializado com sucesso!\n");
                    } else {
                        printf("Erro ao inicializar o sistema!\n");
                    }
                } else {
                    printf("O sistema ja foi inicializado!\n");
                }
                break;

            case 2:
                if (sistema_inicializado == 1) {
                    processar_dados(&planta);
                    printf("Dados processados com sucesso!\n");
                } else {
                    printf("Inicialize o sistema primeiro!\n");
                }
                break;

            case 3:
                if (sistema_inicializado == 1) {
                    avaliar_seguranca(&planta, &controle);
                    printf("Avaliacao de seguranca concluida!\n");
                    printf("Total de alarmes: %d\n", controle.total_alarmes);
                } else {
                    printf("Inicialize o sistema primeiro!\n");
                }
                break;

            case 4:
                if (sistema_inicializado == 1) {
                    emitir_relatorio(&planta, &controle);
                } else {
                    printf("Inicialize o sistema primeiro!\n");
                }
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcao != 0);

    if (sistema_inicializado == 1) {
        liberar_memoria(&planta, &controle); //libera a memoria alocada pelo sistema
    }

    return 0;
}