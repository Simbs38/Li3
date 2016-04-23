#include "./../src/headers/filial.h"
#include "./../src/headers/global.h"
#include "./../src/headers/faturacao.h"
#include "testes_queries.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define Linhas_de_Vendas 0
#define Total_de_Clientes_Registados 1
#define Total_de_Codigos_de_Produtos 2
#define Vendas_validas 3
#define Vendas_invalidas 4
#define Total_de_Compradores_Diferentes 5
#define Produtos_Comprados 6
#define Produtos_Nunca_Comprados 7
#define Clientes_Sem_Compras 8
#define FACTURADO_TOTAL 9
#define MAXBUFFER 128


typedef struct lista{
  int tipo;
  double quantidade;
  Lista next;
}*Lista;


static Boolean testavendas(Lista lista,FILE *file,Cat_Produtos cat_produtos,Cat_Clientes cat_clientes);
static Boolean testaclientes(Lista lista,FILE *file);
static Boolean testaprodutos(Lista lista,FILE *file);
static Boolean testa_total_faturado(Faturacao faturas,Lista testes);
static Boolean testa_produtos_nunca_comprados(Faturacao faturas,Lista testes);
static Boolean testa_produtos_comprados(Faturacao faturas,Lista testes);
static Boolean testa_clientes_sem_compras(Filial filiais[3],Lista testes);
static Boolean testa_clientes_diferentes(Filial filiais[3],Lista testes);
static void testadados(Cat_Produtos produtos,Cat_Clientes clientes, Faturacao faturacao,Filial filiais[3],Lista testes,int n);
static Lista insere_lista(Lista lista,char *information);
static Lista load_testes(FILE *file_dados);
static double get_quant(char *information);





static Boolean testavendas(Lista lista,FILE *file,Cat_Produtos cat_produtos,Cat_Clientes cat_clientes){
  int total=0;
  char line[MAXBUFFER];
  Lista aux;
  int i;
  Boolean verify;
  int vendas_validas=0,vendas_invalidas=0;
  char* product;
  double price;
  int ammount; 
  char type;
  char* client;
  int month;
  int shop;
  int teste1,teste2;
  char *information;
   
  Venda venda = initVenda();
  

  while(fgets(line,MAXBUFFERVENDAS,file)) {

      information = strtok(line,"\n\r");
      information = strtok(information," ");
      for(i = 0; information != NULL; i++) {
         switch(i) {
            case 0: product = information; break;
            case 1: price = atof(information); break;
            case 2: ammount = atoi(information);break; 
            case 3: type = information[0];break;
            case 4: client = information;break;
            case 5: month = atoi(information);break;
            case 6: shop = atoi(information); /*printf("shop: %d\n",shop);*/ break;
            default: break;
         }
         information = strtok(NULL," ");
      }

      venda = change_sale(venda,product,price,ammount,type,client,month,shop);
      /* Verifica a existencia do produto e do cliente de uma dada venda */
      
      verify = validate_sale(cat_produtos,cat_clientes,venda);
      /* Caso verifique adiciona á estrutura das vendas a venda validada nessa iteração */
      if(verify) {
         vendas_validas++;
         total++;
      } else {
         total++;
         vendas_invalidas++;
      }

   }

  for(aux=lista;aux!=NULL;aux=aux->next)
    if(aux->tipo==Linhas_de_Vendas) break;
    teste1=aux->quantidade;
  printf("Vendas     |                |                |\nLidas      |      %7d   |      %7d   |  %s\n           |                |                |\n",(int)aux->quantidade,total,(total==aux->quantidade ? "SIM" : "NÂO"));
  printf("------------------------------------------------------\n");
  for(aux=lista;aux!=NULL;aux=aux->next)
    if(aux->tipo==Vendas_validas) break;
  teste2=aux->quantidade;
  printf("Vendas     |                |                |\nValidas    |      %7d   |      %7d   |  %s\n           |                |                |\n",(int)aux->quantidade,vendas_validas,(vendas_validas==aux->quantidade ? "SIM" : "NÂO"));
  printf("------------------------------------------------------\n");
  for(aux=lista;aux!=NULL;aux=aux->next)
    if(aux->tipo==Vendas_invalidas) break;
  printf("Vendas     |                |                |\nInvalidas  |      %7d   |      %7d   |  %s\n           |                |                |\n",(int)aux->quantidade,vendas_invalidas,(vendas_invalidas==aux->quantidade ? "SIM" : "NÂO"));
  printf("------------------------------------------------------\n");
  return (total==teste1 && teste2==vendas_validas && vendas_invalidas==aux->quantidade);
}


static Boolean testaclientes(Lista lista,FILE *file){
  int total=0;
  char line[MAXBUFFER];
  Lista aux;
  char *s;
  while(fgets(line,MAXBUFFER,file)) {
          if(line != NULL) {
             total++; 
          }
   }
  for(aux=lista;aux!=NULL;aux=aux->next)
    if(aux->tipo==Total_de_Clientes_Registados) break;

  printf("Numero de  |                |                |\nClientes   |      %7d   |      %7d   |  %s\nRegistados |                |                |\n",(int)aux->quantidade,total,(total==aux->quantidade ? "SIM" : "NÂO"));
  printf("------------------------------------------------------\n");
  return (total==aux->quantidade);
}

static Boolean testaprodutos(Lista lista,FILE *file){
  int total=0;
  char line[MAXBUFFER];
  Lista aux;
  while(fgets(line,MAXBUFFER,file)) {
          if(line != NULL)
            total++;
    }
   for(aux=lista;aux!=NULL;aux=aux->next)
    if(aux->tipo==Total_de_Codigos_de_Produtos) break;

  printf("Numero de  |                |                |\nProdutos   |      %7d   |      %7d   |  %s\nRegistados |                |                |\n",(int)aux->quantidade,total,(total==aux->quantidade ? "SIM" : "NÂO"));
  printf("------------------------------------------------------\n");
  
  return (total==aux->quantidade);
}



static Boolean testa_total_faturado(Faturacao faturas,Lista testes){
  Lista aux=testes;
  for(;aux!=NULL;aux=aux->next)
    if(aux->tipo==FACTURADO_TOTAL) break;
  double n=get_total_faturado_intervalo(faturas,1,12);
  double res=n-aux->quantidade;
  printf("Total      |                |                |\nFaturado   |  %13.2f|  %13.2f|  %s\n           |                |                |\n",aux->quantidade,n,((int)res==0) ? "SIM" : "NÂO");
  printf("------------------------------------------------------\n");
  return(n==aux->quantidade);
}


static Boolean testa_produtos_nunca_comprados(Faturacao faturas,Lista testes){
  Lista aux;
  Conj_Faturas nao_comprados= init_Lista_Faturacao(1000);
  int nr_produtos;

  for(aux=testes;aux!=NULL;aux=aux->next)
    if(aux->tipo==Produtos_Nunca_Comprados) break;

  nao_comprados = faturas_produtos_nao_comprados_totais(nao_comprados,faturas);
  nr_produtos = faturacao_getPos(nao_comprados);
  printf("Produtos   |                |                |\nNunca      |      %7d   |      %7d   |  %s\nComprados  |                |                |\n",(int)aux->quantidade,nr_produtos,(nr_produtos==aux->quantidade ? "SIM" : "NÂO"));
  printf("------------------------------------------------------\n");
  
  return (nr_produtos==aux->quantidade);  
}

static Boolean testa_produtos_comprados(Faturacao faturas,Lista testes){
  Boolean n=false;
  Lista aux;
  Conj_Faturas nao_comprados= init_Lista_Faturacao(1000);
  int nr_produtos;
  double total;


  for(aux=testes;aux!=NULL;aux=aux->next)
    if(aux->tipo==Total_de_Codigos_de_Produtos) break;
  total=aux->quantidade;


  for(aux=testes;aux!=NULL;aux=aux->next)
    if(aux->tipo==Produtos_Comprados) break;


  nao_comprados = faturas_produtos_nao_comprados_totais(nao_comprados,faturas);
  nr_produtos = faturacao_getPos(nao_comprados);
  total=total-nr_produtos;
  printf("Produtos   |                |                |\nComprados  |      %7d   |      %7d   |  %s\n           |                |                |\n",(int)aux->quantidade,(int)total,(total==aux->quantidade) ? "SIM" : "NÂO");
  printf("------------------------------------------------------\n");
  return n;  
}





static Boolean testa_clientes_sem_compras(Filial filiais[3],Lista testes){
  Conj_Filiais clientes_nao_comprados_total = init_Conj_Filiais(1000);
  clientes_nao_comprados_total = converte_total_clientes(clientes_nao_comprados_total,filiais[0]);
  Lista aux;
  char *client;
  int nr_clientes=0;
  int i;

  for(i = 0; i < filial_getPos(clientes_nao_comprados_total); i++) {
    client = filial_get_elemento_lista(clientes_nao_comprados_total,i); 
    if(verifica_cliente_comprado(filiais[0],client) == false && verifica_cliente_comprado(filiais[1],client) == false && verifica_cliente_comprado(filiais[2],client) == false) nr_clientes++;
  }

  for(aux=testes;aux!=NULL;aux=aux->next)
    if(aux->tipo==Clientes_Sem_Compras) break;

  printf("Clientes   |                |                |\nSem        |      %7d   |      %7d   |  %s\nCompras    |                |                |\n",(int)aux->quantidade,nr_clientes,(nr_clientes==aux->quantidade ? "SIM" : "NÂO"));
  printf("------------------------------------------------------\n");
  
  return (nr_clientes==aux->quantidade);  

}

static Boolean testa_clientes_diferentes(Filial filiais[3],Lista testes){


  Conj_Filiais clientes_nao_comprados_total = init_Conj_Filiais(1000);
  clientes_nao_comprados_total = converte_total_clientes(clientes_nao_comprados_total,filiais[0]);
  Lista aux;
  char *client;
  int nr_clientes=0;
  int i;
  double total;

  for(i = 0; i < filial_getPos(clientes_nao_comprados_total); i++) {
    client = filial_get_elemento_lista(clientes_nao_comprados_total,i); 
    if(verifica_cliente_comprado(filiais[0],client) == false && verifica_cliente_comprado(filiais[1],client) == false && verifica_cliente_comprado(filiais[2],client) == false) nr_clientes++;
  }

  for(aux=testes;aux!=NULL;aux=aux->next)
    if(aux->tipo==Total_de_Clientes_Registados) break;
  total=aux->quantidade;


  for(aux=testes;aux!=NULL;aux=aux->next)
    if(aux->tipo==Total_de_Compradores_Diferentes) break;

  total=total-nr_clientes;
  printf("Clientes   |                |                |\nque fizeram|      %7d   |      %7d   |  %s\nCompras    |                |                |\n",(int)aux->quantidade,(int)total,(total==aux->quantidade) ? "SIM" : "NÂO");
  printf("------------------------------------------------------\n");
  return (total==aux->quantidade);  
}



static void testadados(Cat_Produtos produtos,Cat_Clientes clientes, Faturacao faturacao,Filial filiais[3],Lista testes,int n){
      char s[10];
      FILE *file_clientes = NULL;
      FILE *file_produtos = NULL;
      FILE *file_vendas = NULL;
      char line[MAXBUFFER];
      char f_clientes[MAXBUFFER];
      strcpy(f_clientes,"./data/Clientes.txt");
      file_clientes = fopen(f_clientes,"r");
      char f_produtos[MAXBUFFER];
      strcpy(f_produtos,"./data/Produtos.txt");
      file_produtos = fopen(f_produtos,"r");
      char f_vendas[MAXBUFFER];
      strcpy(f_vendas,"./data/Vendas_1M.txt");
      file_vendas = fopen(f_vendas,"r");
      int input;

      if(n==1);
      else if(n==2){ 
        strcpy(f_vendas,"./data/Vendas_3M.txt");
        file_vendas = fopen(f_vendas,"r");
      }
      else if(n==3){
        strcpy(f_vendas,"./data/Vendas_5M.txt");
        file_vendas = fopen(f_vendas,"r");
      }
      else{
      
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
      }

      system("clear");
      printf("             TESTE DE DADOS DO PROGRAMA \n");
      printf("------------------------------------------------------\n");
      printf("   TESTE   | VALOR ESPERADO |   VALOR LIDO   | PASSOU\n");
      printf("------------------------------------------------------\n");
      testaclientes(testes,file_clientes);
      testaprodutos(testes,file_produtos);
      testavendas(testes,file_vendas,produtos,clientes);
      testa_total_faturado(faturacao,testes);
      testa_clientes_diferentes(filiais,testes);
      testa_produtos_comprados(faturacao,testes);
      testa_produtos_nunca_comprados(faturacao,testes);
      testa_clientes_sem_compras(filiais,testes);
      printf("Carregue numa tecla para continuar --> ");
      scanf("%s",s);


}

static Lista insere_lista(Lista lista,char *information){
  Lista new=(Lista) malloc(sizeof(struct lista));
  Lista aux=lista;
  new->tipo=information[0]-'A';
  new->quantidade=get_quant(information);
  new->next=NULL;
  
  if(aux==NULL) return new;
  for(;aux->next!=NULL;aux=aux->next);
  aux->next=new;

  return lista;
}


static Lista load_testes(FILE *file_dados){
    char *information;
    char line[MAXBUFFER];
    Lista lista=NULL; 
      while(fgets(line,MAXBUFFER,file_dados)) {
        if(line[0]=='#');  
        else{
          information = strtok(line,"\n\r");
          if(information != NULL) {
             lista=insere_lista(lista,information);
              
          }
        }
   }
   return lista;
}



static double get_quant(char *information){
  int i,j=0;
  double n;
  for(i=0;information[i] && information[i]!=':';i++);
  i++;
  for(j=0;information[i];i++)
    information[j++]=information[i];
  
  information[j]='\0';
  information=strtok(information,"\n\r");
  n=strtod(information,NULL);
  return n;
}


int main(){
    int i,n,j;
    FILE *file_dados =NULL;
    Boolean existe=false;
    char produto[MAXBUFFER];
    int input;

        Cat_Clientes clientes = init_cat_clientes();
        Cat_Produtos produtos = init_cat_produtos();
        Faturacao faturacao = init_Faturacao();
        Filial filiais[3];
        for(i = 0; i < 3; i++) {
            filiais[i] = init_Filial();
        }
        file_dados =fopen("./test/dados_teste.txt","r");

        Lista testes=load_testes(file_dados);

          while (existe == false) {
            system("clear");
            printf("  Bem vindo ao programa de testes do programa gereVendas, para inicializar escolha\n  uma opção do ficheiro vendas para ser apresentado\n\n");
            printf("  1-Vendas_1M.txt\n");
            printf("  ---------------\n");
            printf("  2-Vendas_3M.txt\n");
            printf("  ---------------\n");
            printf("  3-Vendas_5M.txt\n");
            printf("  ---------------\n");
            printf("  4-Outro ficheiro\n\n");
            
            printf("  Insira o Ficheiro de vendas que quer ler >> ");
            input = scanf("%s",produto);
            input=atoi(produto);
            if(input!=1 && input!=2 && input!=3 && input!=4 ) printf("A opção não é válida, insira de novo\n\n");
            else existe=true;
          }
        
        querie_1(produtos,clientes,faturacao,filiais,input);
        

        testadados(produtos,clientes,faturacao,filiais,testes,input);
 
       

        testaqueries(produtos,clientes,faturacao,filiais);
    

        remove_Catalogo_Clientes(clientes);
        remove_Catalogo_Produtos(produtos);
        free_Faturacao(faturacao);

    return 0;


}