#include "./headers/queries.h"

int querie_2(Cat_Produtos produtos) {

	Lista lista_produtos = init_Lista(1000);
	
	int estado = 1, input;
	char opcao[20];
	char letra;

	while(estado) {
		printf("\e[1;1H\e[2J");
		printf( "_____________________________________________\n" );
		printf( "\tListagem de Produtos - QUERIE 2\n\n" );
		printf( "  1 - Voltar\t\t0 - Sair:\n" );
		printf( "_____________________________________________\n" );
	
		printf("Diga a letra a procurar >> ");
	
		input = scanf("%s",opcao);
	
		switch(opcao[0]) {
			case '0': return 0; break;
			case '1': return 1; break;
			default : break;
		}
		
		if(isalpha(opcao[0])) {
			char letra = toupper(opcao[0]);
			lista_produtos = converte_Produtos(lista_produtos,produtos,letra);
			apresenta_Lista(lista_produtos);
		}
	}
	
	return 1;
}