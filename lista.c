#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define EXITO 0
#define FRACASO -1
typedef struct nodo
{
    struct nodo* siguiente;
    void* contenido;
}nodo_t;

struct lista
{
    nodo_t* inicio;
    size_t tamanio;
};
//TODO DOC devuelve true si posicion está en el rango [0, lista->tamanio] inclusive
static bool posicion_en_rango(lista_t* lista, size_t posicion)
{
    return (posicion<=(lista->tamanio));
}

//TODO DOC Devuelve true si el tamaño de la lista es 0.
bool lista_vacia(lista_t* lista) 
{ 
    return lista->tamanio == 0; 
} 
//Devuelve la cantidad de elementos en la lista
size_t lista_elementos(lista_t* lista)
{
    return (lista->tamanio);
}
//TODO-DOC aloca memoria a un nodo, le asigna un contenido y lo hace apuntar a NULL.
//devuelve el nodo si fue creado. Si falla devuelve NULL.
static nodo_t* nodo_crear(void* contenido)
{
    nodo_t* nodo = malloc(sizeof(nodo_t)); 
    if(!nodo) return NULL;
    nodo->contenido = contenido;
    nodo->siguiente = NULL;
    return nodo;
}
//TODO-DOC busca el nodo [indice] y lo devuelve, si no lo encuentra devuelve NULL. 
//Si la posición provista es inválida, devuelve NULL.
static nodo_t* lista_acceder_nodo(lista_t* lista, size_t indice)
{
    if(!lista || indice >= lista->tamanio || lista_vacia(lista)) 
        return NULL;
    nodo_t* nodo_actual = lista->inicio;
    while(indice) //Nodo nunca apunta prematuramente a NULL si el tamanio de la lista es correcto
    {
        nodo_actual = nodo_actual->siguiente; 
        indice--;
    }
    return nodo_actual;
}
//TODO-DOC devuelve el nodo lista->tamanio-1, o NULL si la lista está vacía
static nodo_t* lista_ultimo_nodo(lista_t* lista)
{
    return lista_acceder_nodo(lista, (lista->tamanio)-1 );
}

lista_t* lista_crear()
{
    lista_t* nueva = malloc(sizeof(lista_t));
    if(!nueva)
    {
        printf("ERROR creación lista\n");
        return NULL;
    }
    nueva->inicio = NULL;
    nueva->tamanio = 0;
    return nueva;
}
void lista_destruir(lista_t* lista)
{
    if(!lista)
    {
        printf("Lista no existe\n");
        return;
    }
    nodo_t* auxiliar;
    nodo_t* actual = lista->inicio;
    while(actual)
    {
        auxiliar = actual->siguiente;
        free(actual);
        actual = auxiliar;
    }
    free(lista);
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion)
{
    if(!lista||!posicion_en_rango(lista, posicion)) 
        return FRACASO;
    nodo_t* nuevo_nodo = nodo_crear(elemento);
    if(!nuevo_nodo) 
        return FRACASO;
    //DEL lista acceder nodo devuelve NULL si posicion es igual al tope de la lista
    nuevo_nodo->siguiente = lista_acceder_nodo(lista, posicion); 
    if(posicion>0) //el nodo anterior apunta al nuevo nodo
        lista_acceder_nodo(lista, posicion-1)->siguiente = nuevo_nodo;
    else // inserto en el primer nodo
        lista->inicio =  nuevo_nodo;
    (lista->tamanio)++;
    //DEBUG
    printf("insertó %c, ahora hay %li elementos\n", *((char*) elemento), lista->tamanio);
    return EXITO;
}
int lista_insertar(lista_t* lista, void* elemento)
{
    if(lista_insertar_en_posicion(lista, elemento, lista->tamanio)==EXITO)
        return EXITO;
    return FRACASO;
}
//borra el elemento [posicion]
int lista_borrar_de_posicion(lista_t* lista, size_t posicion)
{
    if(!lista||!posicion_en_rango(lista, posicion) || posicion == lista->tamanio) 
        return FRACASO;
    nodo_t* a_borrar;
    nodo_t* previo = NULL; 
    previo = lista_acceder_nodo(lista, posicion-1); //accedo el nodo justo antes del nodo a borrar
    if(previo)
    {
        a_borrar = previo->siguiente; //guardo puntero
        previo->siguiente = a_borrar->siguiente; //reapunto previo
    }
    else
    {
        a_borrar = lista->inicio; //guardo puntero
        lista->inicio = a_borrar->siguiente; //reapunto previo
    }
    free(a_borrar);
    
    (lista->tamanio)--;
    return EXITO;
}
int lista_borrar(lista_t* lista)
{
    return lista_borrar_de_posicion(lista,(lista->tamanio) - 1);
}
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion)
{
    if(!lista) return NULL;
    if(posicion_en_rango(lista, posicion) && posicion != lista->tamanio) 
        return lista_acceder_nodo(lista,posicion)->contenido;
    else return NULL;
}
void* lista_ultimo(lista_t* lista)
{
    return lista_acceder_nodo(lista,(lista->tamanio)-1)->contenido;
}
int lista_apilar(lista_t* lista, void* elemento)
{
    return lista_insertar_en_posicion(lista, elemento, 0); //Complejidad O(1) para insertar al inicio
}
int lista_desapilar(lista_t* lista)
{
    return lista_borrar_de_posicion(lista, 0); //Complejidad O(1) para borrar al inicio
}
void* lista_tope(lista_t* lista)
{

}

