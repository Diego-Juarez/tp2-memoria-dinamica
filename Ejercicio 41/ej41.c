#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct{
        long partNumber;
        long serialNumber;
        char descripcion[40];
        char ubicacion[100];
    }repuestos_t;

    struct lista{
        repuestos_t repuesto;
        struct lista *lazo;
    };


int main()
{
    struct lista *aux;
    struct lista *p;
    struct lista *r;
    struct lista *u;

    p = u = NULL;

    int opcion;

    // Para generar archivo stock.dat
    FILE *archivo;
    repuestos_t articulo;


    printf("\n*** Carga de datos de los repuestos ***\n");
    do{
        aux = (struct lista *)malloc(sizeof(struct lista));
        if(aux == NULL){
            printf("\nNo hay memoria disponible.\n");
            exit(-1);
        }

        printf("\nPart Number: ");
        scanf("%ld", &aux->repuesto.partNumber);
        printf("\nSerial Number: ");
        scanf("%ld", &aux->repuesto.serialNumber);
        printf("\nDescripcion: ");
        scanf("%s", aux->repuesto.descripcion);
        printf("\nUbicacion: ");
        scanf("%s", aux->repuesto.ubicacion);



        // Ordenamiento alfabetico por campo descripcion
        aux->lazo = NULL;
        if(p == NULL || strcasecmp(p->repuesto.descripcion, aux->repuesto.descripcion) > 0){
            aux->lazo = p;
            p = aux;
        }else{
            r = p;
            while(r->lazo != NULL && strcasecmp(r->lazo->repuesto.descripcion, aux->repuesto.descripcion) < 0)
                r = r->lazo;
            aux->lazo = r->lazo;
            r->lazo = aux;
        }

        do{
            printf("\nFinalizar carga - Pulse \'0\'\tContinuar- Pulse \'1\'\n");
            scanf("%d", &opcion);
        }while(opcion != 0 && opcion != 1);

    }while(opcion != 0);


    // Se genera archivo de stock de repuestos
    if((archivo = fopen("stock.dat","wb")) == NULL){
        printf("\n\aNo se pudo crear el archivo \"stock.dat\"");
        exit(-1);
    }

    r = p;

    do{
        articulo.partNumber = r->repuesto.partNumber;
        articulo.serialNumber = r->repuesto.serialNumber;
        strcpy(articulo.descripcion, r->repuesto.descripcion);
        strcpy(articulo.ubicacion, r->repuesto.ubicacion);
        fwrite(&articulo, sizeof(repuestos_t), 1, archivo);
        aux = r;
        r = r->lazo;

    }while(r != NULL);

    fclose(archivo);

    printf("\nSe ha generado el archivo \"stock.dat\".\n");

    /*
    //Muestro archivo no se pide en enunciado
    archivo = fopen("stock.dat","rb");
    fread(&articulo,sizeof(repuestos_t),1,archivo);
		while(!feof(archivo)){
            printf("\nPart Number: %ld", articulo.partNumber);
            printf("\nSerial Number: %ld", articulo.serialNumber);
            printf("\nUbicacion: %s", articulo.ubicacion);
            printf("\nDescripcion: %s\n", articulo.descripcion);
            fread(&articulo,sizeof(repuestos_t),1,archivo);
        }

    fclose(archivo);
    */

    // Se muestra lista ordenada
    printf("\nRepuestos (lista ordenada alfabeticamente por descripcion):\n");

    do{
        printf("\nDescripcion: %s", p->repuesto.descripcion);
        printf("\nPart Number: %ld", p->repuesto.partNumber);
        printf("\nSerial Number: %ld", p->repuesto.serialNumber);
        printf("\nUbicacion: %s\n", p->repuesto.ubicacion);
        aux = p;
        p = p->lazo;
        free(aux);
    }while(p != NULL);

    free(p);

    return 0;
}
