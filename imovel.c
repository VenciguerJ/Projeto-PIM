#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <windows.h>

#define fimoveis "imoveis.txt"
#define fclientes "clientes.txt"
#define fcorretores "corretores.txt"

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

void imprimir_dados(imovel a){
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
    printf("Possui piscina: %s\n", a.tempiscina);
    printf("Possui churrasqueira: %s\n", a.temchurrasqueia);
    printf("Valor do imovel: %f\n", a.valor);
}

void removerIMOVEL(char *arquivo, int nroimovel, int cep){
    imovel tmp;
    FILE* arq = fopen(arquivo,"r");
    FILE* arqNovo = fopen("novo.txt","w"); 
    while(!feof(arq)){
	    fscanf(arq,"%i %s %s %s %s %s %i %i %i %i %i %i %f\n", &tmp.nroimovel, tmp.endereco[101], tmp.bairro[101], tmp.cidade[101], temp.estado[2], tmp.cep[9], &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, tmp.tempiscina, tmp.temchurrasqueia, %tmp.valor);
        if (tmp.nroimovel!=nroimovel && tmp.cep != cep){
            fprintf(arq,"%i %s %s %s %s %s %i %i %i %i %i %i %f\n", &tmp.nroimovel, tmp.endereco[101], tmp.bairro[101], tmp.cidade[101], temp.estado[2], tmp.cep[9], &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, tmp.tempiscina, tmp.temchurrasqueia, %tmp.valor);
        }
    }
    fclose(arq); 
    fclose(arqNovo); 
    system("del imoveis.txt");
    system("rename novoemp.txt imoveis.txt");
}


imovel pesquisaIMOVEL(char *arquivo, int nroimovel, int cep){

	FILE *arq = fopen(arquivo, "r");
	imovel tmp;
	
	while(!feof(arq)){
		fscanf(arq,"%i %s %s %s %s %s %i %i %i %i %i %i %f\n", &tmp.nroimovel, tmp.endereco[101], tmp.bairro[101], tmp.cidade[101], temp.estado[2], tmp.cep[9], &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, tmp.tempiscina, tmp.temchurrasqueia, %tmp.valor);
		if(cep == tmp.cep && nroimovel == tmp.nroimovel){
			break;
		}
		else{
			tmp.cpf = -1;
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
        fscanf(arq,"%i %s %s %s %s %s %i %i %i %i %i %i %f\n", &tmp.nroimovel, tmp.endereco[101], tmp.bairro[101], tmp.cidade[101], temp.estado[2], tmp.cep[9], &tmp.metragemtotal, &tmp.metragemconstruido, &tmp.numerodequartos, &tmp.numerodesiutes, &tmp.numerodesalas, &tmp.numerodebanheiros, tmp.tempiscina, tmp.temchurrasqueia, %tmp.valor);
        c++;
    }
    fclose(arq);
    return c;
}

void imovel_cadastro_criaInfos(char *arquivo){
    int i=0;
    imovel tmp, pesq;
    FILE *arq = fopen(arquivo, "a+");
    tmp.nroimovel = qtd_imoveis(arquivo) + 1;
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
        if strlen(tmp.cep) != 8{
            printf("Ops... acho que deu algo errado, vamos tentar novamente.\n\n");
            i = 1
        }
    }while (i>0)
    getchar(); 
    printf("Metragem do terreno total: ");
    scanf("%i", &tmp.metragemtotal);    
    getchar(); 
    printf("Metragem da area contruida total: ");
    scanf("%i", &tmp.metragemconstruido); 
    getchar(); 
    printf("Numeros de quartos na casa: ");
    scanf("%i", &tmp.numerodequartos); 
    getchar(); 
    printf("Numeros de suites na casa: ");
    scanf("%i", &tmp.numerodesiutes); 
    getchar(); 
    printf("Numeros de salas na casa: ");
    scanf("%i", &tmp.numerodesalas); 
    getchar(); 
    printf("Numeros de banheiros na casa: ");
    scanf("%i", &tmp.numerodesalas); 
    getchar(); 
    printf("Tem piscina na casa, informa S para SIM e N para NAO [S/N]: ");
    scanf("%i", &tmp.tempiscina); 
    getchar(); 
    printf("Tem churrasqueira na casa, informa S para SIM e N para NAO [S/N]: ");
    scanf("%i", &tmp.temchurrasqueia); 
    getchar(); 
    printf("Informe o valor do preco do imovel para venda, casas decimais devem ser informas com ponto da seguinte forma R$ 200300.33: ");
    scanf("%i", &tmp.valor);
    printf("O cadastro do imovel foi feito com sucesso, a identificacao dele e %i em nosso sistema, guarde a informacao", &tmp.nroimovel);
}

void consultaIMOVEL(char *arquivo){
    imovel consulta;
    int nroimovel,cep;
    printf("Consulta de imoveis \n\n");
    printf("Informe o codigo de identificacao do imovel: ");
    scanf("%i", &nroimovel);
    getchar();
    printf("Informe o CEP do imovel: ");
    scanf("%i", &cep);
    consulta = pesquisar(arquivo, nroimovel, cep);
    if(pesq.matricula!=-1)
    {
    printf("\n\n");
    imprimir_dados(consulta);
    }
    else
    {
    printf("Imovel nao encontrado!\n\n");
    }
}
