#include "./headers/queries.h"


int querie_1(Cat_Produtos produtos,Cat_Clientes clientes,Faturacao faturas, int modo) {

	int input;
	char* f_clientes;
	char* f_produtos;
	char* f_vendas;
	FILE *file_clientes = NULL;
	FILE *file_produtos = NULL;
	FILE *file_vendas = NULL;

		if(modo == 1) {

			f_clientes = "./data/Clientes.txt";
            f_produtos = "./data/Produtos.txt";
            f_vendas = "./data/Vendas_1M.txt";
            
            file_clientes = fopen(f_clientes,"r");
            file_produtos = fopen(f_produtos,"r");
            file_vendas = fopen(f_vendas,"r");
			
			leitura_ficheiros(clientes,produtos,faturas,file_clientes,file_produtos,file_vendas,f_clientes,f_produtos,f_vendas);
			
		}
		else {
			while(file_clientes == NULL) {
				printf("\nIndique o nome do ficheiro de clientes >> ");
				input = scanf("%s",f_clientes);
				file_clientes = fopen(f_clientes,"r");
				if(file_clientes == NULL) printf("Ficheiro de Clientes Inválido\n");
			}
			while(file_produtos == NULL) {
				printf("\nIndique o nome do ficheiro de produtos >> ");
				input = scanf("%s",f_produtos);
				file_produtos = fopen(f_produtos,"r");
				if(file_produtos == NULL) printf("Ficheiro de Produtos Inválido\n");
			}
			while(file_vendas == NULL) {
				printf("\nIndique o nome do ficheiro de vendas >> ");
				input = scanf("%s",f_vendas);
				file_vendas = fopen(f_vendas,"r");
				if(file_vendas == NULL) printf("Ficheiro de Vendas Inválido\n");
			}
			leitura_ficheiros(clientes,produtos,faturas,file_clientes,file_produtos,file_vendas,f_clientes,f_produtos,f_vendas);
		}
	return 1;
}


int querie_2(Cat_Produtos produtos) {
	
	int estado = 1, input;
	char opcao[20];
	char letra;

	while(estado) {
	Conj_Produtos lista_produtos = init_Conjunto(1000);
		printf("\e[1;1H\e[2J");
		printf( "_____________________________________________\n" );
		printf( "\tListagem de Produtos - QUERIE 2\n\n" );
		printf( "  1 - Voltar\t\t0 - Sair:\n" );
		printf( "_____________________________________________\n" );
	
		printf("\nDiga a letra a procurar >> ");
	
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

	int estado = 1, input, filial;
	char opcao[10];
	char letra;
	
	while(estado) {
	Conj_Faturas nao_comprados = init_Lista_Faturacao(1000); 
		printf("\e[1;1H\e[2J");
		printf( "_____________________________________________\n" );
		printf( "   Produtos não comprados - QUERIE 4\n\n" );
		printf( "_____________________________________________\n" );
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
			nao_comprados = faturas_produtos_nao_comprados_totais(nao_comprados,faturas);
			apresenta_faturas(nao_comprados);
		}		
		else if(opcao[0] == '2') { 
			Conj_Faturas totais = init_Lista_Faturacao(1000);
			totais = cria_lista_total(totais,faturas);
			printf("\nInsira a filial que pretende >> ");
			input = scanf("%d",&filial);
		    nao_comprados = faturas_nao_comprado_filial(totais,nao_comprados,faturas,filial);
			apresenta_faturas(nao_comprados);
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


void apresenta_Lista(Lista list) {
    int i;
    int input;
    int estado = 1;
    int nr_de_elementos = lista_getPos(list);

    if(nr_de_elementos == 0) estado = 0;
    
    int elementos_pagina = 20;
    
    
    int last_pagina = nr_de_elementos % elementos_pagina;
    
    int total_paginas = (last_pagina == 0) ? (nr_de_elementos / elementos_pagina) : ((nr_de_elementos / elementos_pagina) + 1); 

    int nr_pagina = 1;

    while(estado) {

        printf("\e[1;1H\e[2J");
        printf("\n");
        printf("Número total de elementos: %d\n\n",nr_de_elementos);
        printf(" --- Página número |%d| de |%d| ---\n", nr_pagina,total_paginas);
        

        for(i = (nr_pagina-1) * elementos_pagina; i < (nr_pagina * elementos_pagina) && i < nr_de_elementos; i++) {
            printf("\t%d\t%s\n",i+1,lista_getNome(list,i));
        }

        putchar('\n');
        printf(" 1 - [<<]  2 - [<]  3 - [>]  4 - [>>]   0 - Voltar\n");
        putchar('\n');
        printf("Opcao numero > ");
        input = scanf("%d",&estado);

        switch(estado) {
            case 0: break;
            case 1: nr_pagina = 1;

            case 2: if(nr_pagina > 1) nr_pagina --;
                   break;
            case 3: if(nr_pagina < total_paginas) nr_pagina++;
                   break;
            case 4: nr_pagina = total_paginas;
            default:printf("Opção não valida\n"); 
                    break;
        }

    }
}