//
// Created by lucas on 24/06/2021.
//

#include "funcionario.h"
#include "dependente.h"

void abrir_arq_dep(){
    fd = fopen("dependentes.bin","rb+");
    if (fd == NULL){
        fd = fopen("dependentes.bin","wb+");
        if(fd == NULL){
            printf("\nNão foi possível criar o arquivo.\n");
            exit(1);
        }
    }
}

void fechar_arq_dep(){
    fclose(fd);
}

void inserir_dep(int a){
    struct dependente dep;
    char aux[t];
    char aux2[t];
    char op;
    int tamanho;
    float ajuda_custo = 0;

    printf("\n############ Inserir Dependentes ############");
    do{
        printf("\nDigite o CPF do Dependente:");
        do{
            do {
                fflush(stdin);
                gets(aux);

                tamanho = strlen(aux);

                if(tamanho != 0) {
                    continue;
                }

                printf("\nCampo obrigat\xF3rio. (*)");
                printf("\nInsira um CPF:");
            } while (tamanho == 0);
            fseek(fd, 0, SEEK_SET);
            while (!feof(fd)) {
                fread(&dep, sizeof(struct dependente), 1, fd);
                if (feof(fd)) {
                    break;
                }
                do{
                    if (!strcmp(dep.cpf, aux)) {
                        printf("\nJ\xE1 existe um dependente com este CPF cadastrado.");
                        printf("\nCodigo de Dependente: D-%d.\n", dep.cod);
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
                        fseek(fd, 0, SEEK_SET);
                        break;
                    }
                }while(!strcmp(dep.cpf, aux));

            }
            strcpy(dep.cpf, aux);

        } while (!strcmp(aux,aux2));

    printf("\nDigite o nome do Dependente:");

        do {
            fflush(stdin);
            gets(aux);
            strcpy(dep.nome, aux);
            tamanho = strlen(aux);

            if(tamanho != 0){
                continue;
            }
            printf("\nCampo obrigat\xF3rio. (*)");
            printf("\nInsira um nome:");
        } while (tamanho == 0);

        printf("\nDigite a data de nascimento do Dependente:");
        do {
            fflush(stdin);
            gets(aux);
            strcpy(dep.nasc, aux);
            tamanho = strlen(aux);

            if(tamanho != 0){
                continue;
            }
            printf("\nCampo obrigat\xF3rio. (*)");
            printf("\nInsira uma data:");

        } while (tamanho == 0);

        printf("\nDigite o valor da ajuda de custa ao Dependente:");
        scanf("%f", &ajuda_custo);
        dep.ajuda_custo = ajuda_custo;

        dep.cod = pegar_chaves_dep();
        printf("\nCodigo de Dependente gerado: D-%d\n", dep.cod);

        dep.c_func = a;

        strcpy(dep.atv, "Atv");

        fseek(fd, 0, SEEK_END);
        fwrite(&dep, sizeof(struct dependente), 1, fd);

        printf("\nDeseja cadastrar um novo Dependente? (S/N)");
        scanf("%s", &op);
    }while (op == 's');
}

void listar_dep(int a){
    struct dependente dep;
    float total = 0;
    int num = 0;
    fseek(fd, 0, SEEK_SET);
    printf("\nDependentes do Funcion\xE1rio:\n");
    printf("\tNome\t\tCPF\t\tNascimento\tAjuda de custos (R$)\tCodigo de Dependente\tEstatus");
    while (!feof(fd)){
        fread(&dep, sizeof(struct dependente),1, fd);
        if(feof(fd)){
            break;
        }
        if(!strcmp(dep.atv, "Atv") && dep.c_func == a) {
            printf("\n%-20s %-20s", dep.nome, dep.cpf);
            printf("%-20s %-25.2f", dep.nasc, dep.ajuda_custo);
            printf("%-18d %-20s", dep.cod, dep.atv);
            total += dep.ajuda_custo;
            num++;
        }
    }
    printf("\nN\xFAmero de dependentes: %28d.", num);
    printf("\nValor total relativo as ajudas de custos: R$ %.2f.", total);
    printf("\n------------------------------------------------------------");
    printf("------------------------------------------------------------");
}

void pesquisar_dep(){
    struct dependente dep;
    int codigo;
    fseek(fd, 0, SEEK_SET);
    printf("\nDependentes de Funcion\xE1rio:\n");
    printf("\tNome\t\tCPF\t\tNascimento\tAjuda de custos (R$)\tCodigo de Dependente\tEstatus");
    fflush(stdin);
    scanf("%d", &codigo);
    while (!feof(fd)){
        fread(&dep, sizeof(struct dependente),1, fd);
        fseek(fd, -1 * sizeof(struct dependente), SEEK_CUR);
        if(codigo == dep.cod) {
            printf("\n%-20s %-20s", dep.nome, dep.cpf);
            printf("%-20s %-25.2f", dep.nasc, dep.ajuda_custo);
            printf("%-18d %-20s", dep.cod, dep.atv);
            break;
        }
    }

    if(codigo != dep.cod){
        printf("\nN\xE3o existe dependente com este codigo.");
    }
}

void listar_dep_ina(int a){
    struct dependente dep;
    float total = 0;
    int num = 0;
    fseek(fd, 0, SEEK_SET);
    printf("\nDependentes do Funcion\xE1rio:\n");
    printf("\tNome\t\tCPF\t\tNascimento\tAjuda de custos (R$)\tCodigo de Dependente\tEstatus");
    while (!feof(fd)){
        fread(&dep, sizeof(struct dependente),1, fd);
        if(feof(fd)){
            break;
        }
        if(!strcmp(dep.atv, "ina") && dep.c_func == a) {
            printf("\n%-20s %-20s", dep.nome, dep.cpf);
            printf("%-20s %-25.2f", dep.nasc, dep.ajuda_custo);
            printf("%-18d %-20s", dep.cod, dep.atv);
            total += dep.ajuda_custo;
            num++;
        }
    }
    printf("\nN\xFAmero de dependentes: %28d.", num);
    printf("\nValor total relativo as ajudas de custos: R$ %.2f.", total);
    printf("\n------------------------------------------------------------");
    printf("------------------------------------------------------------");
}

void remover_dep(int a){
    struct dependente dep;
    int codigo;
    char op;
    fseek(fd, 0, SEEK_SET);
    printf("\n############ Remover Dependente ############");
    printf("\nDigite o codigo do Dependente a ser excluido (Apenas n\xFAmeros):");
    fflush(stdin);
    scanf("%d", &codigo);
    while (!feof(fd)){
        fread(&dep, sizeof(struct dependente),1, fd);
        if(codigo == dep.cod && dep.c_func == a){
            fseek(fd, -1 * sizeof(struct dependente), SEEK_CUR);
            printf("\tNome\t\tCPF\t\tNascimento\tAjuda de custos (R$)\tCodigo de Dependente\tEstatus");
            printf("\n%-20s %-20s", dep.nome, dep.cpf);
            printf("%-20s %-25.2f", dep.nasc, dep.ajuda_custo);
            printf("%-18d %-20s", dep.cod, dep.atv);

            printf("\nConfirmar exclus\xE3o? (S/N)");
            scanf("%s", &op);
            if (op == 's') {
                strcpy(dep.atv, "ina");
                dep.ajuda_custo = 0;
                fwrite(&dep, sizeof(struct dependente), 1, fd);
                printf("\nDependente excluido(a)...\n");
            }

            break;
        }

        else if(codigo == dep.cod && dep.c_func != a){
            printf("\nN\xE3o h\xE1 dependente com este codigo relacionado a este funcion\xE1rio...\n");
            break;
        }
    }
}

void alterar_dep(int a){
    struct dependente dep;
    int codigo;
    char aux[t];
    int op, tamanho;
    float ajuda_custo;

    fseek(fd, 0, SEEK_SET);
    printf("\n############ Alterar dados de Dependente ############");
    printf("\nDigite o codigo do dependente que deseja alterar (apenas n\xFAmeros):");
    fflush(stdin);
    scanf("%d", &codigo);
    while (!feof(fd)){
        fread(&dep, sizeof(struct dependente),1, fd);
        if(codigo == dep.cod && dep.c_func == a){
            fseek(fd,-1 * sizeof(struct dependente), SEEK_CUR);
            printf("\tNome\t\tCPF\t\tNascimento\tAjuda de custos (R$)\tCodigo de Dependente\tEstatus");
            printf("\n%-20s %-20s", dep.nome, dep.cpf);
            printf("%-20s %-25.2f", dep.nasc, dep.ajuda_custo);
            printf("%-18d %-20s", dep.cod, dep.atv);

            printf("\nEscolha a opç\xE3o que deseja alterar. \n1 - Nome.\n2 - CPF.\n3 - Nascimento.\n4 - Ajuda de custo.\n");
            scanf("%d", &op);
            switch (op) {
                case 1:
                    printf("\nDigite o Nome do Dependente:");
                    do {
                        fflush(stdin);
                        gets(aux);
                        strcpy(dep.nome, aux);
                        tamanho = strlen(aux);

                        if (tamanho != 0) {
                            continue;
                        }
                        printf("\nCampo obrigat\xF3rio. (*)");
                        printf("\nInsira um nome:");
                    } while (tamanho == 0);
                    fwrite(&dep, sizeof(struct dependente), 1, fd);
                    break;

                case 2:
                    printf("\nDigite o CPF do dependente:");
                    do {
                        fflush(stdin);
                        gets(aux);
                        strcpy(dep.cpf, aux);
                        tamanho = strlen(aux);

                        if(tamanho != 0) {
                            continue;
                        }

                        printf("\nCampo obrigat\xF3rio. (*)");
                        printf("\nInsira um CPF:");
                    } while (tamanho == 0);
                    fwrite(&dep, sizeof(struct dependente), 1, fd);
                    break;

                case 3:
                    printf("\nDigite a data de nascimento do dependente:");
                    do {
                        fflush(stdin);
                        gets(aux);
                        strcpy(dep.nasc, aux);
                        tamanho = strlen(aux);

                        if (tamanho != 0) {
                            continue;
                        }
                        printf("\nCampo obrigat\xF3rio. (*)");
                        printf("\nInsira uma data:");

                    } while (tamanho == 0);
                    fwrite(&dep, sizeof(struct dependente), 1, fd);
                    break;

                case 4:
                    printf("\nDigite o valor da ajuda de custo paga ao dependente:");
                    scanf("%f", &ajuda_custo);
                    dep.ajuda_custo = ajuda_custo;

                    fwrite(&dep, sizeof(struct dependente), 1, fd);
                    break;

                default:
                    printf("\nN\xE3o foi possiv\xE9l executar a operação.\n");
                    break;
            }

            break;
        }
        else if(codigo == dep.cod && dep.c_func != a){
            printf("\nN\xE3o existe dependente com este codigo relacionado a este funcion\xE1rio.");
            printf("\nN\xE3o foi possiv\xE9l executar a operação.\n");
            break;
        }
    }
}

float total_dep(){
    struct dependente dep;
    float total = 0;
    int num = 0;
    fseek(fd, 0, SEEK_SET);
    while (!feof(fd)){
        fread(&dep, sizeof(struct dependente),1, fd);
        if(feof(fd)){
            break;
        }
        if(!strcmp(dep.atv, "Atv")) {
            total += dep.ajuda_custo;
            num++;
        }
    }
    printf("\nN\xFAmero total de dependentes de funcion\xE1rios da empresa: %d.", num);
    printf("\nValor total pago aos funcion\xE1rios relativo as ajudas de custo: R$ %.2f.", total);
    printf("\n------------------------------------------------------------");
    printf("------------------------------------------------------------");

    return total;
}

float total_dep2(){
    struct dependente dep;
    float total = 0;
    int num = 0;
    fseek(fd, 0, SEEK_SET);
    while (!feof(fd)){
        fread(&dep, sizeof(struct dependente),1, fd);
        if(feof(fd)){
            break;
        }
        if(!strcmp(dep.atv, "Atv")) {
            total += dep.ajuda_custo;
            num++;
        }
    }

    return total;
}

void ordenar_dep(int a){
    struct dependente dep;
    struct aux2 b[20];
    float total = 0;
    float total_final = 0;
    int num = 0;
    int i = 0;
    int count = 0;
    char memo[t];
    char memo_atv[t];
    int memo_cod;
    int me;
    float memo_sal;

    fseek(fd, 0, SEEK_SET);
    printf("\nDependentes do Funcion\xE1rio:\n");
    printf("\tNome\t\tCPF\t\tNascimento\tAjuda de custos (R$)\tCodigo de Dependente\tEstatus");
    while (!feof(fd)) {
        fread(&dep, sizeof(struct dependente), 1, fd);
        if (feof(fd)) {
            break;
        }
        //if (!strcmp(dep.atv, "Atv") && dep.c_func == a) {
            strcpy(b[i].aux_nome,dep.nome);
            strcpy(b[i].aux_cpf,dep.cpf);
            strcpy(b[i].aux_nasc,dep.nasc);
            b[i].aux_sal = dep.ajuda_custo;
            b[i].aux_cod = dep.cod;
            b[i].aux_c_func = dep.c_func;
            strcpy(b[i].aux_atv, dep.atv);

        //}
        total_final += dep.ajuda_custo;
        i++;
        count++;
    }

    for (i = 0; i < count; i++) {
        for (int j = 0; j < count-1; j++) {
            if(strcmp(b[j].aux_nome,b[j+1].aux_nome) > 0){
                strcpy(memo, b[j].aux_nome);
                strcpy(b[j].aux_nome, b[j+1].aux_nome);
                strcpy(b[j+1].aux_nome, memo);

                strcpy(memo, b[j].aux_cpf);
                strcpy(b[j].aux_cpf, b[j+1].aux_cpf);
                strcpy(b[j+1].aux_cpf, memo);

                strcpy(memo, b[j].aux_nasc);
                strcpy(b[j].aux_nasc, b[j+1].aux_nasc);
                strcpy(b[j+1].aux_nasc, memo);

                memo_sal = b[j].aux_sal;
                b[j].aux_sal = b[j+1].aux_sal;
                b[j+1].aux_sal = memo_sal;

                memo_cod = b[j].aux_cod;
                b[j].aux_cod = b[j+1].aux_cod;
                b[j+1].aux_cod = memo_cod;

                me = b[j].aux_c_func;
                b[j].aux_c_func = b[j+1].aux_c_func;
                b[j+1].aux_c_func = me;

                strcpy(memo_atv, b[j].aux_atv);
                strcpy(b[j].aux_atv, b[j+1].aux_atv);
                strcpy(b[j+1].aux_atv, memo_atv);
            }
        }
    }

    for (i = 0; i < count; i++){
        if(b[i].aux_c_func == a && !strcmp(b[i].aux_atv, "Atv")) {
            /*printf("\nNome: %s.\nCPF: %s", b[i].aux_nome, b[i].aux_cpf);
            printf("\nNascimento: %s.\nAjuda de custo: R$ %.2f.", b[i].aux_nasc, b[i].aux_sal);
            printf("\nCódigo de dependente: D-%d.\nEstatus: %s\n", b[i].aux_cod, b[i].aux_atv);*/
            printf("\n%-20s %-20s", b[i].aux_nome, b[i].aux_cpf);
            printf("%-20s %-25.2f", b[i].aux_nasc, b[i].aux_sal);
            printf("%-18d %-20s", b[i].aux_cod, b[i].aux_atv);
            num++;
            total += b[i].aux_sal;
        }
    }

    printf("\nN\xFAmero de dependentes: %28d.", num);
    printf("\nValor total relativo as ajudas de custos: R$ %.2f.", total);
    printf("\n------------------------------------------------------------");
    printf("------------------------------------------------------------");
}

void remover_dep_aut(int a){
    struct dependente dep;
    fseek(fd, 0, SEEK_SET);
    while (!feof(fd)){
        fread(&dep, sizeof(struct dependente),1, fd);

        do {

            if (!strcmp(dep.atv, "Atv") && dep.c_func == a) {
                fseek(fd, -1 * sizeof(struct dependente), SEEK_CUR);
                printf("\tNome\t\tCPF\t\tNascimento\tAjuda de custos (R$)\tCodigo de Dependente\tEstatus");
                printf("\n%-20s %-20s", dep.nome, dep.cpf);
                printf("%-20s %-25.2f", dep.nasc, dep.ajuda_custo);
                printf("%-18d %-20s", dep.cod, dep.atv);


                strcpy(dep.atv, "ina");
                dep.ajuda_custo = 0;
                fwrite(&dep, sizeof(struct dependente), 1, fd);
                printf("\nDependente excluido(a)...\n");
                fseek(fd, 0, SEEK_SET);
            }

            else{
                continue;
            }

        } while (!strcmp(dep.atv, "Atv") && dep.c_func == a);

    }
}

void reativar_dep_aut(int a){
    struct dependente dep;
    fseek(fd, 0, SEEK_SET);
    while (!feof(fd)){
        fread(&dep, sizeof(struct dependente),1, fd);

        do {

            if (!strcmp(dep.atv, "ina") && dep.c_func == a) {
                fseek(fd, -1 * sizeof(struct dependente), SEEK_CUR);
                printf("\tNome\t\tCPF\t\tNascimento\tAjuda de custos (R$)\tCodigo de Dependente\tEstatus");
                printf("\n%-20s %-20s", dep.nome, dep.cpf);
                printf("%-20s %-25.2f", dep.nasc, dep.ajuda_custo);
                printf("%-18d %-20s", dep.cod, dep.atv);


                strcpy(dep.atv, "Atv");
                dep.ajuda_custo = 0;
                fwrite(&dep, sizeof(struct dependente), 1, fd);
                printf("\nDependente reativado(a)...\n");
                fseek(fd, 0, SEEK_SET);
            }

            else{
                continue;
            }

        } while (!strcmp(dep.atv, "ina") && dep.c_func == a);

    }
}

void imprimir_dep(int a) {
    struct dependente dep;
    struct aux2 b[20];
    float total = 0;
    float total_final = 0;
    int num = 0;
    int i = 0;
    int count = 0;
    char memo[t];
    char memo_atv[t];
    int memo_cod;
    int me;
    float memo_sal;

    fseek(fd, 0, SEEK_SET);
    fprintf(fr, "\nDependentes do Funcion\xE1rio:\n");
    fprintf(fr, "\tNome\t\t\t\tCPF\t\t\t\t  Nascimento\t\tAjuda de custos (R$)\tCodigo de Dependente\tEstatus");
    while (!feof(fd)) {
        fread(&dep, sizeof(struct dependente), 1, fd);
        if (feof(fd)) {
            break;
        }
        strcpy(b[i].aux_nome, dep.nome);
        strcpy(b[i].aux_cpf, dep.cpf);
        strcpy(b[i].aux_nasc, dep.nasc);
        b[i].aux_sal = dep.ajuda_custo;
        b[i].aux_cod = dep.cod;
        b[i].aux_c_func = dep.c_func;
        strcpy(b[i].aux_atv, dep.atv);

        total_final += dep.ajuda_custo;
        i++;
        count++;
    }

    for (i = 0; i < count; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (strcmp(b[j].aux_nome, b[j + 1].aux_nome) > 0) {
                strcpy(memo, b[j].aux_nome);
                strcpy(b[j].aux_nome, b[j + 1].aux_nome);
                strcpy(b[j + 1].aux_nome, memo);

                strcpy(memo, b[j].aux_cpf);
                strcpy(b[j].aux_cpf, b[j + 1].aux_cpf);
                strcpy(b[j + 1].aux_cpf, memo);

                strcpy(memo, b[j].aux_nasc);
                strcpy(b[j].aux_nasc, b[j + 1].aux_nasc);
                strcpy(b[j + 1].aux_nasc, memo);

                memo_sal = b[j].aux_sal;
                b[j].aux_sal = b[j + 1].aux_sal;
                b[j + 1].aux_sal = memo_sal;

                memo_cod = b[j].aux_cod;
                b[j].aux_cod = b[j + 1].aux_cod;
                b[j + 1].aux_cod = memo_cod;

                me = b[j].aux_c_func;
                b[j].aux_c_func = b[j + 1].aux_c_func;
                b[j + 1].aux_c_func = me;

                strcpy(memo_atv, b[j].aux_atv);
                strcpy(b[j].aux_atv, b[j + 1].aux_atv);
                strcpy(b[j + 1].aux_atv, memo_atv);
            }
        }
    }

    for (i = 0; i < count; i++) {
        if (b[i].aux_c_func == a && !strcmp(b[i].aux_atv, "Atv")) {
            fprintf(fr, "\n%-20s %-20s", b[i].aux_nome, b[i].aux_cpf);
            fprintf(fr, "%-20s %-30.2f", b[i].aux_nasc, b[i].aux_sal);
            fprintf(fr, "%-18d %-20s", b[i].aux_cod, b[i].aux_atv);
            num++;
            total += b[i].aux_sal;
        }
    }

    fprintf(fr, "\n\nN\xFAmero de dependentes: %29d.", num);
    fprintf(fr, "\nValor total relativo as ajudas de custos: R$ %.2f.", total);
    fprintf(fr, "\n------------------------------------------------------------");
    fprintf(fr, "------------------------------------------------------------");
}