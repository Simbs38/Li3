#include "./headers/interpretador.h"

#define MENU_PRINCIPAL 1
#define SAIR_PROGRAMA 0
#define REFAZER_DADOS 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int menu_leitura(Cat_Produtos produtos, Cat_Clientes clientes,Faturacao faturas,Filial filiais[]);
static int menu_catalogo(Cat_Produtos produtos);
static int menu_faturacao(Faturacao faturas);
static int menu_filiais(Filial filiais[]);


int menu_principal(Cat_Produtos produtos, Cat_Clientes clientes, Faturacao faturas, Filial filiais[3], int estado) {

	int input = 0;
	char opcao[20];
	/*	
	if(estado == REFAZER_DADOS) {
		estado = menu_leitura(produtos,clientes,faturas);
	}
*/
	while(estado) {
		system("clear");
		printf( "_____________________________________________\n" );
		printf( "\n\t\tMENU PRINCIPAL\n\n" );
		printf( "---------------------------------------------\n" );
		printf(" Escolha uma das seguintes opções:\n\n" );
		printf("  1. Leitura de Ficheiros\n");
		printf("  2. Catálogo de Produtos\n");
		printf("  3. Faturação\n");
		printf("  4. Filiais\n");
		printf( "---------------------------------------------\n" );
		printf( "\t\t\t\tQ - Sair\n" );
		printf( "_____________________________________________\n" );
		
		printf("\nEscolha uma opção >> ");
		
		input = scanf("%s",opcao);
		
		switch(opcao[0]) {
			
			case 'Q': estado = SAIR_PROGRAMA; break;
			
			case '1': estado = menu_leitura(produtos,clientes,faturas,filiais); break;
			/*if(!total_Produtos(produtos)) {
					  	estado = menu_leitura(produtos,clientes,faturas); break;
					  }
					  else {
					  	printf("Esta acção irá refazer os dados em memória, prima Q para cancelar >> ");
					  	input = scanf("%s",opcao);
					  	if(opcao[0] == 'Q') break;
					  	else {
					  		estado = REFAZER_DADOS;
					  		return estado;
					  	}
					  }*/
			case '2': if(total_Produtos(produtos)) estado = menu_catalogo(produtos);
					  else  {
					  	system("clear");
					  	printf("\nAinda não foram lidos nenhuns dados!\n");
					  	printf("\nPrima qualquer tecla para voltar ao menu >> ");
						input = scanf("%s",opcao);			  	
					  }
					  break;
			case '3': if(total_Produtos(produtos)) estado = menu_faturacao(faturas);
					  else {
					  	system("clear");
					  	printf("\nAinda não foram lidos nenhuns dados!\n");
					  	printf("\nPrima qualquer tecla para voltar ao menu >> ");
					  	input = scanf("%s",opcao);
					  }
					  break;
					  
			case '4': if(total_Produtos(produtos)) estado = menu_filiais(filiais);
					  else {
					  	system("clear");
					  	printf("\nAinda não foram lidos nenhuns dados!\n");
					  	printf("\nPrima qualquer tecla para voltar ao menu >> ");
					  	input = scanf("%s",opcao);
					  }
					  break;

			default: break;
		}
	}
	return estado;
}


static int menu_leitura(Cat_Produtos produtos, Cat_Clientes clientes,Faturacao faturas,Filial filiais[3]) {

	int estado = 1, input = 0;
	char opcao[20];

	while(estado) {
	
		system("clear");
		printf("_____________________________________________\n");
		printf("\n\t\tMENU LEITURA\n\n");
		printf("---------------------------------------------\n");
		printf(" Escolha uma das seguintes opções:\n\n");
		printf("  1. Carregar ficheiros pré-definidos\n\n");
		printf("  2. Introduzir ficheiros\n\n");
		printf("---------------------------------------------\n");
		printf("  V - Voltar\t\t\tQ - Sair\n" );
		printf("_____________________________________________\n");
		
		printf("\nEscolha uma opção >> ");
		
		input = scanf("%s",opcao);
		
		switch(opcao[0]) {
			
			case 'Q': return SAIR_PROGRAMA; break;
			
			case '1': estado = querie_1(produtos,clientes,faturas,filiais,1);
					  return estado;
					  break;
			case '2': estado = querie_1(produtos,clientes,faturas,filiais,2);
					  return estado;
					  break;

			case 'V': return MENU_PRINCIPAL; break;

			default: break;
		}

	}
	return estado;
}


static int menu_catalogo(Cat_Produtos produtos) {

	int estado = 1, input = 0;
	char opcao[20];

	while(estado) {
	
		system("clear");
		printf("_____________________________________________\n");
		printf("\n\t\tMENU CATALOGOS\n\n");
		printf("---------------------------------------------\n");
		printf(" Escolha uma das seguintes opções:\n\n");
		printf("  1. Listagem de Produtos por letra\n\n");
		printf("---------------------------------------------\n");
		printf("  V - Voltar\t\t\tQ - Sair\n" );
		printf("_____________________________________________\n");
		
		printf("\nEscolha uma opção >> ");
		
		input = scanf("%s",opcao);
		
		switch(opcao[0]) {
			
			case 'Q': return SAIR_PROGRAMA; break;
			
			case '1': estado = querie_2(produtos);
					  return estado;
					  break;
			
			case 'V': return MENU_PRINCIPAL; break;

			default: break;
		}

	}
	return estado;
}



static int menu_faturacao(Faturacao faturas) {

	int estado = 1, input = 0;
	char opcao[20];

	while(estado) {
	
		system("clear");
		printf("_____________________________________________\n");
		printf("\n\t\tMENU FATURACAO\n\n");
		printf("---------------------------------------------\n");
		printf(" Escolha uma das seguintes opções:\n\n");
		printf("  1. Total de vendas/faturação dado um mês\n");
		printf("  2. Produtos não comprados\n");
		printf("  3. Vendas/faturação num intervalo de meses\n\n");
		printf("---------------------------------------------\n");
		printf("  V - Voltar\t\t\tQ - Sair\n");
		printf("_____________________________________________\n");
		
		printf("\nEscolha uma opção >> ");
		
		input = scanf("%s",opcao);
		
		switch(opcao[0]) {
			
			case 'Q': return SAIR_PROGRAMA; break;
			
			case '1': estado = querie_3(faturas);
					  return estado;
			          break;
			
			case '2': estado = querie_4(faturas);
					  return estado;
			          break;
			case '3': estado = querie_6(faturas);
					  return estado;
			          break;			
			case 'V': return MENU_PRINCIPAL; break;

			default: break;
		}
	}
	return estado;
}



static int menu_filiais(Filial filiais[3]) {
	int estado = 1;
	return estado;
}
