/* Protótipo de um sistema de controle empresarial desenvolvido para a conclusão da disciplina
 * de introdução a programação.
 * Autor: Davison Lucas Mendes Viana - Engenharia da Computação - IFCE
 * Professor: Aljamar Rego da Rocha Neto*/

#include "funcionario.h"
#include "dependente.h"
#include <locale.h>

void menu(){
    int op;
    do {
        system ("cls");
        printf("\nSistema de Controle Empresarial - SisCEm\nAlfa version 0.2.1");
        printf("\n%s",setlocale(LC_ALL, ""));
        fflush(stdin);
        printf(ANSI_COLOR_RED"\n######################################################### Menu ");
        printf("#########################################################\n"ANSI_COLOR_RESET);
        printf("\n1 - Inserir Funcion\xE1rio/Dependente\t2 - Alterar Dados de Funcion\xE1rio");
        printf("\t3 - Listar Funcion\xE1rios por antiguidade\n4 - Listar em ordem alfab\xE9tica");
        printf("\t\t5 - Pesquisar por Funcion\xE1rio\t\t6 - Remover Funcion\xE1rio");
        printf("\n7 - Imprimir custos totais da Empresa\t8 - Reativar Funcion\xE1rio");
        printf("\t\t9 - Listar Funcion\xE1rios inativos\n10 - Imprimir relat\xF3rio"ANSI_COLOR_RESET);
        printf(ANSI_COLOR_RED"\t\t\t0 - Encerrar programa\n"ANSI_COLOR_RESET);
        scanf("%d",&op);

        switch(op) {
            case 1:
                inserir_func();
                break;

            case 2:
                alterar_func();
                break;

            case 3:
                listar_func();
                break;

            case 4:
                ordenar_func();
                break;

            case 5:
                pesquisar_func();
                break;

            case 6:
                remover_func();
                break;

            case 7:
                printf(ANSI_COLOR_RED"\n################################################# Custos ");
                printf("Empresariais #################################################\n"ANSI_COLOR_RESET);
                printf("Sal\xE1rios mais Beneficios aos dependentes: %.2f\n",total_dep() + total_func());
                system("pause");
                break;

            case 8:
                reativar_func();
                break;

            case 9:
                listar_func_ina();
                break;

            case 10:
                imprimir_func();
                break;

            default:
                printf("Encerrando...\n");
                system("pause");
                break;
        }
        fflush(stdin);
    }while (op != 0);
}

int main() {
    abrir_arq_func();
    abrir_arq_chaves();
    abrir_arq_dep();
    menu();
    fechar_arq_func();
    fechar_arq_chaves();
    fechar_arq_dep();
    return 0;
}