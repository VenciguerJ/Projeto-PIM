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
	char id[100];
	char password[11];
} user;

void login_cadastro(){
	user tmp;
	char tmppass[10];
	int resp = 0, iguais;

	

    printf("NOVO CADASTRO! \n");

	printf("Voce e um novo cliente, ou corretor? \n 1 - cliente \n 2 - corretor \n \n Escolha: ");
	scanf("%i", &resp);
	
	if(resp == 1){

		printf("Digite seu nome: ");
		scanf("%s", tmp.nome);


		printf("Digite sua idade: ");
		scanf("%i", &tmp.idade);
		
		printf("Digite seu CPF: ");
		scanf("%i", &tmp.cpf);
		
		printf("Escolha um ID para login (ele dever ter no maximo 50 caracteres): ");
		scanf("%s", tmp.id);

		do{
			iguais = 1;
			printf("Crie uma senha (ela deve ter no maximo 10 caracteres): ");
			scanf("%s", tmp.password);

			printf("Confirme sua nova senha: ");
			scanf("%s", tmppass);

			for(int count = 0; count <= strlen(tmp.password); count++){
				if (tmp.password[count] != tmppass[count]){
					iguais = 0;
					break;
				}
			}
			if(iguais == 0){
				printf("As senhas nao conferem! Tente novamente \n \n");
			}
		}while(iguais == 0);

		FILE *arq = fopen(fclientes, "w");

		fprintf(arq, "%s %i %i %s %s \n", tmp.nome, tmp.idade, tmp.cpf, tmp.id, tmp.password);
        fclose(arq);
		printf("Cadastro concluido com sucesso!");
		getchar();	/*Pausa para que o usuário veja o código*/
	}
	else if(resp == 2){
		printf("Digite seu nome: ");
		scanf("%s", tmp.nome);
		
		printf("Digite sua idade: ");
		scanf("%i", &tmp.idade);
		
		printf("Digite seu CPF: ");
		scanf("%i", &tmp.cpf);
		
		printf("Escolha um ID para login (ele dever ter no maximo 50 caracteres): ");
		scanf("%s", tmp.id);

		do{
			iguais = 1;
			printf("Crie uma senha (ela deve ter no maximo 10 caracteres): ");
			scanf("%s", tmp.password);

			printf("Confirme sua nova senha: ");
			scanf("%s", tmppass);

			for(int count = 0; count <= strlen(tmp.password); count++){
				if (tmp.password[count] != tmppass[count]){
					iguais = 0;
					break;
				}
			}
			if(iguais == 0){
				printf("As senhas nao conferem! Tente novamente \n \n");
			}
		}while(iguais == 0);

		FILE *arq = fopen(fcorretores, "w");

		fprintf(arq, "%s %i %i %s %s \n", tmp.nome, tmp.idade, tmp.cpf, tmp.id, tmp.password);
        fclose(arq);
		printf("Cadastro concluido com sucesso!");
		getchar();
	}
	else{
		printf("Entrada iválida!");
	}
}

void login(){
	char tempID[101], tempPass[11];
	user usuario;
    int resp, tempresp, logado = 1, iguais = 0;
	
	printf("----Area de Login----\n\n");
	
    while(logado = 1){
		printf("Possui login ou deseja cadastrar? \n \n 1 - Login \n 2 - Cadastrar \n \n Escolha: ");
		scanf("%i", &resp);
		getchar();
		
		if(resp == 2){
			login_cadastro();
		}
		else if (resp ==1){
			printf("Logar como cliente ou corretor? \n \n 1 - Cliente \n 2 - Corretor \n \n Escolha: ");
			scanf("%i", &tempresp);

			if (tempresp == 1)
			{
				printf("Digite o ID de usuario: ");
				scanf("%s", tempID);

				FILE* arq = fopen(fclientes, "r");
				while(!feof(arq)){
					fscanf(arq, "%s %i %i %s %s", usuario.nome, &usuario.idade, &usuario.cpf, usuario.id, usuario.password);
					for(int i=0; i < strlen(tempID); i++){
						if (usuario.id[i] == tempID[i]){
							iguais = 1;			
						}
						else{
							printf("não encontrado");
							break;
						}
					}
				}
				if(iguais == 1){
					usuario.id = tempID;
					printf("digite a senha: ");
					scanf("%s", tempPass);
					while(!feof(arq)){
						fscanf(arq, "%s %i %i %s %s", usuario.nome, &usuario.idade, &usuario.cpf, usuario.id, usuario.password);
						senhacorreta = 
						if (te{
							iguais = 1;			
						}
						else{
							printf("incorreto!");
							break;
						}
					}
				}
					}
					else{
						printf("acho nao painho");
					}
			
				fclose(arq);
			}
			else if (tempresp == 2){
				/* code */
			}
			else{
				printf("Entrada inválida");
			}
		}
		else{
			printf("entrada invalida!");
		}			
    }
	
}

int main()
{
    login();
    return 0;
}