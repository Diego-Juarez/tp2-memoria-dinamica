#include <stdio.h>
#include <stdlib.h>

int main()
{

    struct datos{
        char nombre[20];
        char apellido[20];
        int edad;
        long telefono;
        char mail[50];
    };

    // Estructura autorreferenciada: Pila
    struct pila{
        struct datos persona;
        struct pila *lazo;
    };

    //Puntero al primer elemento de la pila y puntero auxiliar

    struct pila *aux;
    struct pila *primero = NULL;


    // Para las opciones de eleccion del usuario
    int opcion;

    // Para el archivo de organizacion secuencial
    FILE *archivo;

    struct datos bf;



    printf("\n*** Ingreso de datos de contacto ***\n");
    if((archivo = fopen("contactos.dat","wb")) == NULL){
        printf("\n\aNo se pudo crear el archivo \"contactos.dat\"");
        exit(-1);
    }

    do{
        aux = (struct pila *) malloc(sizeof(struct pila));
        if(aux == NULL){
            printf("\n\aError en la reserva de espacio de memoria\n");
            exit(-1);
        }else{
            printf("\nNombre: ");
            scanf("%s", aux->persona.nombre);
            printf("\nApellido: ");
            scanf("%s", aux->persona.apellido);
            printf("\nEdad: ");
            scanf("%d", &aux->persona.edad);
            printf("\nTelefono: ");
            scanf("%ld", &aux->persona.telefono);
            printf("\nMail: ");
            scanf("%s", aux->persona.mail);
            aux->lazo = primero;
            primero = aux;

            if(aux->persona.edad > 21){
                fwrite(&aux->persona,sizeof(struct datos),1,archivo);
                primero = primero->lazo;
                free(aux);
            }
            do{
                printf("\nFinalizar carga de datos - Pulse \'0\'\tContinuar- Pulse \'1\'\n");
                scanf("%d", &opcion);
            }while(opcion != 0 && opcion != 1);
        }

    }while(opcion != 0);

    fclose(archivo);

    printf("\nDatos de las personas mayores de 21 años que se registraron:\n");
    if((archivo = fopen("contactos.dat","rb")) == NULL){
        printf("\n\aNo se pudo abrir el archivo \"contactos.dat\"");
        exit(-1);
    }
    else{
        fread(&bf,sizeof(struct datos),1,archivo);
		while(!feof(archivo)){
            printf("\nNombre: %s", bf.nombre);
            printf("\nApellido: %s", bf.apellido);
            printf("\nEdad: %d", bf.edad);
            printf("\nTelefono: %ld", bf.telefono);
            printf("\nMail: %s\n", bf.mail);
            fread(&bf,sizeof(struct datos),1,archivo);
        }
    }
    fclose(archivo);
    return 0;
}
