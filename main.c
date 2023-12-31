#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>

#define fimoveis "imoveis.txt"
#define fclientes "clientes.txt"
#define fcorretores "corretores.txt"
#define fpropostas "propostas.txt"

typedef struct{ //estrutura do usuario
	char nome[101];
	int idade;
	char cpf[12]; 
	char password[11];
	char nrocllr[15];
	char email[101];
	int rendaMensal;
} user;

typedef struct{ //estrutura do imovel
	char cpfcorretor[12];
    int nroimovel;
	char endereco[101];
    char bairro[101];
    char cidade[101];
    char estado[3];
    char cep[8];
	int metragemtotal;
	int metragemconstruido;
	int numerodequartos;
    int numerodesiutes;
    int numerodesalas;
    int numerodebanheiros;
    char tempiscina;
    char temchurrasqueia;
    float valor; //valor venda
} imovel;

typedef struct{ //estrutura da proposta
	char cpfsolicitante[12];
	int nroproposta;
	int type; // 1aluguel 2financiamento 3 compra
	int numeroImovel;
	int status; // 1 aguardando aprovação, 2 - Aprovado 3 - Rejeitado
}proposta;

char cpf_user[12]; //cpf do usuario logado

void getSenha(char *tenta_senha) { //mascara de senha
    int c = 0;
    char password[11];
    
    while ((tenta_senha[c] = getch()) != 13) {
        printf("%c", '*'); // Exibe '*' no lugar do caractere digitado
        c++;
    }
    tenta_senha[c] = '\0'; // Adiciona o terminador de string à senha inserida
}

void tirar_espaco(char *texto){ // usado para recolocar o espaço na hora de demonstrar o programa ao usuario 
    for(int i=0;i<strlen(texto);i++){
		if (texto[i]==' '){ //vê quando tem espaço e coloca " "
			texto[i]='+';
		}
	}
}

void colocar_espaco(char *texto){ //função usada para adicionar um sinal do arquivo texto para não dar erros de leitura
    for(int i=0;i<strlen(texto);i++){
		if (texto[i]=='+'){//vê quando tem "+" e coloca " "
			texto[i]=' ';	
		}
	}
}

int qtd_propostas(char *arquivo){ // retorna quantas propostas existem

    FILE *arq = fopen(arquivo, "r");
    proposta tmp;
    int c = 0;
    while (!feof(arq)){
        fscanf(arq,"%s %i %i %i %i\n",tmp.cpfsolicitante, &tmp.nroproposta, &tmp.type, &tmp.numeroImovel, &tmp.status);
        c++; 
    }
    fclose(arq);
    return c;
}

void calculadora_price(char *arquivo, float principal, int numParcelas, int nroimovel) { // faz o calculo de orçamaento pela tabela price
	int status = 1, financimento = 2;
	char resp;
	float taxamensal =  0.007974, pv, calculo1,calculo2,pmt,juros,totalfinancimanto,valorentrada2;
	int i=1,resp5;
	int nroproposta = qtd_propostas(fpropostas);
	FILE *arq = fopen(arquivo, "a+");

	do{	
		float valorentrada = principal * 0.2;
		printf("Valor minimo da entrada do imovel deve ser: R$%.2f\n", valorentrada);
		printf("1 - Irei dar a entrada de R$%.2f\n2 - Outro Valor\n3 - Desejo Sair\n\nEscolha:", valorentrada);
		scanf("%i",&resp5);

		if(resp5 == 1){
			pv = principal - valorentrada;
			juros = pv*taxamensal;
			calculo1 = (pow((1+taxamensal),numParcelas));
			calculo2 = (calculo1 -1)/(calculo1*taxamensal);
			pmt = pv/calculo2;
			totalfinancimanto = pmt * numParcelas;
			printf("Valor a pagar sera em %i parcelas de R$%.2f. Totalizando o valor de R$%.2f, com uma entrada de R$%.2f\n", numParcelas,pmt,totalfinancimanto,valorentrada);
			i = 0;
			do{
				printf("Confirma proposta de financiamento? S para SIM N para NAO [S/N]: ");
				getchar();
				scanf("%c", &resp);
				i = 1;
				if(resp=='S'|| resp=='s'){
					fprintf(arq, "%s %i %i %i %i\n", cpf_user, nroproposta, financimento,nroimovel,status);
					printf("Proposta Enviada com sucesso! Iremos entrar em contato com voce para darmos continuidade no processo");
					i = 0;
				}
				else if(resp=='N'|| resp=='n'){}
				else{
					i = 1;
					printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
				}
			}while(i>0);
			fclose(arq);

		}
		else if(resp5 == 2){
			do{	
				printf("Informe o valor da entrada, lembrando que deve ser superior a R$%.2f\n\n Valor Entrada: ", valorentrada);
				scanf("%f",&valorentrada2);
				if(valorentrada2>=valorentrada){
					pv = principal - valorentrada2;
					juros = principal*taxamensal;
					calculo1 = (pow((1+taxamensal),numParcelas));
					calculo2 = (calculo1 -1)/(calculo1*taxamensal);
					pmt = pv/calculo2;
					totalfinancimanto = pmt * numParcelas;
					printf("Valor a pagar sera em %i parcelas de R$%.2f. Totalizando o valor de R$%.2f, com uma entrada de R$%.2f\n", numParcelas,pmt,totalfinancimanto,valorentrada2);
					i = 0;
					do{
						printf("Confirma proposta de financiamento? S para SIM N para NAO [S/N]: ");
						getchar();
						scanf("%c", &resp);
						i = 1;
						if(resp=='S'|| resp=='s'){
							fprintf(arq, "%s %i %i %i %i\n", cpf_user, nroproposta, financimento,nroimovel,status);
							printf("Proposta Enviada com sucesso! Iremos entrar em contato com voce para darmos continuidade no processo");
							i = 0;
						}
						else if(resp=='N'|| resp=='n'){}
						else{
							i = 1;
							printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
						}
					}while(i>0);
					fclose(arq);
					}
				else{
					printf("Insira um valor de entrada igual ou maior do que R$%.2f.\n",valorentrada);	
					i = 1;				
				}
			}while(i>0);
		}
		else if(resp5 == 3){
			printf("Infelizmente nao conseguiremos simular um financimento.");
			i = 0;

		}
		else{
			i = 1;
			printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");

		}
	}while(i>0);

	//caro professor Cesar, se você estiver lendo isso, saiba que nos dedicamos muito e gostariamos de tirar um 10
	// dá uma olhada depois no nosso github ;) https://github.com/VenciguerJ/Projeto-PIM/blob/main/main.c

}

void imprimir_dados(imovel a){
    printf("Identificacao Imovel: %i\n", a.nroimovel);
	colocar_espaco(a.endereco);
    printf("Endereco: %s\n", a.endereco);
	colocar_espaco(a.bairro);
    printf("Bairro: %s\n", a.bairro);
	colocar_espaco(a.cidade);
    printf("Cidade: %s\n", a.cidade);
	colocar_espaco(a.estado);
    printf("Estado: %s\n", a.estado);
    printf("CEP: %s\n", a.cep);
    printf("Metragem do terreno: %i\n", a.metragemtotal);
    printf("Metragem area construida: %i\n", a.metragemconstruido);
    printf("Quantidade de quartos: %i\n", a.numerodequartos);
    printf("Quantidade de suites: %i\n", a.numerodesiutes);
    printf("Quantidade de salas: %i\n", a.numerodesalas);
    printf("Quantidade de banheiros: %i\n", a.numerodebanheiros);
    printf("Possui piscina: %c\n", a.tempiscina);
    printf("Possui churrasqueira: %c\n", a.temchurrasqueia);
    printf("Valor do imovel: %.2f\n", a.valor);
}

void imprimir_dados_resumidos(imovel a){
	printf("Imovel numero: [%i] Estado: [%s] Cidade: [%s] Tamanho: [%i]M2\nEndereco: [%s] Quartos: [%i]\nValor: R$ [%.2f]\n\n\n",a.nroimovel, a.estado, a.cidade, a.metragemtotal, a.endereco, a.numerodequartos, a.valor);
}

void remover_imovel(char *arquivo, int numimovel, char *cep2){
    imovel tmp;
    FILE* arq = fopen(arquivo,"r");
    FILE* arqNovo = fopen("novo.txt","w"); 
    while(!feof(arq)){
	    fscanf(arq,"%s %i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n", tmp.cpfcorretor, &tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, &tmp.tempiscina, &tmp.temchurrasqueia, &tmp.valor);
        if (tmp.nroimovel!=numimovel && strcmp(tmp.cep, cep2)!=0){ //compara os dois imoveis
            fprintf(arq, "%s %i %s %s %s %s %s %i %i %i %i %i %i %c %c %.2f \n",tmp.cpfcorretor, tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, tmp.metragemtotal, tmp.metragemconstruido, tmp.numerodequartos, tmp.numerodesiutes, tmp.numerodesalas, tmp.numerodebanheiros, tmp.tempiscina, tmp.temchurrasqueia, tmp.valor);
        }
    }
    fclose(arq); 
    fclose(arqNovo); 
    system("del imoveis.txt");
    system("rename novoemp.txt imoveis.txt");
}

imovel pesquisa_imovel(char *arquivo, int numimovel){ // retorna uma variavel do tipo imovel do numero que pesquisamos

	FILE *arq = fopen(arquivo, "r");
	imovel tmp;
	
	while(!feof(arq)){
		fscanf(arq,"%s %i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n",tmp.cpfcorretor, &tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, &tmp.tempiscina, &tmp.temchurrasqueia, &tmp.valor);
		if(numimovel == tmp.nroimovel){
			break;
		}
		else{
			tmp.nroimovel = -1;
		}
	}
	fclose(arq);
	return tmp;
}

int qtd_imoveis(char *arquivo){ // retorna quantidade de imoveis

    FILE *arq = fopen(arquivo, "r");
    imovel tmp;
    int c = 0;
    while (!feof(arq)){
        fscanf(arq,"%s %i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n",tmp.cpfcorretor, &tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, &tmp.tempiscina, &tmp.temchurrasqueia, &tmp.valor);
        c++; 
    }
    fclose(arq);
    return c;
}

void imovel_cadastro_cria_infos(char *arquivo){ // cadastra as informações do imovel
    int i=0;
    imovel tmp;
    FILE *arq = fopen(arquivo, "a+");
    tmp.nroimovel = qtd_imoveis(arquivo)+1;

    printf("Vamos iniciar o cadastro de um novo imovel, coloque as inforacoes a seguir\n\n");
	printf("Endereco: ");
	getchar();
	fgets(tmp.endereco, sizeof(tmp.endereco), stdin);
	if (tmp.endereco[strlen(tmp.endereco) - 1] == '\n'){
    	tmp.endereco[strlen(tmp.endereco) - 1] = '\0';
	}
	tirar_espaco(tmp.endereco);
    printf("Bairro: ");
    fgets(tmp.bairro, sizeof(tmp.bairro), stdin);
	if (tmp.bairro[strlen(tmp.bairro) - 1] == '\n'){
    	tmp.bairro[strlen(tmp.bairro) - 1] = '\0';
	}
	tirar_espaco(tmp.bairro);
    printf("Cidade: "); 
    fgets(tmp.cidade, sizeof(tmp.cidade), stdin);
    if (tmp.cidade[strlen(tmp.cidade) - 1] == '\n'){
    	tmp.cidade[strlen(tmp.cidade) - 1] = '\0';
	}
	tirar_espaco(tmp.cidade);
    printf("Estado: ");
    scanf("%s", tmp.estado); 
    do{    
        printf("Informe o CEP com 8 digitos no seguinte formarto 13214743 (sem o traco): ");
        scanf("%s", tmp.cep);
        if(strlen(tmp.cep) > 10){
            printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
            i = 1;
		}

    }while(i>0);
	getchar(); 
	printf("Metragem do terreno total: ");
	scanf("%i", &tmp.metragemtotal);    
	printf("Metragem da area contruida total: ");
	scanf("%i", &tmp.metragemconstruido); 
	printf("Numeros de quartos na casa: ");
	scanf("%i", &tmp.numerodequartos); 
	printf("Numeros de suites na casa: ");
	scanf("%i", &tmp.numerodesiutes); 
	printf("Numeros de salas na casa: ");
	scanf("%i", &tmp.numerodesalas); 
	printf("Numeros de banheiros na casa: ");
	scanf("%i", &tmp.numerodebanheiros); 
	getchar(); 

	i = 0;
	do{    
        printf("Tem piscina na casa, informa S para SIM e N para NAO [S/N]: ");
        scanf("%c", &tmp.tempiscina);
        if(tmp.tempiscina != 'S' && tmp.tempiscina != 'N' && tmp.tempiscina != 's' && tmp.tempiscina != 'n'){
            printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
            i = 1;
        }
    }while(i>0);

	i=0;
	do{    
        printf("Tem churrasqueira na casa, informa S para SIM e N para NAO [S/N]: ");
		getchar();
        scanf("%c", &tmp.temchurrasqueia);
        if(tmp.tempiscina != 'S' && tmp.tempiscina != 'N' && tmp.tempiscina != 's' && tmp.tempiscina != 'n'){
            printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
            i = 1;
        }
    }while(i>0);
	printf("Informe o valor do preco do imovel para venda, casas decimais devem ser informas com ponto da seguinte forma R$ 200300.33: ");
	scanf("%f", &tmp.valor);

	strcpy(tmp.cpfcorretor, cpf_user);

	if (arq!=NULL){
		fprintf(arq, "%s %i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n", tmp.cpfcorretor, tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, tmp.metragemtotal, tmp.metragemconstruido, tmp.numerodequartos, tmp.numerodesiutes, tmp.numerodesalas, tmp.numerodebanheiros, tmp.tempiscina, tmp.temchurrasqueia, tmp.valor);
	}
	fclose(arq);
	printf("\n\nO cadastro do imovel foi feito com sucesso! A identificacao dele e '%i' em nosso sistema, guarde a informacao\n\n", tmp.nroimovel);
	
}

void altera_imovel(){ // recadastra o imovel
    imovel tmp;
	int numimovel;
	char  cep2[9];
    FILE* arq = fopen(fimoveis,"r");
    FILE* arqNovo = fopen("novo.txt","w"); 
	int i=0;
    tmp.nroimovel = qtd_imoveis(fimoveis) + 1;

	printf("Qual o numero do imovel?");
	scanf("%i", &numimovel);
	printf("\n");
	printf("Qual o cep do imovel?");
	scanf("%s", cep2);

    while(!feof(arq)){
	    fscanf(arq,"%s %i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n", tmp.cpfcorretor, &tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, &tmp.tempiscina, &tmp.temchurrasqueia, &tmp.valor);
        if (tmp.nroimovel!=numimovel && strcmp(tmp.cep, cep2)!=0){
            fprintf(arqNovo, "%s %i %s %s %s %s %s %i %i %i %i %i %i %c %c %.2f \n",tmp.cpfcorretor, tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, tmp.metragemtotal, tmp.metragemconstruido, tmp.numerodequartos, tmp.numerodesiutes, tmp.numerodesalas, tmp.numerodebanheiros, tmp.tempiscina, tmp.temchurrasqueia, tmp.valor);
        }	
		else{
			    printf("Vamos iniciar a alteracao do imovel %i, coloque as inforacoes a seguir para alteracao\n\n",tmp.nroimovel);
				printf("Endereco: ");
				getchar();
				fgets(tmp.endereco, sizeof(tmp.endereco), stdin);
				if (tmp.endereco[strlen(tmp.endereco) - 1] == '\n'){
					tmp.endereco[strlen(tmp.endereco) - 1] = '\0';
				}
				tirar_espaco(tmp.endereco);
				printf("Bairro: ");
				fgets(tmp.bairro, sizeof(tmp.bairro), stdin);
				if (tmp.bairro[strlen(tmp.bairro) - 1] == '\n'){
					tmp.bairro[strlen(tmp.bairro) - 1] = '\0';
				}
				tirar_espaco(tmp.bairro);
				printf("Cidade: "); 
				fgets(tmp.cidade, sizeof(tmp.cidade), stdin);
				if (tmp.cidade[strlen(tmp.cidade) - 1] == '\n'){
					tmp.cidade[strlen(tmp.cidade) - 1] = '\0';
				}
				tirar_espaco(tmp.cidade);
				printf("Estado: ");
				scanf("%s", tmp.estado); 
				do{    
					printf("Informe o CEP com 8 digitos no seguinte formarto 13214743 (sem o traco): ");
					scanf("%s", tmp.cep);
					if(strlen(tmp.cep) > 10){
						printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
						i = 1;
					}

				}while(i>0);
				getchar(); 
				printf("Metragem do terreno total: ");
				scanf("%i", &tmp.metragemtotal);    
				printf("Metragem da area contruida total: ");
				scanf("%i", &tmp.metragemconstruido); 
				printf("Numeros de quartos na casa: ");
				scanf("%i", &tmp.numerodequartos); 
				printf("Numeros de suites na casa: ");
				scanf("%i", &tmp.numerodesiutes); 
				printf("Numeros de salas na casa: ");
				scanf("%i", &tmp.numerodesalas); 
				printf("Numeros de banheiros na casa: ");
				scanf("%i", &tmp.numerodebanheiros); 
				getchar(); 

				i = 0;
				do{    
					printf("Tem piscina na casa, informa S para SIM e N para NAO [S/N]: ");
					scanf("%c", &tmp.tempiscina);
					if(tmp.tempiscina != 'S' && tmp.tempiscina != 'N' && tmp.tempiscina != 's' && tmp.tempiscina != 'n'){
						printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
						i = 1;
					}
				}while(i>0);

				i=0;
				do{    
					printf("Tem churrasqueira na casa, informa S para SIM e N para NAO [S/N]: ");
					getchar();
					scanf("%c", &tmp.temchurrasqueia);
					if(tmp.tempiscina != 'S' && tmp.tempiscina != 'N' && tmp.tempiscina != 's' && tmp.tempiscina != 'n'){
						printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
						i = 1;
					}
				}while(i>0);
				printf("Informe o valor do preco do imovel para venda, casas decimais devem ser informas com ponto da seguinte forma R$ 200300.33: ");
				scanf("%f", &tmp.valor);

				strcpy(tmp.cpfcorretor, cpf_user);

				if (arqNovo!=NULL){
					fprintf(arqNovo, "%s %i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n", tmp.cpfcorretor, tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, tmp.metragemtotal, tmp.metragemconstruido, tmp.numerodequartos, tmp.numerodesiutes, tmp.numerodesalas, tmp.numerodebanheiros, tmp.tempiscina, tmp.temchurrasqueia, tmp.valor);
				}
				printf("\n\nO cadastro do imovel %i foi autalizado com sucesso!!!\n\n", tmp.nroimovel);

			}
		
    }
    fclose(arq); 
    fclose(arqNovo); 
    system("del imoveis.txt");
    system("rename novo.txt imoveis.txt");
}

int consulta_imovel(char *arquivo){ // retorna o numero no imovel
    imovel consulta;
    int nroimovel;
    printf("Consulta de imoveis \n\n");
    printf("Informe o codigo de identificacao do imovel: ");
    scanf("%i", &nroimovel);
    consulta = pesquisa_imovel(arquivo, nroimovel);
    if(consulta.nroimovel!=-1)
    {
    printf("\n\n");
    imprimir_dados(consulta);
    }
    else
    {
    printf("Imovel nao encontrado!\n\n");
    }
	return consulta.nroimovel;
}

void atualiza_dado(const char *novovalor){ // atualiza o CPF para ser usado na MAIN
	strcpy(cpf_user, novovalor);
}

user pesquisa_user(char *arquivo, char *cpf){ // pesquisa os dados do usuario

	FILE *arq = fopen(arquivo, "r");
	user tmp;
	
	while(!feof(arq)){
		fscanf(arq, "%s %i %i %s %s %s %s\n", tmp.nome, &tmp.idade, &tmp.rendaMensal, tmp.cpf, tmp.password, tmp.nrocllr, tmp.email);
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

char *pesquisa_arquivo(char *cpf){ //vê qual é o arquivo que está o cpf
	user tmp;
    char *arqcorreto = NULL;

    tmp = pesquisa_user(fclientes, cpf);
    if (strcmp(tmp.cpf, "-1") != 0) {
        arqcorreto = (char *)malloc(strlen(fclientes) + 1); // Aloca memória para arqcorreto
        strcpy(arqcorreto, fclientes);
    } else {
        tmp = pesquisa_user(fcorretores, cpf);
        if (strcmp(tmp.cpf, "-1") != 0) {
            arqcorreto = (char *)malloc(strlen(fcorretores) + 1); // Aloca memória para arqcorreto
            strcpy(arqcorreto, fcorretores);
        }
    }
    return arqcorreto;
}

int verifica_cpf(char *cpf){ //retorna 1 se o cpf estiver cadastrado e 0 se o cpf não estiver cadastrado
	user tmp;
	int pode;
	tmp = pesquisa_user(fclientes, cpf);
	if (strcmp(tmp.cpf, "-1") == 0){
		tmp = pesquisa_user(fcorretores, cpf);
		if (strcmp(tmp.cpf, "-1") == 0){
			pode = 0; // pode cadastrar o cpf
		}
	}
	else{
		pode = 1; //não pode cadastrar o cpf
	}
	return pode;
}

void login_cadastro_cria_infos(char *arquivo){ // cria as informações de cadastro do usuário
	int iguais, podeusarcpf;
	char tmppass[11];
	user tmp;
	
	// começa perguntando dados
	printf("Digite seu nome: ");
	getchar();
	fgets(tmp.nome, sizeof(tmp.nome), stdin);
    size_t tamanho = strlen(tmp.nome);
    if (tamanho > 0 && tmp.nome[tamanho - 1] == '\n'){
        tmp.nome[tamanho - 1] = '\0';
    }
	tirar_espaco(tmp.nome);

	printf("Digite sua idade: ");
	scanf("%i", &tmp.idade);
	
	printf("digite seu numero de celular (com ddd)");
	scanf("%s", tmp.nrocllr);
	
	printf("DIgite seu E-mail: ");
	scanf("%s", tmp.email);

	printf("Qual a sua renda mensal ?: ");
	scanf("%i", &tmp.rendaMensal);

	printf("Digite seu CPF (apenas numeros): ");
	scanf("%s", tmp.cpf);

	podeusarcpf = verifica_cpf(tmp.cpf);

	if(podeusarcpf == 0){
		do {
			iguais = 1;
			do{
				printf("Crie uma senha (ela deve ter no maximo 10 caracteres): ");
				getSenha(tmp.password);
				printf("\n");
				if(strlen(tmp.password)>10){
					printf("senha muito longa\n");
				} 
			}while (strlen(tmp.password)>10);
			printf("Confirme sua nova senha: ");
			getSenha(tmppass);

			// Verifica se as senhas têm o mesmo comprimento e se são iguais
			if (strlen(tmp.password) != strlen(tmppass) || strcmp(tmp.password, tmppass) != 0) {
				iguais = 0;
				printf("\nAs senhas nao conferem! Tente novamente.\n\n");
			}
		} while (iguais == 0);
		
		FILE *arq = fopen(arquivo, "a+"); //abre o arquivo para escrita
	
		if(arq != NULL){
			fprintf(arq, "%s %i %i %s %s %s %s\n", tmp.nome, tmp.idade, tmp.rendaMensal, tmp.cpf, tmp.password, tmp.nrocllr, tmp.email);
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

    printf("\n NOVO CADASTRO! \n \n");

	printf("Novo cliente ou corretor? \n 1 - cliente \n 2 - corretor \n \n Escolha: "); //pergunta o tipo de usuario
	scanf("%i", &resp);
	
	if(resp == 1){
		login_cadastro_cria_infos(fclientes);
	}
	else if(resp == 2){
		login_cadastro_cria_infos(fcorretores);
	}
	else{
		printf("Entrada ivalida!");
	}
}

void login(){ // Loga o usuario (obviamente)
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
				
				pesq = pesquisa_user(fclientes, tempCPF);
				if(strcmp(pesq.cpf, "-1") == 0){//retorna -1 casoo não seja encontrado
					pesq = pesquisa_user(fcorretores, tempCPF);
					if(strcmp(pesq.cpf, "-1") == 0){
						printf("usuario não encontrado\n\n");
						break;
					}
				}
				if(strlen(pesq.cpf) == strlen(tempCPF) && strcmp(pesq.cpf, tempCPF) == 0) //pesq.cpf == tempCPF
				{
					do{
						printf("Digite sua senha: ");
						getSenha(tempsenha);

						if (strlen(pesq.password) == strlen(tempsenha) && strcmp(pesq.password, tempsenha) == 0){
							printf("Login concluido! \n \n");
							atualiza_dado(pesq.cpf);
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
//termina login e começa proposta
void aluguel(float valorimovel,char *cpf, int nroimovel){//Mostra os valores de aluguel
	float aluguel = (valorimovel * 0.5)/100;
	float calcao = aluguel*2;
	char resp;
	int  status = 1;
	int valuguel=1;
	int i;
	int nroproposta = qtd_propostas(fpropostas) + 1;
	FILE *arq = fopen(fpropostas, "a+");


	printf("Aluguel do Imovel tera de um calcao inicial de R$%.2f e o valor do aluguel de R$%.2f, Total inicial (primeiro mes) de: R$%.2f\n\n", calcao, aluguel, (aluguel + calcao));
	do{	
		printf("Confirma proposta de aluguel? S para SIM N para NAO [S/N]: ");
		getchar();
		scanf("%c", &resp);
		i = 1;
		if(resp=='S'||resp=='s'){
			fprintf(arq, "%s %i %i %i %i\n", cpf, nroproposta, valuguel, nroimovel,status);
			printf("Proposta Enviada com sucesso! Iremos entrar em contato com voce para darmos continuidade no processo");
			i = 0;
		}
		else if(resp=='N'||resp=='n'){}
		else{
			i = 1;
			printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
		}
	}while(i>0);
	fclose(arq);
}

void compra(float valorimovel,char *cpf, int nroimovel){
	int resp3, i=1,compra = 3, status = 1,nroparcelas;
	char resp4;
	int nroproposta = qtd_propostas(fpropostas) + 1;
	FILE *arq = fopen(fpropostas, "a+");

	do{	printf("1 - Pagamento a vista\n2 - Financiamento\n\nEscolha:");
		getchar();
		scanf("%i", &resp3);
		if(resp3==1){ // pagamento à vista
			printf("O Imovel esta no valor de R$%.2f, \n", valorimovel);
			do{ 
				printf("Confirma proposta de compra? S para SIM N para NAO [S/N]: ");
				getchar();
				scanf("%c", &resp4);
				if(resp4=='S'||resp4=='s'){
					fprintf(arq, "%s %i %i %i %i\n", cpf, nroproposta, compra,nroimovel,status);
					printf("Proposta Enviada com sucesso! Iremos entrar em contato com voce para darmos continuidade no processo\n\n");
					i = 0;
				}
				else if(resp4=='N'||resp4=='n'){
					
					do{	printf("Deseja verificar as possibilidades de Financimento ou Aluguel? 1 - Aluguel\n2 - Financiamento\n3 - Sair\n\nEscolha:");
						getchar();
						scanf("%i", &resp3);
						if(resp3==1){
							aluguel(valorimovel,cpf,nroimovel);
							i = 0;
						}
						else if(resp3==2){
							printf("Informe em quantos meses deseja pagar o imovel: ");
							scanf("%i",&nroparcelas);
							calculadora_price(fpropostas, valorimovel,nroparcelas,nroimovel);
							i = 0;
						}
						else if(resp3==3){
							i = 0;
						}
						else{
							i = 1;
							printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
						}
					}while(i>0);
				}
				i = 0;
			}while(i>0);
			
		}
		else if(resp3==2){ // Financiamento
			    printf("Informe em quantos meses deseja pagar o imovel: ");
				scanf("%i",&nroparcelas);
				calculadora_price(fpropostas, valorimovel,nroparcelas,nroimovel);
				i = 0;	
		}
		else{
				printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
				i = 1;
			}
	}while(i>0);		
	fclose(arq);	
	}

void nova_proposta(float valorimovel,int nroimovel){
	//Tabela price
	printf("NOVA PROPOSTA\n\n");
	int resp, i=1;
    char *arquser; 
	arquser = pesquisa_arquivo(cpf_user);
    FILE *arq = fopen(arquser, "r");
 
	printf("Deseja comprar ou alugar o imovel?\n1 - Alugar\n2 - Comprar\n\nEscolha: ");
	scanf("%i", &resp);
	do{	if(resp==1){ // aluguel
			aluguel(valorimovel,cpf_user,nroimovel);
			i = 0;
			}
		
		else if(resp==2){ // compra
			compra(valorimovel,cpf_user,nroimovel);
			i = 0;		
		}

		else{
			printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
		}
	}while(i>0);

	fclose(arq);
}

proposta pesquisa_proposta(){ // retorna a variavel proposta
	int numeroproposta;
	FILE *arq = fopen(fpropostas, "a+");
	proposta tmp;
	printf("Digite o numero da proposta: ");
	scanf("%i", &numeroproposta);

	while(!feof(arq)){
		fscanf(arq, "%s %i %i %i %i\n", tmp.cpfsolicitante, &tmp.nroproposta, &tmp.type, &tmp.numeroImovel, &tmp.status);
		if(numeroproposta == tmp.nroproposta){
			break;
		}
		else{
			tmp.nroproposta = -1;
		}
	}
	fclose(arq);
	return tmp;
}

void proposta_imprimir_dados_cliente(proposta a){
	
	char status[50];
	switch (a.status){
	case 1: // Aguardando aprovação
		strcpy(status, "Aguardando aprovacao");
		break;
	case 2: // Aprovado
		strcpy(status, "Aprovado!");
		break;
	case 3: // Recusado
		strcpy(status, "Recusado :/");
		break;
	default:
		break;
	}
	imovel imv = pesquisa_imovel(fimoveis, a.numeroImovel);	
	user corretorimovel = pesquisa_user(fcorretores, imv.cpfcorretor);
	colocar_espaco(corretorimovel.nome);
	printf("Proposta N: [%i] Imovel: [%i] DE: [%s]\nStatus[%s]\n\n",a.nroproposta, imv.nroimovel, corretorimovel.nome, status);
}

void proposta_imprimir_dados_corretor(proposta a){
	char status[50];
	switch (a.status){
	case 1: // Aguardando aprovação
		strcpy(status, "Aguardando aprovacao");
		break;
	case 2: // Aprovado
		strcpy(status, "Aprovado!");
		break;
	case 3: // Recusado
		strcpy(status, "Recusado :/");
		break;
	default:
		break;
	}
	user solicitante = pesquisa_user(fclientes, a.cpfsolicitante);
	imovel imv = pesquisa_imovel(fimoveis, a.numeroImovel);
	printf("PROPOSTAS PARA MEU IMOVEL\n\n");

	printf("Numero da proposta: [%i] Proposta para o imovel: [%i] Bairro: [%s] Status: [%s]\nProposta de: [%s]\n\n",a.nroproposta, imv.nroimovel, imv.bairro,status, solicitante.nome);
}

void menu_buscar_imoveis(){
	system("cls");
	printf("IMOVEIS\n\n");
	int resp;
	char resp2;
	imovel tmp, imovelSelecionado;
	FILE *arq = fopen(fimoveis, "r");
	user usu;
	do{
		while(!feof(arq)){
			fscanf(arq,"%s %i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n",tmp.cpfcorretor, &tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, &tmp.tempiscina, &tmp.temchurrasqueia, &tmp.valor);
			colocar_espaco(tmp.endereco);
			colocar_espaco(tmp.bairro);
			colocar_espaco(tmp.cidade);
			imprimir_dados_resumidos(tmp);
		}
		printf("O que deseja fazer?\n\n1 - Selecionar um imovel\n2 - Sair\n\nEscolha: ");
		scanf("%i", &resp);

		if(resp==1){
			
			int numeroDoImovel = consulta_imovel(fimoveis); //perga o numero do imovel

			imovelSelecionado = pesquisa_imovel(fimoveis, numeroDoImovel);
			printf("\nDeseja compar ou alugar o Imovel? S para SIM N para NAO [S/N]: ");
			getchar();
			scanf("%c", &resp2);
			if (resp2=='s'||resp2=='S'){	
				usu = pesquisa_user(fclientes, cpf_user);
				if(strcmp (usu.cpf, "-1")==0){
					printf("Voce esta com um perfil de corretor, portanto somente clientes podem fazer propostas\n");
				}
				else{
					nova_proposta(imovelSelecionado.valor,imovelSelecionado.nroimovel);
				}	
				
			}
			else if(resp2=='n'|| resp2=='N'){ // Não faz nada
			}
			else{
				printf("Entrada invalida!");
			}
		}
		else if(resp==2){} //não faz nada
		else{
			printf("Entrada invalida\n");
		}
	}while(resp!=2);
}

void menu_propostas_e_alugueis(){
	printf("MINHAS PROPOSTAS\n\n");
	FILE *arq = fopen(fpropostas, "a+");
	FILE *tmparq = fopen("temp.txt", "a+");
	proposta a, menu;
	imovel tmp;
	user logado, solicitante;
	int resp; 
	char resp2;

	logado = pesquisa_user(fclientes, cpf_user);


	if(strcmp(logado.cpf, "-1")==0){ 
		logado = pesquisa_user(fcorretores, cpf_user); // ve o menu de corretores

		while (!feof(arq)){
			fscanf(arq, "%s %i %i %i %i\n", a.cpfsolicitante,&a.nroproposta, &a.type, &a.numeroImovel, &a.status);
			tmp = pesquisa_imovel(fimoveis, a.numeroImovel);
			if(strcmp(tmp.cpfcorretor, cpf_user)==0){
				proposta_imprimir_dados_corretor(a);
			}
		}	
		
		printf("O que deseja fazer?\n\n1 - Selecionar proposta\n2 - sair\n\nEscolha: ");
		scanf("%i", &resp);
		if(resp==1){
			menu = pesquisa_proposta(); // ver se abre o menu
			solicitante = pesquisa_user(fclientes, a.cpfsolicitante);

			printf("DADOS DA PROPOSTA\n\n");
			imprimir_dados_resumidos(tmp);
			printf("Solicitante [%s] Idade[%i]\n", solicitante.nome, solicitante.idade);
			printf("Renda mensal [%i]\n\n", solicitante.rendaMensal);
			
			printf("Aprova proposta? S para SIM N para NAO [S/N]: ");
			getchar();
			scanf("%c", &resp2);

			if(resp2 == 's'||resp2=='S'){
				while(!feof(arq)){
					fscanf(arq, "%s %i %i %i %i\n", a.cpfsolicitante, &a.nroproposta, &a.type, &a.numeroImovel, &a.status);
					if(strcmp(menu.cpfsolicitante, a.cpfsolicitante)!=0){
						fprintf(tmparq, "%s %i %i %i %i\n", a.cpfsolicitante, a.nroproposta, a.type, a.numeroImovel, a.status);
					}
				}
				fprintf(tmparq, "%s %i %i %i %i\n", a.cpfsolicitante, a.nroproposta, a.type, a.numeroImovel, 2);
				fclose(arq);
				fclose(tmparq);
				remove(fpropostas);
				rename("temp.txt", fpropostas);

				printf("PROPOSTA APROVADA!\n\n");
			}
			else if(resp2=='n'||resp2=='N'){
				while(!feof(arq)){
					fscanf(arq, "%s %i %i %i %i\n", a.cpfsolicitante, &a.nroproposta, &a.type, &a.numeroImovel, &a.status);
					if(strcmp(menu.cpfsolicitante, a.cpfsolicitante)!=0){
						fprintf(tmparq, "%s %i %i %i %i\n", a.cpfsolicitante, a.nroproposta, a.type, a.numeroImovel, a.status);
					}
				}
				fprintf(tmparq, "%s %i %i %i %i\n", a.cpfsolicitante, a.nroproposta, a.type, a.numeroImovel, 3);
				fclose(arq);
				fclose(tmparq);
				remove(fpropostas);
				rename("temp.txt", fpropostas);

				printf("PROPOSTA NEGADA!\n\n");
			}

		}
		
	}
	else{
		while (!feof(arq)){// menu de clientes
			fscanf(arq, "%s %i %i %i %i\n", a.cpfsolicitante,&a.nroproposta, &a.type, &a.numeroImovel, &a.status);
			if(strcmp(cpf_user, a.cpfsolicitante)==0){
				proposta_imprimir_dados_cliente(a);
			}
		}
	}
}

void edita_arquivo(char *arquivo, user usuario){ //arquivo a ser editado e cpf a sofrer a alteração
	user tmp; // usuario temporário
	FILE *arq = fopen(arquivo, "r");
	FILE *tmparq = fopen("temp.txt", "a+");

	while(!feof(arq)){
		fscanf(arq, "%s %i %i %s %s %s %s\n", tmp.nome, &tmp.idade, &tmp.rendaMensal, tmp.cpf, tmp.password, tmp.email, tmp.nrocllr);
		if(strlen(usuario.cpf)!=strlen(tmp.cpf)&&strcmp(usuario.cpf, tmp.cpf)!=0){
			fprintf(tmparq, "%s %i %i %s %s %s %s\n", tmp.nome, tmp.idade, tmp.rendaMensal, tmp.cpf, tmp.password, tmp.email, tmp.nrocllr);
		}
	}
	fprintf(tmparq, "%s %i %i %s %s %s %s\n", tmp.nome, tmp.idade, tmp.rendaMensal, tmp.cpf, tmp.password, tmp.email, tmp.nrocllr);

	fclose(arq);
	fclose(tmparq);
	remove(arquivo);
	rename("temp.txt", arquivo);
}

void remove_do_arquivo(char *arquivo, user usuario){ //tira o cpf do arquivo
	user tmp;
	FILE *arq = fopen(arquivo, "r");
	FILE *tmparq = fopen("temp.txt", "a+");
	
	fscanf(arq, "%s %i %i %s %s %s %s\n", tmp.nome, &tmp.idade, &tmp.rendaMensal, tmp.cpf, tmp.password, tmp.email, tmp.nrocllr);
	if(strlen(usuario.cpf)!=strlen(tmp.cpf)&&strcmp(usuario.cpf, tmp.cpf)!=0){
		fprintf(tmparq, "%s %i %i %s %s %s %s\n", tmp.nome, tmp.idade, tmp.rendaMensal, tmp.cpf, tmp.password, tmp.email, tmp.nrocllr);
	} 
	fclose(arq);
	fclose(tmparq);
	remove(arquivo);
	rename("temp.txt", arquivo);
}

void ver_perfil(){ // módulo do perfil 

	int resp=0, resp2, resp3;
	char *arquser;
	arquser = pesquisa_arquivo(cpf_user);
	user usuario = pesquisa_user(arquser, cpf_user);
	printf("Perfil do usuario: \n");
	
	colocar_espaco(usuario.nome);
	printf("Nome: %s \n", usuario.nome);
	printf("Idade: %i \n", usuario.idade);
	printf("CPF: %s \n", usuario.cpf);
	printf("Renda Mensal: %i\n", usuario.rendaMensal);
	printf("E-mail: %s\n", usuario.email);
	printf("Numero de Cel: %s\n\n", usuario.nrocllr);
	
	do{
		printf("1 - excluir usuario\n2 - Editar perfil\n3 - sair\n\nEscolha: ");
		scanf("%i", &resp);
	
		if(resp == 1){ // exclusão de usuário
			printf("Confirma a exlusão deste usuário?\n\n1 - sim\n2 - não\n\nEscolha: ");
			scanf("%i",&resp2);
			if(resp2 == 1){
				remove_do_arquivo(arquser, usuario);
			}
		}
		else if(resp == 2){ // alteração do usuário
			printf("EDICAO DE USUARIO\n\n1 - Nome\n2 - Idade\n3 - CPF\n4 - Senha\n5 - E-mail\n6 - Celular\n7 - Renda Mensal\n\nEscolha: ");
			scanf("%i", &resp2);
			
			if(resp2==1){//nome
				char tempname[101];
				printf("\nQual e o novo nome?: ");
				getchar();
				fgets(tempname, sizeof(tempname), stdin); //pega a linha inteira
				size_t tamanho = strlen(tempname);
    			if (tamanho > 0 && tempname[tamanho - 1] == '\n'){
        			tempname[tamanho - 1] = '\0'; //termina a linha no final da string
    			}
				tirar_espaco(tempname);
				if(strlen(usuario.nome)==strlen(tempname)&&strcmp(usuario.nome, tempname)==0){
					printf("Nomes iguais!");
				}
				else{
					// termina de perguntar dados e começa a tratar os dados
					printf("Confirma alteracao?\n1 - Sim\n2 - Nao\n\nEscolha: ");
					scanf("%i",&resp3);
					if(resp3==1){
						strcpy(usuario.nome,tempname);
						edita_arquivo(arquser, usuario);	
					}
					
				}
			}
			else if(resp2==2){
				int tempidade;
				printf("Qual e a nova idade?: ");
				scanf("%i",&tempidade);
				printf("Confirma alteracao?\n1 - Sim\n2 - Nao\n\nEscolha: ");
				scanf("%i",&resp3);
				if(resp3==1){
					usuario.idade = tempidade;
					edita_arquivo(arquser, usuario);
				}
			}
			else if(resp2==3){//altera cpf
				char tempcpf[12];
				printf("Qual e o novo CPF?: ");
				scanf("%s",tempcpf);
				printf("Confirma alteracao?\n1 - Sim\n2 - Nao\n\nEscolha: ");
				scanf("%i",&resp3);
				if(resp3==1){
					strcpy(usuario.cpf,tempcpf);
					atualiza_dado(usuario.cpf);
					edita_arquivo(arquser, usuario);
				}
			}
			else if(resp2==4){//alterasenha
				char temppassword[10];
				char temppassword2[10];
				printf("Digite sua senha:");
				scanf("%s", temppassword);
				
				if(strlen(temppassword)==strlen(usuario.password)&&strcmp(temppassword, usuario.password)==0){
					printf("Qual e a nova senha?: ");
					scanf("%s", temppassword2);
					printf("confirma alteracao da nova senha?:\n1 - Sim\n2 - Nao\n\nEscolha: ");
					scanf("%i",&resp3);
					if(resp3==1){
						strcpy(usuario.password,temppassword2);
						edita_arquivo(arquser, usuario);
					}
				}
				else{
					printf("senha incorreta, operation cancelled\n\n");
				}
			}
			else if(resp2==5){
				char tempemail[101];
				printf("Qual e o novo E-mail?: ");
				scanf("%s",tempemail);
				printf("Confirma alteração?\n1 - Sim\n2 - Nao\n\nEscolha: ");
				scanf("%i",&resp3);
				if(resp3==1){
					strcpy(usuario.email,tempemail);
					edita_arquivo(arquser, usuario);
				}
			}
			else if(resp2==6){
				char tempcell[15];
				printf("Qual e o novo numero?: ");
				scanf("%s",tempcell);
				printf("Confirma alterao?\n1 - Sim\n2 - Nao\n\nEscolha: ");
				scanf("%i",&resp3);
				if(resp3==1){
					strcpy(usuario.nrocllr,tempcell);
					edita_arquivo(arquser, usuario);
				}
			}
			else if(resp2==7){
				int tempRenda;
				printf("Qual e a nova renda mensal?: ");
				scanf("%i",&tempRenda);
				printf("Confirma alteracao?\n1 - Sim\n2 - Nao\n\nEscolha: ");
				scanf("%i",&resp3);
				if(resp3==1){
					usuario.rendaMensal = tempRenda;
					edita_arquivo(arquser, usuario);
				}
			}
			else{
				printf("Entrada invalida!\n\n");
			}
			
			printf("Alteracao realizada com sucesso! Por favor, reinicie o sistema para que as alteracoes sejam gravadas!\n\n");
		}
		else if(resp==3){
			printf("saindo");
		}
		else{
			printf("Entrada invalida");
		}
	} while(resp!=3);	
	free(arquser);
}

int menu_cliente(){
	int resp;
	printf("1 - Buscar imoveis\n2 - Propostas e alugueis\n3 - Ver perfil\n4 - Sair\n\nEscolha: ");
	scanf("%i", &resp);
	return resp;
}

int menu_corretor(){
	int resp;	
	printf("1 - Buscar imoveis\n2 - Cadastrar imoveis\n3 - Alterar imoveis\n4 - Propostas e alugueis\n5 - Ver perfil\n6 - Sair\n\nEscolha: ");
	scanf("%i", &resp);
	return resp;
}

int main(){
	setlocale(LC_ALL, "Portuguese");

	user usuario; //variável global que armazena o CPF na main
	strcpy(cpf_user, "");
	login();
	usuario = pesquisa_user(fclientes, cpf_user);
	int resp;
	
	if (strcmp(usuario.cpf,"-1")!=0){//identifica se o cpf está na database de clientes
		while(resp !=4){
			resp = menu_cliente();
			system("cls");
			switch(resp){
				case 1:
					menu_buscar_imoveis();
					break;
				case 2:
					menu_propostas_e_alugueis();
					break;
				case 3:
					ver_perfil();
					break;
				case 4:
					printf("Ate breve!");
					break;
				default:
					printf("entrada invalida");
					break;
			}
		}
	}
	else{
		usuario = pesquisa_user(fcorretores, cpf_user); 
		if(strcmp(usuario.cpf,"-1")!=0){ //identifica se o cpf está na database de corretores
			system("cls");
			while(resp !=5){
				resp = menu_corretor();
				
				switch(resp){
					case 1:
						menu_buscar_imoveis();
						break;
					case 2:
						imovel_cadastro_cria _infos(fimoveis);
						break;
					case 3:
						altera_imovel();
						break;
					case 4:
						menu_propostas_e_alugueis();
						break;

					case 5:
						ver_perfil();
						break;
					case 6:
						printf("Ate breve!");
						break;
					default:
						printf("entrada invalida");
						break;
				}
			}
		}
		else{
			printf("Usuario nao encontrado");
		}
	}
	return 0;
}
