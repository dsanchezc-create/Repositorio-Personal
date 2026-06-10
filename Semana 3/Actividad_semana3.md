## Actividad 3-CC232

    ### Integrantes
    - Luis David Sanchez Cirilo

#### Bloque 1

1.  Al pasar de almacenamiento contiguo a dinámico se pierde la capacidad de acceder a los elementos de forma directa, ya que en el almacenamiento contiguo los elementos están almacenados en posiciones adyacentes, lo que permite acceder a ellos mediante un índice. 
    En cambio, en el almacenamiento dinámico, los elementos pueden estar dispersos en la memoria, lo que requiere recorrer la estructura de datos para acceder a un elemento específico.

2.  El acceso por rango calcula una posición directamente a partir de un índice, lo que permite acceder a los elementos de forma rápida y eficiente. 
    En cambio, el acceso por enlace requiere recorrer la estructura de datos para encontrar el elemento deseado, lo que puede ser más lento, especialmente si la estructura es grande.

3.  En las listas enlazadas, cuando se ubica el punto, insertar/eliminar un elemento es más eficiente que en los arreglos, ya que no es necesario desplazar los elementos para hacer espacio o eliminar un elemento (O(1)). 
    Sin embargo, el acceso a un elemento específico en una lista enlazada puede ser más lento que en un arreglo, ya que se requiere recorrer la lista para encontrar el elemento deseado (O(n)).

4. SLList implementa bien Stack y Queue porque tiene operaciones O(1) eficientes en ambos extremos de la lista. 
    En una Stack, se pueden agregar y eliminar elementos en el extremo superior de la lista, mientras que en una Queue, se pueden agregar elementos al final de la lista y eliminar elementos del frente de la lista. 
    Esto permite que SLList sea una estructura de datos versátil para implementar ambas estructuras.

5. SLList no da naturalmente todas las operaciones de una Deque, ya que una Deque requiere operaciones eficientes en ambos extremos de la estructura. 
    En SLList, las operaciones en el extremo opuesto al que se está trabajando pueden ser menos eficientes (O(n)) debido a la necesidad de recorrer la lista para acceder a ese extremo. 
    Por lo tanto, aunque SLList puede implementar algunas operaciones de una Deque, no es la estructura de datos más adecuada para esa función. 

6. El nodo centinela dummy en DLList elimina casi todos los casos borde. Mantiene una estructura circular uniforme y simplifica add/remove con menos if y menos errores.

7. En DLList, getNode(i) decide si recorrer desde inicio o desde final, así el costo es O(min(i, n-i)). Luego en get/set hacen acceso/modificación local, y add/remove ajustan punteros en O(1) adcional; quedando en total O(1+min(i, n-i)).

8. La idea espacial central de SEList es agrupar varios elementos en cada nodo, reduciendo la cantidad de nodos y punteros necesarios. 
    Esto mejora la eficiencia espacial al disminuir la sobrecarga de punteros, aunque puede aumentar el tiempo de acceso a elementos individuales dentro de un nodo.

9. En SEList se reutiliza BDeque sobre ArrayDeque porque cada bloque necesita operaciones eficientes en ambos extremos para agregar y eliminar elementos. 
    ArrayDeque proporciona estas operaciones de manera eficiente, lo que hace que sea una elección adecuada para implementar los bloques en SEList.

10. DengList cumple un papel de puente pedágogico y compatibilidad (incluye operaciones como sort, debup, reverse, etc., y conversión con MorinDengBridge). No reemplaza a Morin porque el nucleo de esta semana está diseñado con otro foco.


#### Bloque 2

|                Archivo                 | Salida u observable importante                                           | Idea estructural                                | Argumento de costo o espacio                                                                             |
|----------------------------------------|--------------------------------------------------------------------------|-------------------------------------------------|----------------------------------------------------------------------------------------------------------|
| `demo_sllist.cpp`                      | size=3, peek=5, pop=5, remove=10 tras add, add, push                     | SLList combina operaciones por cabeza y cola    | push/pop/remove(peek) en extremos son O(1); útil para pila y cola                                        |
| `demo_dllist.cpp`                      | Secuencia final: 10 20 30                                                | Inserción posicional en lista doble             | add(1,20) muestra inserción intermedia; localizar cuesta O(1+min(i,n-i))                                 |
| `demo_selist.cpp`                      | Imprime 0 10 20 ... 90 con get(i)                                        | Lista enlazada por bloques (b=3)                | Mantiene orden lógico por índice aunque internamente redistribuye por bloques; mejor compromiso espacial |
| `demo_deng_list.cpp`                   | size/front/back y luego ordenada: 5 10 20 30                             | Lista “completa” tipo ADT con operaciones extra | Muestra más que inserción/eliminación básica: ordenamiento y exportación (to_vector)                     |
| `demo_morin_deng_bridge.cpp`           | DLList reforzada con Deng: 1 2 3 4 y Removido = 1                        | Bridge Morin↔Deng                               | Reutiliza sort/dedup de Deng sobre DLList sin reescribir DLList                                          |
| `demo_min_structures.cpp`              | MinStack min=3, MinQueue min=2, MinDeque min=1                           | Estructuras con metadato de mínimo              | No solo guardan valor: guardan estado auxiliar para responder min() eficientemente                       |
| `demo_linked_adapters.cpp`             | LinkedStack, LinkedQueue, LinkedDeque con API propia                     | Patrón adaptador sobre listas base              | Reuso por composición: interfaz nueva delegando en SLList/DLList                                         |
| `demo_contiguous_vs_linked.cpp`        | ArrayDeque get(4)=40, DLList get(4)=40 + observaciones impresas          | Comparación contiguo vs enlazado                | Contiguo: mejor localidad/acceso por índice; enlazado: mejores cambios locales                           |
| `demo_capitulo3_panorama.cpp`          | “Semana 3 cargada correctamente” y panorama de estructuras               | Demo integrador                                 | Validación de diseño modular y consistencia de interfaces                                                |
| `demo_xor_list.cpp`                    | XorList: 5 10 20, front=5 back=20                                        | Lista XOR (enlace comprimido)                   | Prioriza ahorro de punteros/espacio, a costa de mayor complejidad de implementación                      |



1. En demo_sllist.cpp, la secuencia add(10), add(20), push(5), pop(), remove() es la más clara: pop() saca 5 y luego remove() saca 10, dejando solo 20. Esto muestra claramente la diferencia entre operaciones de cabeza (push/pop) y cola (add/remove) en SLList.

2. En demo_dllist.cpp, la mejor operación es d.add(1,20) porque muestra la capacidad de insertar en una posición intermedia de la lista doblemente enlazada. Esto destaca la flexibilidad de DLList para manejar inserciones en cualquier parte de la lista, a diferencia de SLList que se enfoca en extremos.

3. En demo_selist.cpp, el observable más importante es la impresión de los elementos 0, 10, 20, ..., 90 usando get(i). Esto demuestra cómo SEList mantiene un orden lógico por índice a pesar de su estructura interna de bloques, mostrando la eficiencia de acceso a elementos individuales.

4. En demo_deng_list.cpp, la evidencia más importante es que además de push_front/push_back/size se usa sort() y luego to vector() para mostrar la lista ordenada; eso se acerca a un ADT de lista más completo.

5. En demo_morin_deng_bridge.cpp, la parte decisiva es stable_sort() sobre la DLList reforzada con Deng. Esto muestra cómo el bridge permite reutilizar funcionalidades avanzadas de Deng (como sort) sin modificar la implementación base de DLList, demostrando la flexibilidad del diseño modular.

6. En demo_min_structures.cpp, almacenar solo valores responde top/front/back; almacenar información adicional permite responder min() eficientemente. Esto muestra cómo estas estructuras no solo mantienen los elementos, sino también un estado auxiliar para optimizar consultas de mínimo.

7. El adaptador LinkedStack es el más importante en demo_linked_adapters.cpp porque muestra cómo se pueden crear nuevas interfaces reutilizando las implementaciones de SLList. Esto destaca el poder del patrón adaptador para extender funcionalidades sin duplicar código.

8. En demo_contiguous_vs_linked.cpp, la comparación entre ArrayDeque y DLList al acceder a get(4) es crucial. ArrayDeque muestra un acceso directo eficiente debido a su almacenamiento contiguo, mientras que DLList requiere recorrer la lista, lo que ilustra claramente las diferencias en eficiencia de acceso entre estructuras contiguas y enlazadas.


#### Bloque 3

1.  En la prueba pública de SLList, se verifica que las operaciones push(), pop(), add(), remove(), size() y peek() funcionan correctamente. 
    Se prueba la capacidad de la lista para manejar operaciones en ambos extremos y se asegura de que el tamaño se actualice adecuadamente después de cada operación.

2.  En la prueba pública de DLList, se verifica que las operaciones add(i,x), remove(i), get(i) y size() funcionan correctamente.
    Se prueba la capacidad de la lista para manejar inserciones y eliminaciones en posiciones específicas.

3.  En SEList la prueba pública mínima valida la construcción con bloques (SEList<int> s(3)), add(i,x) para llenar la lista, get(i) para verificar el orden lógico, y remove(i) para probar la eliminación. 
    Esto asegura que SEList maneja correctamente su estructura de bloques y mantiene la integridad de los índices.

4.  test_public_extras.cpp cubre operaciones nuevas respecto al test base:
    - En SSList: add(i,x), to_vector(), secondLast(), reverse(), checkSize().
    - En DLList: rotate(r), to_vector(), checkSize(), isPalindrome().
    - Estructuras mínimas: MinStack, MinQueue, MinDeque con operaciones de soporte.
    - En XorList: push_back(x), push_front(x), to_vector(), reverse().

5.  En test_public_linked_adapters.cpp, se prueba que LinkedStack, LinkedQueue y LinkedDeque implementan correctamente sus respectivas APIs. 
    Se verifica que las operaciones de apilado/desapilado, encolado/desencolado y operaciones en ambos extremos funcionan como se espera, asegurando que los adaptadores delegan correctamente en las estructuras base.

6.  test_public_deng_bridge.cpp demuestra integración y reutilización porque muestra cómo se puede usar la funcionalidad de Deng (como sort y dedup) sobre una DLList sin modificar la implementación de DLList. 
    Esto valida el diseño modular y la capacidad de extender funcionalidades mediante el patrón bridge, permitiendo que las mejoras en Deng se reflejen automáticamente en las estructuras que lo utilizan.

7.  En stress_selist_week3.cpp, se prueba la eficiencia de SEList bajo una carga pesada de operaciones. 
    Se realizan múltiples inserciones, eliminaciones y accesos a elementos para evaluar el rendimiento y la estabilidad de SEList en condiciones de uso intensivo, asegurando que su estructura de bloques maneja eficientemente la carga.

8.  Una prueba pública sí demuestra corrección funcional en los casos cubiertos: que ciertas secuencias de operaciones producen salidas esperadas y mantienen propiedades observables (orden, tamaño, semántica FIFO/LIFO, etc.).

9.  Una prueba pública:
    -No demuestra corrección funcional en casos no cubiertos: si una secuencia de operaciones o un caso límite no está incluido en la prueba, no se puede garantizar que el código funcione correctamente en esa situación, lo que podría ocultar errores o comportamientos inesperados.
    -No demuestra la ausencia total de bugs de memoria/punteros.
    -No demuestra el cumplimiento formal de complejidades asintóticas, ni tampoco robustez ante entradas no cubiertas.

10. Porque las pruebas son un muestreo de comportamientos específicos; en cambio:
    -Los invariantes explican propiedades que deben mantenerse en todo momento, proporcionando una garantía más amplia sobre el comportamiento del código.
    -El razonamiento de punteros explica cómo se gestionan las referencias y la memoria, lo que es crucial para evitar errores de memoria y garantizar la integridad de las estructuras de datos.
    -El análisis de complejidades asintóticas proporciona una comprensión de la eficiencia del código en términos de tiempo y espacio, lo que es esencial para evaluar su rendimiento en diferentes escenarios.


#### Bloque 4

1.  En SLList, head apunta al primer nodo, tail apunta al último nodo, y n guarda el tamaño de la lista. 
    Estos punteros permiten realizar operaciones eficientes en ambos extremos de la lista, como agregar o eliminar elementos.

2.  En SLList, los cambios de punteros ocurren en push() y pop() para head, y en add() y remove() para tail. 
    En push(), se crea un nuevo nodo que apunta al nodo actual de head, y luego head se actualiza para apuntar a este nuevo nodo. 
    En pop(), head se actualiza para apuntar al siguiente nodo, eliminando el nodo anterior. 
    En add(), se crea un nuevo nodo que apunta a null, y tail se actualiza para apuntar a este nuevo nodo. 
    En remove(), tail se actualiza para apuntar al nodo anterior, eliminando el nodo actual.

3.  secondaLast() en SLList devuelve el valor del nodo antes del último nodo (tail). 
    Si la lista tiene al menos dos elementos, se puede acceder a este nodo a través de tail->prev. 
    Si la lista tiene menos de dos elementos, se debe manejar el caso de error adecuadamente.

4.  reverse() en SLList invierte el orden de los nodos en la lista. 
    Esto se logra recorriendo la lista y cambiando los punteros next y prev de cada nodo, así como actualizando head y tail al final del proceso.

5.  checkSize() en SLList recorre la lista contando el número de nodos y comparando este conteo con el valor almacenado en n. 
    Si el conteo coincide con n, la función devuelve true; de lo contrario, devuelve false, indicando que hay una discrepancia en el tamaño de la lista.

6.  En DLList, getNode(i) devuelve un puntero al nodo en la posición i. 
    Si i es menor que n/2, se recorre la lista desde el inicio (head) hacia adelante; si i es mayor o igual a n/2, se recorre desde el final (tail) hacia atrás. 
    Esto optimiza el acceso a los nodos al reducir la cantidad de pasos necesarios para llegar a la posición deseada.

7.  En addBefore(w,x) se actualizan los punteros de los nodos adyacentes para insertar un nuevo nodo con valor x antes del nodo w. 
    Esto implica actualizar los punteros next y prev de los nodos involucrados para mantener la integridad de la lista.

8.  rotate(r) no mueve datos, solo reconecta punteros. Normaliza r, calcula newFirst = getNode(n-r) y newLast = newFirst->prev, conecta la lista lineal vieja como ciclo temporal y vuelve a “cortar” en el nuevo punto, actualizando dummy.next y dummy.prev.

9.  isPalindrome() usa dos punteros, left y right, que comienzan en los extremos de la lista (head y tail). 
    Se comparan los valores en estas posiciones; si son iguales, se mueven los punteros hacia el centro (left hacia adelante y right hacia atrás) y se repite el proceso. 
    Si en algún momento los valores no coinciden, la función devuelve false, indicando que la lista no es un palíndromo. 
    Si los punteros se cruzan o se encuentran sin encontrar diferencias, la función devuelve true, indicando que la lista es un palíndromo.

10. En SEList, Location representa una ubicación lógica en la lista, que se traduce a una posición física dentro de un bloque. 
    Esto permite acceder a los elementos de manera eficiente, ya que se puede calcular rápidamente la ubicación física a partir de la ubicación lógica, facilitando las operaciones de acceso y modificación en la estructura de bloques.

11. spread(u) redistribuye en inserción: si el bloque u está lleno, se crea un nuevo bloque después de u, se mueve la mitad de los elementos de u al nuevo bloque, y luego se inserta el nuevo elemento en el bloque adecuado. 
    gather(u) redistribuye en eliminación: si el bloque u tiene pocos elementos, se intenta mover elementos desde bloques adyacentes para mantener un equilibrio, o se fusiona con un bloque vecino si es necesario. 
    Estas operaciones aseguran que los bloques mantengan un tamaño adecuado para optimizar el rendimiento de SEList.

12. b controla el compromiso:
    - Un b pequeño reduce la sobrecarga de punteros, mejorando la eficiencia espacial, pero puede aumentar el tiempo de acceso a elementos individuales dentro de un bloque.
    - Un b grande mejora la eficiencia de acceso a elementos individuales, pero aumenta la sobrecarga de punteros, lo que puede afectar negativamente la eficiencia espacial.
    Elegir un valor adecuado de b es crucial para equilibrar la eficiencia temporal y espacial de SEList.


#### Bloque 5

1.  LinkedStack reutiliza SLList por composición, delegando las operaciones de apilado y desapilado a las operaciones de cabeza de SLList (push y pop). 
    Esto permite que LinkedStack aproveche la eficiencia de SLList para manejar operaciones en el extremo superior de la pila.

2.  LinkedQueue reutiliza SLList por delegación, utilizando las operaciones de cola de SLList (add y remove) para implementar las operaciones de encolado y desencolado. 
    Esto permite que LinkedQueue maneje eficientemente las operaciones en ambos extremos de la cola.

3.  LinkedDeque se apoya en DLList porque un deque requiere operaciones eficientes en ambos extremos, y DLList proporciona esta capacidad con sus punteros head y tail. 
    Esto permite que LinkedDeque maneje operaciones de inserción y eliminación en ambos extremos de manera eficiente.

4.  En MinStack, cada entrada guarda el valor del elemento y el mínimo actual en la pila. 
    Al apilar un nuevo elemento, se compara su valor con el mínimo actual y se actualiza el mínimo si es necesario. 
    Esto permite que min() devuelva el mínimo en O(1) tiempo, ya que siempre se tiene acceso al mínimo actual.

5.  En MinQueue, se utilizan dos pilas (stack_in y stack_out) para mantener los elementos de la cola. 
    stack_in se utiliza para encolar elementos, mientras que stack_out se utiliza para desencolar elementos. 
    Para obtener el mínimo, se compara el mínimo de stack_in y stack_out, lo que permite que min() devuelva el mínimo en O(1) tiempo, ya que ambos mínimos se mantienen actualizados durante las operaciones de encolado y desencolado.

6.  En MinDeque, el rebalanceo resuelve el caso en el que una de las pilas (stack_front o stack_back) está vacía. 
    Si stack_front está vacía, se mueve la mitad de los elementos de stack_back a stack_front, y viceversa. 
    Esto asegura que ambas pilas tengan elementos para mantener la capacidad de responder min() en O(1) tiempo, incluso después de varias operaciones de inserción y eliminación.

7.  *Implementar significa crear lógica e invariantes nuevas (MinStack, MinQueue, MinDeque) que añaden metadatos de mínimo y lógica de rebalanceo.
    *Adaptar significa reutilizar una implementación existente (SLList, DLList) para crear una nueva interfaz (LinkedStack, LinkedQueue, LinkedDeque) sin modificar la lógica interna de la estructura base.

8.  *Operaciones Constantes: LinkedStack y LinkedQueue tienen operaciones de apilado/desapilado y encolado/desencolado que son O(1) debido a la eficiencia de SLList. 
        MinStack, MinQueue y MinDeque también tienen operaciones min() que son O(1) gracias a la información adicional que mantienen sobre el mínimo actual.
    *Operaciones Amortizadas: MinQueue y MinDeque pueden tener operaciones de rebalanceo que son O(n) en el peor caso, pero estas operaciones se realizan de manera amortizada, lo que significa que el costo promedio por operación sigue siendo O(1) a lo largo de una secuencia de operaciones.

#### Bloque 6

1.  En DengList se refuerzan operaciones del ADT de lista al agregar funcionalidades utilitarias y algorítmicas como sort(), dedup(), reverse(), contains(), find_index(), etc. 
    Esto amplía el conjunto de operaciones disponibles más allá de las básicas de inserción, eliminación y acceso, proporcionando una lista más completa y versátil.

2.  La ventaja de encapsular una lista más rica sin tocar el resto de Semana 3 es desacoplar: reutilizas algoritmos “avanzados” sin modificar DLList ni SEList, preservando compatibilidad, pruebas e invariantes existentes. 
    Esto permite que las mejoras en DengList se reflejen automáticamente en cualquier estructura que lo utilice, sin riesgo de introducir errores en las implementaciones base.

3.  *to_deng convierte una estructura de datos compatible (como DLList) a DengList, copiando los elementos y construyendo la estructura de DengList. 
    *assign_from_deng hace lo contrario: toma un DengList y copia sus elementos a una estructura de datos compatible.

4.  stable_sort_with_deng() no obliga a reimplementar ordenamiento en DLList/SEList porque se puede convertir la DLList a DengList, usar el sort() de DengList, y luego convertir de nuevo a DLList. 
    Esto permite aprovechar la funcionalidad de ordenamiento de DengList sin modificar la implementación de DLList, demostrando la flexibilidad del diseño modular.

5.  dedup_with_deng() elimina repetidos globales (no solo consecutivos) devolviendo cuantos elementos se eliminaron. 
    Esto se logra convirtiendo la estructura a DengList, utilizando deduplicate() y no uniquify(), que elimina solo duplicados adyacentes en listas ordenadas.

6.  reverse_with_deng() ejemplifica cómo se pueden implementar operaciones adicionales utilizando DengList como intermediario. 
    Al convertir la estructura a DengList, usar reverse() y luego convertir de nuevo, se puede invertir el orden de los elementos sin modificar la lógica de reversión en DLList o SEList.

7.  El costo adicional es de conversión/copia y memoria temporal:
    -Tiempo extra por pasar ida y vuelta.
    -Espacio extra O(n) para la estructura temporal de DengList.
    -En este código, to_deng usa get(i) sobre listas enlazadas, lo que es O(n) por acceso, resultando en O(n^2) para convertir toda la lista.

#### Bloque 7

1.  ArrayDeque vs LinkedDeque:
    -Respresentación: ArrayDeque usa un arreglo circular, mientras que LinkedDeque usa una lista doblemente enlazada.
    -Costo Observable: En ambos, las operaciones de acceso a extremos son O(1), pero ArrayDeque tiene redimensionamiento en acceso por índice, mientras que LinkedDeque tiene acceso O(min(i,n-i)).

2.  Mejor localidad de memoria en contiguo significa que elementos vecinos están físicamente cerca en RAM, así la caché de CPU aprovecha mejor lecturas/escrituras secuenciales y reduce fallos de caché.

3.  La representación enlazada favorece inserciones/eliminaciones locales (sobre todo en extremos o cerca de un nodo ya localizado), porque evita desplazar bloques completos de elementos.

4.  En el Benchmark:
    -Para acceso aleatorio: random_get_arraydeque vs random_get_dllist, ArrayDeque es más rápido debido a su acceso directo por índice, mientras que DLList requiere recorrer la lista.
    - Para operaciones en extremos: deque_contiguo_arraydeque vs deque_enlazado_linddeque, LinkedDeque es más rápido para operaciones en extremos debido a su estructura de nodos, mientras que ArrayDeque puede requerir redimensionamiento.

5.  Porque es un microbenchmark que depende de n fijo, patrón de acceso específico, y no mide otros factores como uso de memoria, rendimiento en casos reales, o comportamiento bajo carga variable. 
    Además, el rendimiento puede variar según la implementación específica de las estructuras de datos y el entorno de ejecución.

6.  XorList muestra la idea de ahorrar espacio usando un solo puntero para almacenar la dirección XOR de los nodos anterior y siguiente. 
    Esto reduce la cantidad de memoria utilizada por nodo, pero hace que la implementación sea más compleja, ya que se requiere conocer el nodo anterior para calcular el siguiente.

7.  La implementación de XorList es más compleja que una lista enlazada tradicional debido a la necesidad de manejar punteros XOR, lo que requiere un manejo cuidadoso de las referencias y puede ser propenso a errores si no se implementa correctamente.


#### Bloque 8

Cuando pasamos de “usar arreglos dinámicos” a “diseñar estructuras enlazadas y adaptadores sobre nodos”, cambia el foco: de mover bloques contiguos a mantener enlaces correctos y reutilizar algoritmos por interfaz.

-Representación: En contiguas, la secuencia vive en memoria adyacente (base + i); en enlazadas, vive en nodos dispersos conectados por punteros/referencias.
-Acceso por rango vs por posición: Con arreglos, el acceso por índice/rango es directo y muy cache-friendly; con nodos, el acceso por posición exige recorrer enlaces hasta llegar al nodo objetivo.
-Inserciones y eliminaciones locales: En arreglos, insertar/eliminar implica desplazar elementos; en nodos, solo ajustar punteros, lo que es más eficiente para cambios locales.
-Complejidad (SLList,DLList,SEList):
    *SLList*: O(1) para operaciones en extremos, O(n) para acceso por índice.
    *DLList*: O(1) para operaciones en extremos, O(1+min(i,n-i)) para acceso por índice.
    *SEList*: O(1+min(i,n-i)/b) en compromiso por bloques y add/remove amortizado O(b+min(i,n-i)/b).
-Reutilización con adaptadores: Un bridge como DengList permite agregar funcionalidades avanzadas sin modificar la estructura base, mientras que adaptadores como LinkedStack reutilizan la lógica de SLList para crear nuevas interfaces.
-Comparación contiguo vs enlazado: Contiguo ofrece mejor localidad de memoria y acceso aleatorio eficiente, mientras que enlazado ofrece mejor eficiencia para inserciones/eliminaciones locales y flexibilidad en la estructura.

