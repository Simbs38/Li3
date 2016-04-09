#include "./headers/interpretador.h"


void menu_principal(Cat_Produtos produtos, Cat_Clientes clientes, Faturacao faturas) {

	int estado = 1, input = 0;
	char opcao[20];
	printf("Prima c para continuar para o menu principal >> ");
	input = scanf("%s",opcao);
		
	while(estado) {
		printf("\e[1;1H\e[2J");
		printf( "_____________________________________________\n" );
		printf( "\t\tMENU PRINCIPAL\n\n" );
		printf( "---------------------------------------------\n" );
		printf(" Escolha uma das seguintes opções:\n\n" );
		printf("  1. Catalogo de Produtos\n");
		printf("  2. Faturação\n");
		printf("  3. Filiais\n");
		printf( "---------------------------------------------\n" );
		printf( "\t\t\t\t0 - Sair:\n" );
		printf( "_____________________________________________\n" );
		
		printf("Escolha uma opção >> ");
		
		int input = scanf("%s",opcao);
		
		switch(opcao[0]) {
			
			case '0': estado = 0; break;
			
			case '1': estado = menu_catalogo(produtos); break;
			
			case '2': estado = menu_faturacao(faturas); break;
		/*	
			case '3': estado = menu_filiais(); break; */
			
			default: break;
		}

	}
}


int menu_catalogo(Cat_Produtos produtos) {

	int estado = 1, input = 0;
	char opcao[20];

	while(estado) {
	
		printf("\e[1;1H\e[2J");
		printf( "_____________________________________________\n" );
		printf( "\t\tMENU CATALOGOS\n" );
		printf( "---------------------------------------------\n" );
		printf(" Escolha uma das seguintes opções:\n\n" );
		printf("  1. Listagem de Produtos por letra\n\n");
		printf( "---------------------------------------------\n" );
		printf( "  2 - Voltar\t\t0 - Sair:\n" );
		printf( "_____________________________________________\n" );
		
		printf("Escolha uma opção >> ");
		
		int input = scanf("%s",opcao);
		
		switch(opcao[0]) {
			
			case '0': return 0; break;
			
			case '1': estado = querie_2(produtos); break;
			
			case '2': return estado; break;

			default: break;
		}

	}
	return estado;
}



int menu_faturacao(Faturacao faturas) {

	int estado = 1, input = 0;
	char opcao[20];

	while(estado) {
	
		printf("\e[1;1H\e[2J");
		printf( "_____________________________________________\n" );
		printf( "\t\tMENU FATURACAO\n" );
		printf( "---------------------------------------------\n" );
		printf(" Escolha uma das seguintes opções:\n\n" );
		printf("  1. Total de vendas/faturação dado um mês\n");
		printf("  2. Produtos não comprados\n");
		printf("  3. Vendas/faturação num intervalo de meses\n");
		printf( "---------------------------------------------\n" );
		printf( "  4 - Voltar\t\t0 - Sair:\n" );
		printf( "_____________________________________________\n" );
		
		printf("Escolha uma opção >> ");
		
		int input = scanf("%s",opcao);
		
		switch(opcao[0]) {
			
			case '0': return 0; break;
		/*	
			case '1': estado = querie_2(produtos); break;
			
			case '2': return estado; break;
			*/
			case '4': return estado; break;

			default: break;
		}

	}
	return estado;
}