#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

struct datos{
        char nombre[20];
        char apellido[20];
        int edad;
        long telefono;
        char mail[50];
    };

    // Estructura autorreferenciada: Lista
    struct lista{
        struct datos persona;
        struct lista *lazo;
    };

    // Para el archivo de organizacion directa
    struct o{
        unsigned int id;
        char nombre[20];
        char apellido[20];
        int edad;
        long telefono;
        char mail[50];
    };



int main()
{

    FILE *archivo;

    struct datos bf;

    struct o orden;


    struct lista *aux;
    struct lista *primero;
    struct lista *r;
    struct lista *ultimo;

    primero = ultimo = NULL;

    unsigned int contador = 0;

    if((archivo = fopen("contactos.dat","rb")) == NULL){
    printf("\a\nNo se pudo abrir archivo 'contactos.dat'\n");
    exit(-1);
    }

    // Listado condicionado

    fread(&bf, sizeof(struct datos), 1, archivo);
    while(!feof(archivo)){

        aux = (struct lista *)malloc(sizeof(struct lista));
        if(aux == NULL){
            printf("\nNo hay memoria disponible.\n");
            exit(-1);
        }
        aux->persona = bf;
        aux->lazo = NULL;
        if(primero == NULL || strcasecmp(primero->persona.apellido, aux->persona.apellido) > 0){
            aux->lazo = primero;
            primero = aux;
        }else{
            r = primero;
            while(r->lazo != NULL && strcasecmp(r->lazo->persona.apellido, aux->persona.apellido) < 0)
                r = r->lazo;
            aux->lazo = r->lazo;
            r->lazo = aux;

        }
        fread(&bf, sizeof(struct datos), 1, archivo);

    }

    fclose(archivo);



    if((archivo = fopen("contactos_ordenados.dat", "wb")) == NULL){
        printf("\nNo se pudo crear el archivo \"contactos_ordenados.dat\".\n");
        exit(-1);
    }

    printf("\nLista ordenada por apellido (se guarda en \"contactos_ordenados.dat\"):\n");

    do{
        contador ++;
        orden.id = contador;
        strcpy(orden.apellido, primero->persona.apellido);
        strcpy(orden.nombre, primero->persona.nombre);
        orden.edad = primero->persona.edad;
        orden.telefono = primero->persona.telefono;
        strcpy(orden.mail, primero->persona.mail);
        printf("\n%u - %s %-10s\t", orden.id, primero->persona.apellido, primero->persona.nombre);
        printf("Edad: %d\tTel: %ld\t\tMail: %s\n\n", primero->persona.edad, primero->persona.telefono, primero->persona.mail);
        fwrite(&orden, sizeof(struct o), 1, archivo);
        aux = primero;
        primero = primero->lazo;
        free(aux);

    }while(primero != NULL);

    fclose(archivo);
   
    return 0;
}


