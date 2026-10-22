#include <stdio.h>
#include <stdlib.h>
#include "../include/armazem.h"

int main(void) {
    int sistema_inicializado = 0; //indica se o sistema ja foi inicializado
    int opcao; //guarda o numero escolhido pelo usuário no menu
    PlantaIndustrial planta = {0}; //representa o armazem, matriz de pesos e os totais por corredor
    SistemaControle controle = {0}; //sistema de segurançanca, autuadore e o limite critico

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
                    if (alocar_sistema(&planta, &controle)) {
                        inicializar_sensores(&planta);
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
                printf("Processar dados dos sensores\n");
                break;

            case 3:
                printf("Avaliar seguranca\n");
                break;

            case 4:
                printf("Emitir relatorio\n");
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}