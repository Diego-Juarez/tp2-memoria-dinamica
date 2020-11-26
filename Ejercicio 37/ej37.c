#include <stdio.h>
#include <stdlib.h>

struct d{
        long clave;         // Clave o Id del registro
        char d[30];         // Descripcion
        unsigned char tipo; // Tipo de datos como entero sin signo
        char b;             // 'A':Alta 'B':Baja
    };

    struct pila{
        long clave;
        int posicion;
        struct pila *lazo;
    };

    struct pila * apilar(long clave, struct pila *puntero);

int main()
{
    struct d datos;
    struct pila *aux;
    struct pila *primero;
    primero = NULL;

    FILE *archivo;

    int opcion;

    unsigned int tipo;

    struct d bf;

    long clave;


    if((archivo = fopen("datos.dat","rb")) == NULL){
        printf("\n\aNo se pudo abrir el archivo \"datos.dat\".\n");

        do{
            printf("\nPara crear el archivo e ingresar datos, pulse \'1\' \nPara salir del programa, pulse \'0\'\n");
            scanf("%d", &opcion);
        }while(opcion != 0 && opcion != 1);

            if(opcion == 1){
                printf("\n*** Ingreso de datos ***\n");
                if((archivo = fopen("datos.dat","wb")) == NULL){
                printf("\n\aNo se pudo crear el archivo \"datos.dat\"..");
                exit(-1);
                }
                do{
                    printf("\nClave: ");
                    scanf("%ld", &datos.clave);
                    printf("\nDescripcion: ");
                    scanf("%s", datos.d);
                    printf("\nTipo [0 - 255]: ");
                    scanf("%u", &tipo);
                    datos.tipo = (unsigned char)(tipo);
                    datos.b = 'A';

                    fwrite(&datos,sizeof(struct d),1,archivo);

                    do{
                        printf("\nFinalizar carga de datos - Pulse \'0\'\tContinuar- Pulse \'1\'\n");
                        scanf("%d", &opcion);
                    }while(opcion != 0 && opcion != 1);


                }while(opcion != 0);
                fclose(archivo);
            }else{

                exit(-1);
            }
    }

    do{
        printf("\nPara realizar busquedas con apilamiento condicional, pulse \'1\'\nPara salir del programa, pulse \'0\'\n");
        scanf("%d", &opcion);
    }while(opcion != 0 && opcion != 1);

    if(opcion == 1){


        do{
            printf("\nIngrese la clave buscada: ");
            scanf("%ld", &clave);
            primero = apilar(clave, primero);
            printf("\nFinalizar las busquedas - Pulse \'0\'\tBuscar otra clave - Pulse \'1\'\n");
            scanf("%d", &opcion);
        }while(opcion != 0);

        if(primero == NULL){
            free(primero);
            exit(0);

        }


        printf("\nDescripciones del archivo que corresponden a las claves apiladas:\n");
        if((archivo = fopen("datos.dat","rb")) == NULL){
            printf("\n\aNo se pudo abrir el archivo \"datos.dat\"\n");
            return 0;
            }
        do{
            fseek(archivo, (long)(primero->posicion - 1) * sizeof(struct d),0);
            fread(&bf,sizeof(struct d),1,archivo);
            printf("\nDescripcion: %s\n", bf.d);
            aux = primero;
            primero = primero->lazo;
            free(aux);
        }while(primero != NULL);

        fclose(archivo);

    }else{
        exit(0);
    }



    return 0;

}


    struct pila * apilar(long clave, struct pila *puntero){

        struct pila *auxiliar;
        struct d data;
        int contador = 0;
        FILE *bf;

        if((bf = fopen("datos.dat","rb")) == NULL)
            printf("\n\aNo se pudo abrir el archivo \"datos.dat\"\n");
        fread(&data,sizeof(struct d), 1, bf);
                while(!feof(bf)){
                    contador ++;
                   
                    if(clave == data.clave){
                        if((unsigned int)data.tipo & (1<<4)){
                            auxiliar = (struct pila *)malloc(sizeof(struct pila));
                            auxiliar->clave = data.clave;
                            auxiliar->posicion = contador;
                            auxiliar->lazo = puntero;
                            puntero = auxiliar;
                            printf("\nClave y posicion apilados.\n");
                            fclose(bf);
                            return puntero;
                        }
                        fclose(bf);
                        printf("\nNo se apila nada. El campo 'tipo' no tiene el bit 4 con valor 1.\n");
                        return puntero;
                    }
                    fread(&data,sizeof(struct d), 1, bf);
                }
                fclose(bf);
                printf("\nRegistro no encontrado.\n");
                return puntero;
    }


