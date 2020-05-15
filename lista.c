#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#define VERDADERO '1'
#define FALSO '0'
typedef struct nodo
{
    struct nodo* siguiente;
    void* contenido;
}nodo_t;

typedef struct lista
{
    nodo_t* inicio;
    size_t tamanio;
    char esta_vacia;
}lista_t;
//TODO-DOC aloca memoria a un nodo, le asigna un contenido y lo hace apuntar a NULL.
//devuelve el nodo si fue creado. Si falla devuelve NULL.
nodo_crear(void* contenido)
{
    nodo_t* nodo = malloc(sizeof(nodo_t)); 
    if(!nodo) return NULL;
    nodo->contenido = contenido;
    nodo->siguiente = NULL;
    return nodo;
}
//TODO-DOC itera cada nodo [indice] veces 
nodo_t* lista_acceder_nodo(lista_t* lista, size_t indice)
{
    if(indice >= lista->tamanio) return NULL;
    nodo_t* nodo_actual = lista->inicio;
    while(indice)
    {
        nodo_actual = nodo_actual->siguiente; //Nodo nunca apunta prematuramente a NULL si el tamanio de la lista es correcto
        indice--;
    }
    return nodo_actual;
}
nodo_t* lista_ultimo_nodo(lista_t* lista)
{
    return lista_acceder_nodo(lista, lista->tamanio);
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
    nueva->esta_vacia = VERDADERO;
    return nueva;
}
int lista_insertar(lista_t* lista, void* elemento)
{
    nodo_t* nuevo_nodo;
    nodo_crear(elemento);
    lista_ultimo_nodo(lista)->siguiente = nuevo_nodo;
    lista->tamanio++;
}