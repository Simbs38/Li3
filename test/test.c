#include "./../src/headers/avl.h"
#include "./../src/headers/catalogo.h"
#include "./../src/headers/clientes.h"
#include "./../src/headers/filiais.h"
#include "./../src/headers/global.h"
#include "./../src/headers/heap.h"
#include "./../src/headers/interpretador.h"
#include "./../src/headers/leituras.h"
#include "./../src/headers/produtos.h"
#include "./../src/headers/queries.h"
#include "./../src/headers/venda.h"


int clientes(Cat_Clientes costumers, FILE *f_clients, char* file_name){
       time_t begin, end;
   double time_spent;

   begin = clock();

   char *information;
   char line[MAXBUFFERCLIENTES];
   
   int clientes_validos = 0, total = 0;

   Cliente client = criaCliente();
   while(fgets(line,MAXBUFFERCLIENTES,f_clients)) {
      
      information = strtok(line,"\n\r");
      
      if(information != NULL) {
         alteraCliente(client,information);   
         costumers = insere_Cliente(costumers, client);   
      
         clientes_validos++;
      }

      total++;
   }
   free_cliente(client);
   end = clock();
   time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   
   printf(" Nome do Ficheiro: %s\n",file_name);
   printf(" Número de linhas lidas: %d\n",total);
   printf(" Número de linhas válidas: %d\n",clientes_validos);
   printf(" Tempo de Leitura: %f segundos\n",time_spent);
   putchar('\n');


   fclose(f_clients);
   
   return costumers;
}


int leitura(Cat_Produtos produtos,Cat_Clientes clientes,Faturacao faturas, Filial filiais[3]){
    int input;
    char f_clientes[50];
    char f_produtos[50];
    char f_vendas[50];
    FILE *file_clientes = NULL;
    FILE *file_produtos = NULL;
    FILE *file_vendas = NULL;


            strcpy(f_clientes,"./data/Clientes.txt");
            strcpy(f_produtos,"./data/Produtos.txt");
            strcpy(f_vendas,"./data/Vendas_1M.txt");
            
            file_clientes = fopen(f_clientes,"r");
            file_produtos = fopen(f_produtos,"r");
            file_vendas = fopen(f_vendas,"r");
            
            leitura_ficheiros(clientes,produtos,faturas,filiais,file_clientes,file_produtos,file_vendas,f_clientes,f_produtos,f_vendas);
    return 1;
}





int main(){
    int i;
    /*numero de testes disponiveis*/
    int testes_dados=18;
    int testes_produtos_nao_comprados=5;
    int testes_clientes=15;
    int testes_faturacao_produtos=102;

        Cat_Clientes clientes = init_cat_clientes();
        Cat_Produtos produtos = init_cat_produtos();
        Faturacao faturacao = init_Faturacao();
        Filial filiais[3];
        for(i = 0; i < 3; i++) {
            filiais[i] = init_Filial();
        }
        leitura(produtos,clientes,faturacao,filiais);
        printf("Produtos\n");
        

        remove_Catalogo_Clientes(clientes);
        remove_Catalogo_Produtos(produtos);
        free_Faturacao(faturacao);

    return 0;


}


/*fazer import dos dados do ficheiro, fazer read do ficheiro, fazer clientes, produtos e valida vendas neste modulo*/