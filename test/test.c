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
#include <time.h>

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

typedef struct lista_clientes{
  char *nome;
  int registos;
  int produtos;
  double faturado;
  int mes[12];
  struct lista_clientes *next;
}*Lista_clientes;




typedef struct lista_produto{
  char *nome;
  double quantidade;
  double faturacao;
  double clientes;
  double mesF[12][2];
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


Lista_Prod alloca_nome(Lista_Prod lista,char * string){
  printf("%s\n",string );
  lista->nome = malloc((strlen(string)+1)*sizeof(char));
  strcpy(lista->nome,string);
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

Lista_Prod init_testes_produtos(FILE*file){
  Lista_Prod new=addnode("###");
  Lista_Prod aux=new;
  char *information;
  char line[MAXBUFFER],tmp[3];
  int i,mes;
  while(fgets(line,MAXBUFFER,file)) {
    switch(line[0]){
      case '#': break;
      case '-': {
        information=strtok(line,"\n\r");
        for(i=0;line[i];i++) information[i]=information[i+2]; 
        if(aux->nome==NULL){aux=alloca_nome(aux,information);}
        else {aux->next=addnode(information);aux=aux->next;}
        break;
      }
      case 'M':{
        information = strtok(line,"\n\r");
          tmp[0]=information[8];
          tmp[1]=information[9];
          tmp[2]='\0';
          mes=atoi(tmp);
          if(information != NULL){
            if(information[4]=='Q'){
              if(information[6]=='N')aux->mesT[mes-1][0]=get_quant(information);
              if(information[6]=='P')aux->mesT[mes-1][1]=get_quant(information);
            }
            if(information[4]=='P'){
              if(information[6]=='N')aux->mesF[mes-1][0]=get_quant(information);
              if(information[6]=='P')aux->mesF[mes-1][1]=get_quant(information);
            }
          }
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
  return new;
}


Boolean testa_info_produtos(Lista_Prod lista,Faturacao faturacao){
  int i,j,n=1;
  double x;
  int y;
  Lista_Prod aux;
  char a;
  for(aux=lista;aux!=NULL;aux=aux->next){
    for(i=0;i!=12;i++){
      for(j=0;j!=2;j++){
        if(j==0) a='N';
        else a='P';
        x=get_total_precos_mes_produto(faturacao,aux->nome,i+1,a);
        if(x!=lista->mesF[i][j]){n=0;
        printf("Faturado pelo cliente  %s no mes %d em modo %c :%f ==%f\n",aux->nome,i+1,a,lista->mesF[i][j],x);
        }
        aux->faturacao-=x;
        y=get_total_quantidades_mes_produto(faturacao,aux->nome,i+1,a);
        if(y!=lista->mesT[i][j]){n=0;
        printf("Quantidade comprada pelo cliente %s no mes %d em modo %c :%d ==%d\n",aux->nome,i+1,a,lista->mesT[i][j],y);
        }
        aux->quantidade-=y;
        if(x!=0)aux->clientes--;
      }
    }
  if(aux->quantidade!=0 || aux->clientes!=0 || aux->faturacao!=0) n=0;
  }
  return n;

}

void testa_querie_2(Cat_Produtos produtos){
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
      printf("QUERIE 2 TOTAL:%f MEDIA:%f\n",time_spent,time_spent/10);
}

void testa_querie_3(Faturacao faturas){
  int i;
  double time_spent=0;
  time_t begin, end;
  char *produto="NR1091";
  int mes;

  /*get produto aleatorio!!!!*/

    for(i=0;i!=5;i++){
      begin = clock();      
      mes=i;
      int total_quant_mes_normal = get_total_quantidades_mes_produto(faturas,produto,mes,'N');
      int total_quant_mes_promo = get_total_quantidades_mes_produto(faturas,produto,mes,'P');
      double total_preco_mes_normal = get_total_precos_mes_produto(faturas,produto,mes,'N');
      double total_preco_mes_promo = get_total_precos_mes_produto(faturas,produto,mes,'P');



      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }



    for(i=0;i!=5;i++){
      begin = clock();      
      mes=i;
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

      
      
      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }  
      printf("QUERIE 3 TOTAL:%f MEDIA:%f\n",time_spent,time_spent/10);
}


void testa_querie_4(Faturacao faturas){
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
      printf("QUERIE 4 TOTAL:%f MEDIA:%f\n",time_spent,time_spent/10);
}


void testa_querie_5(Filial filiais[3]){
  int i;
  Conj_Produtos lista_produtos = init_Conjunto(1000);
  char letra;
  double time_spent=0;
  time_t begin,end;


  int estado = 1, input,j;
  int resultado[12][3];
  char cliente[10];
  char opcao[10];
  Boolean existe = false;
  strcpy(cliente,"Z5000");
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
      printf("QUERIE 5 TOTAL:%f MEDIA:%f\n",time_spent,time_spent/10);
}


void testa_querie_6(Faturacao faturas){
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
    total_vendas_intervalo = get_total_quantidades_intervalo(faturas,mes1,mes2);


      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
      printf("QUERIE 6 TOTAL:%f MEDIA:%f\n",time_spent,time_spent/10);
}


void testa_querie_7(Filial filiais[3]){
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
      printf("QUERIE 7 TOTAL:%f MEDIA:%f\n",time_spent,time_spent/10);
}


void testa_querie_8(Filial filiais[3]){
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
      existe = filial_existe_Produto(filiais[0],"NR1091");
    

      normal = lista_clientes_de_produto(filiais[filial-1],"NR1091",'N');
      promocao = lista_clientes_de_produto(filiais[filial-1],"NR1091",'P');



      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
      printf("QUERIE 8 TOTAL:%f MEDIA:%f\n",time_spent,time_spent/10);
}

/*
void testa_querie_2(Cat_Produtos produtos){
  int i;
  Conj_Produtos lista_produtos = init_Conjunto(1000);
  char letra;
  double time_spent=0;


    for(i=0;i!=10;i++){
      begin = clock();      
      letra = 'A'+i;
      lista_produtos = converte_Produtos(lista_produtos,produtos,letra);
      apresenta_Produtos(lista_produtos);
      free_Conj_Produtos(lista_produtos);
      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
      printf("QUERIE 2 MEDIA:%f",time_spent);
}


void testa_querie_2(Cat_Produtos produtos){
  int i;
  Conj_Produtos lista_produtos = init_Conjunto(1000);
  char letra;
  double time_spent=0;


    for(i=0;i!=10;i++){
      begin = clock();      
      letra = 'A'+i;
      lista_produtos = converte_Produtos(lista_produtos,produtos,letra);
      apresenta_Produtos(lista_produtos);
      free_Conj_Produtos(lista_produtos);
      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
      printf("QUERIE 2 MEDIA:%f",time_spent);
}


void testa_querie_2(Cat_Produtos produtos){
  int i;
  Conj_Produtos lista_produtos = init_Conjunto(1000);
  char letra;
  double time_spent=0;


    for(i=0;i!=10;i++){
      begin = clock();      
      letra = 'A'+i;
      lista_produtos = converte_Produtos(lista_produtos,produtos,letra);
      apresenta_Produtos(lista_produtos);
      free_Conj_Produtos(lista_produtos);
      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
      printf("QUERIE 2 MEDIA:%f",time_spent);
}


void testa_querie_2(Cat_Produtos produtos){
  int i;
  Conj_Produtos lista_produtos = init_Conjunto(1000);
  char letra;
  double time_spent=0;


    for(i=0;i!=10;i++){
      begin = clock();      
      letra = 'A'+i;
      lista_produtos = converte_Produtos(lista_produtos,produtos,letra);
      apresenta_Produtos(lista_produtos);
      free_Conj_Produtos(lista_produtos);
      end = clock();
      time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
   
      }
      printf("QUERIE 2 MEDIA:%f",time_spent);
}


*/


int main(){
    int i,n,j;
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
        
        querie_1(produtos,clientes,faturacao,filiais,1);
        leitura(produtos,clientes,faturacao,filiais,testes);
        n=testa_total_faturado(faturacao,testes);
        if(n) printf("##Teste passado!\n");
        else printf("##Teste falhado!\n");

        /*for(aux=testes_produtos;aux!=NULL;aux=aux->next){
          printf("%s\n",aux->nome );
          for(i=0;i!=12;i++){
            for(j=0;j!=2;j++){
            printf("Mes %d quantidade:%d modo:%d\n",i+1,aux->mesT[i][j],j );
            printf("Mes %d preco:%f modo:%d\n",i+1,aux->mesF[i][j],j );
            
            }
          }
        }*//*
        n=testa_info_produtos(testes_produtos,faturacao);
        if(n) printf("##Teste passado!\n");
        else printf("##Teste falhado!\n");
        */

        testa_querie_2(produtos);
        testa_querie_3(faturacao);
        testa_querie_4(faturacao);
        testa_querie_5(filiais);
        testa_querie_6(faturacao);
        testa_querie_7(filiais);
        /*testa_querie_8(filiais);*/
        

    

        remove_Catalogo_Clientes(clientes);
        remove_Catalogo_Produtos(produtos);
        free_Faturacao(faturacao);

    return 0;


}


/*fazer import dos dados do ficheiro, fazer read do ficheiro, fazer clientes, produtos e valida vendas neste modulo*/