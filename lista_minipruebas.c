#include "lista.h"
#include <stdio.h>
#define EXITO 0
#define FRACASO -1
void mostrar_elemento(void* elemento, void* contador){
  if(elemento && contador)
    printf("Elemento %i: %c \n", (*(int*)contador)++, *(char*)elemento);
  
}


void probar_operaciones_lista(){
 lista_t* lista = lista_crear();
  /*
  char a='a', b='b', c='c', d='d', w='w';
  
  if(lista_insertar(lista, &a)==FRACASO)
  {
    printf("FALLO: no pudo insertar a\n");
  }
  if(lista_insertar(lista, &c)==FRACASO)
  {
    printf("FALLO: no pudo insertar c\n");
  }
   if(lista_insertar_en_posicion(lista, &d, 100)==FRACASO)
  {
    printf("FALLO: no pudo insertar d\n");
  }
   if(lista_insertar_en_posicion(lista, &b, 1)==FRACASO)
  {
    printf("FALLO: no pudo insertar b\n");
  }
   if(lista_insertar_en_posicion(lista, &w, 3)==FRACASO)
  {
    printf("FALLO: no pudo insertar w\n");
  }
  */
 //CASOS BORDE
 //mala lista
  char letras[10] = {"valores y respeto mutuo"};
  for(int i = 0; i < 10; i++)
  {
    lista_insertar(lista,letras+i);
  }
  for(int i = 0; i < 10; i+=3)
  {
    lista_borrar_de_posicion(lista, i);
    lista_insertar_en_posicion(lista,(letras[i])+3,i);
  }
  
  lista_borrar_de_posicion(lista, 3);

  printf("Elementos en la lista: ");
  for(size_t i=0;i<lista_elementos(lista);i++){
    if(lista_elemento_en_posicion(lista, i))
      printf("%c ", *(char*)lista_elemento_en_posicion(lista, i));
    else printf("ERROR\n");
  }
  printf("\n\n");
/*
  printf("Imprimo la lista usando el iterador externo: \n");
  lista_iterador_t* it = lista_iterador_crear(lista);
  while(lista_iterador_tiene_siguiente(it))
    printf("%c ", *(char*)lista_iterador_siguiente(it));
  printf("\n\n");

  lista_iterador_destruir(it);

  int contador=0;
  printf("Imprimo la lista usando el iterador interno: \n");
  lista_con_cada_elemento(lista, mostrar_elemento, (void*)&contador);
  printf("\n");*/
  
  lista_destruir(lista);
}

void probar_operaciones_cola(){
  /*
  lista_t* cola = lista_crear();

  int numeros[]={1,2,3,4,5,6};

  for(size_t i=0;i<sizeof(numeros)/sizeof(int);i++){
    printf("Encolo %i\n", numeros[i]);
    lista_encolar(cola, &numeros[i]);
  }
  
  printf("\nDesencolo los numeros y los muestro: ");
  while(!lista_vacia(cola)){
    printf("%i ", *(int*)lista_primero(cola));
    lista_desencolar(cola);
  }
  printf("\n");
  lista_destruir(cola);*/
}

void probar_operaciones_pila(){
  /*lista_t* pila = lista_crear();
  char* algo="somtirogla";

  for(int i=0;algo[i]!= 0;i++){
    printf("Apilo %c\n", algo[i]);
    lista_apilar(pila, &algo[i]);
  }

  printf("\nDesapilo y muestro los elementos apilados: ");
  while(!lista_vacia(pila)){
    printf("%c", *(char*)lista_tope(pila));
    lista_desapilar(pila);
  }
  printf("\n");

  lista_destruir(pila);
  /*/
}

int main(){

  printf("Pruebo que la lista se comporte como lista\n");
  probar_operaciones_lista();
  
  printf("\nPruebo el comportamiento de cola\n");
  probar_operaciones_cola();

  printf("\nPruebo el comportamiento de pila\n");
  probar_operaciones_pila();
  return 0;
}
