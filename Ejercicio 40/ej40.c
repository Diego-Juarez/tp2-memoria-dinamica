#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    struct d{
        char desc[60];
        unsigned char potencia;
        unsigned int estado;
    };

    struct pila{
        unsigned char pot;
        struct pila *lazo;
    };

// Para el archivo de organizacion directa
    struct o{
        unsigned int id;
        char desc[60];
        unsigned char potencia;
        unsigned int estado;
    };


    struct pila *funcion(FILE *, unsigned int, struct pila *);



int main()
{
    FILE *archivo;

    struct pila *aux;
    struct pila *primero;
    primero = NULL;

    unsigned int opc;


    //para ver salida.dat
    struct d regs;

    if((archivo = fopen("potencia.dat", "rb+")) == NULL){
        printf("\a\nNo se pudo abrir el archivo \"potencia.dat\".\n");
        exit(-1);
    }


    do{
        printf("\nIngrese clave del registro: ");
        scanf("%u", &opc);

        primero = funcion(archivo, opc, primero);
        printf("\nIngresar otra clave: 1\t\tSalir: 0 ");
        scanf("%u", &opc);
    }while(opc != 0);

    fclose(archivo);

    //Se muestra pila - no se pide en enunciado

    if(primero != NULL){
        printf("\nPotencias apiladas (bits 0 y 2 encendidos en campo estado):\n");

        do{
            printf("\nPotencia: %d\n", primero->pot);
            aux = primero;
            primero = primero->lazo;
            free(aux);
        }while(primero != NULL);
    }else{
        printf("\nNo se apilo ninguna potencia.\n");
    }


    free(primero);



    // Se imprime registros salida.dat - no se pide en enunciado

    printf("\nRegistros agregados al archivo \"salida.dat\":\n");
    if ((archivo = fopen("salida.dat", "rb")) == NULL){
        printf("\n--- No se han agregado registros al archivo \"salida.dat\" ---\n");
        exit(0);
    }else{
        fread(&regs, sizeof(struct d), 1, archivo);
        while(!feof(archivo)){
        printf("\nDescripcion: %-10s\t Potencia: %d\t Estado: %d\t\n", regs.desc, regs.potencia, regs.estado);
        fread(&regs, sizeof(struct d), 1, archivo);
        }
    }

    fclose(archivo);

    if(remove("salida.dat")){
        printf("\nError al eliminar el archivo \"salida.dat\".\n");
        exit(-1);
    }else{
        printf("\nSe ha eliminado el archivo \"salida.dat\" de esta sesion.\n");
    }

    return 0;
}


    struct pila *funcion(FILE * archivo, unsigned int id, struct pila *cima){

        
        //Para inversion de palabra
        char cadinv[60];
        char *b;
        char *a;

        struct o orden;
        struct d regs;
        struct pila *aux;
        struct pila *p;
        p = cima;

        FILE *bf;
        
        fseek(archivo, (long)(id - 1)* sizeof(struct o), 0);
        fread(&orden, sizeof(struct o), 1, archivo);

        if(orden.id == id){

        b = &orden.desc[0];
        a = cadinv;
        while(*b) b++;
        b--;
        while(b != &orden.desc[0]){
            *a = *b;
            b--;
            a++;
        }
        *a = *b;
        a++;
        *a = '\0';
        printf("\nDescripcion invertida: %s", cadinv);
        printf("\n");



        //printf("\nCampo estado antes del cambio del bit 3 = %u\n", orden.estado);


        orden.estado = orden.estado ^ (1 << 3);

        fseek(archivo, (long)(-1)* sizeof(struct o), 1);
        fwrite(&orden, sizeof(struct o), 1, archivo);


        fseek(archivo, (long)(-1)* sizeof(struct o), 1);
        fread(&orden, sizeof(struct o), 1, archivo);

        //printf("\nCampo estado luego del cambio del bit 3 = %u\n", orden.estado);

        if(orden.estado & (1 << 0) && orden.estado & (1 << 2)){
            aux = (struct pila *)malloc(sizeof(struct pila));
            aux->pot = orden.potencia;
            aux->lazo = p;
            p = aux;

        }else{

            if((bf = fopen("salida.dat", "ab")) == NULL){
                bf = fopen("salida.dat", "wb");
            }

            strcpy(regs.desc, orden.desc);
            regs.potencia = orden.potencia;
            regs.estado = orden.estado;
            fwrite(&regs, sizeof(struct d), 1, bf);
            fclose(bf);

        }

        }else{
            printf("\nNo se ha registrado esa clave.\n");
        }

        return p;


    }


