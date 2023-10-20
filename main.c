#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <windows.h>

#define fimoveis "imoveis.txt"
#define fclientes "clientes.txt"
#define fcorretores "corretores.txt"

typedef struct{
	char nome[101];
	int idade;
	int cpf;
	char password[11];
} user;
	
user pesquisaUser(char *arquivo, int cpf){

	FILE *arq = fopen(arquivo, "r");
	user tmp;
	
	while(!feof(arq)){
		fscanf(arq, "%s %i %i %s", tmp.nome, &tmp.idade, &tmp.cpf, tmp.password);
		if(cpf == tmp.cpf){
			break;
		}
		else{
			tmp.cpf = -1;
		}
	}
	fclose(arq);
	return tmp;
}

char* verifica_arquivo(int cpf){
	
	FILE *arqCorreto;
	user pesq;
	
	pesq = pesqisaUser(fclientes, cpf);
	if(pesq.cpf == -1){
		pesq = pesqisaUser(fclientes, cpf);
		if(pesq.cpf == -1){
			printf("Usuario nao encontrado");
		}
		else{
			return fcorretores;
		}
	
	}
	else{
		return fclientes;
	}
	
}

void login_cadastro_criaInfos(char *arquivo){
	int iguais;
	char tmppass[11];
	user tmp;

	// começa perguntando dados
		printf("Digite seu nome: ");
		scanf("%s", tmp.nome);


		printf("Digite sua idade: ");
		scanf("%i", &tmp.idade);
		
		printf("Digite seu CPF: ");
		scanf("%i", &tmp.cpf);	
		do {
			iguais = 1;
			printf("Crie uma senha (ela deve ter no máximo 10 caracteres): ");
			scanf("%s", tmp.password); 

			printf("Confirme sua nova senha: ");
			scanf("%s", tmppass); 

			// Verifica se as senhas têm o mesmo comprimento e se são iguais
			if (strlen(tmp.password) != strlen(tmppass) || strcmp(tmp.password, tmppass) != 0) {
				iguais = 0;
				printf("\nAs senhas não conferem! Tente novamente.\n\n");
			}
		} while (iguais == 0);

		FILE *arq = fopen(arquivo, "a+"); //abre o arquivo para escrita

		
		if(arq != NULL){
			fprintf(arq, "%s %i %i %s \n", tmp.nome, tmp.idade, tmp.cpf, tmp.password);
		}
        fclose(arq);
		printf("Cadastro concluido com sucesso!");
		getchar();	/*Pausa para que o usuário veja o código*/
}

void login_cadastro(){
	int resp;

    printf("NOVO CADASTRO! \n");

	printf("Novo cliente ou corretor? \n 1 - cliente \n 2 - corretor \n \n Escolha: "); //pergunta o tipo de usuario
	scanf("%i", &resp);
	
	if(resp == 1){
		login_cadastro_criaInfos(fclientes);
	}
	else if(resp == 2){
		login_cadastro_criaInfos(fcorretores);
	}
	else{
		printf("Entrada iválida!");
	}
}

void login(){
	char tempsenha[11], arquivoCorreto;
	int logado=1, resp, tempCPF;
	user pesq;
	printf("----Area de Login----\n\n");

	
    while(logado == 1){ //quando conseguir logar, "logado vai ficar = a 0"
		printf("Possui login ou deseja cadastrar? \n \n 1 - Login \n 2 - Cadastrar \n \n Escolha: ");
		scanf("%i", &resp);
		
		if(resp == 2){
			login_cadastro();
		}
		else if(resp == 1){
			do{
				printf("Digite seu CPF: ");
				scanf("%i", &tempCPF);
				
				arquivoCorreto = verifica_arquivo(tempCPF);
				
				pesq = pesquisaUser(arquivoCorreto, tempCPF);
				if(pesq.cpf == tempCPF){

					do{
						printf("Digite sua senha: ");
						scanf("%s", tempsenha);

						if (strlen(pesq.password) == strlen(tempsenha) && strcmp(pesq.password, tempsenha) == 0){
							printf("Login concluido! \n \n");
							getchar();
						}
						else{
							printf("Senha incorreta! \n \n");
						}
					}while(strlen(pesq.password) != strlen(tempsenha) || strcmp(pesq.password, tempsenha) != 0);
					logado = 0;
				}
				else{
					printf("CPF nao encontrado \n \n");
				}
			}while (pesq.cpf == -1);
			
		}
		else{
			printf("Entrada invalida!");
		}
}

int main(){

	login();
	printf("teste concluido");

    return 0;
}
