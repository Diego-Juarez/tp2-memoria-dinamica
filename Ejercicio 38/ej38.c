#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.141593

struct cola{
    char muestra;
    struct cola *siguiente;
    struct cola *anterior;
};



int main()
{
    struct cola *p;
    struct cola *u;
    struct cola *aux;
    p = NULL;
    u = NULL;
    aux = NULL;

    int i;
    int contador = 1;

    
    printf("\nValores de 1/4 de ciclo:\n");

    for(i=0; i<91; i+=5){

        aux = (struct cola *)malloc(sizeof(struct cola));
        aux->muestra = (char)((double)127.001*sin((double)i*pi/180));
        aux->siguiente = NULL;

        printf("\n Muestra %02d - Grados [0:90]: %3d", contador++, (int)aux->muestra);

        if(p == NULL){
            p = aux;
            u = aux;
            u->anterior = p;
        }else{
            u->siguiente = aux;
            aux->anterior = u;
            u = aux;
        }
    }

    printf("\n");
    printf("\nValores de 2/4 de ciclo:\n");
    contador = 19;
    aux = u;
    printf("\n Muestra %02d - Grados [90:180]: %3d", contador--, (int)aux->muestra);

    do{
        aux = aux->anterior;
        printf("\n Muestra %02d - Grados [90:180]: %3d", contador--, (int)aux->muestra);

    }while(aux != p);

    printf("\n");
    printf("\nValores de 3/4 de ciclo:\n");
    contador = 1;
    aux = p;
    printf("\n Muestra %02d - Grados [180:270]: %4d", contador++, 0*((aux->muestra) | (1 << 7)) );

    do{
        aux = aux->siguiente;
        printf("\n Muestra %02d - Grados [180:270]: %4d", contador++, (-1* aux->muestra) | (1 << 7));

    }while(aux != u);

    printf("\n");
    printf("\nValores de 4/4 de ciclo:\n");
    contador = 19;
    aux = u;
    printf("\n Muestra %02d - Grados [90:180]: %4d", contador--, (-1* aux->muestra) | (1 << 7));

    do{
        aux = aux->anterior;
        printf("\n Muestra %02d - Grados [90:180]: %4d", contador--, (-1* aux->muestra) | (1 << 7));

    }while(aux ->anterior != p);

    aux = aux->anterior;
    printf("\n Muestra %02d - Grados [90:180]: %4d", contador--, 0*((aux->muestra) | (1 << 7)));
    printf("\n");

    return 0;
}
