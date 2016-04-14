#include "./headers/queries.h"



int querie_1(Cat_Produtos produtos,Cat_Clientes clientes,Faturacao faturas,INFO_FILIAL info, int modo) {
	/*
	if(total_Produtos(produtos) && total_Clientes(clientes)) {
		remove_Catalogo_Produtos(produtos);
		remove_Catalogo_Clientes(clientes);
		free_Faturacao(faturas);
		Cat_Clientes clientes = init_cat_clientes();
    	Cat_Produtos produtos = init_cat_produtos();
    	Faturacao faturacao = init_Faturacao();
	}
	*/
	int input;
	char f_clientes[50];
	char f_produtos[50];
	char f_vendas[50];
	FILE *file_clientes = NULL;
	FILE *file_produtos = NULL;
	FILE *file_vendas = NULL;

		if(modo == 1) {

			strcpy(f_clientes,"./data/Clientes.txt");
            strcpy(f_produtos,"./data/Produtos.txt");
            strcpy(f_vendas,"./data/Vendas_1M.txt");
            
            file_clientes = fopen(f_clientes,"r");
            file_produtos = fopen(f_produtos,"r");
            file_vendas = fopen(f_vendas,"r");
			
			leitura_ficheiros(clientes,produtos,faturas,info,file_clientes,file_produtos,file_vendas,f_clientes,f_produtos,f_vendas);
			
		}
		else {
			system("clear");
			printf("_____________________________________________\n");
			printf("\n\t   Leitura de Ficheiros\n");
			printf("_____________________________________________\n");
			while(file_clientes == NULL) {
				printf("\nIndique o nome do ficheiro de clientes >> ");
				input = scanf("%s",f_clientes);
				file_clientes = fopen(f_clientes,"r");
				if(file_clientes == NULL) printf("\nFicheiro de Clientes Inválido\n");
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
	return 10;
}


int querie_2(Cat_Produtos produtos) {
	
	int estado = 1, input;
	char opcao[20];
	char letra;
	
	Conj_Produtos lista_produtos = init_Conjunto(1000);

	while(estado) {
		system("clear");
		printf( "_____________________________________________\n" );
		printf( "\tListagem de Produtos - QUERIE 2\n\n" );	
		printf("Diga a letra a procurar >> ");
	
		input = scanf("%s",opcao);
			
		if(isalpha(opcao[0])) {
			char letra = toupper(opcao[0]);
			lista_produtos = converte_Produtos(lista_produtos,produtos,letra);
			apresenta_Produtos(lista_produtos);
			return estado;
		}
	}
	return 1;
}


int querie_3(Faturacao faturas) {
	
	int estado = 1, input, voltar = 1;
	char produto[20];
	char opcao[10];
	char mese[10];
	int mes = 0;
	char letra;
	
	while(estado) {
		voltar = 1;
		system("clear");
		printf( "_____________________________________________\n" );
		printf( "   Vendas e Faturacao dado mês - QUERIE 3\n\n" );
		
		while(mes < 1 || mes > 12) {
		printf("Diga o mês a procurar >> ");
		input = scanf("%s",mese);
		mes = atoi(mese);
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
				system("clear");
				printf( "    Vendas no mês %d do produto %s\n",mes,produto);
				printf( "_____________________________________________\n" );
				printf( "     Vendas\t\t   Faturação\n");
				printf( "_____________________________________________\n" );
				printf(" Normal\tPromoção\tNormal\tPromoção\n");
				printf(" %5d\t%5d\t\t%7.2f\t%7.2f\n",total_quant_mes_normal,total_quant_mes_promo,total_preco_mes_normal,total_preco_mes_promo);
				printf( "_____________________________________________\n" );
				printf( "  V - Voltar\t\tQ - Sair:\n" );
				printf("\nEscolha uma opção >> ");
				
				input = scanf("%s",opcao);
				
				switch(opcao[0]) {
					case 'V': return estado; break;
					
					case 'Q': return 0; break;
					
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
				
				system("clear");
				printf( "\tVendas no mês %d do produto %s\n",mes,produto);
				printf( "______________________________________________________\n" );
				printf( "\t\tVendas\t\t   Faturação\n");
				printf( "______________________________________________________\n" );
				printf("\t  Normal  Promoção\tNormal    Promoção\n");
				printf("Filial 1 %5d \t%5d \t\t%7.2f\t  %7.2f\n",total_quant_mes_normal_1,total_quant_mes_promo_1,total_preco_mes_normal_1,total_preco_mes_promo_1);
				printf("Filial 2 %5d \t%5d \t\t%7.2f\t  %7.2f\n",total_quant_mes_normal_2,total_quant_mes_promo_2,total_preco_mes_normal_2,total_preco_mes_promo_2);
				printf("Filial 3 %5d \t%5d \t\t%7.2f\t  %7.2f\n",total_quant_mes_normal_3,total_quant_mes_promo_3,total_preco_mes_normal_3,total_preco_mes_promo_3);
				printf( "______________________________________________________\n" );
				printf( "  V - Voltar\t\tQ - Sair:\n" );
				
				printf("Escolha uma opção >> ");
				
				input = scanf("%s",opcao);
				
				switch(opcao[0]) {
					case 'V': return estado; break;
					
					case 'Q': return 0; break;
					
					default: break;
				}	
			}
		}
	}

	return estado;
}


int querie_4(Faturacao faturas) {

	int estado = 1, input, filial = 0;
	char opcao[10];
	char fil[10];

	while(estado) {
	Conj_Faturas nao_comprados = init_Lista_Faturacao(1000); 
		system("clear");
		printf( "_____________________________________________\n" );
		printf( "   Produtos não comprados - QUERIE 4\n\n" );
		printf( "_____________________________________________\n" );
		printf(" Escolha uma das seguintes opções:\n\n");
		printf("  1. Valores Totais\n");
		printf("  2. Valores por filiais\n");
		printf("_____________________________________________\n" );
		printf( "  V - Voltar\t\tQ - Sair:\n" );
		printf( "_____________________________________________\n" );

		printf("\nEscolha uma opção >> ");
		input = scanf("%s",opcao);
		
		switch(opcao[0]) {
			case 'Q': return 0; break;

			case 'V': return estado; break;

			default: break;
		}

		if(opcao[0] == '1') { 
			nao_comprados = faturas_produtos_nao_comprados_totais(nao_comprados,faturas);
			apresenta_faturas(nao_comprados);
			return estado;
		}		
		else if(opcao[0] == '2') { 
			
			Conj_Faturas totais = init_Lista_Faturacao(1000);
			totais = cria_lista_total(totais,faturas);
			
			while(filial < 1 || filial > 3) {
				printf("\nInsira a filial que pretende >> ");
				input = scanf("%s",fil);
				filial = atoi(fil);
			}

			nao_comprados = faturas_nao_comprado_filial(totais,nao_comprados,faturas,filial);
			apresenta_faturas(nao_comprados);
			return estado;
		}
	}
	return estado;
}
int querie_5(INFO_FILIAL info){


	/*Conj_Filiais lista_filiais = init_ConjuntoF(1000); */
	int estado = 1, input, filial = 0,i,j;
	char cliente[10];
	int resultado[12][3];
	system("clear");
		printf( "_____________________________________________\n" );
		printf( "   Produtos comprados - QUERIE 5\n\n" );
		printf( "_____________________________________________\n\n" );
		printf("  Insira o codigo do seu cliente\n");
		printf("_____________________________________________\n" );
		printf( "  Escreva o nome do cliente:\n" );
		printf( "  V - Voltar\t\tQ - Sair:\n" );
		printf( "_____________________________________________\n" );

		while(estado){
		printf("\nEscolha uma opção >> ");

		input = scanf("%s",cliente);
		cliente[6]='\0';
		/*if(info_lookUp(info,cliente,1)!=0){*/
			if(cliente[1]!=' '){
				switch(cliente[0]) {
					case 'Q': return 0; break;

					case 'V': return estado; break;

					default: break;
				}
			}
			for(i=0;i!=12;i++)
				for(j=0;j!=3;j++)
					resultado[i][j]=getprodutosComprados(info,cliente,i,j);




			system("clear");
			printf( "\tCompras pelo cliente %s\n",cliente);
			printf( "______________________________________________________\n" );
			printf("\t  Filial 1   Filial 2   Filial 3\n");
			for(i=0;i!=12;i++)
			printf("Mes %2d\t %3d \t\t%3d \t\t%3d\n",i,resultado[i][0],resultado[i][1],resultado[i][2]);
			
			printf( "______________________________________________________\n" );
			printf( "  V - Voltar\t\tQ - Sair:\n" );
			}
		/*}*/
	return estado;	
	}
	



int querie_6(Faturacao faturas) {


	int estado = 1, input, mes1 = 50, mes2 = 50;
	int voltar = 1;
	double total_faturado_intervalo;
	int total_vendas_intervalo;
	char opcao[10];
	char m1[10];
	char m2[10];
	
	while(estado) {
		
		system("clear");
		printf( "_____________________________________________\n" );
		printf( " Valores totais num intervalo - QUERIE 6\n\n" );
		
		printf("\nInsira o primeiro mês do intervalo >> ");
		
		while(mes1 < 1 || mes1 > 12) {
			input = scanf("%s",m1);
			mes1 = atoi(m1);
			if(mes1 < 1 && mes1 > 12) { 
				printf("\nMês inserido invalido\n");
				printf("\nInsira o primeiro mês do intervalo >> ");
			}
		}

		printf("\nInsira o segundo mês do intervalo >> ");

		while(mes2 < 1 || mes2 > 12) {
			input = scanf("%s",m2);
			mes2 = atoi(m2);
			if(mes2 < 1 && mes2 > 12) { 
				printf("\nMês inserido invalido\n");
				printf("\nInsira o segundo mês do intervalo >> ");
			}
		}

		total_faturado_intervalo = get_total_faturado_intervalo(faturas,mes1,mes2);
		total_vendas_intervalo = get_total_quantidades_intervalo(faturas,mes1,mes2);

		while(voltar) {
			system("clear");
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
				case '1': return estado; break;
				case '0': return 0; break;
				default: break;
			}	
		}
	}
	return estado;
}

int querie_7(INFO_FILIAL info){
	int estado=1;
	return estado;
}

int querie_8(INFO_FILIAL info){
	int estado=1;
	return estado;
}

int querie_9(INFO_FILIAL info){
	int estado=1;
	return estado;
}

int querie_10(INFO_FILIAL info){
	int estado=1;
	return estado;

}

int querie_11(INFO_FILIAL info){
	int estado = 1, input;

	return estado;
}

int querie_12(INFO_FILIAL info){
	int estado = 1, input;
	char opcao[10];

	system("clear");
			printf( "_____________________________________________\n" );
			printf( "\n  \n");
			printf("Total de clientes sem compras: %d\n",getnotprodutos(info,26));
			printf("Total de produtos não comprados: %d\n",getnotclientes(info,26));
			printf( "_____________________________________________\n" );
			printf( "  1 - Voltar\t\t0 - Sair:\n" );
			printf( "_____________________________________________\n" );
			
			
			printf("Escolha uma opção >> ");
			input = scanf("%s",opcao);
			
			switch(opcao[0]) {
				case '1': return estado; break;
				case '0': return 0; break;
				default: break;
			}	
	return estado;
}





void apresenta_Lista(Lista list) {
    int i;
    int input;
    char opcao[10];
    int estado = 1;
    int nr_de_elementos = lista_getPos(list);

    if(nr_de_elementos == 0) estado = 0;
    
    int elementos_pagina = 20;
    
    
    int last_pagina = nr_de_elementos % elementos_pagina;
    
    int total_paginas = (last_pagina == 0) ? (nr_de_elementos / elementos_pagina) : ((nr_de_elementos / elementos_pagina) + 1); 

    int nr_pagina = 1;

    while(estado) {

        system("clear");
        printf("\n");
        printf("Número total de elementos: %d\n\n",nr_de_elementos);
        printf(" --- Página número |%d| de |%d| ---\n", nr_pagina,total_paginas);
        

        for(i = (nr_pagina-1) * elementos_pagina; i < (nr_pagina * elementos_pagina) && i < nr_de_elementos; i++) {
            printf("\t%d\t%s\n",i+1,lista_getNome(list,i));
        }

        putchar('\n');
        printf(" 1 - [<<]  2 - [<]  3 - [>]  4 - [>>]   V - Voltar\n");
        putchar('\n');
        printf("Opcao numero > ");
        input = scanf("%s",opcao);

        switch(opcao[0]) {
            case 'V': estado = 0; break;
            case '1': nr_pagina = 1;

            case '2': if(nr_pagina > 1) nr_pagina --;
                   break;
            case '3': if(nr_pagina < total_paginas) nr_pagina++;
                   break;
            case '4': nr_pagina = total_paginas;

            default: break;
        }
    }
}