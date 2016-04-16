#include "./headers/heap.h"

#define PAI_P(i) heap->produto[(i-1)/2]
#define PAI_Q(i) heap->quantidade[(i-1)/2]
#define PAI_C(i) heap->custo[(i-1)/2]
#define FILHO_E_P(i) heap->produto[i*2+1]
#define FILHO_E_Q(i) heap->quantidade[i*2+1]
#define FILHO_E_C(i) heap->custo[i*2+1]
#define FILHO_D_P(i) heap->produto[i*2+2]
#define FILHO_D_Q(i) heap->quantidade[i*2+2]
#define FILHO_D_C(i) heap->custo[i*2+2]
#define NODO_P(i) heap->produto[i]
#define NODO_Q(i) heap->quantidade[i]
#define NODO_C(i) heap->custo[i]
#define PAI(i) (i-1)/2
#define ESQUERDO(i) 2*i+1
#define DIREITO(i) 2*i+2





struct heap {
    int tamanho;
    int pos; 
    int *quantidade;
    float *custo;
    char **produto;
};


Heap initHeap(){
    Heap heap = malloc(sizeof(struct heap));
    heap->tamanho = 5;
    heap->pos=0;
    heap->quantidade=malloc(sizeof(int)*5);
    heap->custo=malloc(sizeof(float)*5);
    heap->produto=malloc(sizeof(char *)*5);
    return heap;
}

Heap heap_push(Heap heap,char *produto,int quantidade, float custo){
    if(heap->tamanho==(heap->pos-1)){
        heap->tamanho = heap->tamanho*2;
        heap->quantidade = realloc(heap->quantidade,heap->tamanho *sizeof(int *));
        heap->custo = realloc(heap->custo,heap->tamanho *sizeof(int *));
        heap->produto = realloc(heap->produto,heap->tamanho *sizeof(int *));
    }
    
    NODO_Q(heap->pos)=quantidade;
    NODO_C(heap->pos)=custo;
    strcpy(heap->produto[heap->pos],produto);
    heap=bubbleUp(heap,heap->pos);
    heap->pos++;

    return heap;

}

char *heap_pop(Heap heap){
    if(heap->pos==0) return 0;
    char *string=NODO_P(0);
    heap->pos--;
    NODO_P(0)=NODO_P(heap->pos);
    NODO_Q(0)=NODO_Q(heap->pos);
    NODO_C(0)=NODO_C(heap->pos);
    heap=bubbleDown(heap,heap->pos);
    return string;
}


Heap bubbleDown(Heap heap,int n){
    int i,m;
    i=0;

    while(ESQUERDO(i)<n){
        if(DIREITO(i)<n)
            m=FILHO_E_Q(i)>FILHO_D_Q(i)? ESQUERDO(i) :DIREITO(i);
        else m=ESQUERDO(i);

        if(NODO_Q(i)<NODO_Q(m)){ 
            heap=swap(heap,i,m);
            i=m;
        }
        else return heap;

    }
    return heap;
}


Heap bubbleUp(Heap heap,int i){
    while(i>0 && PAI_Q(i)>NODO_Q(i)){
        heap=swap(heap,i,(i-1)/2);
        i=(i-1)/2;
    }
    return heap;
}


Heap swap(Heap heap,int n1,int n2){
    int n=NODO_Q(n1);
    float x=NODO_C(n1);
    char *string=NODO_P(n1);

    NODO_Q(n1)=NODO_Q(n2);
    NODO_C(n1)=NODO_C(n2);
    strcpy(NODO_P(n1),NODO_P(n2));

    NODO_Q(n2)=n;
    NODO_C(n2)=x;
    strcpy(NODO_P(n2),string);

    return heap;
}



int heap_count(Heap heap){
    return heap->pos;
}

void heap_free(Heap heap){
    free(heap->quantidade);
    free(heap->custo);
    free(heap->produto);
    free(heap);
}


/*
Heap avlToHeap(NODO avl,Heap heap){
    if(avl==NULL) return heap;
    push(heap,avl->produto,avl->quantidade,avl->custo);
    heap=avlToHeap(avl->left,heap);
    heap=avlToHeap(avl->right,heap);
    return heap;
}*/