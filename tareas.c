#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct Tarea{
int TareaID;//Número autoincremental comenzando en 1000
char *Descripcion; //porque hay que hacer reserva dinamica de memoria 
int Duracion; // entre 10 – 100
} typedef Tarea;

typedef struct Nodo{
Tarea T;
struct Nodo *Siguiente;
} Nodo;

// funciones 
Nodo * CrearListaVacia(){ //retorna un puntero que apunta a un dato de tipo nodo 
    return NULL;
}
Nodo * CrearNodo(char *desc,int duracion, int id){ //retirna la direccion del nodo creado 
    Nodo * NuevoNodo= (Nodo*) malloc(sizeof(Nodo));
    NuevoNodo->T.Descripcion = malloc(strlen(desc) + 1);
    strcpy(NuevoNodo->T.Descripcion, desc); //porque todo el tiempo estoy modifican
    NuevoNodo->T.Duracion = duracion ;
    NuevoNodo->Siguiente = NULL;
    NuevoNodo->T.TareaID= id;

    return NuevoNodo;
}

void InsertarNodo ( Nodo **start, Nodo *nodo ){ // **puntero que apunta a puntero guarda la direccion de memoria del puntero porque quiero modificar el puntero no a lo que apunta 
    nodo->Siguiente=*start;
    *start=nodo;
}
 Nodo * QuitarNodo (Nodo **start, int dato){
    Nodo **aux= start; //puntero que apunta a puntero. aux apunta a lo mismo q start
    while (*aux !=NULL){                              // porque aux no es un nodo, apunta a un puntero de un puntero o sea al comienzo apunta a start
        if ((*aux)->T.TareaID == dato ){
            Nodo *temp = *aux;  // Guardamos el nodo a eliminar en una variable temporal.
            *aux = (*aux)->Siguiente;  // Desvinculamos el nodo de la lista.
            temp->Siguiente =NULL; // Ponemos en NULL el puntero siguiente para asegura no llevar vinculos por fuera de la lista
        return temp;
        } else {
            aux = &(*aux)->Siguiente; //no se modifica la lista solo pasa al otro nodo. Le da la direccion de memoria de lo que apunta aux 
        }   
    }
 }

void mostrar (Nodo *start){
    int i =0;
    Nodo *aux;
    aux = start;
    if (aux == NULL){
        printf ("No hay tareas pendientes");
    }
    while (aux!=NULL){
        printf ("----------Nodo %d------------", i);
        i++;
        printf("\nID de la tarea: %d ", aux->T.TareaID);
        printf("\nDescripcion de la tarea: %s ", aux->T.Descripcion);
        printf("\nDuracion de la tarea: %d ", aux->T.Duracion);
        aux=aux->Siguiente;
    }
}

bool pertenece (Nodo *start, int id_busc){
    Nodo * aux;
    aux = start;
    int contador=0;
    while (aux!=NULL){
    if (aux->T.TareaID== id_busc){
        contador++;
    }
    aux= aux->Siguiente;
    }
    if (contador==1){
        return true ;
    } else 
    return false ;

}
void liberar (Nodo *lista){
    Nodo *aux ;
    while (aux != NULL){
        aux = lista;
        lista = lista->Siguiente; //paso al proximo nodo antes de borrarlo
        free (aux->T.Descripcion);
        free(aux);
    }
}






int main(){
Nodo *start, *start_realizadas;
Nodo *nodo, *nodo_mover;
start = CrearListaVacia();
start_realizadas=CrearListaVacia();
int control, durac, id_mover=1, id=0, id_buscar;
control=0;
char descripcion[150];
while (control==0){
    printf("Ingrese la descripcion de la tarea: ");

    scanf("%s", descripcion);
    printf ("\n Ingrese la duracion: ");
    scanf("%d", &durac);
    id++;
    printf("\n Desea seguir agregando nodos? En caso de que no lo desee, ingrese 1, sino 0: ");
    scanf("%d", &control);
    nodo = CrearNodo(descripcion, durac, id);
    InsertarNodo(&start, nodo); //los inserta al comienzo de la lista
}
while (id_mover!=0 && start!=NULL){
printf ("Indique el ID de la tarea realizada (si no quiere indicar mas tareas escriba 0): ");
scanf("%d", &id_mover);
if (id_mover!=0){
    nodo_mover = QuitarNodo(&start, id_mover);
    InsertarNodo(&start_realizadas, nodo_mover);
}
}
printf("\nTareas pendientes: \n");
mostrar ( start);
printf("\nTareas realizadas: \n ");
mostrar ( start_realizadas);

//consultar tareas por id

printf ("\n Ingrese el id de la tarea buscada: ");
scanf("%d", &id_buscar);
if (id_buscar>id){
    printf ("El id ingresado no es valido");
}else{
    if(pertenece(start, id_buscar)){
    printf ("Es una tarea pendiente");
    }else {
    printf ("Es una tarea realizada");
    }
}

    liberar(start);
    liberar(start_realizadas);
return 0;
}