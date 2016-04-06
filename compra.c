#include "compra.h"

#define MAXBUFFERCLIENTES 32


char *getProd(Compra compra){
    int i;

    char *new;

    for(i=0;i!=6;i++)new[i]=compra[i];


    return new;
}


float getPreco(Compra compra){
    int i,j;

    for(i=0,j=0;i!=1;j++)
        if(compra[j]==' ') i++;

    char new[6];
    j++;
    for(i=j;i!=j+5;i++)new[i]=compra[i];

    new[i]='\0';
    float price=atof(new);

    return price;
}


int getQuantidade(Compra compra){
    int i,j;

    for(i=0,j=0;i!=2;j++)
        if(compra[j]==' ') i++;

    char new[6];
    j++;
    for(i=j;i!=5;i++)new[i]=compra[i];

    new[i]='\0';
    int quant=atoi(new);

    return quant;
}



char getTipo(Compra compra){
    int i,j;

    for(i=0,j=0;j!=3;j++)
        if(compra[j]==' ') i++;

    char new;
    j++;
    new=compra[i];

    return new;
}

char *getCli(Compra compra){
    int i,j;

    for(i=0,j=0;i!=4;j++)
        if(compra[j]==' ') i++;

    char *new;
    j++;
    for(i=j;i!=j+5;i++)new[i]=compra[i];

    return new;
}

int getMes(Compra compra){
    int i,j;

    for(i=0,j=0;i!=5;j++)
        if(compra[j]==' ') i++;

    char new[3];
    j++;
    for(i=j;i!=j+2;i++)new[i]=compra[i];

    new[i]='\0';
    int mes=atoi(new);

    return mes;
}


int getFilial(Compra compra){
    int new;
    int i,j;

    for(i=0,j=0;i!=6;j++)
        if(compra[j]==' ') i++;
    j++;
    new=compra[j]-'0';

    return new;
}


