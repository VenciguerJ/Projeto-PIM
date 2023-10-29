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
	char cpf[12];
	char password[11];
} user;

char cpf_user[12];

void atualiza_dado(char *var, char *novoValor){ // atualiza o CPF para ser usado na MAIN
	strcpy(var, novoValor);
}

user pesquisaUser(char *arquivo, char *cpf){ // pesquisa os dados do usuario

	FILE *arq = fopen(arquivo, "r");
	user tmp;
	
	while(!feof(arq)){
		fscanf(arq, "%s %i %s %s", tmp.nome, &tmp.idade, tmp.cpf, tmp.password);
		if(strlen(cpf) == strlen(tmp.cpf) && strcmp(cpf, tmp.cpf) ==0){
			break;
		}
		else{
			strcpy(tmp.cpf, "-1");
		}
	}
	fclose(arq);
	return tmp;
}

int verificaCPF(char *cpf){ //retorna 1 se o cpf estiver cadastrado e 0 se o cpf não estiver cadastrado
	user tmp;
	int pode;
	tmp = pesquisaUser(fclientes, cpf);
	if (strcmp(tmp.cpf, "-1") == 0){
		tmp = pesquisaUser(fcorretores, cpf);
		if (strcmp(tmp.cpf, "-1") == 0){
			pode = 0; // pode cadastrar o cpf
		}
	}
	else{
		pode = 1; //não pode cadastrar o cpf
	}
	return pode;
}

void login_cadastro_criaInfos(char *arquivo){ // cria as informações de cadastro do usuário
	int iguais, podeusarcpf;
	char tmppass[11];
	user tmp;
	
	// começa perguntando dados
	printf("Digite seu nome: ");
	scanf("%s", tmp.nome);


	printf("Digite sua idade: ");
	scanf("%i", &tmp.idade);
	
	printf("Digite seu CPF: ");
	scanf("%s", tmp.cpf);

	podeusarcpf = verificaCPF(tmp.cpf);

	if(podeusarcpf == 0){
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
			fprintf(arq, "%s %i %s %s \n", tmp.nome, tmp.idade, tmp.cpf, tmp.password);
		}
		fclose(arq);
		printf("Cadastro concluido com sucesso! \n \n");
		getchar();	/*Pausa para que o usuário veja o código*/
	}
	else{
		printf("usuario ja cadastrado, faça seu login \n \n");
	}
}

void login_cadastro(){ // função que direciona o arquivo de cadastro corretamente
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
	char tempsenha[11], tempCPF[12];
	int logado=1, resp;
	user pesq;
	printf("Area de Login\n\n");

	
    while(logado == 1){ //quando conseguir logar, "logado vai ficar = a 0"
		printf("Possui login ou deseja cadastrar? \n \n 1 - Login \n 2 - Cadastrar \n \n Escolha: ");
		scanf("%i", &resp);
		
		if(resp == 2){
			login_cadastro();
		}
		else if(resp == 1){
			do{
				printf("Digite seu CPF: ");
				scanf("%s", tempCPF);
				
				pesq = pesquisaUser(fclientes, tempCPF);
				if(strcmp(pesq.cpf, "-1") == 0){//retorna -1 casoo não seja encontrado
					pesq = pesquisaUser(fcorretores, tempCPF);
					if(strcmp(pesq.cpf, "-1") == 0){
						printf("usuario não encontrado");
						break;
					}
				}
				if(strlen(pesq.cpf) == strlen(tempCPF) && strcmp(pesq.cpf, tempCPF) == 0) //pesq.cpf == tempCPF
				{
					do{
						printf("Digite sua senha: ");
						scanf("%s", tempsenha);

						if (strlen(pesq.password) == strlen(tempsenha) && strcmp(pesq.password, tempsenha) == 0){
							printf("Login concluido! \n \n");
							atualiza_dado(cpf_user, pesq.cpf);
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
			}while (strcmp(pesq.cpf, "-1") == 0);
		}
		else{
			printf("Entrada invalida! \n \n");
		}
	}
}


int main(){
	user usuario;
	strcpy(cpf_user, "");
	login();
	usuario = pesquisaUser(fclientes,cpf_user);
	if (strcmp(usuario.cpf, "-1")!=0){
		printf("menu de clientes");
	}
	else{
		usuario = pesquisaUser(fcorretores,cpf_user);
		if(strcmp(usuario.cpf, "-1")!=0){
			printf("menu de corretores");
		}
	}
    return 0;
}
