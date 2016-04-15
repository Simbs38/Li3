#include "./headers/heap.h"

#define PAI_P(i) heap->produto[i/2]
#define PAI_Q(i) heap->quantidade[i/2]
#define PAI_C(i) heap->custo[i/2]
#define FILHO_E_P(i) heap->produto[i*2]
#define FILHO_E_Q(i) heap->quantidade[i*2]
#define FILHO_E_C(i) heap->custo[i*2]
#define FILHO_D_P(i) heap->produto[i*2+1]
#define FILHO_D_Q(i) heap->quantidade[i*2+1]
#define FILHO_D_C(i) heap->custo[i*2+1]
#





struct heap {
    int tamanho;
    int pos; 
    int *quantidade;
    float *custo;
    char *produto;
};


Heap initHeap(){
    Heap heap = malloc(sizeof(struct heap));
    heap->heap_tamanho = 5;
    heap->pos=0;
    heap->quantidade=malloc(sizeof(int)*5);
    heap->custo=malloc(sizeof(float)*5);
    heap->produto=malloc(sizeof(char *)*5);
    return heap;
}

Heap heap_push(Heap heap,char *produto,int quantidade, float custo){
    if(heap->heap_tamanho==(heap->pos-1)){
        heap->heap_tamanho = heap->heap_tamanho*2;
        heap->quantidade = realloc(node->quantidade,node->heap_tamanho *sizeof(int *));
        heap->custo = realloc(node->custo,node->heap_tamanho *sizeof(int *));
        heap->produto = realloc(node->produto,node->heap_tamanho *sizeof(int *));
    }
    
    heap->quantidade[heap->pos]=quantidade;
    strcpy(heap->produto[heap->pos],produto);
    heap->custo[heap->pos]=custo;
    heap->pos++;

    return heap;

}

char *heap_pop(Heap heap){
    char *string=heap->produto[0];

    /*fazer join e bubble up*/

    return string;
}


Heap bubbleUp(Heap heap);


Heap heap_join(Heap heap1,Heap heap2);

Heap heap_clone(Heap heap);

Boolean heap_look(Heap heap,char *produto);

int heap_count(Heap heap);

void heap_free(Heap heap);
