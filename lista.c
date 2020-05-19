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
    nodo_t* final;
};
struct lista_iterador
{
    lista_t* lista;
    nodo_t* nodo;
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
//TODO-DOC busca el nodo [indice] de 0 a tamanio-1 y lo devuelve, si no lo encuentra devuelve NULL. 
//Si la posición provista es inválida, devuelve NULL.
static nodo_t* lista_acceder_nodo(lista_t* lista, size_t indice)
{
    if(!lista || indice >= lista->tamanio || lista_vacia(lista)) 
        return NULL;
    nodo_t* nodo_actual = lista->inicio;
    for(size_t i = 0; i < indice; i++)
    {
        nodo_actual = nodo_actual->siguiente; 
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
    nueva->final = NULL;
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
    if(!lista) 
        return FRACASO;

    nodo_t* nuevo_nodo = nodo_crear(elemento);
    if(!nuevo_nodo) 
        return FRACASO;

    if(!posicion_en_rango(lista, posicion))
        posicion = lista->tamanio;

    bool inserta_al_final = posicion == lista->tamanio;
    bool inserta_al_principio = posicion == 0;

    if(inserta_al_final)
    {
        if(lista->final) 
            lista->final->siguiente = nuevo_nodo; 
        lista->final =nuevo_nodo; 
    }
    else 
        nuevo_nodo->siguiente = lista_acceder_nodo(lista, posicion);

    if(inserta_al_principio)
        lista->inicio = nuevo_nodo;
    else 
        lista_acceder_nodo(lista, posicion-1)->siguiente = nuevo_nodo;
    (lista->tamanio)++;
    return EXITO;
}
int lista_insertar(lista_t* lista, void* elemento)
{
    return lista_insertar_en_posicion(lista, elemento,lista->tamanio);
}
int lista_borrar_de_posicion(lista_t* lista, size_t posicion)
{
    if(!lista) 
        return FRACASO;
    if(posicion >= lista->tamanio)
        posicion = lista->tamanio - 1;

    nodo_t* a_borrar = NULL;
    if(posicion==0 && lista->tamanio==1) 
    {   //eliminar único elemento
        a_borrar = lista->inicio;
        lista->inicio = NULL; lista->final = NULL;
    }
    else
    {   //Asigno nodo anterior
        nodo_t* previo = lista_acceder_nodo(lista, posicion-1); 
        //asigno nodo a borrar
        if(!previo) 
            a_borrar = lista->inicio;
        else
        {
            a_borrar = previo->siguiente;
            if(posicion == lista->tamanio-1) lista->final = previo;
        }
        //Asigno nodo posterior
        nodo_t* posterior = a_borrar->siguiente;
        //asignación con if else
        if(!previo)
            lista->inicio = posterior;
        else
            previo->siguiente = posterior;
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
    nodo_t* nodo=lista_acceder_nodo(lista,posicion);
    return nodo->contenido;
}
void* lista_ultimo(lista_t* lista)
{
    return lista_ultimo_nodo(lista)->contenido;
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
    return lista->inicio->contenido;
}
int lista_encolar(lista_t* lista, void* elemento)
{
    return lista_insertar(lista, elemento);
}
int lista_desencolar(lista_t* lista)
{
    return lista_borrar_de_posicion(lista, 0);
}
void* lista_primero(lista_t* lista)
{
    return lista->inicio->contenido;
}
lista_iterador_t* lista_iterador_crear(lista_t* lista)
{
    lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
    if(!iterador) 
        return NULL;
    iterador->lista = lista;
    iterador->nodo = lista->inicio;
    return iterador;
}
void* lista_iterador_siguiente(lista_iterador_t* iterador)
{
    if(!lista_iterador_tiene_siguiente(iterador)) return NULL;
    void* contenido = iterador->nodo->contenido;
    iterador->nodo = iterador->nodo->siguiente;
    return contenido;
}
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador)
{
    if(iterador) 
        return iterador->nodo != NULL;
    else return false;
}
void lista_iterador_destruir(lista_iterador_t* iterador)
{
    if(iterador) 
        free(iterador);
}
void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*, void*), void *contexto)
{
    nodo_t* nodo_actual = lista->inicio;
    int i = 0;
    while(nodo_actual)
    {
        funcion(nodo_actual->contenido, contexto);
        nodo_actual = nodo_actual->siguiente;
        i++;
    }
}



