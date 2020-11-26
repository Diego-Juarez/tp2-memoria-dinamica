#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct d{
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
};

struct lista{
    struct d datos;
    struct lista *lazo;
};

// Para el archivo de organizacion directa
struct o{
    unsigned int id;
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
};



int main()
{
    FILE *archivo;

    struct o orden;


    struct lista *aux;
    struct lista *p;
    struct lista *r;
    struct lista *u;

    p = u = NULL;

    unsigned int contador = 0;

    int opc;

    unsigned int pot;

// Carga de datos en lista ordenada

    do{
        printf("\n*** Carga de datos ***:\n");
        aux = (struct lista*)malloc(sizeof(struct lista));
        printf("\nDescripcion: ");
        scanf("%s", aux->datos.desc);
        printf("\nPotencia [0 - 255]: ");
        scanf("%d", &pot);
        aux->datos.potencia = (unsigned char)pot;
   
        aux->datos.estado = aux->datos.potencia * (int)aux->datos.desc[0];


        if(p == NULL || p->datos.potencia < aux->datos.potencia){
            aux->lazo = p;
            p = aux;
        }else{
        r = p;
        while(r->lazo != NULL && r->lazo->datos.potencia > aux->datos.potencia)
            r = r->lazo;
        aux->lazo = r->lazo;
        r->lazo = aux;
        }

        printf("\n¿Sigue? (sale con cero)");
        scanf("%d", &opc);
    }while(opc != 0);

    // Se busca crear archivo potencia.dat y mostrar lista ordenada
    if((archivo = fopen("potencia.dat", "wb")) == NULL){
        printf("\nNo se pudo crear el archivo \"potencia.dat\".\n");
        exit(-1);
    }

    printf("\nLista ordenada por valor de potencia (se guarda en \"potencia.dat\"):\n");

    do{
        contador ++;
        orden.id = contador;
        strcpy(orden.desc, p->datos.desc);
        orden.potencia = p->datos.potencia;
        orden.estado = p->datos.estado;
        printf("\n%u - Descripcion: %-10s\t Potencia: %d\t Estado: %d\t\n", orden.id, p->datos.desc, p->datos.potencia, p->datos.estado);

        fwrite(&orden, sizeof(struct o), 1, archivo);
        aux = p;
        p = p->lazo;
        free(aux);

    }while(p != NULL);

    fclose(archivo);
 
    return 0;
}
