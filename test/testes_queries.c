#include "./../src/headers/avl.h"
#include "./../src/headers/catalogo.h"
#include "./../src/headers/clientes.h"
#include "./../src/headers/global.h"
#include "./../src/headers/queries.h"
#include "./../src/headers/faturacao.h"
#include "./../src/headers/filial.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void testa_querie_2(Cat_Produtos produtos);
static void testa_querie_3(Faturacao faturas,char *produto);
static void testa_querie_4(Faturacao faturas);
static void testa_querie_5(Filial filiais[3],char *cliente);
static void testa_querie_6(Faturacao faturas);
static void testa_querie_7(Filial filiais[3]);
static void testa_querie_8(Filial filiais[3],char *produto);
static void testa_querie_9(Filial filiais[3],char *cliente);
static void testa_querie_10(Filial filiais[3]);
static void testa_querie_11(Filial filiais[3],char *cliente);
static void testa_querie_12(Filial filiais[3],Faturacao faturas);


static void testa_querie_2(Cat_Produtos produtos){
  int i;
  Conj_Produtos lista_produtos = init_Conjunto(1000);
  char letra;
  time_t begin, end;
  double time_spent=0;


    for(i=0;i!=10;i++){
      begin = clock();      
      letra = 'A'+i;
      lista_produtos = converte_Produtos(lista_produtos,produtos,letra);
      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
      printf("    2     |  %f   |  %f\n",time_spent,time_spent/10);
}

static void testa_querie_3(Faturacao faturas,char *produto){
  int i;
  double time_spent=0;
  time_t begin, end;
  int mes;

    for(i=0;i!=5;i++){
      begin = clock();      
      mes=i;
      int total_quant_mes_normal = get_total_vendas_mes_produto(faturas,produto,mes,'N');
      int total_quant_mes_promo = get_total_vendas_mes_produto(faturas,produto,mes,'P');
      double total_preco_mes_normal = get_total_precos_mes_produto(faturas,produto,mes,'N');
      double total_preco_mes_promo = get_total_precos_mes_produto(faturas,produto,mes,'P');



      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }



    for(i=0;i!=5;i++){
      begin = clock();      
      mes=i;
      int total_quant_mes_normal_1 = get_total_vendas_mes_produto_filial(faturas,produto,mes,'N',1);
      int total_quant_mes_normal_2 = get_total_vendas_mes_produto_filial(faturas,produto,mes,'N',2);
      int total_quant_mes_normal_3 = get_total_vendas_mes_produto_filial(faturas,produto,mes,'N',3);

      int total_quant_mes_promo_1 = get_total_vendas_mes_produto_filial(faturas,produto,mes,'P',1);
      int total_quant_mes_promo_2 = get_total_vendas_mes_produto_filial(faturas,produto,mes,'P',2);
      int total_quant_mes_promo_3 = get_total_vendas_mes_produto_filial(faturas,produto,mes,'P',3);
      
      double total_preco_mes_normal_1 = get_total_precos_mes_produto_filial(faturas,produto,mes,'N',1);
      double total_preco_mes_normal_2 = get_total_precos_mes_produto_filial(faturas,produto,mes,'N',2);
      double total_preco_mes_normal_3 = get_total_precos_mes_produto_filial(faturas,produto,mes,'N',3);
      
      double total_preco_mes_promo_1 = get_total_precos_mes_produto_filial(faturas,produto,mes,'P',1);
      double total_preco_mes_promo_2 = get_total_precos_mes_produto_filial(faturas,produto,mes,'P',2);
      double total_preco_mes_promo_3 = get_total_precos_mes_produto_filial(faturas,produto,mes,'P',3);
      
      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }  
      printf("    3     |  %f   |  %f\n",time_spent,time_spent/10);

}


static void testa_querie_4(Faturacao faturas){
  int i, input, filial = 0;
  char letra;
  double time_spent=0;
  time_t begin, end;
  char opcao[10];
  char fil[10];

   
    for(i=0;i!=5;i++){
      begin = clock();      

 
      Conj_Faturas totais = init_Lista_Faturacao(1000);
      Conj_Faturas nao_comprados_1 = init_Lista_Faturacao(1000); 
      Conj_Faturas nao_comprados_2 = init_Lista_Faturacao(1000); 
      Conj_Faturas nao_comprados_3 = init_Lista_Faturacao(1000); 
      
      totais = cria_lista_total(totais,faturas);
      
      nao_comprados_1 = faturas_nao_comprado_filial(totais,nao_comprados_1,faturas,1);
      nao_comprados_2 = faturas_nao_comprado_filial(totais,nao_comprados_2,faturas,2);
      nao_comprados_3 = faturas_nao_comprado_filial(totais,nao_comprados_3,faturas,3);
      
      faturacao_getPos(nao_comprados_1);
      faturacao_getPos(nao_comprados_2);
      faturacao_getPos(nao_comprados_3);

      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
            printf("    4     |  %f   |  %f\n",time_spent,time_spent/10);
}


static void testa_querie_5(Filial filiais[3],char *cliente){
  int i;
  Conj_Produtos lista_produtos = init_Conjunto(1000);
  char letra;
  double time_spent=0;
  time_t begin,end;


  int estado = 1, input,j;
  int resultado[12][3];
  char opcao[10];
  Boolean existe = false;
  int n;
    for(n=0;n!=10;n++){
      begin = clock();      
      
     existe = filial_existe_Cliente(filiais[0],cliente);

    for(i = 0; i < 12; i++) {
      for(j = 0; j < 3; j++) {
        resultado[i][j] = nr_total_unidades_compradas(filiais[j],cliente,i+1);
      }
    }


      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
            printf("    5     |  %f   |  %f\n",time_spent,time_spent/10);

}


static void testa_querie_6(Faturacao faturas){
  int i;
  Conj_Produtos lista_produtos = init_Conjunto(1000);
  char letra;
  double time_spent=0;
  time_t begin, end;
  int  mes1 = 0, mes2 = 12;
  double total_faturado_intervalo;
  int total_vendas_intervalo;


    for(i=0;i!=10;i++){
      begin = clock();      
        mes1++;
        mes2--;
  
    total_faturado_intervalo = get_total_faturado_intervalo(faturas,mes1,mes2);
    total_vendas_intervalo = get_total_vendas_intervalo(faturas,mes1,mes2);


      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
            printf("    6     |  %f   |  %f\n",time_spent,time_spent/10);

}


static void testa_querie_7(Filial filiais[3]){
  int i,n;
  Conj_Produtos lista_produtos = init_Conjunto(1000);
  char letra;
  double time_spent=0;
  time_t begin, end;
  char *elem;
  Conj_Filiais comprados_1;
  Conj_Filiais comprados_total;  
  int tamanho;

    for(n=0;n!=10;n++){
      begin = clock();      
      

  comprados_1 = init_Conj_Filiais(3000);
  comprados_total = init_Conj_Filiais(3000);

  comprados_1 = lista_clientes_compraram_filial(comprados_1,filiais[0]);
  tamanho = filial_getPos(comprados_1);
  
  for(i = 0; i < tamanho; i++) {
    elem = filial_get_elemento_lista(comprados_1,i);
    if(verifica_cliente_comprado(filiais[1],elem) && verifica_cliente_comprado(filiais[2], elem)) adiciona_Nome(comprados_total,elem); 
    }

      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
            printf("    7     |  %f   |  %f\n",time_spent,time_spent/10);

}


static void testa_querie_8(Filial filiais[3],char *produto){
  int i;
  Conj_Produtos lista_produtos = init_Conjunto(1000);
  char letra;
  double time_spent=0;
  time_t begin,end;
  Conj_Filiais normal;
  Conj_Filiais promocao;  
  int estado = 1, input, filial = 0;
  Boolean existe;
  int index;
 
    for(i=0;i!=10;i++){
      begin = clock();      
      index= i % 3;
      existe = filial_existe_Produto(filiais[index],produto);
    

      normal = lista_clientes_de_produto(filiais[index],produto,'N');
      promocao = lista_clientes_de_produto(filiais[index],produto,'P');



      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
            printf("    8     |  %f   |  %f\n",time_spent,time_spent/10);

}


static void testa_querie_9(Filial filiais[3],char *cliente){
  int i,n,index;
  double time_spent=0;
  time_t begin,end;
  Conj_Filiais valores;  
  HEAP heap;
  Boolean existe;

 
    for(n=0;n!=10;n++){
      begin = clock();      
      index= i % 3;
      heap=init_HEAP();
      valores = init_Conj_Filiais(100);

      existe = filial_existe_Cliente(filiais[index],cliente);

      for(i = 0; i < 3; i++) 
      heap = lista_codigos_de_clientes(filiais[i],heap,cliente,n+1,'Q');
      valores = convert_Heap_Lista(valores,heap,'Q');


      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
            printf("    9     |  %f   |  %f\n",time_spent,time_spent/10);

}

static void testa_querie_10(Filial filiais[3]){
  int i,n,index;
  double time_spent=0;
  time_t begin,end;
  int estado = 1, input, nr = 0;
  char n_produtos[10];
  Conj_Filiais valores_1;
  HEAP heap_1;  
  Conj_Filiais valores_2;
  HEAP heap_2;  
  Conj_Filiais valores_3;
  HEAP heap_3;  
  int nr_de_elementos;
  int elementos_pagina;
  int last_pagina;
  int total_paginas; 
  int nr_pagina;




    for(n=0;n!=10;n++){
      begin = clock();      
  
  
  
      valores_1 = init_Conj_Filiais(1000);
      heap_1 = init_HEAP();
      heap_1 = heap_produtos_mais_vendidos(filiais[0],heap_1);

      valores_2 = init_Conj_Filiais(1000);
      heap_2 = init_HEAP();
      heap_2 = heap_produtos_mais_vendidos(filiais[1],heap_2);

      valores_3 = init_Conj_Filiais(1000);
      heap_3 = init_HEAP();
      heap_3 = heap_produtos_mais_vendidos(filiais[2],heap_3);


      valores_1 = retira_N_Produtos(valores_1,heap_1,nr);
      valores_2 = retira_N_Produtos(valores_2,heap_2,nr); 
      valores_3 = retira_N_Produtos(valores_3,heap_3,nr);


      nr_de_elementos = filial_getPos(valores_1);

      elementos_pagina = 20;
    
    
      last_pagina = nr_de_elementos % elementos_pagina;
    
      total_paginas = (last_pagina == 0) ? (nr_de_elementos / elementos_pagina) : ((nr_de_elementos / elementos_pagina) + 1); 

      nr_pagina = 1;

        for(i = (nr_pagina-1) * elementos_pagina; i < (nr_pagina * elementos_pagina) && i < nr_de_elementos; i++) {
           filial_get_elemento_lista(valores_1,i);
           nr_clientes_de_um_produto(filiais[0],filial_get_elemento_lista(valores_1,i));
           getQuantidadeProduto(filiais[0],filial_get_elemento_lista(valores_1,i));
           filial_get_elemento_lista(valores_2,i);
           nr_clientes_de_um_produto(filiais[1],filial_get_elemento_lista(valores_2,i));
           getQuantidadeProduto(filiais[1],filial_get_elemento_lista(valores_2,i));
           filial_get_elemento_lista(valores_3,i);
           nr_clientes_de_um_produto(filiais[2],filial_get_elemento_lista(valores_3,i));
           getQuantidadeProduto(filiais[2],filial_get_elemento_lista(valores_3,i));
        }



      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
            printf("   10     |  %f   |  %f\n",time_spent,time_spent/10);

}



static void testa_querie_11(Filial filiais[3],char *cliente){
  int i,n,index;
  double time_spent=0;
  time_t begin,end;
  Conj_Filiais valores;  
  HEAP heap;
  Boolean existe = false;
  
    for(n=0;n!=10;n++){
      begin = clock();      
      index=n%3;
      valores = init_Conj_Filiais(5);  
      heap = init_HEAP();


        existe = filial_existe_Cliente(filiais[0],cliente);    
        for(i = 0; i < 3; i++)heap = top3_clientes(filiais[i],heap,cliente,'F');
        valores = lista_top3(valores,heap,'F');
      
  
      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
            printf("   11     |  %f   |  %f\n",time_spent,time_spent/10);

}


static void testa_querie_12(Filial filiais[3],Faturacao faturas){
  int i,n,index;
  double time_spent=0;
  time_t begin,end;
  char *client;
  int estado = 1, nr_clientes = 0, nr_produtos;
  Conj_Faturas nao_comprados;
  Conj_Filiais clientes_nao_comprados_total;
  

  
    for(n=0;n!=10;n++){
      begin = clock();      
  

  nao_comprados = init_Lista_Faturacao(1000);
  nao_comprados = faturas_produtos_nao_comprados_totais(nao_comprados,faturas);
  nr_produtos = faturacao_getPos(nao_comprados);

  clientes_nao_comprados_total = init_Conj_Filiais(1000);
  clientes_nao_comprados_total = converte_total_clientes(clientes_nao_comprados_total,filiais[0]);

  for(i = 0; i < filial_getPos(clientes_nao_comprados_total); i++) {
    client = filial_get_elemento_lista(clientes_nao_comprados_total,i); 
    if(verifica_cliente_comprado(filiais[0],client) == false && 
       verifica_cliente_comprado(filiais[1],client) == false && 
       verifica_cliente_comprado(filiais[2],client) == false) nr_clientes++;
  }
  
      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
            printf("   12     |  %f   |  %f\n",time_spent,time_spent/10);

}


void testaqueries(Cat_Produtos produtos,Cat_Clientes clientes,Faturacao faturacao,Filial filiais[3]){
  int input;
  char cliente[10];
  char produto[10];
  Boolean existe = false;
  char *s;

    while (existe == false) {
      printf(" Insira o codigo do cliente >> ");
      input=scanf("%s",cliente);
      existe = filial_existe_Cliente(filiais[0],cliente);
      if(!existe) printf("O Cliente não é válido, insira de novo\n\n");
    }
    existe=false;
    while (existe == false) {
      printf(" Insira o codigo do produto >> ");
      input = scanf("%s",produto);
      existe = filial_existe_Produto(filiais[0],produto);
      if(!existe) printf("O Produto não é válido, insira de novo\n\n");
    }


      system("clear");
      printf("---------------------------------------------------------\n");
      printf("| Para uma noção mais real do tempo de execução de cada | \n");
      printf("| querie,corremos cada uma delas 10 vezes e apresentamos|  \n");
      printf("| o tempo e a o tempo medio na seguinte tabela          | \n");
      printf("---------------------------------------------------------\n\n");
      printf("  QUERIES | TEMPO TOTAL |   MEDIA\n");
      printf("------------------------------------\n");
      testa_querie_2(produtos);
      printf("------------------------------------\n");
      testa_querie_3(faturacao,produto);
      printf("------------------------------------\n");
      testa_querie_4(faturacao);
      printf("------------------------------------\n");
      testa_querie_5(filiais,cliente);
      printf("------------------------------------\n");
      testa_querie_6(faturacao);
      printf("------------------------------------\n");
      testa_querie_7(filiais);
      printf("------------------------------------\n");
      testa_querie_8(filiais,produto);
      printf("------------------------------------\n");
      testa_querie_9(filiais,cliente);
      printf("------------------------------------\n");
      testa_querie_10(filiais);
      printf("------------------------------------\n");
      testa_querie_11(filiais,cliente);
      printf("------------------------------------\n");
      testa_querie_12(filiais,faturacao);
      printf("------------------------------------\n");
        

}