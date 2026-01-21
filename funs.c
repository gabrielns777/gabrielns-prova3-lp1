#include "funs.h"

void limparscanf() {
    int scan;
    while ((scan = getchar()) != '\n');
}

void scanfcheck(int act) {
    if (scanf("%d", &act) != 1) {
        printf("Entrada invalida.\n\n");
        while (getchar() != '\n');
    }
    else if (scanf("%d", &act) == 1) {
        printf("Entrada invalida.\n\n");
    }
}

int login(FILE* users, usuario *uPt, char username[], char senha[]) {
    char str[201];
    char usercheck[21];
    char senhacheck[22];
    int numhistorico;
    char* tok;
    users = fopen("usuarios.txt", "r");
    if (users == NULL) {
        printf("Falha na abertura.\n\n");
        return -1;
    }
    FILE* historico = fopen("historico.txt", "r");
    if (historico == NULL) {
        printf("Falha na abertura.\n\n");
        return -1;
    }
    while (feof(users) == 0) {
        fscanf(users, "%s %s %d", usercheck, senhacheck, &numhistorico);
        if ((strcmp(usercheck, username) == 0) && (strcmp(senhacheck, senha) == 0)) {
            strcpy(uPt->nome, username);
            strcpy(uPt->senha, senha);
            fclose(users);
            while (fgets(str, 201, historico) != NULL) {
                for (int i = 0; i < 201; i++) {
                    if (str[i] == '\n') {
                        str[i] = '\0';
                        break;
                    }
                }
                if (strcmp(str, "\0\0") == 0) {
                    continue;
                }
                else {
                    tok = strtok(str, "|");
                    if (tok == NULL) {
                        continue;
                    }
                    else if (strcmp(tok, username) == 0) {
                        tok = strtok(NULL, "|");
                        uPt->numhistorico = atoi(tok);
                        uPt->historico = (int*)malloc(uPt->numhistorico * sizeof(int));
                        if (uPt->historico == NULL) {
                            printf("Erro na alocacao de memoria!\n\n");
                            return -1;
                        }
                        for (int j = 0; j < uPt->numhistorico; j++) {
                            tok = strtok(NULL, "|");
                            if (tok == NULL) {
                                break;
                            }
                            uPt->historico[j] = atoi(tok);
                        }
                        fclose(historico);
                        return 1;
                    }
                }
            }
        }
    }
    printf("Usuario nao encontrado.\n\n");
    fclose(users);
    fclose(historico);
    return 0;
}

int registro(FILE * users, char username[], char senha[]) {
    char usertest[22];
    users = fopen("usuarios.txt", "r");
    if (users == NULL) {
        printf("Falha na abertura.\n\n");
        return -1;
    }
    while (feof(users) == 0) {
        fscanf(users, "%s", usertest);
        if (strcmp(usertest, username) == 0) {
            printf("Conta ja existe.\n\n");
            fclose(users);
            return 0;
        }
    }
    fclose(users);
    users = fopen("usuarios.txt", "a+");
    if (users == NULL) {
        printf("Falha na abertura.\n\n");
        return -1;
    }
    fprintf(users, "%s %s %d%c", username, senha, 0, '\n');
    FILE* historico = fopen("historico.txt", "a+");
    if (historico == NULL) {
        printf("Falha na abertura.\n\n");
        return -1;
    }
    fprintf(historico, "%s%c%d%c", username, '|', 0, '\n');
    printf("Usuario registrado com sucesso.\n\n");
    fclose(users);
    fclose(historico);
    return 1;
}

int novoexercicio(FILE * exercicios, char titulo[], char descricao[], char categoria[], int dificuldade, int questid, char delim) {
    exercicios = fopen("exercicios.txt", "r");
    if (exercicios == NULL) {
        printf("Falha na abertura.\n\n");
        return -1;
    }
    fclose(exercicios);
    exercicios = fopen("exercicios.txt", "a+");
    fprintf(exercicios, "%s%c%s%c%s%c%d%c%d\n", titulo, delim, descricao, delim, categoria, delim, dificuldade, delim, questid);
    fclose(exercicios);
    return 1;
}

int exerciciorec(FILE* exercicios, usuario* uPt, char categoria[], int dificuldade, int questid, char delim) {
    char str[1000];
    char str2[100];
    char titulo[51];
    char desc[251];
    char categ[51];
    int dif;
    int exid;
    char* tok;
    char* tok2;
    int* novohistorico = NULL;

    exercicios = fopen("exercicios.txt", "r");
    if (exercicios == NULL) {
        printf("Falha na abertura.\n\n");
        return -1;
    }
    while (fgets(str, 1000, exercicios) != NULL) {
        for (int i = 0; i < 1000; i++) {
            if (str[i] == '\n') {
                str[i] = '\0';
                break;
            }
        }
        if (strcmp(str, "\0\0") == 0) {
            continue;
        }
        else {
            tok = strtok(str, "|");
            strcpy(titulo, tok);
            tok = strtok(NULL, "|");
            strcpy(desc, tok);
            tok = strtok(NULL, "|");
            strcpy(categ, tok);
            tok = strtok(NULL, "|");
            dif = atoi(tok);
            tok = strtok(NULL, "|");
            exid = atoi(tok);

            int check = 0;
            if (strcmp(categoria, categ) == 0 && dif == dificuldade) {
                if (uPt->numhistorico <= 0) {
                    novohistorico = (int*)realloc(uPt->historico, (uPt->numhistorico + 1) * sizeof(int));
                    if (novohistorico == NULL) {
                        printf("Erro na alocacao de memoria.\n\n");
                        fclose(exercicios);
                        return -1;
                    }
                    novohistorico[uPt->numhistorico] = exid;
                    uPt->historico = novohistorico;
                    uPt->numhistorico++;
                    printf("Novo exercicio:\n\n");
                    printf("Titulo: %s. Nivel %d.\n", titulo, dif);
                    printf("Descricao: %s\n\n", desc);
                    FILE* historico = fopen("historico.txt", "r");
                    if (historico == NULL) {
                        printf("Falha na abertura.\n\n");
                        return -1;
                    }
                    FILE* temphistorico = fopen("temphistorico.txt", "w+");
                    if (temphistorico == NULL) {
                        printf("Falha na abertura.\n\n");
                        return -1;
                    }
                    while (fgets(str2, 100, historico) != NULL) {
                        for (int i = 0; i < 100; i++) {
                            if (str2[i] == '\n') {
                                str2[i] = '\0';
                                break;
                            }
                        }
                        if (strcmp(str2, "\0\0") == 0) {
                            continue;
                        }
                        else {
                            char buff2[100];
                            strcpy(buff2, str2);
                            tok2 = strtok(str2, "|");
                            if (tok2 == NULL) {
                                continue;
                            }
                            else if (strcmp(tok2, uPt->nome) == 0) {
                                //fprintf(temphistorico, "%s%c%d%c%d%c", uPt->nome, '|', uPt->numhistorico, '|', exid, '\n');
                                fputs(uPt->nome, temphistorico);
                                fputs("|", temphistorico);
                                fprintf(temphistorico, "%d", uPt->numhistorico);
                                for (int k = 0; k < uPt->numhistorico; k++) {
                                    fputs("|", temphistorico);
                                    fprintf(temphistorico, "%d", uPt->historico[k]);
                                }
                                fputs("\n", temphistorico);
                            }
                            else {
                                strcat(buff2, "\n");
                                fputs(buff2, temphistorico);
                            }
                        }
                    }
                    fclose(exercicios);
                    fclose(historico);
                    fclose(temphistorico);
                    remove("historico.txt");
                    rename("temphistorico.txt", "historico.txt");
                    return 1;
                }
                else if (uPt->numhistorico > 0) {
                    for (int j = 0; j < uPt->numhistorico; j++) {
                        if (uPt->historico[j] == exid) {
                            check = 1;
                            break;
                        }
                    }
                    if (check == 0) {
                        novohistorico = (int*)realloc(uPt->historico, (uPt->numhistorico + 1) * sizeof(int));
                        if (novohistorico == NULL) {
                            printf("Erro na alocacao de memoria.\n\n");
                            fclose(exercicios);
                            return -1;
                        }
                        novohistorico[uPt->numhistorico] = exid;
                        uPt->historico = novohistorico;
                        uPt->numhistorico++;
                        printf("Novo exercicio:\n\n");
                        printf("Titulo: %s. Nivel %d.\n", titulo, dif);
                        printf("Descricao: %s\n\n", desc);
                        FILE* historico = fopen("historico.txt", "r");
                        if (historico == NULL) {
                            printf("Falha na abertura.\n\n");
                            return -1;
                        }
                        FILE* temphistorico = fopen("temphistorico.txt", "w+");
                        if (temphistorico == NULL) {
                            printf("Falha na abertura.\n\n");
                            return -1;
                        }
                        while (fgets(str2, 100, historico) != NULL) {
                            for (int i = 0; i < 1000; i++) {
                                if (str2[i] == '\n') {
                                    str2[i] = '\0';
                                    break;
                                }
                            }
                            if (strcmp(str2, "\0\0") == 0) {
                                continue;
                            }
                            else {
                                char buff2[100];
                                strcpy(buff2, str2);
                                tok2 = strtok(str2, "|");
                                if (strcmp(tok2, uPt->nome) == 0) {
                                    fputs(uPt->nome, temphistorico);
                                    fputs("|", temphistorico);
                                    fprintf(temphistorico, "%d", uPt->numhistorico);
                                    for (int k = 0; k < uPt->numhistorico; k++) {
                                        fputs("|", temphistorico);
                                        fprintf(temphistorico, "%d", uPt->historico[k]);
                                    }
                                    fputs("\n", temphistorico);
                                }
                                else {
                                    strcat(buff2, "\n");
                                    fputs(buff2, temphistorico);
                                }
                            }
                        }
                        fclose(exercicios);
                        fclose(historico);
                        fclose(temphistorico);
                        remove("historico.txt");
                        rename("temphistorico.txt", "historico.txt");
                        return 1;
                    }
                }
            }
        }
    }
    fclose(exercicios);
    return 0;
}

int delexercicio(FILE* exercicios, FILE * tempexercicios, int delid) {
    exercicios = fopen("exercicios.txt", "r");
    if (exercicios == NULL) {
        printf("Falha na abertura.\n\n");
        return -1;
    }
    tempexercicios = fopen("tempexercicios.txt", "w+");
    if (tempexercicios == NULL) {
        printf("Falha na abertura.\n\n");
        return -1;
    }
    char str[100];
    char buf[100];
    char* tok;
    int exid;
    int linecount = 0;
    while (fgets(str, 100, exercicios) != NULL) {
        strcpy(buf, str);
        printf("%s", buf);
        for (int i = 0; i < 100; i++) {
            if (str[i] == '\n') {
                str[i] = '\0';
                break;
            }
        }
        if (strcmp(str, "") == 0) { 
            break; 
        }
        tok = strtok(str, "|");
        tok = strtok(NULL, "|");
        tok = strtok(NULL, "|");
        tok = strtok(NULL, "|");
        tok = strtok(NULL, "|");
        exid = atoi(tok);

        if (exid == delid) {
            continue;
        }
        else {
            fputs(buf, tempexercicios);
        }
    }
    fclose(exercicios);
    fclose(tempexercicios);
    remove("exercicios.txt");
    rename("tempexercicios.txt", "exercicios.txt");
    return 1;
}
