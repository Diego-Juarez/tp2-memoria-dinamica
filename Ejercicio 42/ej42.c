#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
        long partNumber;
        long serialNumber;
        char descripcion[40];
        char ubicacion[100];
    }repuestos_t;

    struct cola{
        repuestos_t repuesto;
        struct cola *siguiente;
        struct cola *anterior;
    };



int main()
{

    FILE *archivo;
    repuestos_t reps;

    FILE *auxiliar;
    repuestos_t nuevo;

    struct cola *p;
    struct cola *u;
    struct cola *aux;
    p = NULL;
    u = NULL;
    aux = NULL;


    if((archivo = fopen("stock.dat","rb")) == NULL){
        printf("\n\aNo se pudo abrir el archivo \"stock.dat\"");
        exit(-1);
    }
    else{
        if((auxiliar = fopen("nuevo.dat","wb")) == NULL){
            printf("\n\aNo se pudo crear el archivo auxiliar para baja fisica.\n");
            exit(-1);
        }
        fread(&reps,sizeof(repuestos_t),1,archivo);
		while(!feof(archivo)){
            if(reps.partNumber == 1234 && reps.serialNumber & (1 << 3) && reps.serialNumber & (1 << 5)){
                aux = (struct cola*)malloc(sizeof(struct cola));
                aux->repuesto.partNumber = reps.partNumber;
                aux->repuesto.serialNumber = reps.serialNumber;
                strcpy(aux->repuesto.descripcion, reps.descripcion);
                strcpy(aux->repuesto.ubicacion, reps.ubicacion);

                aux->siguiente = NULL;
                if(p == NULL){
                    p = aux;
                    u = aux;
                    u->anterior = p;
                }else{
                    u->siguiente = aux;
                    aux->anterior = u;
                    u = aux;
                }

            }else{
                nuevo.partNumber = reps.partNumber;
                nuevo.serialNumber = reps.serialNumber;
                strcpy(nuevo.descripcion, reps.descripcion);
                strcpy(nuevo.ubicacion, reps.ubicacion);
                fwrite(&nuevo, sizeof(repuestos_t), 1, auxiliar);
            }
            fread(&reps,sizeof(repuestos_t),1,archivo);
        }
    }

    fclose(archivo);
    fclose(auxiliar);


    if(p == NULL){
        printf("\nNo se encontraron repuestos fallados.\n");
        exit(0);
    }

    rename("nuevo.dat","stock.dat");
    printf("\nSe ha efectuado la baja fisica de los repuestos fallados\n");

    //Muestro archivo no se pide en enunciado
    printf("\nNuevo stock.dat con repuestos sanos:\n");
    archivo = fopen("stock.dat","rb");
    fread(&reps,sizeof(repuestos_t),1,archivo);
		while(!feof(archivo)){
            printf("\nPart Number: %ld", reps.partNumber);
            printf("\nSerial Number: %ld", reps.serialNumber);
            printf("\nUbicacion: %s", reps.ubicacion);
            printf("\nDescripcion: %s\n", reps.descripcion);
            fread(&reps,sizeof(repuestos_t),1,archivo);
        }

    fclose(archivo);


    if((auxiliar = fopen("fallados.dat","wb")) == NULL){
        printf("\n\aNo se pudo crear el archivo \"fallados.dat\"");
        exit(-1);
    }

    aux = u;
    p->anterior = NULL;

    do{
        nuevo.partNumber = aux->repuesto.partNumber;
        nuevo.serialNumber = aux->repuesto.serialNumber;
        strcpy(nuevo.descripcion, aux->repuesto.descripcion);
        strcpy(nuevo.ubicacion, aux->repuesto.ubicacion);
        fwrite(&nuevo, sizeof(repuestos_t), 1, auxiliar);
        aux = aux->anterior;

    }while(aux != NULL);

    fclose(auxiliar);

    printf("\nSe ha generado el archivo \"fallados.dat\" con los repuestos fallados.\n");

    auxiliar = fopen("fallados.dat","rb");
    fread(&nuevo,sizeof(repuestos_t),1,auxiliar);
		while(!feof(auxiliar)){
            printf("\nPart Number: %ld", nuevo.partNumber);
            printf("\nSerial Number: %ld", nuevo.serialNumber);
            printf("\nUbicacion: %s", nuevo.ubicacion);
            printf("\nDescripcion: %s\n", nuevo.descripcion);
            fread(&nuevo,sizeof(repuestos_t),1,auxiliar);
        }

    fclose(auxiliar);

    return 0;
}
