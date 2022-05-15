//
// Created by lucas on 24/06/2021.
//

#ifndef TRAB2ETAP_DEPENDENTE_H
#define TRAB2ETAP_DEPENDENTE_H

#endif //TRAB2ETAP_DEPENDENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define t 255

FILE *fd;

struct dependente{
    int cod;
    int c_func;
    char nome[t];
    char cpf[t];
    float ajuda_custo;
    char nasc[t];
    char atv[t];
};
struct aux2{
    int aux_cod;
    int aux_c_func;
    char aux_nome[t];
    char aux_cpf[t];
    char aux_nasc[t];
    char aux_atv[t];
    float aux_sal;
};

void abrir_arq_dep();
void fechar_arq_dep();
int pegar_chaves_dep();
void inserir_dep(int a);
void pesquisar_dep();
void listar_dep(int a);
void listar_dep_ina(int a);
void remover_dep(int a);
void alterar_dep(int a);
float total_dep();
float total_dep2();
void ordenar_dep(int a);
void remover_dep_aut(int a);
void reativar_dep_aut(int a);
void imprimir_dep(int a);