#include <stdio.h>
#include <stdlib.h>
#include <string.h>


    // Cambio el nombre de repuestos_t por ordenes_t para poder incluir otro tipo con aquel nombre
    typedef struct{
       long numeroDeOrden;
       char cliente[40];
       char descripciondeFalla[200];
       char modelo[65];
       char fecha[10];
       char hora[10];
    }ordenes_t;

    struct lista{
        ordenes_t trabajo;
        struct lista *lazo;
    };

    struct pila{
        ordenes_t orden;
        struct pila *lazo;
    };


    // Para ejercicios 44 y 45
    typedef struct{
       long partNumber;
       long serialNumber;
       char descripcion[40];
       char ubicacion[100];
    }repuestos_t;

    typedef struct{
        repuestos_t repuesto;
        int cantidad;
    }extraccionRepuestos_t;

    struct lis2{
        extraccionRepuestos_t ext;
        struct lis2 *lazo;
    };


    // Para ej 45
    struct cola{
        extraccionRepuestos_t falta;
        struct cola *lazo;
    };




int main()
{
    FILE *archivo;
    ordenes_t ordenes;
    int opc = 0;

    struct lista *aux;
    struct lista *primero;
    struct lista *r;

    primero = NULL;

    struct pila *auxiliar;
    struct pila *top = NULL;
    struct pila *recorrido;



    // Para ej 44
    struct lis2 *aux2;
    struct lis2 *p;
    struct lis2 *loc;

    p = NULL;

    // Para ej 45
    struct cola *aux3;
    struct cola *head;
    struct cola *tail;

    head = NULL;

    FILE *viejo;
    FILE *nuevo;
    repuestos_t reps;



    // EJERCICIO 43

    archivo = fopen("ordenes.dat", "wb");
    // Carga de ordenes de trabajo en archivo secuencial
    // No puede ponerse el mismo horario o un horario anterior para la misma fecha
    printf("\n*** Carga de ordenes de trabajo ***\n");

    do{
        printf("\nNum. de Orden: ");
        scanf("%ld", &ordenes.numeroDeOrden);
        printf("\nCliente: ");
        scanf("%s", ordenes.cliente);
        printf("\nDescripcion de falla: ");
        scanf("%s", ordenes.descripciondeFalla);
        printf("\nModelo: ");
        scanf("%s", ordenes.modelo);
        printf("\nFecha (aaaammdd): ");
        scanf("%s", ordenes.fecha);
        printf("\nHora (hhmmss): ");
        scanf("%s", ordenes.hora);

        fwrite(&ordenes, sizeof(ordenes_t), 1, archivo);

        printf("\nDesea seguir? Sale con 0\n");
        scanf("%d", &opc);
    }while(opc != 0);
    fclose(archivo);


    // Se armara una lista ordenada antes de preparar la pila

    if((archivo = fopen("ordenes.dat","rb")) == NULL){
    printf("\a\nNo se pudo abrir archivo 'ordenes.dat'\n");
    exit(-1);
    }

    fread(&ordenes, sizeof(ordenes_t), 1, archivo);
        while(!feof(archivo)){

            aux = (struct lista *)malloc(sizeof(struct lista));
            if(aux == NULL){
                printf("\nNo hay memoria disponible.\n");
                exit(-1);
            }

            aux->trabajo = ordenes;
            aux->lazo = NULL;

            if(primero == NULL){
                aux->lazo = primero;
                primero = aux;
            }

            if(atoi(primero->trabajo.fecha) < atoi(aux->trabajo.fecha)){
                aux->lazo = primero;
                primero = aux;
            }else{

                if(atoi(primero->trabajo.fecha) == atoi(aux->trabajo.fecha)){
                    if(atoi(primero->trabajo.hora) < atoi(aux->trabajo.hora)){
                        aux->lazo = primero;
                        primero = aux;
                    }else{

                        r = primero;

                        while(r->lazo != NULL && atoi(r->lazo->trabajo.hora) > atoi(aux->trabajo.hora)){
                            r = r->lazo;
                        aux->lazo = r->lazo;
                        r->lazo = aux;
                        }
                    }

                }else{

                    r = primero;

                    while(r->lazo != NULL && atoi(r->lazo->trabajo.fecha) > atoi(aux->trabajo.fecha))
                        r = r->lazo;
                    if(r->lazo == NULL || atoi(r->lazo->trabajo.fecha) != atoi(aux->trabajo.fecha)){
                        aux->lazo = r->lazo;
                        r->lazo = aux;
                    }else{
                            while(r->lazo != NULL && atoi(r->lazo->trabajo.hora) > atoi(aux->trabajo.hora))
                                r = r->lazo;
                            aux->lazo = r->lazo;
                            r->lazo = aux;
                    }

                }

            }

            fread(&ordenes, sizeof(ordenes_t), 1, archivo);
        }

        fclose(archivo);


    // Se hace la pila con la condicion pedida en el enunciado
    r = primero;

    do{
        auxiliar = (struct pila *) malloc(sizeof(struct pila));
        if(auxiliar == NULL){
            printf("\n\aError en la reserva de espacio de memoria\n");
            exit(-1);
        }else{

            auxiliar->orden = r->trabajo;
            auxiliar->lazo = top;
            top = auxiliar;

            aux = r;
            r = r->lazo;
            free(aux);
        }
    }while(r != NULL);

    free(r);


    // Se muestra la pila - No se pide en enunciado
    recorrido = top;
    printf("\n*** Ordenes de trabajo ***\n");
    do{
        printf("\nNum Orden: %ld", recorrido->orden.numeroDeOrden);
        printf("\nCliente: %s", recorrido->orden.cliente);
        printf("\nDescripcion Falla: %s", recorrido->orden.descripciondeFalla);
        printf("\nModelo: %s", recorrido->orden.modelo);
        printf("\nFecha: %c%c-%c%c-%c%c%c%c", recorrido->orden.fecha[6], recorrido->orden.fecha[7], recorrido->orden.fecha[4], recorrido->orden.fecha[5], recorrido->orden.fecha[0], recorrido->orden.fecha[1], recorrido->orden.fecha[2], recorrido->orden.fecha[3]);
        printf("\nHora: %c%c:%c%c:%c%c\n\n", recorrido->orden.hora[0], recorrido->orden.hora[1], recorrido->orden.hora[2], recorrido->orden.hora[3], recorrido->orden.hora[4], recorrido->orden.hora[5]);
        recorrido = recorrido->lazo;

    }while(recorrido != NULL);



    // EJERCICIO 44

    printf("\n*** Trabajos a realizar (escoger tipo y cantidad de repuestos) ***\n");
    do{
        printf("\nNum Orden: %ld", top->orden.numeroDeOrden);
        printf("\nCliente: %s", top->orden.cliente);
        printf("\nDescripcion Falla: %s", top->orden.descripciondeFalla);
        printf("\nModelo: %s", top->orden.modelo);
        printf("\nFecha: %c%c-%c%c-%c%c%c%c", top->orden.fecha[6], top->orden.fecha[7], top->orden.fecha[4], top->orden.fecha[5], top->orden.fecha[0], top->orden.fecha[1], top->orden.fecha[2], top->orden.fecha[3]);
        printf("\nHora: %c%c:%c%c:%c%c\n", top->orden.hora[0], top->orden.hora[1], top->orden.hora[2], top->orden.hora[3], top->orden.hora[4], top->orden.hora[5]);


        aux2 = (struct lis2 *) malloc(sizeof(struct lis2));

        printf("\nDescripcion de repuesto requerido: ");
        scanf("%s", aux2->ext.repuesto.descripcion);
        printf("\nPart Number de repuesto: ");
        scanf("%ld", &aux2->ext.repuesto.partNumber);
        printf("\nCantidad requerida de repuestos: ");
        scanf("%d", &aux2->ext.cantidad);
        aux2->ext.repuesto.serialNumber = 0;
        strcpy(aux2->ext.repuesto.ubicacion, "-");
        printf("\n------------------------------------------\n");


        if(p == NULL || aux2->ext.repuesto.partNumber < p->ext.repuesto.partNumber){
            aux2->lazo = p;
            p = aux2;
        }else if(aux2->ext.repuesto.partNumber == p->ext.repuesto.partNumber){
            p->ext.cantidad = p->ext.cantidad + aux2->ext.cantidad;
        }else{
            loc = p;
            while(loc->lazo != NULL && aux2->ext.repuesto.partNumber > loc->lazo->ext.repuesto.partNumber)
                loc = loc->lazo;

            if(loc->lazo == NULL || aux2->ext.repuesto.partNumber != loc->lazo->ext.repuesto.partNumber){
                aux2->lazo = loc->lazo;
                loc->lazo = aux2;
            }else{
                loc->lazo->ext.cantidad = loc->lazo->ext.cantidad + aux2->ext.cantidad;

            }
        }

        top = top->lazo;

    }while(top != NULL);


    // Se muestra la lista de repuestos solicitados - No se pide en enunciado
    loc = p;
    printf("\n\n*** Lista de repuestos requeridos por los tecnicos ***\n\n");
    do{
        printf("\nPart Number de repuesto: %ld\n", loc->ext.repuesto.partNumber);
        printf("\nDescripcion de repuesto requerido: %s\n", loc->ext.repuesto.descripcion);
        printf("\nCantidad requerida de repuestos: %d\n", loc->ext.cantidad);
        printf("\n------------------------------------------\n\n");
        loc = loc->lazo;
    }while(loc != NULL);



    //EJERCICIO 45

    viejo = fopen("stock.dat", "rb+");
    do{
        fseek(viejo, (long)(0) * sizeof(repuestos_t), 0);
        fread(&reps, sizeof(repuestos_t), 1, viejo);

        while(!feof(viejo)){
            if(reps.partNumber == p->ext.repuesto.partNumber && p->ext.cantidad > 0){

                p->ext.cantidad = p->ext.cantidad - 1;

                fseek(viejo, (long)(-1) * sizeof(repuestos_t), 1);
                reps.partNumber = p->ext.repuesto.partNumber;
                reps.serialNumber = p->ext.repuesto.serialNumber;
                strcpy(reps.descripcion, "descontado");
                strcpy(reps.ubicacion, p->ext.repuesto.ubicacion);

                fwrite(&reps, sizeof(repuestos_t), 1, viejo);

            }else if(reps.partNumber == p->ext.repuesto.partNumber && (p->ext.cantidad == 0 || p->ext.cantidad < 0)){
                p->ext.cantidad = p->ext.cantidad - 1;
            }

            fread(&reps, sizeof(repuestos_t), 1, viejo);

        }



        if(p->ext.cantidad == 0){
            printf("\nTodos los repuestos con Part Number %ld han sido descontados.\n", p->ext.repuesto.partNumber);
        }else if(p->ext.cantidad < 0){
            printf("\nQueda/n %d repuesto/s con Part Number %ld en stock.\n", (-1)*p->ext.cantidad, p->ext.repuesto.partNumber);
        }else if(p->ext.cantidad > 0){
            //printf("\nFaltan %d repuestos con Part Number %ld en stock.\n", p->ext.cantidad, p->ext.repuesto.partNumber);

            aux3 = (struct cola *)malloc(sizeof(struct cola));
            aux3->falta.cantidad = p->ext.cantidad;
            aux3->falta.repuesto = p->ext.repuesto;

            if(head == NULL){
                head = tail = aux3;
                aux3->lazo = NULL;

            }else{
                tail->lazo = aux3;
                aux3->lazo = NULL;
                tail = aux3;
            }

        }

    p = p->lazo;

    }while(p != NULL);


    // Se muestran repuestos faltantes encolados
    while(head != NULL){
        printf("\nFalta/n %d repuesto/s con Part Number %ld en stock.\n", head->falta.cantidad, head->falta.repuesto.partNumber);
        head = head->lazo;
    }

    // Se creara un nuevo archivo de stock, sin los repuestos utilizados
    nuevo = fopen("descontados.dat", "wb");
    fseek(viejo, (long)(0) * sizeof(repuestos_t), 0);
    fread(&reps, sizeof(repuestos_t), 1, viejo);
    while(!feof(viejo)){
        if(strcmp(reps.descripcion, "descontado")){
            fwrite(&reps, sizeof(repuestos_t), 1, nuevo);
        }
        fread(&reps, sizeof(repuestos_t), 1, viejo);
    }

    fclose(viejo);
    fclose(nuevo);

    rename("descontados.dat", "stock.dat");

    return 0;
}
