#include "./headers/queries.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Ler os 3 ficheiros (Produtos, Clientes e Vendas), cujos nomes poderão ser introduzidos pelo utilizador ou, opcionalmente, assumidos por omissão  
 * @param Cat_Produtos produtos.
 * @param Cat_Clientes clientes.
 * @param Faturacao faturas.
 * @param Filiais filiais.
 * @param int modo.
*/
int querie_1(Cat_Produtos produtos,Cat_Clientes clientes,Faturacao faturas, Filial filiais[3], int modo) {
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
			
			leitura_ficheiros(clientes,produtos,faturas,filiais,file_clientes,file_produtos,file_vendas,f_clientes,f_produtos,f_vendas);
			
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
			leitura_ficheiros(clientes,produtos,faturas,filiais,file_clientes,file_produtos,file_vendas,f_clientes,f_produtos,f_vendas);
		}
	return 10;
}

/**
 * Determina a lista e o total de produtos cujo código se inicia por uma dada letra.
 * @param Cat_Produtos produtos.
 * @return int. 
*/


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

/**
 * Dado um mês e um código de produto, apresentar o número total de vendas e o total facturado com esse produto em tal mês. 
 * @param Faturacao faturas.
 * @return int.
 */

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
		
		printf("Diga o mês a procurar >> ");
		input = scanf("%s",mese);
		mes = atoi(mese);
		
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
				printf("Filial 1 %5d \t%5d \t\t%7.2f\t  %7.2f\n",total_quant_mes_normal_1, total_quant_mes_promo_1, total_preco_mes_normal_1, total_preco_mes_promo_1);
				printf("Filial 2 %5d \t%5d \t\t%7.2f\t  %7.2f\n",total_quant_mes_normal_2, total_quant_mes_promo_2, total_preco_mes_normal_2, total_preco_mes_promo_2);
				printf("Filial 3 %5d \t%5d \t\t%7.2f\t  %7.2f\n",total_quant_mes_normal_3, total_quant_mes_promo_3, total_preco_mes_normal_3, total_preco_mes_promo_3);
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

/*
 * Determina a lista ordenada dos códigos dos produtos que ninguém comprou. 
 * @param Faturacao faturas.
 * @return int.
*/
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

/**
 * Dado um código de cliente, criar uma tabela com o numero total de produtos comprados mês a mês 
 * @param Filiais filial
 * @return int
*/
int querie_5(Filial filiais[3]) {

	int estado = 1, input,j,i;
	int resultado[12][3];
	char cliente[10];
	char opcao[10];
	Boolean existe = false;
	
	while(estado) {
		system("clear");
		printf( "_____________________________________________\n" );
		printf( "  Números de unidades Compradas - QUERIE 5\n\n" );
		
		while (existe == false) {
			printf(" Insira o codigo do cliente >> ");
			input = scanf("%s",cliente);
			existe = filial_existe_Cliente(filiais[0],cliente);
			if(!existe) printf("O Cliente não é válido, insira de novo\n\n");
		}

		for(i = 0; i < 12; i++) {
			for(j = 0; j < 3; j++) {
				resultado[i][j] = nr_total_unidades_compradas(filiais[j],cliente,i+1);
			}
		}

		system("clear");	
		printf( "\n\tQuantidades do cliente |%s| - Querie 5\n",cliente);
		printf( "______________________________________________________\n" );
		printf("\t   Filial 1    Filial 2    Filial 3\n");
		
		for(i = 0; i != 12; i++) {
			printf("Mês %d \t %5d \t    %5d \t %5d\n", i+1, resultado[i][0],resultado[i][1],resultado[i][2]);
		}
		printf( "______________________________________________________\n" );
		printf( "  V - Voltar\t\tQ - Sair:\n" );
		
		input = scanf("%s",opcao);
		switch(opcao[0]) {
			case 'V': return estado; break;

			case 'Q': return 0; break;
					
			default: break;
		}
	}
	return estado;
}	
	
/**
 * Dado um intervalo fechado de meses, determinar o total de vendas registadas nesse intervalo e o total facturado.
 * @param Faturacao faturas.
 * @return int.
*/
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
			printf( "  V - Voltar\t\tQ - Sair:\n" );
			printf( "_____________________________________________\n" );
			
			
			printf("Escolha uma opção >> ");
			
			input = scanf("%s",opcao);
			
			switch(opcao[0]) {
				case 'V': return estado; break;
				
				case 'Q': return 0; break;
				
				default: break;
			}	
		}
	}
	return estado;
}

/**
 * Determinar a lista ordenada de códigos de clientes que realizaram compras em todas as filiais.
 * @param Filiais filial.
 * @return int.
*/
int querie_7(Filial filiais[3]){
	
	int estado = 1, input;
	int i;
	char *elem;
	char opcao[10];
	Conj_Filiais comprados_1 = init_Conj_Filiais(3000);
	Conj_Filiais comprados_total = init_Conj_Filiais(3000);

	comprados_1 = lista_clientes_compraram_filial(comprados_1,filiais[0]);
	int tamanho = filial_getPos(comprados_1);
	
	for(i = 0; i < tamanho; i++) {
		elem = filial_get_elemento_lista(comprados_1,i);
		if(verifica_cliente_comprado(filiais[1],elem) && verifica_cliente_comprado(filiais[2], elem)) adiciona_Nome(comprados_total,elem); 
	}
	
	apresenta_Dados_Filial(comprados_total);
	
	return estado;
}

/**
 * Dado um código de produto e uma filial, determinar os códigos, distinguindo entre compra N e compra P.
 * @param Filiais filial.
 * @return int.
*/
int querie_8(Filial filiais[3]) {

	int estado = 1, input, filial = 0;
	char produto[10];
	char fil[10];
	char promo[10];
	Boolean existe = false;

	Conj_Filiais normal;
	Conj_Filiais promocao;	

	while(estado) {
		system("clear");
		printf( "_____________________________________________\n" );
		printf( "   Clientes de um Produto - QUERIE 8\n\n" );

		while (existe == false) {
			printf(" Insira o codigo do produto >> ");
			input = scanf("%s",produto);
			existe = filial_existe_Produto(filiais[0],produto);
			if(!existe) printf("O Produto não é válido, insira de novo\n\n");
		}
		
		while(filial < 1 || filial > 3) {
			printf("\nInsira a filial que pretende >> ");
			input = scanf("%s",fil);
			filial = atoi(fil);
		}

		normal = lista_clientes_de_produto(filiais[filial-1],produto,'N');
		promocao = lista_clientes_de_produto(filiais[filial-1],produto,'P');
		
		printf("\n  Total em modo N: %d\n",filial_getPos(normal));
		printf("  Total em modo P: %d\n\n",filial_getPos(promocao));
		printf("Indique se pretende ver a lista N ou P >> ");
		input = scanf("%s",promo);

		if(promo[0] == 'N' || promo[0] == 'n') apresenta_Dados_Filial(normal);
		if(promo[0] == 'P' || promo[0] == 'p') apresenta_Dados_Filial(promocao);
		return estado;
	}

		
	return estado;
}


/**
 * Dado  um  código  de  cliente  e  um  mês,  determinar  a  lista  de  códigos  de produtos que mais comprou.
 * @param Filiais filial.
 * @return int.
*/
int querie_9(Filial filiais[3]){
	int i;
	int estado = 1, input, m = 0;
	char cliente[10];
	char mes[10];
	char promo[10];
	Boolean existe = false;

	Conj_Filiais valores = init_Conj_Filiais(100);	
	HEAP heap = init_HEAP();

	while(estado) {
		system("clear");
		printf( "_____________________________________________\n");
		printf( "  Produtos de um cliente num mês - QUERIE 9\n\n");
		
		while (existe == false) {
			printf(" Insira o codigo do cliente >> ");
			input = scanf("%s",cliente);
			existe = filial_existe_Cliente(filiais[0],cliente);
			if(!existe) printf("O Cliente não é válido, insira de novo\n\n");
		}

		while(m < 1 || m > 12) {
		printf("\nInsira o mês >> ");
			input = scanf("%s",mes);
			m = atoi(mes);
		}

		for(i = 0; i < 3; i++) heap = lista_codigos_de_clientes(filiais[i],heap,cliente,m,'Q');
		valores = convert_Heap_Lista(valores,heap,'Q');
		apresenta_Dados_Filial(valores);
		return estado;
	}
	return estado;
}


/**
 *Cria  uma  lista  dos  N produtos mais  vendidos  em  todo  o  ano filial a filial.
 * @param Filiais filial.
 * @return int.
*/
int querie_10(Filial filiais[3]){
	int i;
	int estado = 1, input, nr = 0;
	char n_produtos[10];
	
	Conj_Filiais valores_1 = init_Conj_Filiais(100);
	HEAP heap_1 = init_HEAP();
	
	Conj_Filiais valores_2 = init_Conj_Filiais(100);
	HEAP heap_2 = init_HEAP();
	
	Conj_Filiais valores_3 = init_Conj_Filiais(100);
	HEAP heap_3 = init_HEAP();
	
	system("clear");
	printf( "_____________________________________________\n" );
	printf( "   N Produtos mais comprados - QUERIE 10\n\n" );

	printf("\nIndique o número de produtos mais vendidos que pretende ver >> ");
	input = scanf("%s",n_produtos);
	nr = atoi(n_produtos);
	
	heap_1 = heap_produtos_mais_vendidos(filiais[0],heap_1);
	valores_1 = retira_N_Produtos(valores_1,heap_1,nr);
				
	heap_2 = heap_produtos_mais_vendidos(filiais[1],heap_2);
	valores_2 = retira_N_Produtos(valores_2,heap_2,nr);
		
	heap_3 = heap_produtos_mais_vendidos(filiais[2],heap_3);
	valores_3 = retira_N_Produtos(valores_3,heap_3,nr);


    char opcao[10];
    int nr_de_elementos = filial_getPos(valores_1);

    if(nr_de_elementos == 0) estado = 0;
    
    int elementos_pagina = 20;
    
    
    int last_pagina = nr_de_elementos % elementos_pagina;
    
    int total_paginas = (last_pagina == 0) ? (nr_de_elementos / elementos_pagina) : ((nr_de_elementos / elementos_pagina) + 1); 

    int nr_pagina = 1;

    while(estado) {

        system("clear");
        printf("\n");
        printf(" Querie 10: %d produtos mais vendidos\n\n",nr_de_elementos);
        printf(" --- Página número |%d| de |%d| ---\n", nr_pagina,total_paginas);
        
        printf("\n\tFilial 1\t\tFilial 2\t   Filial 3\n");
        printf("   Produto   C    Q\tProduto   C    Q\tProduto   C    Q\n");

        for(i = (nr_pagina-1) * elementos_pagina; i < (nr_pagina * elementos_pagina) && i < nr_de_elementos; i++) {
            printf("%d  %s   %d    %d\t%s   %d    %d\t%s   %d    %d\n",i+1,filial_get_elemento_lista(valores_1,i),nr_clientes_de_um_produto(filiais[0],filial_get_elemento_lista(valores_1,i)),getQuantidadeProduto(filiais[0],filial_get_elemento_lista(valores_1,i)),filial_get_elemento_lista(valores_2,i),nr_clientes_de_um_produto(filiais[1],filial_get_elemento_lista(valores_2,i)),getQuantidadeProduto(filiais[1],filial_get_elemento_lista(valores_2,i)),filial_get_elemento_lista(valores_3,i),nr_clientes_de_um_produto(filiais[2],filial_get_elemento_lista(valores_3,i)),getQuantidadeProduto(filiais[2],filial_get_elemento_lista(valores_3,i)));
        }

        putchar('\n');
        printf(" 1 - [<<]  2 - [<]  3 - [>]  4 - [>>]   V - Voltar\n");
        putchar('\n');
        printf("Opcao numero > ");
        input = scanf("%s",opcao);

        switch(opcao[0]) {
            case 'V': return estado; break;

            case '1': nr_pagina = 1;

            case '2': if(nr_pagina > 1) nr_pagina --;
                   break;
            case '3': if(nr_pagina < total_paginas) nr_pagina++;
                   break;
            case '4': nr_pagina = total_paginas;

            default: break;
        }
    }
    return estado;
}


/**
 * Dado um código de cliente determinar quais os códigos dos 3 produtos em que tenho gasto mais.
 * @param Filiais filial
 * @return int
*/
int querie_11(Filial filiais[3]){
	
	int i;
	int estado = 1, input, m = 0;
	char cliente[10];
	char mes[10];
	char promo[10];

	Conj_Filiais valores = init_Conj_Filiais(5);	
	HEAP heap = init_HEAP();



	while(estado) {
		system("clear");
		printf( "_____________________________________________\n" );
		printf( "   Top 3 de um Cliente - QUERIE 11\n\n" );

		
		printf("\nIndique o cliente >> ");
		input = scanf("%s",cliente);
		
		for(i = 0; i < 3; i++) heap = top3_clientes(filiais[i],heap,cliente,'F');
		valores = lista_top3(valores,heap,'F');
		apresenta_Dados_Filial(valores);
	}	
	return estado;
}


/**
 * Determina o número de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou.
 * @param Filiais filial
 * @return int
*/
int querie_12(Filial filiais[3]){
	int estado = 1, input;
	char opcao[10];

	system("clear");
			printf( "_____________________________________________\n" );
			printf( "\n  \n");
			printf("Total de clientes sem compras: %d\n",21);
			printf("Total de produtos não comprados: %d\n",21);
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






/**
 *Determinar a lista ordenada de códigos de clientes que realizaram compras em todas as filiais.
 * @param Filiais filial
 * @return int
*/
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
