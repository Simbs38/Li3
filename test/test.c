#include "./../src/headers/avl.h"
#include "./../src/headers/catalogo.h"
#include "./../src/headers/clientes.h"
#include "./../src/headers/filial.h"
#include "./../src/headers/global.h"
#include "./../src/headers/heap.h"
#include "./../src/headers/interpretador.h"
#include "./../src/headers/leituras.h"
#include "./../src/headers/produtos.h"
#include "./../src/headers/queries.h"
#include "./../src/headers/venda.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define Linhas_de_Vendas 0
#define Total_de_Clientes_Registados 1
#define Total_de_Codigos_de_Produtos 2
#define Vendas_validas 3
#define Vendas_invalidas 4
#define Total_de_Compradores_Diferentes 5
#define Produtos_Comprados 6
#define Produtos_Nunca_Comprados 7
#define Clientes_Sem_Compras 8
#define Vendas_de_Preco_Zero 9
#define FACTURADO_TOTAL 10
#define UNIDADES_VENDIDAS 11
#define MAXBUFFER 128



typedef struct lista_produto{
  char *nome;
  double quantidade;
  double faturacao;
  double clientes;
  int mesF[12][2];
  int mesT[12][2];
  struct lista_produto *next;
}*Lista_Prod;


typedef struct lista{
  int tipo;
  double quantidade;
  Lista next;
}*Lista;

Boolean testavendas(Lista lista,FILE *file,Cat_Produtos cat_produtos,Cat_Clientes cat_clientes){
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
  printf("Numero de vendas lidas:%d\nNumero de vendas esperadas:%f\n",total,aux->quantidade );
  for(aux=lista;aux!=NULL;aux=aux->next)
    if(aux->tipo==Vendas_validas) break;
  teste2=aux->quantidade;
  printf("Numero de vendas validas:%d\nNumero de vendas validas esperados:%f\n",vendas_validas,aux->quantidade );
  for(aux=lista;aux!=NULL;aux=aux->next)
    if(aux->tipo==Vendas_invalidas) break;
  printf("Numero de vendas invalidas:%d\nNumero de vendas invalidas esperados:%f\n",vendas_invalidas,aux->quantidade );

  return (total==teste1 && teste2==vendas_validas && vendas_invalidas==aux->quantidade);
}


Boolean testaclientes(Lista lista,FILE *file){
  int total=0;
  char line[MAXBUFFER];
  Lista aux;
  while(fgets(line,MAXBUFFER,file)) {
          if(line != NULL) {
             total++; 
          }
   }
  for(aux=lista;aux!=NULL;aux=aux->next)
    if(aux->tipo==Total_de_Clientes_Registados) break;

  printf("Numero de Clientes registados:%d\nNumero de clientes esperados:%f\n",total,aux->quantidade );

  return (total==aux->quantidade);
}

Boolean testaprodutos(Lista lista,FILE *file){
  int total=0;
  char line[MAXBUFFER];
  Lista aux;
  while(fgets(line,MAXBUFFER,file)) {
          if(line != NULL)
            total++;
    }
   for(aux=lista;aux!=NULL;aux=aux->next)
    if(aux->tipo==Total_de_Codigos_de_Produtos) break;

  printf("Numero de Produtos registados:%d\nNumero de Produtos esperados:%f\n",total,aux->quantidade );

  return (total==aux->quantidade);
}




double get_quant(char *information){
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

Lista insere_lista(Lista lista,char *information){
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


Lista load_testes(FILE *file_dados){
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



int leitura(Cat_Produtos produtos,Cat_Clientes clientes,Faturacao faturas, Filial filiais[3],Lista testes){
    Boolean n;
    char *f_clientes;
    char *f_produtos;
    char *f_vendas;
    FILE *file_clientes = NULL;
    FILE *file_produtos = NULL;
    FILE *file_vendas = NULL;
    char line[MAXBUFFER];
    FILE*file;
    file=fopen("./test/Ficheiros.txt","r");


    fgets(line,MAXBUFFER,file);
      file_clientes=fopen(strtok(line,"\n\r"),"r");     
    fgets(line,MAXBUFFER,file);
      file_produtos=fopen(strtok(line,"\n\r"),"r"); 
    fgets(line,MAXBUFFER,file);
      file_vendas=fopen(strtok(line,"\n\r"),"r");
      
      /*printf("%s\n%s\n%s\n",f_clientes,f_produtos,f_vendas );*/
            

    
    n=testaclientes(testes,file_clientes);
    if(n) printf("##Teste passado!\n");
    else printf("##Teste falhado!\n");
    n=testaprodutos(testes,file_produtos);
    if(n) printf("##Teste passado!\n");
    else printf("##Teste falhado!\n");
    n=testavendas(testes,file_vendas,produtos,clientes);
    if(n) printf("##Teste passado!\n");
    else printf("##Teste falhado!\n");
    return 1;
}
Boolean testa_total_faturado(Faturacao faturas,Lista testes){
  Lista aux=testes;
  for(;aux!=NULL;aux=aux->next)
    if(aux->tipo==FACTURADO_TOTAL) break;

  double n=get_total_faturado_intervalo(faturas,1,12);
  
  printf("Total faturado:%f\nTotal faturado esperado:%f\n",aux->quantidade,n);
  return((n-aux->quantidade)<0.01);
}

Boolean testa_total_quantidade(Faturacao faturas,Lista testes){
  Lista aux=testes;
  for(;aux!=NULL;aux=aux->next)
    if(aux->tipo==UNIDADES_VENDIDAS) break;

  double n=get_total_quantidades_intervalo(faturas,1,12);
  
  printf("Total quantidades:%f\nTotal quantidades esperado:%f\n",aux->quantidade,n);
  return(n==aux->quantidade);
}


Lista_Prod alloca_nome(Lista_Prod lista,char * string){
  lista->nome=string;
  return lista;
}


Lista_Prod addnode(char *string){
  int i,j;
  Lista_Prod new=(Lista_Prod)malloc (sizeof(struct lista_produto));
  for(i=0;i!=12;i++){
    for(j=0;j!=2;j++){
      new->mesF[i][j]=0;
      new->mesT[i][j]=0;
    }
  }
  char *nome_prod=malloc(sizeof(char *));
  if(string[1]=='#')new->nome=NULL; 
  else new=alloca_nome(new,string);
  new->quantidade=0;
  new->faturacao=0;
  new->clientes=0;
  new->next=NULL;
  return new;  
}


Lista_Prod insere_Meses(Lista_Prod lista,char*line){
  int modo,mes,i,j;
  double faturado,total;
  char string_mes[4],string_total[5],*string_faturado;
  if(line[3]=='N')modo=0;
  else modo=1;
  for(i=0;line[i]!=':';i++);
  for(j=(++i);line[j]!=':';j++){
    string_mes[j-i]=line[j];
  }
  string_mes[j-i+1]='\0';

  mes=atoi(string_mes);

  for(;line[i]!=':';i++);
  for(j=(++i);line[j]!=':';j++){
    string_total[j-i]=line[j];
  }
  string_total[j-i+1]='\0';

  total=atof(string_total);
  

  for(j=0;line[i];i++)
    line[j++]=line[i];
  
  line[j]='\0';
  line=strtok(line,"\n\r");
  faturado=strtod(line,NULL);

  lista->mesF[mes][modo]=faturado;
  lista->mesT[mes][modo]=total;
  lista->clientes++;
  lista->quantidade+=total;
  lista->faturacao+=faturado;;


  return lista;
}

Lista_Prod init_testes_produtos(FILE*file){
  Lista_Prod new=addnode("###");
  Lista_Prod aux=new;
  char *information;
  char line[MAXBUFFER];
  Lista_Prod lista=NULL; 
  while(fgets(line,MAXBUFFER,file)) {
    switch(line[0]){
      case '#': break;
      case '-': {
        if(aux->nome==NULL){aux=alloca_nome(aux,information);}
        else aux->next=addnode(information);
        break;
      }
      case 'M':{
        information = strtok(line,"\n\r");
          if(information != NULL) 
            aux=insere_Meses(aux,information);
      break;
      } 
      case 'F':{
        information = strtok(line,"\n\r");
          if(information != NULL) 
            aux->faturacao=get_quant(information);
      break;
      } 
      case 'T':{
        information = strtok(line,"\n\r");
          if(information != NULL) 
            aux->quantidade=get_quant(information);
      break;
      }
      case 'C':{
        information = strtok(line,"\n\r");
          if(information != NULL) 
            aux->clientes=get_quant(information);
      break;
      }
      default: break;
    }
  }
  return lista;
}








int main(){
    int i,n;
    FILE *file_dados =NULL;
    FILE *file_teste_produtos=NULL;

        Cat_Clientes clientes = init_cat_clientes();
        Cat_Produtos produtos = init_cat_produtos();
        Faturacao faturacao = init_Faturacao();
        Filial filiais[3];
        for(i = 0; i < 3; i++) {
            filiais[i] = init_Filial();
        }
        file_dados =fopen("./test/dados_teste.txt","r");

        Lista testes=load_testes(file_dados);
        
        file_teste_produtos=fopen("./test/testes_produtos.txt","r");

        Lista_Prod testes_produtos=init_testes_produtos(file_teste_produtos);
        Lista_Prod aux;
        for(aux=testes_produtos;aux!=NULL;aux=aux->next){
          printf("%s\n",aux->nome );
        }

        querie_1(produtos,clientes,faturacao,filiais,1);
        leitura(produtos,clientes,faturacao,filiais,testes);
        n=testa_total_faturado(faturacao,testes);
        if(n) printf("##Teste passado!\n");
        else printf("##Teste falhado!\n");
        n=testa_total_quantidade(faturacao,testes);
        if(n) printf("##Teste passado!\n");
        else printf("##Teste falhado!\n");

        /*read_produtos();*/

    

        remove_Catalogo_Clientes(clientes);
        remove_Catalogo_Produtos(produtos);
        free_Faturacao(faturacao);

    return 0;


}


/*fazer import dos dados do ficheiro, fazer read do ficheiro, fazer clientes, produtos e valida vendas neste modulo*/