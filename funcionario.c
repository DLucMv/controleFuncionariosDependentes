//
// Created by lucas on 24/06/2021.
//
#include "funcionario.h"
#include "dependente.h"

void abrir_arq_func(){
    f = fopen("funcionarios.bin","rb+");
    if (f == NULL){
        f = fopen("funcionarios.bin","wb+");
        if(f == NULL){
            printf("\nNão foi possível criar o arquivo.\n");
            exit(1);
        }
    }
}

void abrir_arq_chaves(){
    fc = fopen("chaves.bin","rb+");
    if (fc == NULL){
        fc = fopen("chaves.bin","wb+");

        struct chaves chave;
        chave.cod_func = 1;
        chave.cod_dep = 1;
        fseek(fc, 0, SEEK_SET);
        fwrite(&chave, sizeof(struct chaves), 1, fc);

        if(fc == NULL){
            printf("\nNão foi possível criar o arquivo.\n");
            exit(1);
        }
    }
}

int pegar_chaves_func(){
    struct chaves chave;
    int codigo;
    fseek(fc, 0, SEEK_SET);
    fread(&chave, sizeof(struct chaves), 1, fc);
    codigo = chave.cod_func;
    chave.cod_func++;
    fseek(fc, 0, SEEK_SET);
    fwrite(&chave, sizeof(struct chaves), 1, fc);
    return codigo;
}

int pegar_chaves_dep(){
    struct chaves chave;
    int codigo_dep;
    fseek(fc, 0, SEEK_SET);
    fread(&chave, sizeof(struct chaves), 1, fc);
    codigo_dep = chave.cod_dep;
    chave.cod_dep++;
    fseek(fc, 0, SEEK_SET);
    fwrite(&chave, sizeof(struct chaves), 1, fc);
    return codigo_dep;
}

void fechar_arq_func(){
    fclose(f);
}

void fechar_arq_chaves(){
    fclose(fc);
}

void inserir_func(){
    struct funcionario func;
    char aux[t];
    char aux2[t];
    char op;
    int tamanho;
    float salario = 0;

    printf(ANSI_COLOR_BLUE"\n################################################# Inserir Funcion\xE1rio ");
    printf("#################################################\n"ANSI_COLOR_RESET);

    do{
        printf("\nDigite o CPF do Funcion\xE1rio:");

        do{
            do{
                fflush(stdin);
                gets(aux);
                tamanho = strlen(aux);

                if(tamanho != 0){
                    continue;
                }

                printf("\nCampo obrigat\xF3rio. (*)");
                printf("\nInsira um CPF:");

            } while (tamanho == 0);

            fseek(f, 0, SEEK_SET);
            while (!feof(f)){
                fread(&func, sizeof(struct funcionario),1, f);
                if(feof(f)){
                    break;
                }
                do{
                    if(!strcmp(func.cpf,aux)) {
                        printf("\nJ\xE1 existe um funcion\xE1rio com este CPF cadastrado.");
                        printf("\nCodigo de Funcion\xE1rio: F-%d.\n", func.cod);
                        printf("\nPor favor, insira um novo CPF:");
                        do {
                            fflush(stdin);
                            gets(aux);
                            tamanho = strlen(aux);

                            if (tamanho != 0) {
                                continue;
                            }

                            printf("\nCampo obrigat\xF3rio. (*)");
                            printf("\nInsira um CPF:");
                        } while (tamanho == 0);

                        fseek(f, 0, SEEK_SET);
                        break;
                    }
                }while (!strcmp(func.cpf,aux));
            }
            strcpy(func.cpf, aux);

        } while (!strcmp(aux,aux2));


        printf("\nDigite o nome do Funcion\xE1rio:");

            do {
                fflush(stdin);
                gets(aux);
                strcpy(func.nome, aux);
                tamanho = strlen(aux);

                if(tamanho != 0){
                    continue;
                }

                printf("\nCampo obrigat\xF3rio. (*)");
                printf("\nInsira um nome:");

            } while (tamanho == 0);

        printf("\nDigite a data de nascimento do Funcion\xE1rio:");
        do {
            fflush(stdin);
            gets(aux);
            strcpy(func.nasc, aux);
            tamanho = strlen(aux);

            if(tamanho != 0){
                continue;
            }
            printf("\nCampo obrigat\xF3rio. (*)");
            printf("\nInsira uma data:");

        } while (tamanho == 0);

        printf("\nDigite o sal\xE1rio do Funcion\xE1rio:");
        scanf("%f", &salario);
        func.sal = salario;

        func.cod = pegar_chaves_func();
        printf("\nCodigo de Funcion\xE1rio gerado: F-%d\n",func.cod);

        strcpy(func.atv, "Atv");

        fseek(f, 0, SEEK_END);
        fwrite(&func, sizeof(struct funcionario), 1, f);

        printf("\nDeseja cadastrar um Dependente? (S/N)");
        scanf("%s", &op);
        if(op == 's'){
            inserir_dep(func.cod);
        }

        printf("\nDeseja cadastrar um novo Funcion\xE1rio? (S/N)");
        scanf("%s", &op);
    }while (op == 's');
    system("pause");
}

void listar_func(){
    struct funcionario func;
    float total_sal = 0;
    fseek(f, 0, SEEK_SET);
    printf(ANSI_COLOR_GREEN"\n################################################# Listar ");
    printf("Funcion\xE1rios #################################################\n"ANSI_COLOR_RESET);
    while (!feof(f)){
        fread(&func, sizeof(struct funcionario),1, f);
        if(feof(f)){
            break;
        }
        if(!strcmp(func.atv, "Atv")) {
            printf("\n------------------------------------------------------------");
            printf("------------------------------------------------------------");
            printf("\nFUNCION\xC1RIO:\n");
            printf("\tNome\t\tCPF\t\tNascimento\t  Sal\xE1rio (R$)  \tCodigo de Funcion\xE1rio\tEstatus");
            printf("\n%-20s %-20s", func.nome, func.cpf);
            printf("%-20s %-25.2f", func.nasc, func.sal);
            printf("%-18d %-20s\n", func.cod, func.atv);

            listar_dep(func.cod);
        }
        total_sal += func.sal;
    }
    printf("\nValor total relativo aos sal\xE1rios de funcion\xE1rios: R$ %.2f\n", total_sal);
    system("pause");
}

void listar_func_ina(){
    struct funcionario func;
    int count = 0;
    fseek(f, 0, SEEK_SET);
    printf(ANSI_COLOR_GREEN"\n################################################# Listar ");
    printf("Funcion\xE1rios inativos ########################################\n"ANSI_COLOR_RESET);
    while (!feof(f)){
        fread(&func, sizeof(struct funcionario),1, f);
        if(feof(f)){
            break;
        }
        if(!strcmp(func.atv, "ina")) {
            printf("\n------------------------------------------------------------");
            printf("------------------------------------------------------------");
            printf("\nFUNCION\xC1RIO:\n");
            printf("\tNome\t\tCPF\t\tNascimento\t  Sal\xE1rio (R$)  \tCodigo de Funcion\xE1rio\tEstatus");
            printf("\n%-20s %-20s", func.nome, func.cpf);
            printf("%-20s %-25.2f", func.nasc, func.sal);
            printf("%-18d %-20s\n", func.cod, func.atv);

            listar_dep_ina(func.cod);
            count++;
        }
    }

    if(count == 0){
        printf("\nN\xE3o existem funcion\xE1rios inativos.\n");
    }

    system("pause");
}

void alterar_func(){
    struct funcionario func;
    int codigo;
    char aux[t];
    int op, tamanho;
    float salario;

    fseek(f, 0, SEEK_SET);
    printf(ANSI_COLOR_YELLOW"\n############################################ Alterar dados de Funcion\xE1rio ");
    printf("#############################################\n"ANSI_COLOR_RESET);
    printf("\nDigite o codigo do funcion\xE1rio que deseja alterar (apenas n\xFAmeros):");
    fflush(stdin);
    scanf("%d", &codigo);
    while (!feof(f)){
        fread(&func, sizeof(struct funcionario),1, f);
        if(codigo == func.cod){
            fseek(f,-1 * sizeof(struct funcionario), SEEK_CUR);
            printf("\nFUNCION\xC1RIO:\n");
            printf("\tNome\t\tCPF\t\tNascimento\t  Sal\xE1rio (R$)  \tCodigo de Funcion\xE1rio\tEstatus");
            printf("\n%-20s %-20s", func.nome, func.cpf);
            printf("%-20s %-25.2f", func.nasc, func.sal);
            printf("%-18d %-20s\n", func.cod, func.atv);
            listar_dep(func.cod);

            printf("\nEscolha a opç\xE3o que deseja alterar. \n1 - Nome.\n2 - CPF.\n3 - Nascimento.\n4 - Sal\xE1rio.\n");
            printf("5 - Inserir Dependentes\n6 - Excluir Dependentes.\n7 - Alterar dados de dependente.\n");
            scanf("%d", &op);
            break;
        }


    }

    if(codigo != func.cod){
        printf("\nN\xE3o h\xE1 funcion\xE1rio relacionado a este codigo...\n");
        op = 0;
    }


    switch (op) {
        case 1:
            printf("\nDigite o Nome do Funcion\xE1rio:");
            do {
                fflush(stdin);
                gets(aux);
                strcpy(func.nome, aux);
                tamanho = strlen(aux);

                if(tamanho != 0){
                    continue;
                }
                printf("\nCampo obrigat\xF3rio. (*)");
                printf("\nInsira um nome:");
            } while (tamanho == 0);
            fwrite(&func, sizeof(struct funcionario), 1, f);
            break;

        case 2:
            printf("\nDigite o CPF do funcion\xE1rio:");
            do {
                fflush(stdin);
                gets(aux);
                strcpy(func.cpf, aux);
                tamanho = strlen(aux);

                if(tamanho != 0){
                    continue;
                }
                printf("\nCampo obrigat\xF3rio. (*)");
                printf("\nInsira um CPF:");

            } while (tamanho == 0);
            fwrite(&func, sizeof(struct funcionario), 1, f);
            break;

        case 3:
            printf("\nDigite a data de nascimento do funcion\xE1rio:");
            do {
                fflush(stdin);
                gets(aux);
                strcpy(func.nasc, aux);
                tamanho = strlen(aux);

                if(tamanho != 0){
                    continue;
                }
                printf("\nCampo obrigat\xF3rio. (*)");
                printf("\nInsira uma data:");

            } while (tamanho == 0);
            fwrite(&func, sizeof(struct funcionario), 1, f);
            break;

        case 4:
            printf("\nDigite o sal\xE1rio do funcion\xE1rio:");
            scanf("%f", &salario);
            func.sal = salario;

            fwrite(&func, sizeof(struct funcionario), 1, f);
            break;

        case 5:
            inserir_dep(func.cod);
            break;

        case 6:
            remover_dep(func.cod);
            break;

        case 7:
            alterar_dep(func.cod);
            break;

        default:
            printf("\nN\xE3o foi possiv\xE9l executar a operaç\xE3o.\n");
            break;
    }
    system("pause");
}

void pesquisar_func(){
    struct funcionario func;
    int codigo;
    fseek(f, 0, SEEK_SET);
    printf(ANSI_COLOR_MAGENTA"\n################################################ Pesquisar Funcion\xE1rio ");
    printf("################################################\n"ANSI_COLOR_RESET);
    printf("\nDigite o codigo do funcion\xE1rio (apenas n\xFAmeros):");
    fflush(stdin);
    scanf("%d", &codigo);
    while (!feof(f)){
        fread(&func, sizeof(struct funcionario),1, f);
        if(codigo == func.cod){
            fseek(f,-1 * sizeof(struct funcionario), SEEK_CUR);
            printf("\nFUNCION\xC1RIO:\n");
            printf("\tNome\t\tCPF\t\tNascimento\t  Sal\xE1rio (R$)  \tCodigo de Funcion\xE1rio\tEstatus");
            printf("\n%-20s %-20s", func.nome, func.cpf);
            printf("%-20s %-25.2f", func.nasc, func.sal);
            printf("%-18d %-20s\n", func.cod, func.atv);

            printf("\nDependentes ativos do Funcion\xE1rio:");
            listar_dep(func.cod);
            printf("\nDependentes inativos do Funcion\xE1rio:");
            listar_dep_ina(func.cod);
            break;
        }
    }

    if(codigo != func.cod){
        printf("\nN\xE3o h\xE1 funcion\xE1rio relacionado a este codigo...\n");
    }

    system("pause");
}

void remover_func(){
    struct funcionario func;
    int codigo;
    char op;
    fseek(f, 0, SEEK_SET);
    printf(ANSI_COLOR_CYAN"\n################################################ Remover Funcion\xE1rio ");
    printf("#################################################\n"ANSI_COLOR_RESET);
    printf("\nDigite o codigo do funcion\xE1rio a ser excluido (Apenas n\xFAmeros):");
    fflush(stdin);
    scanf("%d", &codigo);
    while (!feof(f)){
        fread(&func, sizeof(struct funcionario),1, f);
        if(codigo == func.cod){
            fseek(f, -1 * sizeof(struct funcionario), SEEK_CUR);
            printf("\nFUNCION\xC1RIO:\n");
            printf("\tNome\t\tCPF\t\tNascimento\t  Sal\xE1rio (R$)  \tCodigo de Funcion\xE1rio\tEstatus");
            printf("\n%-20s %-20s", func.nome, func.cpf);
            printf("%-20s %-25.2f", func.nasc, func.sal);
            printf("%-18d %-20s\n", func.cod, func.atv);

            printf("\nConfirmar exclus\xE3o? (S/N)");
            scanf("%s", &op);
            if(op == 's'){
                strcpy(func.atv, "ina");
                func.sal = 0;
                fwrite(&func, sizeof(struct funcionario), 1, f);
                printf("\nFuncion\xE1rio(a) excluido(a)...\n");

                remover_dep_aut(func.cod);
            }

            break;
        }
    }

    if(codigo != func.cod){
        printf("\nN\xE3o h\xE1 funcion\xE1rio relacionado a este codigo...\n");
    }

    system("pause");
}

float total_func(){
    struct funcionario func;
    float total_sal = 0;
    int num = 0;
    fseek(f, 0, SEEK_SET);
    while (!feof(f)){
        fread(&func, sizeof(struct funcionario),1, f);
        if(feof(f)){
            break;
        }
        if(!strcmp(func.atv, "Atv")) {
            total_sal += func.sal;
            num++;
        }
    }
    printf("N\xFAmero total de funcion\xE1rios da empresa: %d.", num);
    printf("\nValor total relativo aos sal\xE1rios de funcion\xE1rios: R$ %.2f", total_sal);
    printf("\n------------------------------------------------------------");
    printf("------------------------------------------------------------");
    return total_sal;
}

float total_func2(){
    struct funcionario func;
    float total_sal = 0;
    int num = 0;
    fseek(f, 0, SEEK_SET);
    while (!feof(f)){
        fread(&func, sizeof(struct funcionario),1, f);
        if(feof(f)){
            break;
        }
        if(!strcmp(func.atv, "Atv")) {
            total_sal += func.sal;
            num++;
        }
    }

    return total_sal;
}

void ordenar_func(){
    struct funcionario func;
    struct aux a[20];
    float total_sal = 0;
    int i = 0;
    int count = 0;
    char memo[t];
    char memo_atv[t];
    int memoria;
    float memor;
    fseek(f, 0, SEEK_SET);
    printf(ANSI_COLOR_GREEN"\n################################################# Listar ");
    printf("Funcion\xE1rios #################################################\n"ANSI_COLOR_RESET);
        while (!feof(f)) {
            fread(&func, sizeof(struct funcionario), 1, f);
            if (feof(f)) {
                break;
            }
            //if (!strcmp(func.atv, "Atv")) {
                strcpy(a[i].aux_nome,func.nome);
                strcpy(a[i].aux_cpf,func.cpf);
                strcpy(a[i].aux_nasc,func.nasc);
                a[i].aux_sal = func.sal;
                a[i].aux_cod = func.cod;
                strcpy(a[i].aux_atv, func.atv);
                total_sal += func.sal;
          //  }
            i++;
            count++;
        }

    for (i = 0; i < count; i++) {
        for (int j = 0; j < count-1; j++) {
            if(strcmp(a[j].aux_nome,a[j+1].aux_nome) > 0){
                strcpy(memo, a[j].aux_nome);
                strcpy(a[j].aux_nome, a[j+1].aux_nome);
                strcpy(a[j+1].aux_nome, memo);

                strcpy(memo, a[j].aux_cpf);
                strcpy(a[j].aux_cpf, a[j+1].aux_cpf);
                strcpy(a[j+1].aux_cpf, memo);

                strcpy(memo, a[j].aux_nasc);
                strcpy(a[j].aux_nasc, a[j+1].aux_nasc);
                strcpy(a[j+1].aux_nasc, memo);

                memor = a[j].aux_sal;
                a[j].aux_sal = a[j+1].aux_sal;
                a[j+1].aux_sal = memor;

                memoria = a[j].aux_cod;
                a[j].aux_cod = a[j+1].aux_cod;
                a[j+1].aux_cod = memoria;

                strcpy(memo_atv, a[j].aux_atv);
                strcpy(a[j].aux_atv, a[j+1].aux_atv);
                strcpy(a[j+1].aux_atv, memo_atv);
            }
        }
    }

    for (i = 0; i < count; i++){
        if(!strcmp(a[i].aux_atv, "Atv")) {
            printf("\n------------------------------------------------------------");
            printf("------------------------------------------------------------");
            printf("\nFUNCION\xC1RIO:\n");
            printf("\tNome\t\tCPF\t\tNascimento\t  Sal\xE1rio (R$)  \tCodigo de Funcion\xE1rio\tEstatus");
            /*printf("\nNome: %s.\nCPF: %s", a[i].aux_nome, a[i].aux_cpf);
            printf("\nNascimento: %s.\nSalário: R$ %.2f.", a[i].aux_nasc, a[i].aux_sal);
            printf("\nCódigo de Funcionário: F-%d.\nEstatus: %s\n", a[i].aux_cod, a[i].aux_atv);
            printf("\n-------------------------------------------------------------------------\n");*/
            printf("\n%-20s %-20s", a[i].aux_nome, a[i].aux_cpf);
            printf("%-20s %-25.2f", a[i].aux_nasc, a[i].aux_sal);
            printf("%-18d %-20s\n", a[i].aux_cod, a[i].aux_atv);

        }
        if(!strcmp(a[i].aux_atv, "Atv")) {
            ordenar_dep(a[i].aux_cod);
        }
    }

    printf("\nValor total relativo aos sal\xE1rios de funcion\xE1rios: R$ %.2f\n", total_sal);
    system("pause");
}

void reativar_func(){
    struct funcionario func;
    int codigo;
    char op;
    fseek(f, 0, SEEK_SET);
    printf(ANSI_COLOR_CYAN"\n################################################ Reativar Funcion\xE1rio ");
    printf("#################################################\n"ANSI_COLOR_RESET);
    printf("\nDigite o codigo do funcion\xE1rio a ser reativado (Apenas n\xFAmeros):");
    fflush(stdin);
    scanf("%d", &codigo);
    while (!feof(f)){
        fread(&func, sizeof(struct funcionario),1, f);
        if(codigo == func.cod){
            fseek(f, -1 * sizeof(struct funcionario), SEEK_CUR);
            printf("\nFUNCION\xC1RIO:\n");
            printf("\tNome\t\tCPF\t\tNascimento\t  Sal\xE1rio (R$)  \tCodigo de Funcion\xE1rio\tEstatus");
            printf("\n%-20s %-20s", func.nome, func.cpf);
            printf("%-20s %-25.2f", func.nasc, func.sal);
            printf("%-18d %-20s\n", func.cod, func.atv);

            printf("\nConfirmar reativaç\xE3o? (S/N)");
            scanf("%s", &op);
            if(op == 's'){
                strcpy(func.atv, "Atv");
                func.sal = 0;
                fwrite(&func, sizeof(struct funcionario), 1, f);
                printf("\nFuncion\xE1rio(a) reativado(a)...\n");

                reativar_dep_aut(func.cod);
            }

            break;
        }
    }

    if(codigo != func.cod){
        printf("\nN\xE3o h\xE1 funcion\xE1rio relacionado a este codigo...\n");
    }

    system("pause");
}

void imprimir_func(){
    fr = fopen("Relatorio.txt","w+");
    if (fr == NULL){
        fr = fopen("Relatorio.txt","w+");
        if(fr == NULL){
            printf("\nNão foi possível criar o arquivo.\n");
            exit(1);
        }
    }

    struct funcionario func;
    struct aux a[20];
    float total_sal = 0;
    int i = 0;
    int count = 0;
    char memo[t];
    char memo_atv[t];
    int memoria;
    float memor;
    fseek(f, 0, SEEK_SET);
    printf(ANSI_COLOR_GREEN"\n################################################# Gerar ");
    printf("Relat\xF3rio #################################################\n"ANSI_COLOR_RESET);
    while (!feof(f)) {
        fread(&func, sizeof(struct funcionario), 1, f);
        if (feof(f)) {
            break;
        }
        //if (!strcmp(func.atv, "Atv")) {
        strcpy(a[i].aux_nome,func.nome);
        strcpy(a[i].aux_cpf,func.cpf);
        strcpy(a[i].aux_nasc,func.nasc);
        a[i].aux_sal = func.sal;
        a[i].aux_cod = func.cod;
        strcpy(a[i].aux_atv, func.atv);
        total_sal += func.sal;
        //  }
        i++;
        count++;
    }

    for (i = 0; i < count; i++) {
        for (int j = 0; j < count-1; j++) {
            if(strcmp(a[j].aux_nome,a[j+1].aux_nome) > 0){
                strcpy(memo, a[j].aux_nome);
                strcpy(a[j].aux_nome, a[j+1].aux_nome);
                strcpy(a[j+1].aux_nome, memo);

                strcpy(memo, a[j].aux_cpf);
                strcpy(a[j].aux_cpf, a[j+1].aux_cpf);
                strcpy(a[j+1].aux_cpf, memo);

                strcpy(memo, a[j].aux_nasc);
                strcpy(a[j].aux_nasc, a[j+1].aux_nasc);
                strcpy(a[j+1].aux_nasc, memo);

                memor = a[j].aux_sal;
                a[j].aux_sal = a[j+1].aux_sal;
                a[j+1].aux_sal = memor;

                memoria = a[j].aux_cod;
                a[j].aux_cod = a[j+1].aux_cod;
                a[j+1].aux_cod = memoria;

                strcpy(memo_atv, a[j].aux_atv);
                strcpy(a[j].aux_atv, a[j+1].aux_atv);
                strcpy(a[j+1].aux_atv, memo_atv);
            }
        }
    }

    for (i = 0; i < count; i++){
        if(!strcmp(a[i].aux_atv, "Atv")) {
            fprintf(fr,"\n------------------------------------------------------------");
            fprintf(fr,"------------------------------------------------------------");
            fprintf(fr,"\nFUNCION\xC1RIO:\n");
            fprintf(fr,"\tNome\t\t\t\tCPF\t\t\t\t  Nascimento\t    Sal\xE1rio (R$)  \t\t\tCodigo de Funcion\xE1rio\tEstatus");
            /*printf("\nNome: %s.\nCPF: %s", a[i].aux_nome, a[i].aux_cpf);
            printf("\nNascimento: %s.\nSalário: R$ %.2f.", a[i].aux_nasc, a[i].aux_sal);
            printf("\nCódigo de Funcionário: F-%d.\nEstatus: %s\n", a[i].aux_cod, a[i].aux_atv);
            printf("\n-------------------------------------------------------------------------\n");*/
            fprintf(fr,"\n%-20s %-20s", a[i].aux_nome, a[i].aux_cpf);
            fprintf(fr,"%-20s %-30.2f", a[i].aux_nasc, a[i].aux_sal);
            fprintf(fr,"%-18d %-20s\n", a[i].aux_cod, a[i].aux_atv);

        }
        if(!strcmp(a[i].aux_atv, "Atv")) {
            imprimir_dep(a[i].aux_cod);
        }
    }



    fprintf(fr,"\n\n################################################# Custos ");
    fprintf(fr,"Empresariais #################################################\n");
    fprintf(fr,"\nValor total relativo aos sal\xE1rios de funcion\xE1rios: \t\tR$ %.2f\n", total_sal);

    fprintf(fr,"Valor total relativo aos Beneficios de dependentes: \tR$ %.2f\n",total_dep2());

    total_sal = total_dep2() + total_func2();
    fprintf(fr,"Sal\xE1rios mais Beneficios aos dependentes: \t\t\t\tR$ %.2f\n",total_sal);

    printf(ANSI_COLOR_GREEN"Relat\xF3rio Gerado com sucesso.\n"ANSI_COLOR_RESET);

    fclose(fr);

    system("pause");
}