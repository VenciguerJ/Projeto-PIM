#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>

#define fimoveis "imoveis.txt"
#define fclientes "clientes.txt"
#define fcorretores "corretores.txt"

typedef struct{
	char nome[101];
	int idade;
	char cpf[12]; // CPF está sendo uma string pois a quantidade de digitos não consegue ser armazenada em uma única int
	char password[11];
	char nrocllr[15];
	char email[101]; 
} user;

typedef struct{
    int nroimovel;
	char endereco[101];
    char bairro[101];
    char cidade[101];
    char estado[2];
    char cep[8];
	int metragemtotal;
	int metragemconstruido;
	int numerodequartos;
    int numerodesiutes;
    int numerodesalas;
    int numerodebanheiros;
    char tempiscina;
    char temchurrasqueia;
    float valor; 
} imovel;

char cpf_user[12]; //cpf do usuario logado

//começa funções de imoveis
void imprimir_dados(imovel a){ //dados completos do imovel
    printf("Identificacao Imovel: %i\n", a.nroimovel);
    printf("Endereco: %s\n", a.endereco);
    printf("Bairro: %s\n", a.bairro);
    printf("Cidade: %s\n", a.cidade);
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
    printf("Valor do imovel: %f\n", a.valor);
}

void removerIMOVEL(char *arquivo, int numimovel, char *cep2){
    imovel tmp;
    FILE* arq = fopen(arquivo,"r");
    FILE* arqNovo = fopen("novo.txt","w"); 
    while(!feof(arq)){
	    fscanf(arq,"%i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n", &tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, &tmp.tempiscina, &tmp.temchurrasqueia, &tmp.valor);
        if (tmp.nroimovel!=numimovel && strcmp(tmp.cep, cep2)!=0){
            fprintf(arq,"%i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n", tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, tmp.metragemtotal, tmp.metragemconstruido, tmp.numerodequartos, tmp.numerodesiutes, tmp.numerodesalas, tmp.numerodebanheiros, tmp.tempiscina, tmp.temchurrasqueia, tmp.valor);
        }
    }
    fclose(arq); 
    fclose(arqNovo); 
    system("del imoveis.txt");
    system("rename novoemp.txt imoveis.txt");
}

imovel pesquisaIMOVEL(char *arquivo, int numimovel, char *cep2){

	FILE *arq = fopen(arquivo, "r");
	imovel tmp;
	
	while(!feof(arq)){
		fscanf(arq,"%i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n", &tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, &tmp.tempiscina, &tmp.temchurrasqueia, &tmp.valor);
		if(strcmp(cep2, tmp.cep)==0 && numimovel == tmp.nroimovel){
			break;
		}
		else{
			tmp.nroimovel = -1;
		}
	}
	fclose(arq);
	return tmp;
}

int qtd_imoveis(char *arquivo){

    FILE *arq = fopen(arquivo, "r");
    imovel tmp;
    int c = 0;
    while (!feof(arq)){
        fscanf(arq, "%i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n", &tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, &tmp.tempiscina, &tmp.temchurrasqueia, &tmp.valor);
        c++; 
    }
    fclose(arq);
    return c;
}

void imovel_cadastro_criaInfos(char *arquivo){
    int i=0;
    imovel tmp;
    FILE *arq = fopen(arquivo, "a+");
    tmp.nroimovel = qtd_imoveis(arquivo);
	tmp.nroimovel += 1;


    printf("Vamos iniciar o cadastro de um novo imovel, coloque as inforacoes a seguir\n\n");
    printf("Endereco: ");
    scanf("%s", tmp.endereco);
    getchar(); 
    printf("Bairro: ");
    scanf("%s", tmp.bairro);
    getchar(); 
    printf("Cidade: ");
    scanf("%s", tmp.cidade);
    getchar(); 
    printf("Estado: ");
    scanf("%s", tmp.estado);
    getchar(); 
    do{    
        printf("Informe o CEP com 8 digitos no seguinte formar 13214774 (sem o traco): ");
        scanf("%s", tmp.cep);
        if(strlen(tmp.cep) != 8){
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
	printf("Tem piscina na casa, informa S para SIM e N para NAO [S/N]: ");
	scanf("%c", &tmp.tempiscina); 
	printf("Tem churrasqueira na casa, informa S para SIM e N para NAO [S/N]: ");
	scanf("%c", &tmp.temchurrasqueia); 
	printf("Informe o valor do preco do imovel para venda, casas decimais devem ser informas com ponto da seguinte forma R$ 200300.33: ");
	scanf("%f", &tmp.valor);
	
	while (!feof(arq)){
	fprintf(arq,"%i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n", tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, tmp.metragemtotal, tmp.metragemconstruido, tmp.numerodequartos, tmp.numerodesiutes, tmp.numerodesalas, tmp.numerodebanheiros, tmp.tempiscina, tmp.temchurrasqueia, tmp.valor);
	}

	printf("O cadastro do imovel foi feito com sucesso, a identificacao dele e '%i' em nosso sistema, guarde a informacao", tmp.nroimovel);
	
}

void consultaIMOVEL(char *arquivo){
    imovel consulta;
    int nroimovel;
	char cep[8];
    printf("Consulta de imoveis \n\n");
    printf("Informe o codigo de identificacao do imovel: ");
    scanf("%i", &nroimovel);
    getchar();
    printf("Informe o CEP do imovel: ");
    scanf("%s", cep);
    consulta = pesquisaIMOVEL(arquivo, nroimovel, cep);
    if(consulta.nroimovel!=-1)
    {
    printf("\n\n");
    imprimir_dados(consulta);
    }
    else
    {
    printf("Imovel nao encontrado!\n\n");
    }
}

void menu_buscar_imoveis(){
	printf("IMOVEIS");
	
	int c;
	imovel tmp, menu[999];
	FILE *arq = fopen(fimoveis, "r");
	
	for(c=1;!feof(arq);c++){
		c=1;
		fscanf(arq, "%i %s %s %s %s %s %i %i %i %i %i %i %c %c %f \n", &tmp.nroimovel, tmp.endereco, tmp.bairro, tmp.cidade, tmp.estado, tmp.cep, &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, &tmp.tempiscina, &tmp.temchurrasqueia, &tmp.valor);
		
	}

	printf("Imovel [%s] [%s] [%i] \n[%s]", tmp.estado, tmp.cidade, tmp.endereco, tmp.metragemtotal);

	

}
//Termina imoveis e começa funnções úteis
void TirarEspaco(char *texto){ // usado para recolocar o espaço na hora de demonstrar o programa ao usuario 

    int i;
    for (i=0;i<strlen(texto);i++){
		if (texto[i]==' '){
			texto[i]='+';
		}
		
	}
}

void ColocarEspaco(char *texto){ //função usada para adicionar um sinal do arquivo texto para não dar erros de leitura
    int i;
    for (i=0;i<strlen(texto);i++){
		if (texto[i]=='+'){
			texto[i]=' ';	
		}
	}
}
//termina funções úteis e começa o login
void atualiza_dado(char *var, char *novoValor){ // atualiza o CPF para ser usado na MAIN
	strcpy(var, novoValor);
}

user pesquisaUser(char *arquivo, char *cpf){ // pesquisa os dados do usuario XXX

	FILE *arq = fopen(arquivo, "r");
	user tmp;
	
	while(!feof(arq)){
		fscanf(arq, "%s %i %s %s\n", tmp.nome, &tmp.idade, tmp.cpf, tmp.password);
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

char *pesquisaArquivo(char *cpf){ //vê qual é o arquivo que está o cpf
	user tmp;
    char *arqcorreto = NULL;

    tmp = pesquisaUser(fclientes, cpf);
    if (strcmp(tmp.cpf, "-1") != 0) {
        arqcorreto = (char *)malloc(strlen(fclientes) + 1); // Aloca memória para arqcorreto
        strcpy(arqcorreto, fclientes);
    } else {
        tmp = pesquisaUser(fcorretores, cpf);
        if (strcmp(tmp.cpf, "-1") != 0) {
            arqcorreto = (char *)malloc(strlen(fcorretores) + 1); // Aloca memória para arqcorreto
            strcpy(arqcorreto, fcorretores);
        }
    }
    return arqcorreto;
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
	getchar();
	fgets(tmp.nome, sizeof(tmp.nome), stdin);
    size_t tamanho = strlen(tmp.nome);
    if (tamanho > 0 && tmp.nome[tamanho - 1] == '\n'){
        tmp.nome[tamanho - 1] = '\0';
    }
	TirarEspaco(tmp.nome);

	printf("Digite sua idade: ");
	scanf("%i", &tmp.idade);
	
	printf("digite seu numero de celular (com ddd)");
	scanf("%s", tmp.nrocllr);
	
	printf("DIgite seu E-mail: ");
	scanf("%s", tmp.email);
	
	printf("Digite seu CPF (apenas numeros): ");
	scanf("%s", tmp.cpf);

	podeusarcpf = verificaCPF(tmp.cpf);

	if(podeusarcpf == 0){
		do {
			iguais = 1;
			do{
				printf("Crie uma senha (ela deve ter no maximo 10 caracteres): ");
				scanf("%s", tmp.password);
				getchar();
				if(strlen(tmp.password)>10){
					printf("senha muito longa\n");
				} 
			}while (strlen(tmp.password)>10);
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
			fprintf(arq, "%s %i %s %s %s %s\n", tmp.nome, tmp.idade, tmp.cpf, tmp.password, tmp.nrocllr, tmp.email);
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
//termina login e começa os menus
void edita_arquivo(char *arquivo, user usuario){ //arquivo a ser editado e cpf a sofrer a alteração
	user tmp; // usuario temporário
	FILE *arq = fopen(arquivo, "r");
	FILE *tmparq = fopen("temp.txt", "a+");

	while(!feof(arq)){
		fscanf(arq, "%s %i %s %s %s %s\n", tmp.nome, &tmp.idade, tmp.cpf, tmp.password, tmp.email, tmp.nrocllr);
		if(strlen(usuario.cpf)!=strlen(tmp.cpf)&&strcmp(usuario.cpf, tmp.cpf)!=0){
			fprintf(tmparq, "%s %i %s %s %s %s\n", tmp.nome, tmp.idade, tmp.cpf, tmp.password, tmp.nrocllr, tmp.email);
		}
	}
	fprintf(tmparq, "%s %i %s %s %s %s\n", tmp.nome, tmp.idade, tmp.cpf, tmp.password, tmp.nrocllr, tmp.email);

	fclose(arq);
	fclose(tmparq);
	remove(arquivo);
	rename("temp.txt", arquivo);
}

void remove_do_arquivo(char *arquivo, user usuario){ //tira o cpf do arquivo
	user tmp;
	FILE *arq = fopen(arquivo, "r");
	FILE *tmparq = fopen("temp.txt", "a+");
	
	fscanf(arq, "%s %i %s %s %s %s\n", tmp.nome, &tmp.idade, tmp.cpf, tmp.password, tmp.nrocllr, tmp.email);
	if(strlen(usuario.cpf)!=strlen(tmp.cpf)&&strcmp(usuario.cpf, tmp.cpf)!=0){
		fprintf(tmparq, "%s %i %s %s %s %s\n", tmp.nome, tmp.idade, tmp.cpf, tmp.password, tmp.nrocllr, tmp.email);
	} 
	fclose(arq);
	fclose(tmparq);
	remove(arquivo);
	rename("temp.txt", arquivo);
}

void ver_perfil(){ // módulo do perfilXXX

	int resp=0, resp2, resp3;
	char *arquser;
	arquser = pesquisaArquivo(cpf_user);
	user usuario = pesquisaUser(arquser, cpf_user);
	printf("Perfil do usuario: \n");
	
	ColocarEspaco(usuario.nome);
	printf("Nome: %s \n", usuario.nome);
	printf("Idade: %i \n", usuario.idade);
	printf("CPF: %s \n \n", usuario.cpf);
	printf("E-mail %s\n", usuario.email);
	printf("Numero de Cel: %s\n", usuario.nrocllr);
	
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
			printf("EDIÇÃO DE USUARIO\n\n1 - Nome\n2 - Idade\n3 - CPF\n4 - Senha\n5 - E-mail\n6 - Celular\n\nEscolha: ");
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
				TirarEspaco(tempname);
				if(strlen(usuario.nome)==strlen(tempname)&&strcmp(usuario.nome, tempname)==0){
					printf("Nomes iguais!");
				}
				else{
					// termina de perguntar dados e começa a tratar os dados
					printf("Confirma alteração?\n1 - Sim\n2 - Nao\n\nEscolha: ");
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
				printf("Confirma alteração?\n1 - Sim\n2 - Nao\n\nEscolha: ");
				scanf("%i",&resp3);
				if(resp3==1){
					strcpy(usuario.cpf,tempcpf);
					atualiza_dado(cpf_user,usuario.cpf);
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
				printf("Confirma alteração?\n1 - Sim\n2 - Nao\n\nEscolha: ");
				scanf("%i",&resp3);
				if(resp3==1){
					strcpy(usuario.nrocllr,tempcell);
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
	printf("1 - Buscar imoveis\n2 - Cadastrar imoveis\n3 - Propostas e alugueis\n4 - Ver perfil\n5 - Sair\n\nEscolha: ");
	scanf("%i", &resp);
	return resp;
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	user usuario; //variável global que armazena o CPF na main
	strcpy(cpf_user, "");
	login();

	usuario = pesquisaUser(fclientes, cpf_user);

	int resp;
	
	if (strcmp(usuario.cpf,"-1")!=0){//identifica se o cpf está na database de clientes
		while(resp !=4){
			resp = menu_cliente();
			
			switch(resp){
				case 1:
					printf("buscar imoveis");
					break;
				case 2:
					printf("Propostas e alugueis");
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
		usuario = pesquisaUser(fcorretores, cpf_user); 
		if(strcmp(usuario.cpf,"-1")!=0){ //identifica se o cpf está na database de corretores
			
			while(resp !=5){
				resp = menu_corretor();
				
				switch(resp){
					case 1:
						printf("buscar imoveis");
						break;
					case 2:
						imovel_cadastro_criaInfos(fimoveis);
						break;
					case 3:
						printf("Propostas e alugueis");
						break;
					case 4:
						ver_perfil();
						break;
					case 5:
						printf("Até breve!");
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
