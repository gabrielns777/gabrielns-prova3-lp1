#include "funs.h"

int main() {
	//Inicializando arquivos
	FILE* users;
	users = fopen("usuarios.txt", "a+");
	if (users == NULL) {
		printf("Falha na abertura.\n\n");
		return -1;
	}
	fclose(users);
	FILE* exercicios;
	exercicios = fopen("exercicios.txt", "a+");
	if (exercicios == NULL) {
		printf("Falha na abertura.\n\n");
		return -1;
	}
	fclose(exercicios);
	FILE* tempexercicios;
	tempexercicios = fopen("tempexercicios.txt", "a+");
	if (tempexercicios == NULL) {
		printf("Falha na abertura.\n\n");
		return -1;
	}
	fclose(tempexercicios);
	FILE* historico;
	historico = fopen("historico.txt", "a+");
	if (historico == NULL) {
		printf("Falha na abertura.\n\n");
		return -1;
	}
	fclose(historico);
	FILE* temphistorico;
	temphistorico = fopen("temphistorico.txt", "a+");
	if (temphistorico == NULL) {
		printf("Falha na abertura.\n\n");
		return -1;
	}
	fclose(temphistorico);
	FILE* dados;
	dados = fopen("dados.txt", "a+");
	if (dados == NULL) {
		printf("Falha na abertura.\n\n");
		return -1;
	}
	if (dados != NULL) {
		fseek(dados, 0, SEEK_END);
		int dadosteste = ftell(dados);
		if (dadosteste == 0) {
			fprintf(dados, "%d %d", 1, 0); //respectivamente ID de exercicio e numero de exercicios
		}
	}
	fclose(dados);

	printf("===   PROXIMO EXERCICIO   ===\n\n");

	char str[100];
	int act1;
	int act2;
	int logincheck = 0;
	int spacecheck = 0;
	int questid;
	int numquest;
	char c;
	usuario u = { "a", "a", 0, NULL };
	usuario* uPt = &u;

	dados = fopen("dados.txt", "r");
	if (dados == NULL) {
		printf("Falha na abertura.\n\n");
		return -1;
	}
	fscanf(dados, "%d %d", &questid, &numquest);
	fclose(dados);

	do {
		printf("1. Entrar no sistema\n");
		printf("2. Registrar-se no sistema\n\n");
		printf("0. Sair do sistema\n\n");
		printf("Sua escolha: ");
		scanf("%d", &act1);
		printf("\n");
		if (act1 == 0) {
			printf("Saindo.\n");
		}
		else if (act1 == 1) {
			limparscanf();
			char username[21];
			printf("Nome de usuario: ");
			fgets(username, 21, stdin);
			for (int i = 0; i < 21; i++) {
				if (username[i] == '\n') {
					username[i] = '\0';
					break;
				}
			}
			while ((c = getchar()) != '\n' && c != EOF);
			char senha[21];
			printf("Senha: ");
			fgets(senha, 21, stdin);
			for (int j = 0; j < 21; j++) {
				if (senha[j] == '\n') {
					senha[j] = '\0';
					break;
				}
			}
			while ((c = getchar()) != '\n' && c != EOF);
			if (strcmp(username, "admin") == 0 && strcmp(senha, "987654") == 0) {
				printf("Entrando como administrador.\n\n");
				logincheck = 1;
				break;
			}
			if (login(users, uPt, username, senha) == 1) {
				printf("Login bem-sucedido.\n\n");
				logincheck = 2;
				break;
			}
		}
		else if (act1 == 2) {
			limparscanf();
			spacecheck = 0;
			printf("Registrando novo usuario.\n\n");
			char novouser[21];
			printf("Novo usuario: ");
			fgets(novouser, 21, stdin);
			for (int i = 0; i < 21; i++) {
				if (novouser[i] == '\n') {
					novouser[i] = '\0';
					break;
				}
			}
			while ((c = getchar()) != '\n' && c != EOF);
			char novasenha[21];
			printf("Nova senha: ");
			fgets(novasenha, 21, stdin);
			for (int j = 0; j < 21; j++) {
				if (novasenha[j] == '\n') {
					novasenha[j] = '\0';
					break;
				}
			}
			while ((c = getchar()) != '\n' && c != EOF);
			for (int j = 0; j < 21; j++) {
				if (novouser[j] == ' ') {
					printf("Nome de usuario nao pode conter espacos.\n\n");
					spacecheck = 1;
					break;
				}
			}
			for (int k = 0; k < 21; k++) {
				if (novasenha[k] == ' ') {
					printf("Senha nao pode conter espacos.\n\n");
					spacecheck = 1;
					break;
				}
			}
			if (spacecheck == 0) {
				registro(users, novouser, novasenha);
			}
		}
		else {
			scanfcheck(act1);
		}
	} while (act1 != 0);

	do {
		if (logincheck == 1) {
			printf("---------- Administrador ----------\n\n");
			printf("1. Cadastrar novos exercicios\n");
			printf("2. Apagar um exercicio\n\n");
			printf("0. Log off, e sair do sistema\n\n");
			printf("Sua escolha: ");
			scanf("%d", &act2);
			if (act2 == 1) {
				limparscanf();
				printf("Cadastrando novo exercicio.\n\n");
				char titulo[51];
				printf("Nome do exercicio: ");
				fgets(titulo, 51, stdin);
				for (int i = 0; i < 21; i++) {
					if (titulo[i] == '\n') {
						titulo[i] = '\0';
						break;
					}
				}
				while ((c = getchar()) != '\n' && c != EOF);
				char descricao[251];
				printf("Descricao do exercicio: ");
				fgets(descricao, 251, stdin);
				for (int i = 0; i < 21; i++) {
					if (descricao[i] == '\n') {
						descricao[i] = '\0';
						break;
					}
				}
				while ((c = getchar()) != '\n' && c != EOF);
				char categoria[51];
				printf("Categoria do exercicio: ");
				fgets(categoria, 51, stdin);
				for (int i = 0; i < 21; i++) {
					if (categoria[i] == '\n') {
						categoria[i] = '\0';
						break;
					}
				}
				while ((c = getchar()) != '\n' && c != EOF);
				int dificuldade;
				printf("Dificuldade do exercicio: ");
				scanf("%d", &dificuldade);
				dados = fopen("dados.txt", "r");
				while (feof(dados) == 0) {
					fscanf(dados, "%d %d", &questid, &numquest);
				}
				fclose(dados);
				dados = fopen("dados.txt", "w+");
				if (dados == NULL) {
					printf("Falha na abertura.\n\n");
					return -1;
				}
				if (novoexercicio(exercicios, titulo, descricao, categoria, dificuldade, questid, '|') == 1) {
					questid++;
					numquest++;
					fprintf(dados, "%d %d", questid, numquest);
					fclose(dados);
				}
			}
			else if (act2 == 2) {
				printf("Apagando um exercicio\n\n");
				int delid;
				printf("ID do exercicio para apagar: ");
				scanf("%d", &delid);
				delexercicio(exercicios, tempexercicios, delid);
				numquest--;
				FILE* dados = fopen("dados.txt", "w+");
				if (dados == NULL) {
					printf("Falha na abertura.\n\n");
					return -1;
				}
				fprintf(dados, "%d %d", questid, numquest);
				fclose(dados);
			}
			else if (act2 == 0) {
				printf("Saindo.\n\n");
			}
			else {
				scanfcheck(act2);
			}
		}
		else if (logincheck == 2) {
			printf("-----------------------------------\n\n");
			printf("1. Receber novos exercicios\n");
			printf("0. Log off, e sair do sistema.\n\n");
			printf("Sua escolha: ");
			scanf("%d", &act2);
			char categoria[51] = "";
			int dificuldade = 0;
			if (act2 == 1) {
				limparscanf();
				int questid;
				int numquest;
				dados = fopen("dados.txt", "r");
				if (dados == NULL) {
					printf("Falha na abertura.\n\n");
					return -1;
				}
				while (feof(dados) == 0) {
					fscanf(dados, "%d %d", &questid, &numquest);
				}
				fclose(dados);
				printf("Indique a categoria desejada: ");
				fgets(categoria, 51, stdin);
				for (int i = 0; i < 51; i++) {
					if (categoria[i] == '\n') {
						categoria[i] = '\0';
						break;
					}
				}
				while ((c = getchar()) != '\n' && c != EOF);
				printf("Indique a dificuldade desejada: ");
				scanf("%d", &dificuldade);
				if (numquest <= 0) {
					printf("Sem exercicios cadastrados!\n\n");
				}
				else if (numquest > 0) {
					int abc = exerciciorec(exercicios, uPt, categoria, dificuldade, questid, '|');
					if (strcmp(categoria, "") == 0 || dificuldade == 0) {
						printf("Indique uma categoria e/ou dificuldade!\n\n");
					}
					else if (abc == 0) {
						printf("Nao ha exercicios disponiveis.\n\n");
					}
					else if (abc == 1) {
						printf("\n");
					}
				}

			}
			else if (act2 == 0) {
				free(u.historico);
				printf("Saindo.\n\n");
			}
			else {
				scanfcheck(act2);
			}
		}
		else {
			act2 = 0;
		}
	} while (act2 != 0);
}
