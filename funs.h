#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char titulo[51];
	char descricao[251];
	char categoria[51];
	int dificuldade;
	int exid;
} exercicio;

typedef struct {
	char nome[21];
	char senha[21];
	int numhistorico;
	int *historico;
} usuario;

void limparscanf();
void scanfcheck(int act);
int login(FILE* users, usuario *uPt, char username[], char senha[]);
int registro(FILE* users, char username[], char senha[]);
int novoexercicio(FILE* exercicios, char titulo[], char descricao[], char categoria[], int dificuldade, int questid, char delim);
int exerciciorec(FILE* exercicios, usuario *uPt, char categoria[], int dificuldade, int questid, char delim);
int delexercicio(FILE* exercicios, FILE* tempexercicios, int delid);
