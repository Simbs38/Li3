#include "./headers/queries.h"

int querie_2(Cat_Produtos produtos) {

	Conj_Produtos lista_produtos = init_Conjunto(1000);
	
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
			
			apresenta_Produtos(lista_produtos);
		}
	}
	
	return 1;
}

int querie_3(Faturacao faturas) {
	
	int estado = 1, input;
	char produto[20];
	char opcao[10];
	int mes;
	char letra;
	
	while(estado) {
		int voltar = 1;
		printf("\e[1;1H\e[2J");
		printf( "_____________________________________________\n" );
		printf( "   Vendas e Faturacao dado mês - QUERIE 3\n\n" );
		printf( "  13 - Voltar\t\t0 - Sair:\n" );
		printf( "_____________________________________________\n" );
	
		printf("Diga o mês a procurar >> ");
		input = scanf("%d",&mes);
	
		switch(mes) {
			case 0: return 0; break;
			case 13: return estado; break;
			default : break;
		}
		printf("\nDiga o produto a procurar >> ");
		input = scanf("%s",produto);

		printf("\nPretende valor T (Total) ou F (Filiais) >> ");
		input = scanf("%s",opcao);
		
		while(voltar) {
			
			if(opcao[0] == 'T') {
				int total_quant_mes_normal = get_total_quantidades_mes_produto(faturas,produto,mes,'N');
				int total_quant_mes_promo = get_total_quantidades_mes_produto(faturas,produto,mes,'P');
				double total_preco_mes_normal = get_total_precos_mes_produto(faturas,produto,mes,'N');
				double total_preco_mes_promo = get_total_precos_mes_produto(faturas,produto,mes,'P');
				printf("\e[1;1H\e[2J");
				printf( "    Vendas no mês %d do produto %s\n",mes,produto);
				printf( "_____________________________________________\n" );
				printf( "     Vendas\t\t   Faturação\n");
				printf( "_____________________________________________\n" );
				printf(" Normal\tPromoção\tNormal\tPromoção\n");
				printf(" %5d\t%5d\t\t%7.2f\t%7.2f\n",total_quant_mes_normal,total_quant_mes_promo,total_preco_mes_normal,total_preco_mes_promo);
				printf( "_____________________________________________\n" );
				printf( "  1 - Voltar\t\t0 - Sair:\n" );
				printf("Escolha uma opção >> ");
				input = scanf("%s",opcao);
				switch(opcao[0]) {
					case '1': voltar = 0; break;
					case '0': return 0; break;
					default: break;
				}	
			}

			if(opcao[0] == 'F') {
				int total_quant_mes_normal_1 = get_total_quantidades_mes_produto_filial(faturas,produto,mes,'N',1);
				int total_quant_mes_normal_2 = get_total_quantidades_mes_produto_filial(faturas,produto,mes,'N',2);
				int total_quant_mes_normal_3 = get_total_quantidades_mes_produto_filial(faturas,produto,mes,'N',3);

				int total_quant_mes_promo_1 = get_total_quantidades_mes_produto_filial(faturas,produto,mes,'P',1);
				int total_quant_mes_promo_2 = get_total_quantidades_mes_produto_filial(faturas,produto,mes,'P',2);
				int total_quant_mes_promo_3 = get_total_quantidades_mes_produto_filial(faturas,produto,mes,'P',3);
				
				double total_preco_mes_normal_1 = get_total_precos_mes_produto_filial(faturas,produto,mes,'N',1);
				double total_preco_mes_normal_2 = get_total_precos_mes_produto_filial(faturas,produto,mes,'N',2);
				double total_preco_mes_normal_3 = get_total_precos_mes_produto_filial(faturas,produto,mes,'N',3);
				
				double total_preco_mes_promo_1 = get_total_precos_mes_produto_filial(faturas,produto,mes,'P',1);
				double total_preco_mes_promo_2 = get_total_precos_mes_produto_filial(faturas,produto,mes,'P',2);
				double total_preco_mes_promo_3 = get_total_precos_mes_produto_filial(faturas,produto,mes,'P',3);
				
				printf("\e[1;1H\e[2J");
				printf( "\tVendas no mês %d do produto %s\n",mes,produto);
				printf( "______________________________________________________\n" );
				printf( "\t\tVendas\t\t   Faturação\n");
				printf( "______________________________________________________\n" );
				printf("\t  Normal  Promoção\tNormal    Promoção\n");
				printf("Filial 1 %5d \t%5d \t\t%7.2f\t  %7.2f\n",total_quant_mes_normal_1,total_quant_mes_promo_1,total_preco_mes_normal_1,total_preco_mes_promo_1);
				printf("Filial 2 %5d \t%5d \t\t%7.2f\t  %7.2f\n",total_quant_mes_normal_2,total_quant_mes_promo_2,total_preco_mes_normal_2,total_preco_mes_promo_2);
				printf("Filial 3 %5d \t%5d \t\t%7.2f\t  %7.2f\n",total_quant_mes_normal_3,total_quant_mes_promo_3,total_preco_mes_normal_3,total_preco_mes_promo_3);
				printf( "______________________________________________________\n" );
				printf( "  1 - Voltar\t\t0 - Sair:\n" );
				printf("Escolha uma opção >> ");
				input = scanf("%s",opcao);
				switch(opcao[0]) {
					case '1': voltar = 0; break;
					case '0': return 0; break;
					default: break;
				}	
			}

		}

	}
	
	return estado;
}


int querie_4(Faturacao faturas) {

	int estado = 1, input;
	char opcao[10];
	char letra;
	Conj_Faturas nao_comprados; 
	
	while(estado) {
		
		printf("\e[1;1H\e[2J");
		printf( "_____________________________________________\n" );
		printf( "   Produtos não comprados - QUERIE 4\n\n" );
		printf(" Escolha uma das seguintes opções:\n\n");
		printf("  1. Valores Totais\n");
		printf("  2. Valores por filiais\n");
		printf("_____________________________________________\n" );
		printf( "  3 - Voltar\t\t0 - Sair:\n" );
		printf( "_____________________________________________\n" );

		printf("\nEscolha uma opção >> ");
		input = scanf("%s",opcao);
		switch(opcao[0]) {
			case '0': return 0; break;

			case '3': return estado; break;

			default: break;
		}
		if(opcao[0] == '1') { 
			nao_comprados = init_Lista_Faturacao(1000);
	        nao_comprados = faturas_produtos_nao_comprados_totais(nao_comprados,faturas);
			apresenta_faturas(nao_comprados);
		}		
		else if(opcao[0] == '2') { 
			nao_comprados = init_Lista_Faturacao(1000);
			printf("\nInsira a filial que pretende >> ");
			input = scanf("%s",opcao);
			
		}
	}
	return estado;
}

int querie_6(Faturacao faturas) {


	int estado = 1, input, mes1 = 50, mes2 = 50;
	int voltar = 1;
	double total_faturado_intervalo;
	int total_vendas_intervalo;
	char opcao[10];
	
	while(estado) {
		
		printf("\e[1;1H\e[2J");
		printf( "_____________________________________________\n" );
		printf( " Valores totais num intervalo - QUERIE 6\n\n" );
		printf( "  13 - Voltar\t\t0 - Sair:\n" );
		printf( "_____________________________________________\n" );

		printf("\nInsira o primeiro mês do intervalo >> ");
		input = scanf("%d",&mes1);
		while(mes1 < 1 || mes1 > 12) {
		
			if(mes1 == 0) return 0;
			if(mes1 == 13) return estado;
			if(mes1 < 1 && mes1 > 12) { 
				printf("Mês inserido invalido\n");
				printf("\nInsira o primeiro mês do intervalo >> ");
			}
		}

		printf("\nInsira o segundo mês do intervalo >> ");

		while(mes2 < 1 || mes2 > 12) {
		
			input = scanf("%d",&mes2);
			if(mes2 == 0) return 0;
			if(mes2 == 13) return estado;
			if(mes2 < 1 && mes2 > 12) { 
				printf("Mês inserido invalido\n");
				printf("\nInsira o segundo mês do intervalo >> ");
			}
		}

		total_faturado_intervalo = get_total_faturado_intervalo(faturas,mes1,mes2);
		total_vendas_intervalo = get_total_quantidades_intervalo(faturas,mes1,mes2);

		while(voltar) {
			printf("\e[1;1H\e[2J");
			printf( "_____________________________________________\n" );
			printf( "\n  Total de vendas entre mês %d e o mês %d\n",mes1,mes2);
			printf( "_____________________________________________\n" );
			printf( "\tVendas\t\tFaturação\n");
			printf("\t%7d\t%7.2f\n",total_vendas_intervalo,total_faturado_intervalo);
			printf( "_____________________________________________\n" );
			printf( "  1 - Voltar\t\t0 - Sair:\n" );
			printf( "_____________________________________________\n" );
			
			
			printf("Escolha uma opção >> ");
			
			input = scanf("%s",opcao);
			
			switch(opcao[0]) {
				case '1': voltar = 0; break;
				case '0': return 0; break;
				default: break;
				}	
		}

	}
	return estado;
}