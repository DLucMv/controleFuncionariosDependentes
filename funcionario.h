//
// Created by lucas on 24/06/2021.
//

#ifndef TRAB2ETAP_FUNCIONARIO_H
#define TRAB2ETAP_FUNCIONARIO_H

#endif //TRAB2ETAP_FUNCIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define t 255
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN     "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA     "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

FILE *f;
FILE *fc;
FILE *fr;

struct funcionario{
    int cod;
    char nome[t];
    char cpf[t];
    float sal;
    char nasc[t];
    char atv[t];
} ;
struct chaves{
    int cod_func;
    int cod_dep;
};
struct aux{
    int aux_cod;
    char aux_nome[t];
    char aux_cpf[t];
    char aux_nasc[t];
    char aux_atv[t];
    float aux_sal;
};

void abrir_arq_func();
void abrir_arq_chaves();
void fechar_arq_func();
void fechar_arq_chaves();
int pegar_chaves_func();
void inserir_func();
void listar_func();
void listar_func_ina();
void alterar_func();
void pesquisar_func();
void remover_func();
float total_func();
float total_func2();
void ordenar_func();
void reativar_func();
void imprimir_func();