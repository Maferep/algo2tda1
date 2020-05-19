Este archivo contiene la implementación de los TDA lista, cola y pila.

La lista soporta acceso a todos sus elementos,
La pila permite apilar, desapilar y acceder al elemento en su tope.
La cola permite encolar y desencolar elementos.

Además incluye un iterador interno,
y una función para iterar sobre todos los elementos
con cierta función.

La implementación está conformada por tres estructuras:
nodo, lista y lista_iterador. 
La lista es simplemente enlazada,
cada nodo puede acceder al nodo que lo sigue pero no
al anterior. Esto implica que acceder a un elemento
cualquiera tiene complejidad O(n). Sin embargo,
la lista cuenta con punteros al inicio y al final
de la lista, con los cuales acceder y agregar elementos
al inicio y al final de la lista tiene complejidad O(1).

Borrar un elemento al comienzo de la lista
es posible cambiando el puntero a inicio,
pero borrarlo al final de una lista de n elementos
no es trivial pues se requiere acceder al elemento 
n-1 para cambiar su puntero 'siguiente'.

La cola y la pila están implementadas 'por encima'
del struct lista, utilizando sus funciones. 
El tope de la pila es el puntero inicio,
desde el cual las operaciones de apilar y desapilar
son las funciones de insertar y borrar en 0.
La pila encola elementos agregándolos al final
y los desencola borrándolos del principio.
Por lo tanto la complejidad de las 4 operaciones es O(1).



Se escogió esta implementación pues permite evitar
redundancia implementando funciones particulares de 
pila y cola por separado. Para la cola se escogió
desencolar elementos desde el principio pues
era más eficiente que borrar siempre del final,
recorriendo toda la lista cada vez para editar
el penúltimo nodo.

