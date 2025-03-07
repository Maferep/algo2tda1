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
  
  char a='a', b='b', c='c', d='d', w='w';
  
  lista_insertar(lista, &a);
  lista_insertar(lista, &c);
  lista_insertar_en_posicion(lista, &d, 100);
  lista_insertar_en_posicion(lista, &b, 1);
  lista_insertar_en_posicion(lista, &w, 3);

  lista_borrar_de_posicion(lista, 3);

  printf("Elementos en la lista: ");
  for(size_t i=0;i<lista_elementos(lista);i++)
    printf("%c ", *(char*)lista_elemento_en_posicion(lista, i));

  printf("\n\n");

  printf("Imprimo la lista usando el iterador externo: \n");
  lista_iterador_t* it = lista_iterador_crear(lista);
  while(lista_iterador_tiene_siguiente(it))
    printf("%c ", *(char*)lista_iterador_siguiente(it));
  printf("\n\n");

  lista_iterador_destruir(it);

  int contador=0;
  printf("Imprimo la lista usando el iterador interno: \n");
  lista_con_cada_elemento(lista, mostrar_elemento, (void*)&contador);
  printf("\n");
  
  lista_destruir(lista);
}

void probar_operaciones_cola(){
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
  lista_destruir(cola);
}

void probar_operaciones_pila(){
  lista_t* pila = lista_crear();
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
}

void abuso_de_lista()
{
  lista_t* lista = NULL;
  
  if(lista_apilar(lista,NULL)==EXITO)
  {
    printf("Apila elemento nulo");
  }
  if(lista_desapilar(lista)==EXITO)
  { 
      printf("FALLO2");return;
  }
  if(lista_borrar_de_posicion(lista, 0)==EXITO)
  {  
      printf("FALLO3");return;
  }
  if(lista_encolar(lista, NULL)==EXITO)
  {  
     printf("FALLO4");return;
  }
  if(lista_desencolar(lista)==EXITO) 
  {
    printf("FALLO5");return;
  }
  if(lista_borrar(lista)==EXITO) 
  {
    printf("FALLO6"); return;
  }
  if(lista_insertar(lista, NULL)==EXITO) 
  {
    printf("FALLO7");return;
  }
  if(lista_primero(lista)) 
  {
    printf("FALLO8"); return;
  }
  
  lista = lista_crear();
  if(lista_desapilar(lista)==EXITO)
  { 
      printf("FALLO2");lista_destruir(lista);return;
  }
  if(lista_borrar_de_posicion(lista, 0)==EXITO)
  {  
      printf("FALLO3");lista_destruir(lista);return;
  }
  if(lista_desencolar(lista)==EXITO) 
  {
    printf("FALLO5"); lista_destruir(lista);return;
  }
  if(lista_borrar(lista)==EXITO) 
  {
    printf("FALLO6"); lista_destruir(lista);return;
  }
  if(lista_primero(lista)) 
  {
    printf("FALLO8"); lista_destruir(lista);return;
  }
  if(lista_elemento_en_posicion(lista,0)) 
  {
    printf("FALLO8"); lista_destruir(lista);return;
  }
  printf("lista vacia\n");
  lista_destruir(lista);
}
int abuso_de_iterador()
{
  lista_t *lista = lista_crear();
  int v[5] = {1,2,3,4,5};
  lista_insertar(lista,&(v[0]));
  lista_insertar(lista,&(v[1]));
  lista_insertar(lista,&(v[2]));
  lista_insertar(lista,&(v[3]));
  lista_insertar(lista,&(v[4]));
  lista_iterador_t *it = lista_iterador_crear(lista);
  for(int i = 0; i < 5;i++)
    {
      int numero = *((int*)lista_iterador_siguiente(it));
      printf( "%i;\n" , numero);
    }
  int* p_i = ((int*) lista_iterador_siguiente(it));
  
  if (p_i || lista_iterador_tiene_siguiente(it)) 
  {
    printf("FALLO\n");
    return FRACASO;
  }
  lista_iterador_destruir(it);
  lista_destruir(lista);
  return EXITO;
}
int main(){
  
  printf("Pruebo que la lista se comporte como lista\n");
  probar_operaciones_lista();
  
  printf("\nPruebo el comportamiento de cola\n");
  probar_operaciones_cola();

  printf("\nPruebo el comportamiento de pila\n");
  probar_operaciones_pila();

  printf("\nabuso lista\n");
  abuso_de_lista();

  printf("\nabuso iterador\n");
  abuso_de_iterador();
  return 0;
}
