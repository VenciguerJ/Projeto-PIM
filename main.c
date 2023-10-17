#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <windows.h>

#define fimoveis "imoveis.txt"
#define fusuarios "usuarios.txt"
#define fcorretores "corretores.txt"

typedef struct{
	char nome[100];
	int idade;
	int cpf;
	char id[50];
	char password[10];
} user

void login(){	
	/* declarar variáveis */
	user usuario;
	
	system("cls");
	
	Printf("Digite seu login \n Caso não tenha, didite '#'");
	scanf("s", &usuario.id);
	
	if(usuario.id == "#"){
		login_cadastro();
	}
	
	FILE *users = fopen(txtfusuarios, "r");
	
	fclose(txtFusuarios);
}

void login_cadastro(){
	user tmp;
	char tmppass[10];
	int resp = 0, count;
	printf("Voce é um novo cliente, ou corretor? \n 1 - cliente \n 2 - corretor");
	scanf("%i", resp);
	
	if(resp == 1){
		printf("Digite seu nome");
		scanf("%s", tmp.nome);
		
		printf("Digite sua idade");
		scanf("%i", &tmp.idade);
		
		printf("Digite seu CPF");
		scanf("%i", &tmp.cpf);
		
		printf("Escolha um ID para login (ele dever ter no maximo 50 caracteres)");
		scanf("%s", tmp.id);
		
		while(count < 1){
			count = 0;
			printf("Crie uma senha (ela deve ter no máximo 10 caracteres)");
			scanf("%s" tmp.password);
			
			printf("Confirme sua nova senha");
			scanf("%s", tmppass);
			
			if(tmp.password != tmppass){
				printf("As senhas não conferem! Tente novamente");
			}
			else{count++}
		}
		
		FILE *users = fopen(txtfusuarios, "w");
		
		fprintf(txtfusuarios, "%s %i %i %s %s %s");
		
		
		printf("Cadastro concluido com sucesso!");
		getchar();	/*Pausa para que o usuário veja o código*/
		
	login(); /* chama a função de login pra ele logar */
	}
	else if(resp == 2){
	
	}
	else{
		printf("Entrada iválida!");
	}
	
}

int main()
{
    /* code */
    
    return 0;
}