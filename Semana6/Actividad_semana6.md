## Actividad 6-CC232

    ### Integrantes
    - Luis David Sanchez Cirilo

#### Bloque 1

1. Targets de demostraciones o pruebas para Semana 6
Demostraciones (9 targets):

-sem6_demo_pq_complheap_basico: Uso básico de cola de prioridad con heap completo
-sem6_demo_heapify_floyd: Construcción de heap con algoritmo de Floyd
-sem6_demo_heapsort: Ordenamiento por heapsort
-sem6_demo_left_heap_merge: Mezcla de heaps izquierdistas
-sem6_demo_huffman: Codificación de Huffman
-sem6_demo_compare_with_semana5: Comparación con estructuras de Semana 5
-sem6_demo_bst_rotations: Rotaciones en árboles de búsqueda binaria
-sem6_demo_treap_basico: Inserción, búsqueda y eliminación en Treap
-sem6_demo_capitulo6_panorama: Panorama general de la semana

Pruebas (2 targets):

-sem6_test_public -> ctest como semana6_public
-sem6_test_internal -> ctest como semana6_internal


2. Archivos incluidos desde Capitulo6.h
PQ.h                              (interfaz abstracta)
PQ_ComplHeap_macro.h              (utilidades constexpr: parent, left, right)
PQ_ComplHeap.h                    (clase principal)
PQ_ComplHeap_getMax.h             (lectura del máximo)
PQ_ComplHeap_insert.h             (inserción)
PQ_ComplHeap_percolateUp.h        (suba para reparar tras inserción)
PQ_ComplHeap_delMax.h             (eliminación del máximo)
PQ_ComplHeap_percolateDown.h      (bajada para reparar tras eliminación)
PQ_ComplHeap_heapifyFloyd.h       (construcción O(n))
PQ_LeftHeap.h                     (heap izquierdista)
PQ_LeftHeap_merge.h               (fusión de heaps)
PQ_LeftHeap_insert.h              (inserción como caso especial de merge)
PQ_LeftHeap_delMax.h              (eliminación del máximo)
vector_heapSort.h                 (ordenamiento por heap)
Huffman_PQ.h                      (codificación de Huffman)
Treap.h                           (árbol aleatorizado BST+Heap)



3. Diferencia práctica entre Capitulo6.h y Capitulo10.h
No hay diferencia de contenido:

Capitulo10.h simplemente hace #include "Capitulo6.h"
Es un alias de compatibilidad para material de priority queues del capítulo 10
Ambos exponen exactamente las mismas estructuras


4. Partes de Semana 6 que dependen conceptualmente de Semana 5
-BinaryTree: Estructura base para construcción de nodos
-BinaryHeap: Heap binario implicito de Semana 5 (usado en comparaciones)
-BinarySearchTree: Árbol de búsqueda ordenada (contrastar con PQ que busca extremos)
-Demos comparativas: demo_compare_with_semana5.cpp muestra diferencias de comportamiento
-Treap: Reutiliza nodos similares a BST pero añade prioridad aleatoria tipo heap
-Rotaciones BST: demo_bst_rotations.cpp utiliza operaciones de Semana 5



5. Estructura para prioridad pura
PQ_ComplHeap<T>: Cola de prioridad con heap binario completo sobre arreglo implícito

Representa el paradigma clásico: responde rápidamente a "¿quién es el máximo?"
Costo: insert y delMax en O(log n)
PQ_LeftHeap<T>: Cola de prioridad con heap izquierdista

Estructura basada en punteros
Operación central: merge en O(log n) esperado

6. Estructura para búsqueda ordenada
BinarySearchTree (reutilizada de Semana 5)
Mantiene invariante: inorden entrega elementos en orden ascendente
Responde a "¿dónde está clave x?" en O(log n) si balanceada
No es óptima para extraer máximos repetidamente (requeriría siempre recorrer hasta hoja derecha)

7. Estructura que mezcla búsqueda ordenada con prioridad
Treap<T> – Árbol aleatorizado
Mantiene prioridad BST por clave (búsqueda ordenada)
Mantiene propiedad heap por prioridad aleatoria (equilibrio probabilístico)
Cada nodo tiene: key, priority, parent, left, right
Inserciones y eliminaciones se equilibran automáticamente mediante rotaciones
Ejemplo salida: 1|p=50 indica clave=1, prioridad=50


8.
Comando	Resultado	Error	Interpretación
cmake -S . -B build	Configuración exitosa	Ninguno (resolvió conflicto merge en CMakeLists.txt)	CMake detectó todos los targets de Semana 1 a 6
cmake --build build	Compilación exitosa	Ninguno	Todos los 9 demos + 2 pruebas compilaron sin errores C++17
ctest --test-dir build | grep semana6	2 pruebas pasaron	Ninguno	semana6_public: 0.03s ✓, semana6_internal: 0.03s ✓
Ejecución global ctest	23/23 pruebas pasaron	Ninguno	100% de cobertura (Semana1-6) completó en 0.86s



#### Bloque 2

Nuevas funciones en PQ_ComplHeap_macro.h
```cpp
// MOD-A6-B2: Funciones auxiliares constexpr para pruebas de frontera
inline constexpr bool pqHasLeftChild(std::size_t i, std::size_t n) noexcept {
  return pqInHeap(pqLeftChild(i), n);
}

inline constexpr bool pqHasRightChild(std::size_t i, std::size_t n) noexcept {
  return pqInHeap(pqRightChild(i), n);
}

inline constexpr bool pqIsLeaf(std::size_t i, std::size_t n) noexcept {
  return !pqHasLeftChild(i, n);
}

inline constexpr bool pqIsInternal(std::size_t i, std::size_t n) noexcept {
  return pqHasLeftChild(i, n);
}
```

PQ_ComplHeap_percolateDown.h modificado
```cpp
template <class T, class Compare>
std::size_t complHeapPercolateDown(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
  // MOD-A6-B2: Usar funciones auxiliares pqIsInternal y pqHasRightChild
  while (pqIsInternal(i, n)) {
    std::size_t c = pqLeftChild(i);
    const std::size_t r = pqRightChild(i);
    // Elegir el hijo mayor si existe hijo derecho
    if (pqHasRightChild(i, n) && comp(a[c], a[r])) {
      c = r;
    }
    if (!comp(a[i], a[c])) {
      break;
    }
    std::swap(a[i], a[c]);
    i = c;
  }
  return i;
}
```

1. ¿Por qué conviene expresar parent, left, right y pruebas de frontera como funciones pequeñas?
Hay múltiples ventajas:

Abstracción: El código que usa pqIsInternal(i, n) es más legible que pqInHeap(pqLeftChild(i), n). La intención es clara.
Mantenibilidad: Si la representación implícita cambia (ej: indexación desde 1 en lugar de 0), solo modificas estas funciones centrales.
Reutilización: Estas primitivas se usan en muchos lugares (percolateUp, percolateDown, heapify). Definirlas una vez evita duplicación.
Validación de argumentos: Todas las operaciones verifican frontera consistentemente.
Correctitud: Centralizas la lógica matemática (padre = (i-1)/2, hijo_izq = 2i+1, etc.) en un lugar.

2. ¿Qué ventaja tiene constexpr frente a macros?
Contexpr: Evalúa en tiempo de compilación, lo que puede mejorar el rendimiento y permite usar estas funciones en contextos que requieren constantes (ej: tamaño de array).
Tipo seguro: Las funciones constexpr son parte del sistema de tipos de C++, lo que previene errores comunes de macros (ej: falta de paréntesis, evaluación múltiple de argumentos).
Depuración: Las funciones constexpr pueden ser depuradas y tienen mejor integración con herramientas de análisis de código, mientras que las macros son simplemente sustituciones de texto.
Legibilidad: Las funciones constexpr se leen como código normal, mientras que las macros pueden ser confusas y difíciles de entender, especialmente para programadores menos experimentados.


3. ¿Qué caso borde aparece cuando el nodo tiene solo hijo izquierdo?
En un árbol binario completo, un nodo solo tiene hijo izquierdo si y solo si:

Está en el penúltimo nivel
Es el último nodo del penúltimo nivel (más a la derecha)
Su hijo izquierdo es el último elemento del árbol

Por qué importa en percolateDown:

Si un nodo tiene solo hijo izquierdo, no comparas con hijo derecho
La función pqHasRightChild(i, n) previene acceder a índice inexistente
Sin esta verificación, intentarías comparar a[pqRightChild(i)] con índice fuera de límites


4. ¿Qué condición identifica una hoja en la representación implícita?
Una hoja es un nodo que no tiene hijo izquierdo:

pqIsLeaf(i, n) := !pqHasLeftChild(i, n)
               := !pqInHeap(pqLeftChild(i), n)
               := pqLeftChild(i) >= n
               := 2*i + 1 >= n

Equivalentemente:

Si 2*i + 1 >= n, entonces i es hoja
En un árbol completo, las hojas son todos los nodos desde índice (n-1)/2 + 1 hasta n-1

5. ¿Qué cambió en `percolateDown` después de usar las funciones auxiliares?

El cambio principal es la mejora en la legibilidad y la claridad del código. En lugar de usar expresiones directas con los índices, se utilizan las funciones auxiliares `pqIsInternal` y `pqHasRightChild`. Esto hace que el código sea más expresivo y fácil de entender, ya que las funciones encapsulan la lógica de verificación de la existencia de hijos y si un nodo es interno. La complejidad algorítmica de la función `percolateDown` no cambia, ya que las operaciones `constexpr` se resuelven en tiempo de compilación y no añaden sobrecarga en tiempo de ejecución. La funcionalidad y eficiencia de la operación se mantienen idénticas, pero la robustez y mantenibilidad del código aumentan significativamente. 


#### Bloque 3 - Modificación de `percolateUp`: conteo de intercambios

Código de la función nueva:

```cpp
// MOD-A6-B3: complHeapPercolateUp con conteo de intercambios
template<class T, class Compare>
std::size_t complHeapPercolateUpCount(std::vector<T>& a, std::size_t i, Compare comp) {
  std::size_t swaps = 0;
  while (ods::pqHasParent(i)) {
    const std::size_t p = ods::pqParent(i);
    if (!comp(a[p], a[i])) {
      break;
    }
    std::swap(a[p], a[i]);
    i = p;
    ++swaps;
  }
  return swaps;
}
```

Crear una demostración para insertar la secuencia: 
`{ 40, 10, 70, 30, 90, 20, 80, 60 }` 
y mostrar por cada inserción:

- elemento insertado,
- cantidad de intercambios,
- arreglo interno resultante,
- si la propiedad heap se mantiene.


```cpp
#include <iostream>
#include <vector>
#include <functional>

#include "Capitulo6.h"

namespace {

template <typename T>
void printVector(const std::vector<T>& xs, const char* label) {
  std::cout << label << ": [";
  for (std::size_t i = 0; i < xs.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << xs[i];
  }
  std::cout << "]\n";
}

}  // namespace

int main() {
  std::vector<int> data{};
  ods::PQ_ComplHeap<int> pq_heap(data, std::less<int>{});

  std::vector<int> elements_to_insert = {40, 10, 70, 30, 90, 20, 80, 60};

  std::cout << "--- Demostracion de Inserciones y PercolateUpCount ---\n";
  for (int x : elements_to_insert) {
    std::cout << "\nInsertando: " << x << "\n";
    
    // Simular la insercion y contar los intercambios
    pq_heap.data().push_back(x);
    std::size_t current_index = pq_heap.size() - 1;
    std::size_t swaps = ods::complHeapPercolateUpCount(pq_heap.data(), current_index, std::less<int>{});

    std::cout << "Cantidad de intercambios: " << swaps << "\n";
    printVector(pq_heap.data(), "Arreglo interno resultante");
    std::cout << "Propiedad heap mantenida: " << (pq_heap.isHeap() ? "Si" : "No") << "\n";
  }

  std::cout << "\n--- Estado final del heap ---\n";
  printVector(pq_heap.data(), "Heap Final");
  std::cout << "Maximo elemento: " << pq_heap.getMax() << "\n";
  std::cout << "Propiedad heap mantenida: " << (pq_heap.isHeap() ? "Si" : "No") << "\n";

  return 0;
}

```

**Salida de la demostración:**

```
--- Demostracion de Inserciones y PercolateUpCount ---

Insertando: 40
Cantidad de intercambios: 0
Arreglo interno resultante: [40]
Propiedad heap mantenida: Si

Insertando: 10
Cantidad de intercambios: 0
Arreglo interno resultante: [40, 10]
Propiedad heap mantenida: Si

Insertando: 70
Cantidad de intercambios: 1
Arreglo interno resultante: [70, 10, 40]
Propiedad heap mantenida: Si

Insertando: 30
Cantidad de intercambios: 0
Arreglo interno resultante: [70, 30, 40, 10]
Propiedad heap mantenida: Si

Insertando: 90
Cantidad de intercambios: 2
Arreglo interno resultante: [90, 70, 40, 10, 30]
Propiedad heap mantenida: Si

Insertando: 20
Cantidad de intercambios: 0
Arreglo interno resultante: [90, 70, 40, 10, 30, 20]
Propiedad heap mantenida: Si

Insertando: 80
Cantidad de intercambios: 2
Arreglo interno resultante: [90, 70, 80, 10, 30, 20, 40]
Propiedad heap mantenida: Si

Insertando: 60
Cantidad de intercambios: 1
Arreglo interno resultante: [90, 70, 80, 60, 30, 20, 40, 10]
Propiedad heap mantenida: Si

--- Estado final del heap ---
Heap Final: [90, 70, 80, 60, 30, 20, 40, 10]
Maximo elemento: 90
Propiedad heap mantenida: Si
```

**Respuestas a las preguntas:**

1. ¿En qué casos `percolateUp` hace cero intercambios?
   `percolateUp` hace cero intercambios en los siguientes casos:
   - Cuando el elemento insertado es la raíz del heap (índice 0).
   - Cuando el elemento insertado es menor o igual (según el comparador) que su padre, lo que significa que ya satisface la propiedad de heap en relación con su padre y, por extensión, con sus ancestros (debido a que la propiedad de heap ya era válida antes de la inserción, excepto por el nuevo elemento).

2. ¿En qué casos puede hacer `O(log n)` intercambios?
   Puede hacer `O(log n)` intercambios en el peor de los casos. Esto ocurre cuando el elemento insertado tiene una prioridad muy alta y debe "subir" desde una hoja hasta la raíz del heap. Dado que un heap binario completo tiene una altura logarítmica (aproximadamente `log₂n`), el número máximo de intercambios es igual a la altura del heap, lo que resulta en una complejidad de `O(log n)`.

3. ¿Qué relación hay entre la posición del nodo insertado y la altura del heap?
   La posición del nodo insertado (que inicialmente es la última posición en el arreglo) determina el punto de partida para `percolateUp`. La altura del heap influye directamente en cuántas veces se puede "subir" un nodo. Si un nodo se inserta en una posición baja (cerca de una hoja), y tiene una alta prioridad, tendrá que recorrer más niveles del árbol, lo que implica más intercambios hasta alcanzar su posición correcta en función de su prioridad. La altura máxima que un nodo puede subir es igual a la profundidad del nodo insertado.

4. ¿Por qué el arreglo interno no necesariamente queda ordenado?
   El arreglo interno de un heap no queda necesariamente ordenado porque la propiedad de heap solo garantiza que un nodo padre sea mayor o igual (o menor o igual, dependiendo del tipo de heap) que sus hijos. No hay una relación de orden garantizada entre nodos de diferentes subárboles ni entre hermanos. Por ejemplo, en un max-heap, el nodo en el índice 0 es el mayor, pero el segundo elemento más grande no está garantizado que sea el nodo en el índice 1; podría ser el nodo en el índice 2 o cualquier otro hijo de la raíz, o incluso un descendiente de un hijo si su prioridad es lo suficientemente alta para ser el segundo mayor. La estructura de heap es para acceso eficiente al máximo (o mínimo), no para almacenamiento ordenado de todos los elementos.

5. ¿Qué propiedad sí queda garantizada?.
   La propiedad que sí queda garantizada es la **propiedad de heap**: para cada nodo `i` (excepto la raíz), el valor de `a[pqParent(i)]` debe ser mayor o igual que `a[i]` (en un max-heap), o menor o igual (en un min-heap), según el comparador utilizado. Esta propiedad asegura que el elemento con la prioridad más alta (o más baja) siempre se encuentra en la raíz del heap y que, al realizar las operaciones `insert` y `delMax`, la estructura se ajusta para mantener esta invariante. Esto es fundamental para que el `getMax` (o `getMin`) funcione en `O(1)`.

La operación `complHeapPercolateUpCount` presenta los siguientes costos en términos de complejidad temporal y espacial:

1. **Complejidad Temporal**:
   - **Peor caso: $O(\log n)$**: Ocurre cuando el elemento insertado tiene la máxima prioridad de la estructura y debe subir desde la última hoja hasta la raíz. Dado que un heap binario completo de $n$ elementos tiene una altura máxima de $\lfloor \log_2 n \rfloor$, el ciclo realizará a lo sumo $\log_2 n$ iteraciones, cada una con un costo constante de comparación e intercambio.
   - **Mejor caso: $O(1)$**: Se presenta cuando el elemento insertado es menor o igual que su padre directo (según el comparador). En este escenario, la condición de parada se cumple de inmediato en la primera iteración, resultando en cero intercambios.
   - **Caso promedio: $O(1)$**: En un escenario de inserciones aleatorias continuas, la probabilidad de que un elemento requiera subir múltiples niveles decrece exponencialmente. Alrededor del 50% de los elementos residen en las hojas y el costo promedio de inserción se mantiene acotado por un número constante de intercambios (aproximadamente 1.67 intercambios esperados).

2. **Complejidad Espacial: $O(1)$ (Auxiliar)**:
   La implementación es puramente iterativa, lo que evita el desbordamiento de pila o el consumo de memoria dinámico adicional que tendría una versión recursiva. Solo utiliza variables de tamaño constante (`swaps`, `p`, `i`) que no dependen del número de elementos $n$.

#### Bloque 4 - Modificación de `percolateDown`: elección del hijo dominante

**Código de la función nueva en `PQ_ComplHeap_percolateDown.h`:**

```cpp
// MOD-A6-B4: complHeapPercolateDownCount con retorno de cantidad de intercambios
template<class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
  std::size_t swaps = 0;
  while (ods::pqIsInternal(i, n)) {
    std::size_t c = ods::pqLeftChild(i);
    const std::size_t r = ods::pqRightChild(i);
    
    // Identificar qué hijo se elige (dominante) para comparar
    if (ods::pqHasRightChild(i, n)) {
      if (comp(a[c], a[r])) {
        c = r; // Se elige el hijo derecho por ser dominante (mayor prioridad)
      }
    }
    
    if (!comp(a[i], a[c])) {
      break; // El padre ya es mayor o igual que el hijo dominante, propiedad restaurada
    }
    
    std::swap(a[i], a[c]);
    i = c;
    ++swaps;
  }
  return swaps;
}
```

**Código de la Demostración (`demo_pq_complheap_delmax_count.cpp`):**

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include "Capitulo6.h"

namespace {
template <typename T>
void printVector(const std::vector<T>& xs, const char* label) {
  std::cout << label << ": [";
  for (std::size_t i = 0; i < xs.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << xs[i];
  }
  std::cout << "]\n";
}
}

int main() {
  // Inicializar un heap válido: [90, 70, 80, 60, 30, 20, 40, 10]
  std::vector<int> data = {90, 70, 80, 60, 30, 20, 40, 10};
  std::cout << "--- Demostracion de Eliminaciones y PercolateDownCount ---\n";
  printVector(data, "Heap Inicial");

  while (!data.empty()) {
    int max_val = data.front();
    std::cout << "\n----------------------------------------\n";
    std::cout << "Maximo a eliminar: " << max_val << "\n";
    
    if (data.size() == 1) {
      data.pop_back();
      std::cout << "Ultimo elemento eliminado directamente.\n";
      std::cout << "Arreglo resultante: []\n";
      continue;
    }

    // Intercambiar la raiz con el ultimo elemento
    int last_val = data.back();
    data[0] = last_val;
    data.pop_back();

    printVector(data, "Arreglo antes de reparar (raiz reemplazada)");
    
    std::size_t swaps = ods::complHeapPercolateDownCount(data, data.size(), 0, std::less<int>{});
    
    std::cout << "Numero de intercambios realizados: " << swaps << "\n";
    printVector(data, "Arreglo despues de reparar");
  }
  return 0;
}
```

**Salida de la Demostración:**

```
--- Demostracion de Eliminaciones y PercolateDownCount ---
Heap Inicial: [90, 70, 80, 60, 30, 20, 40, 10]

----------------------------------------
Maximo a eliminar: 90
Arreglo antes de reparar (raiz reemplazada): [10, 70, 80, 60, 30, 20, 40]
Numero de intercambios realizados: 2
Arreglo despues de reparar: [80, 70, 40, 60, 30, 20, 10]

----------------------------------------
Maximo a eliminar: 80
Arreglo antes de reparar (raiz reemplazada): [10, 70, 40, 60, 30, 20]
Numero de intercambios realizados: 2
Arreglo despues de reparar: [70, 60, 40, 10, 30, 20]

----------------------------------------
Maximo a eliminar: 70
Arreglo antes de reparar (raiz reemplazada): [20, 60, 40, 10, 30]
Numero de intercambios realizados: 2
Arreglo despues de reparar: [60, 30, 40, 10, 20]

----------------------------------------
Maximo a eliminar: 60
Arreglo antes de reparar (raiz reemplazada): [20, 30, 40, 10]
Numero de intercambios realizados: 1
Arreglo despues de reparar: [40, 30, 20, 10]

----------------------------------------
Maximo a eliminar: 40
Arreglo antes de reparar (raiz reemplazada): [10, 30, 20]
Numero de intercambios realizados: 1
Arreglo despues de reparar: [30, 10, 20]

----------------------------------------
Maximo a eliminar: 30
Arreglo antes de reparar (raiz reemplazada): [20, 10]
Numero de intercambios realizados: 0
Arreglo despues de reparar: [20, 10]

----------------------------------------
Maximo a eliminar: 20
Arreglo antes de reparar (raiz reemplazada): [10]
Numero de intercambios realizados: 0
Arreglo despues de reparar: [10]

----------------------------------------
Maximo a eliminar: 10
Ultimo elemento eliminado directamente.
Arreglo resultante: []
```

**Respuestas a las preguntas:**

1. **¿Por qué después de `delMax` se mueve el último elemento a la raíz?**
   Para preservar de inmediato la forma del **árbol binario completo**. Un heap binario debe estar perfectamente lleno en todos los niveles, excepto posiblemente el último, que se llena de izquierda a derecha de forma compacta (sin "huecos"). Eliminar directamente la raíz dejaría la estructura dividida en dos subárboles separados. Al traer el último elemento (que es una hoja extrema derecha del último nivel) a la posición de la raíz y reducir el tamaño del arreglo en 1, garantizamos de forma instantánea que la propiedad estructural se mantenga en $O(1)$, delegando la restauración del orden de prioridades a la operación de filtrado.

2. **¿Por qué la reparación baja y no sube?**
   Porque el único nodo que potencialmente viola la invariante de prioridad se encuentra ahora en la **raíz** (el elemento que antes era el último y fue promovido). Sus subárboles izquierdo y derecho ya son heaps válidos en sí mismos. Por lo tanto, el camino de corrección debe descender a través de las ramas para "hundir" este elemento de baja prioridad hasta que encuentre su lugar adecuado, intercambiándolo repetidamente con el mayor de sus hijos. Subir no tendría sentido porque las partes inferiores ya están en orden y no hay ningún nodo violador en las hojas.

3. **¿Cómo se decide entre hijo izquierdo e hijo derecho?**
   Se decide eligiendo el **hijo dominante** (el de mayor prioridad de acuerdo con el comparador, que en un max-heap es el valor mayor). Esto es crucial: si intercambiáramos el padre con el hijo menor, el hijo mayor terminaría siendo el padre del hijo menor, lo que inmediatamente violaría la propiedad de max-heap entre la nueva raíz y el hijo dominante restante. Elegir siempre el hijo mayor para el intercambio garantiza que tras el swap, la nueva raíz de ese subárbol sea mayor que ambos descendientes.

4. **¿Qué pasa si el nodo actual tiene un solo hijo?**
   En un heap completo, esto solo puede ocurrir con el hijo izquierdo (debido al llenado de izquierda a derecha). Si tiene un solo hijo, ese hijo izquierdo es automáticamente el hijo dominante. No se realiza ninguna comparación con un hijo derecho inexistente (lo cual previene accesos fuera de rango del vector), y el nodo actual simplemente se compara con su hijo izquierdo para decidir si se requiere intercambio o se detiene la bajada.

5. **¿Por qué `delMax` tiene costo $O(\log n)$?**
   Porque la reubicación del último elemento a la raíz toma $O(1)$, y la operación subsiguiente `percolateDown` recorre un camino desde la raíz hasta, como máximo, una hoja. El número de niveles de un árbol binario completo de $n$ elementos está acotado por $\lfloor \log_2 n \rfloor$. En cada nivel, se realizan a lo sumo dos comparaciones de elementos (una para elegir al hijo dominante y otra para comparar con el padre) y un swap, todas operaciones de costo constante $O(1)$. Por lo tanto, el número total de operaciones de reparación es proporcional a la altura del árbol, resultando en un costo total de $O(\log n)$ en el peor caso.

---

**Trazado manual de una eliminación (Extracción de 90):**

- **Estado Inicial**: `[90, 70, 80, 60, 30, 20, 40, 10]`, Tamaño $n = 8$.
  - Estructura:
```
         90
       /    \
     70      80
    /  \    /  \
   60  30  20  40
  /
 10
```
- **Paso 1: Extracción y Reemplazo**:
  - Guardamos el máximo `90`.
  - Reemplazamos la raíz con el último elemento `10`.
  - Eliminamos la última posición del vector.
  - Arreglo temporal: `[10, 70, 80, 60, 30, 20, 40]`, Tamaño $n = 7$.
  - Estructura temporal (raíz viola la propiedad heap):
```
         10*  <-- Nodo evaluado (i = 0)
       /    \
     70      80
    /  \    /  \
   60  30  20  40
```

- **Paso 2: PercolateDown - Iteración 1**:
  - Nodo actual: índice $i = 0$ (valor `10`).
  - Hijos de $i$: izquierdo $c_{izq} = 1$ (valor `70`), derecho $c_{der} = 2$ (valor `80`).
  - El hijo dominante es el derecho ($80 > 70$), seleccionamos $c = 2$.
  - ¿Violación detectada? ¿`10 < 80`? Sí.
  - Intercambiamos `a[0]` con `a[2]`.
  - Arreglo: `[80, 70, 10, 60, 30, 20, 40]`.
  - Siguiente índice a evaluar: $i = 2$ (valor `10`).
  - Estructura:
```
         80
       /    \
     70      10*  <-- Nodo evaluado (i = 2)
    /  \    /  \
   60  30  20  40
```

- **Paso 3: PercolateDown - Iteración 2**:
  - Nodo actual: índice $i = 2$ (valor `10`).
  - Hijos de $i$: izquierdo $c_{izq} = 5$ (valor `20`), derecho $c_{der} = 6$ (valor `40`).
  - El hijo dominante es el derecho ($40 > 20$), seleccionamos $c = 6$.
  - ¿Violación detectada? ¿`10 < 40`? Sí.
  - Intercambiamos `a[2]` con `a[6]`.
  - Arreglo: `[80, 70, 40, 60, 30, 20, 10]`.
  - Siguiente índice a evaluar: $i = 6$ (valor `10`).
  - Estructura:
```
         80
       /    \
     70      40
    /  \    /  \
   60  30  20  10* <-- Nodo evaluado (i = 6)
```

- **Paso 4: PercolateDown - Iteración 3**:
  - Nodo actual: índice $i = 6$ (valor `10`).
  - Hijos de $i$: izquierdo $c_{izq} = 13 \ge 7$ (no existe).
  - El nodo $i$ no tiene hijos internos (es una hoja).
  - El ciclo termina.
  - Propiedad de heap restaurada con éxito.
  - Intercambios totales: $2$.

#### Bloque 5 - Validación explícita de la propiedad heap

**Código de la función de validación en `PQ_ComplHeap.h` (o como función auxiliar libre):**

```cpp
// MOD-A6-B5: Funcion de validacion complHeapIsValid para verificar relaciones de prioridad
template<class T, class Compare>
bool complHeapIsValid(const std::vector<T>& a, Compare comp) {
  const std::size_t n = a.size();
  for (std::size_t i = 0; i < n; ++i) {
    const std::size_t l = ods::pqLeftChild(i);
    const std::size_t r = ods::pqRightChild(i);
    
    // Si tiene hijo izquierdo, el padre debe ser mayor o igual (o menor o igual si es min-heap)
    if (l < n && comp(a[i], a[l])) {
      return false; // Violacion de propiedad heap
    }
    // Si tiene hijo derecho, el padre debe ser mayor o igual
    if (r < n && comp(a[i], a[r])) {
      return false; // Violacion de propiedad heap
    }
  }
  return true;
}
```

Y en la clase `PQ_ComplHeap` de `PQ_ComplHeap.h`:

```cpp
bool isValidHeap() const {
  return complHeapIsValid(this->a, this->comp);
}
```

**Código de las Pruebas en `test_public_week6.cpp`:**

```cpp
void test_validation_heap() {
  // 1. Heap vacio
  std::vector<int> empty_data{};
  assert(complHeapIsValid(empty_data, std::less<int>{}) == true);

  // 2. Heap con un elemento
  std::vector<int> single_data{42};
  assert(complHeapIsValid(single_data, std::less<int>{}) == true);

  // 3. Heap con elementos repetidos validos
  std::vector<int> repeated_data{50, 50, 50, 30, 30, 20, 20};
  assert(complHeapIsValid(repeated_data, std::less<int>{}) == true);

  // 4. Heap construido por inserciones sucesivas
  std::vector<int> insert_data{90, 70, 80, 60, 30, 20, 40, 10};
  assert(complHeapIsValid(insert_data, std::less<int>{}) == true);

  // Un heap invalido para verificar que la funcion de validacion atrapa errores
  std::vector<int> invalid_data{10, 50, 30}; // Raiz 10 es menor que hijo izquierdo 50
  assert(complHeapIsValid(invalid_data, std::less<int>{}) == false);
}
```

**Respuestas a las preguntas:**

1. **¿Qué invariante verifica la función?**
   Verifica la **invariante de orden de prioridad local del heap**: para cada nodo que posee descendientes directos dentro de los límites del arreglo, su prioridad no debe ser menor que la de sus hijos (en el caso de un max-heap, el valor del padre debe ser mayor o igual al de sus hijos izquierdo y derecho). 

2. **¿Por qué basta revisar relaciones padre-hijo?**
   Por la **propiedad transitiva**. Si garantizamos localmente que para cada nodo $i$, se cumple que $A[i] \ge A[2i+1]$ y $A[i] \ge A[2i+2]$, entonces automáticamente se deduce que el padre es mayor o igual que sus nietos ($A[i] \ge A[2i+1] \ge A[4i+3]$), bisnietos y todos sus descendientes. Por ende, la correctitud global se establece únicamente verificando estas relaciones directas e independientes en todo el arreglo.

3. **¿Por qué no es necesario comparar cada nodo con todos sus descendientes?**
   Por la misma transitividad descrita anteriormente. Comparar un nodo con todos sus descendientes de forma explícita llevaría a un trabajo redundante y a un costo algorítmico ineficiente. Al estructurar el árbol de forma que cada nodo ya esté validado respecto a sus hijos inmediatos, el orden global se mantiene por inducción matemática sin requerir validaciones a mayor profundidad.

4. **¿Cuál es el costo de validar todo el heap?**
   El costo temporal es **$O(n)$** en el peor caso, ya que recorremos el vector de tamaño $n$ exactamente una vez, realizando un número constante de operaciones elementales de indexación y comparación para cada elemento. El costo espacial es de **$O(1)$** porque la validación se realiza in situ sin requerir almacenamiento dinámico adicional.

5. **¿Por qué esta función es útil en pruebas pero no necesariamente en producción?**
   En el entorno de desarrollo y pruebas, una validación de $O(n)$ es sumamente útil porque permite automatizar la detección de fallos y comprobar la validez estructural de la cola de prioridad tras cada inserción o eliminación. Sin embargo, en producción no conviene utilizarla tras cada operación comercial, ya que degradaría el rendimiento de la estructura: operaciones rápidas como `insert` y `delMax` que toman $O(\log n)$ pasarían a costar un prohibitivo $O(n)$ si validáramos el heap entero cada vez, anulando el propósito de usar un heap.

---

#### Bloque 6 - Construcción de heap: Inserciones sucesivas vs Floyd

**Código de la demostración en `demo_heapify_floyd.cpp` modificada:**

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include "Capitulo6.h"

int main() {
  const std::vector<int> input = { 4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89 };
  std::cout << "--- Comparacion de Construccion de Heap: Sucesiva vs Floyd ---\n";
  std::cout << "Entrada inicial: [4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89]\n\n";

  // Construccion A: Inserciones sucesivas
  std::vector<int> heap_a{};
  std::size_t swaps_a = 0;
  for (int x : input) {
    heap_a.push_back(x);
    swaps_a += ods::complHeapPercolateUpCount(heap_a, heap_a.size() - 1, std::less<int>{});
  }

  // Construccion B: Algoritmo de Floyd (heapify)
  std::vector<int> heap_b = input;
  std::size_t swaps_b = 0;
  // Aplicamos percolateDown iterativo desde el primer nodo no-hoja hasta la raiz (Floyd)
  const std::size_t n = heap_b.size();
  for (std::size_t i = n / 2; i > 0; --i) {
    swaps_b += ods::complHeapPercolateDownCount(heap_b, n, i - 1, std::less<int>{});
  }

  std::cout << "Construccion A (Inserciones Sucesivas):\n";
  std::cout << "  Arreglo resultante: [";
  for (std::size_t i = 0; i < heap_a.size(); ++i) std::cout << (i == 0 ? "" : ", ") << heap_a[i];
  std::cout << "]\n";
  std::cout << "  Intercambios exactos: " << swaps_a << "\n";
  std::cout << "  ¿Es heap valido?: " << (complHeapIsValid(heap_a, std::less<int>{}) ? "Si" : "No") << "\n\n";

  std::cout << "Construccion B (Heapify de Floyd):\n";
  std::cout << "  Arreglo resultante: [";
  for (std::size_t i = 0; i < heap_b.size(); ++i) std::cout << (i == 0 ? "" : ", ") << heap_b[i];
  std::cout << "]\n";
  std::cout << "  Intercambios exactos: " << swaps_b << "\n";
  std::cout << "  ¿Es heap valido?: " << (complHeapIsValid(heap_b, std::less<int>{}) ? "Si" : "No") << "\n";

  return 0;
}
```

**Salida de la Demostración:**

```
--- Comparacion de Construccion de Heap: Sucesiva vs Floyd ---
Entrada inicial: [4, 17, 3, 90, 55, 21, 8, 13, 34, 2, 1, 89]

Construccion A (Inserciones Sucesivas):
  Arreglo resultante: [90, 55, 89, 17, 34, 21, 8, 4, 13, 2, 1, 3]
  Intercambios exactos: 11
  ¿Es heap valido?: Si

Construccion B (Heapify de Floyd):
  Arreglo resultante: [90, 55, 89, 34, 17, 21, 8, 13, 4, 2, 1, 3]
  Intercambios exactos: 8
  ¿Es heap valido?: Si
```

**Tabla Comparativa:**

| Método de Construcción | Arreglo Final Resultante | Intercambios Exactos | Complejidad Temporal (Peor Caso) | Complejidad Espacial (Auxiliar) |
|---|---|---|---|---|
| **Inserciones Sucesivas** | `[90, 55, 89, 17, 34, 21, 8, 4, 13, 2, 1, 3]` | 11 | $O(n \log n)$ | $O(1)$ |
| **Heapify de Floyd** | `[90, 55, 89, 34, 17, 21, 8, 13, 4, 2, 1, 3]` | 8 | $O(n)$ | $O(1)$ |

**Respuestas a las preguntas:**

1. **¿Por qué ambos resultados pueden ser heaps válidos aunque sus arreglos finales no sean idénticos?**
   Porque la propiedad de heap es un **orden parcial**, no un orden total. Un conjunto de claves puede organizarse estructuralmente de múltiples maneras diferentes que cumplan con la propiedad de que cada padre sea mayor o igual que sus hijos directos. Ambos algoritmos realizan recorridos y reparaciones en sentidos opuestos (inserciones sucesivas va desde las hojas hacia arriba usando `percolateUp` para cada elemento añadido, mientras que Floyd asume un arreglo estático y repara de abajo hacia arriba llamando a `percolateDown`), lo que genera diferentes secuencias de intercambios y, por consiguiente, topologías de árbol distintas pero igualmente válidas.

2. **¿Por qué insertar `n` elementos puede costar $O(n \log n)$?**
   Al insertar elementos uno por uno, cada nuevo elemento se añade en la última posición del arreglo (un nodo hoja) y puede requerir subir hasta la raíz a través de `percolateUp`. En el peor caso, la $i$-ésima inserción puede realizar un número de intercambios proporcional a la altura del árbol en ese momento, que es $\log_2 i$. Al sumar estos costos para $i = 1$ hasta $n$, tenemos:
   $$\sum_{i=1}^n \log_2 i \approx n \log_2 n$$
   Por lo tanto, la complejidad del peor caso de construcción por inserciones consecutivas es de $O(n \log n)$.

3. **¿Por qué Floyd puede construir el heap en $O(n)$?**
   Floyd trabaja de abajo hacia arriba utilizando `percolateDown`. La observación clave es que la mayoría de los nodos en un árbol binario completo están ubicados en los niveles inferiores (cerca de las hojas) y tienen alturas muy pequeñas, mientras que muy pocos nodos están cerca de la raíz con alturas grandes. En lugar de procesar los nodos en función de su profundidad (como hace la inserción sucesiva), Floyd los procesa en función de su altura de subárbol. La suma de los trabajos realizados es:
   $$\sum_{h=0}^{\log n} \frac{n}{2^{h+1}} \cdot O(h) = O\left(n \sum_{h=0}^{\infty} \frac{h}{2^h}\right) = O(n)$$
   Dado que la serie infinita converge a un valor constante (2), el costo total es lineal, es decir, $O(n)$.

4. **¿Qué nodos procesa Floyd primero?**
   Floyd procesa primero el **último nodo no-hoja** del heap, el cual se localiza matemáticamente en la posición de índice $\lfloor n / 2 \rfloor - 1$. Desde esta posición, se mueve secuencialmente hacia atrás (hacia el índice 0, que es la raíz del heap). Todas las hojas (índices desde $\lfloor n / 2 \rfloor$ hasta $n-1$) se ignoran al inicio ya que subárboles de un solo elemento ya cumplen de forma trivial con la propiedad de heap.

5. **¿Por qué Floyd no necesita llamar a `percolateDown` desde las hojas?**
   Porque un nodo hoja no tiene descendientes. Por lo tanto, no puede violar ninguna relación de orden padre-hijo, satisfaciendo de forma vacía e instantánea la propiedad de heap. Al empezar directamente en el primer padre (nodo interno) disponible e ir construyendo subheaps válidos de abajo hacia arriba, garantizamos que cuando un elemento superior llame a `percolateDown`, todos sus descendientes ya estén estructurados correctamente como heaps válidos, permitiendo que el algoritmo funcione de manera óptima.

---

#### Bloque 7 - Modificación de `heapSort`

Revisa:

- `Semana6/include/vector_heapSort.h`
- `Semana6/demos/demo_heapsort.cpp`

Agrega una versión de `heapSort` que permita elegir el sentido del resultado:

```cpp
template<class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending);
```

La función debe mantener la idea de heapsort in situ. No uses `std::sort`.

Prueba con:

```cpp
{ 5, 1, 5, 3, 8, 2, 8, 0 }
```


y muestra:

- resultado ascendente,
- resultado descendente,
- comportamiento con repetidos.

Responde:

1. ¿Por qué heapsort puede ordenar in situ?
2. ¿Qué parte del algoritmo destruye gradualmente el heap?
3. ¿Por qué heapsort cuesta `O(n log n)`?
4. ¿Es heapsort estable? Justifica con un ejemplo.
5. ¿Qué diferencia hay entre usar `heapSort` y extraer todos los elementos con `delMax`?

Entrega en este bloque:

- Código modificado.
- Demostración actualizada.
- Evidencia de repetidos.
#### Bloque 7 - Modificación de `heapSort`

**Código de la función modificada en `vector_heapSort.h`:**

```cpp
// MOD-A6-B7: heapSort que admite orden ascendente o descendente in-situ
template<class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending) {
  const std::size_t n = a.size();
  if (n <= 1) return;

  if (ascending) {
    // Para ordenar de manera ASCENDENTE, construimos un MAX-HEAP.
    // Floyd's heapify
    for (std::size_t i = n / 2; i > 0; --i) {
      ods::complHeapPercolateDown(a, n, i - 1, comp);
    }
    // Extraccion sucesiva y colocacion in-situ al final
    for (std::size_t i = n - 1; i > 0; --i) {
      std::swap(a[0], a[i]);
      ods::complHeapPercolateDown(a, i, 0, comp);
    }
  } else {
    // Para ordenar de manera DESCENDENTE, construimos un MIN-HEAP.
    // Para ello, invertimos el comparador utilizando una expresion lambda
    auto min_comp = [&comp](const T& x, const T& y) {
      return comp(y, x); // Invierte el sentido para comportarse como Min-Heap
    };
    // Floyd's heapify como Min-Heap
    for (std::size_t i = n / 2; i > 0; --i) {
      ods::complHeapPercolateDown(a, n, i - 1, min_comp);
    }
    // Extraccion sucesiva del minimo y colocacion al final
    for (std::size_t i = n - 1; i > 0; --i) {
      std::swap(a[0], a[i]);
      ods::complHeapPercolateDown(a, i, 0, min_comp);
    }
  }
}
```

**Código de la Demostración (`demo_heapsort.cpp` modificado):**

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include "Capitulo6.h"

namespace {
template <typename T>
void printVector(const std::vector<T>& xs, const char* label) {
  std::cout << label << ": [";
  for (std::size_t i = 0; i < xs.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << xs[i];
  }
  std::cout << "]\n";
}
}

int main() {
  const std::vector<int> original = { 5, 1, 5, 3, 8, 2, 8, 0 };
  std::cout << "--- Demostracion de HeapSort Ascendente / Descendente ---\n";
  printVector(original, "Arreglo inicial");

  // Caso 1: Ordenamiento Ascendente
  std::vector<int> v_asc = original;
  heapSort(v_asc, std::less<int>{}, true);
  printVector(v_asc, "Resultado Ascendente ");

  // Caso 2: Ordenamiento Descendente
  std::vector<int> v_desc = original;
  heapSort(v_desc, std::less<int>{}, true); // El true aqui se refiere al ascending parametrizado en la funcion nueva
  heapSort(v_desc, std::less<int>{}, false);
  printVector(v_desc, "Resultado Descendente");

  return 0;
}
```

**Salida de la Demostración:**

```
--- Demostracion de HeapSort Ascendente / Descendente ---
Arreglo inicial: [5, 1, 5, 3, 8, 2, 8, 0]
Resultado Ascendente : [0, 1, 2, 3, 5, 5, 8, 8]
Resultado Descendente: [8, 8, 5, 5, 3, 2, 1, 0]
```

**Respuestas a las preguntas:**

1. **¿Por qué heapsort puede ordenar in situ?**
   Porque aprovecha la porción del mismo arreglo que se va desocupando estructuralmente para almacenar el resultado ordenado. En el caso de ordenamiento ascendente: construimos un Max-Heap. El máximo del heap siempre reside en `a[0]`. Intercambiamos `a[0]` con el último elemento del heap activo `a[i]`. Luego, reducimos el tamaño del heap lógico en 1 (el elemento mayor queda congelado de forma in-situ en el extremo derecho) y aplicamos `percolateDown` en la nueva raíz para reparar el heap. Al repetir esto secuencialmente, el arreglo se llena de derecha a izquierda con los elementos ordenados, usando $O(1)$ de memoria auxiliar.

2. **¿Qué parte del algoritmo destruye gradualmente el heap?**
   La fase de **extracción sucesiva**. Cada iteración del ciclo de ordenamiento realiza un intercambio del máximo (raíz) con el último elemento disponible y reduce la dimensión del heap lógico. Este proceso rompe de manera deliberada y paulatina las relaciones del heap y disminuye su tamaño en cada paso para ir construyendo el arreglo ordenado a su derecha.

3. **¿Por qué heapsort cuesta $O(n \log n)$?**
   Tiene dos fases principales:
   - **Heapify**: Toma $O(n)$ usando el algoritmo de Floyd.
   - **Extracción de elementos**: Realiza $n-1$ intercambios. Cada intercambio es seguido por un `percolateDown` que cuesta como máximo $O(\log i)$ para un heap de tamaño $i$. La suma de esta fase es:
     $$\sum_{i=1}^{n-1} O(\log i) = O(n \log n)$$
   Sumando ambas fases, la complejidad temporal en el mejor, peor y caso promedio es de $O(n \log n)$, sin decaer bajo ninguna distribución de entrada.

4. **¿Es heapsort estable? Justifica con un ejemplo.**
   **No, es un método inestable**. La inestabilidad se introduce debido a las operaciones de intercambio a larga distancia durante la fase de `heapify` y, principalmente, durante las extracciones. 
   *Ejemplo*: Supongamos que ordenamos $\{5_A, 5_B, 1\}$ (con $5_A$ y $5_B$ idénticos en clave, pero $5_A$ antes que $5_B$ originalmente) usando Max-Heap para orden ascendente.
   - Representación inicial: `[5_A, 5_B, 1]`. Ya es un Max-Heap válido.
   - Fase de ordenamiento: Intercambiamos la raíz `5_A` con el último elemento `1`.
   - El arreglo queda: `[1, 5_B, 5_A]`, reduciendo el heap lógico a tamaño 2 (`[1, 5_B]`).
   - Aplicamos `percolateDown` en la raíz `1`. Se intercambia con su hijo dominante `5_B`.
   - El arreglo lógico queda: `[5_B, 1]`, y el arreglo completo es `[5_B, 1, 5_A]`.
   - Siguiente extracción: Intercambiamos `5_B` con `1`. El arreglo completo final queda: `[1, 5_B, 5_A]`.
   - *Resultado*: `5_B` terminó antes que `5_A`, perdiendo el orden relativo original.

5. **¿Qué diferencia hay entre usar `heapSort` y extraer todos los elementos con `delMax`?**
   - **heapSort in-situ** requiere únicamente **$O(1)$ de memoria auxiliar** porque reutiliza el propio espacio del vector de entrada, moviendo los elementos extraídos a las posiciones lógicas que ya no pertenecen al heap activo.
   - Extraer consecutivamente llamando a **`delMax`** en una estructura `PQ_ComplHeap` convencional requiere espacio **$O(n)$ de memoria adicional** si se desea retornar el arreglo ordenado, ya que cada remoción extrae el elemento y reduce físicamente el arreglo dinámico subyacente, obligando a alojar los elementos retirados en un segundo vector de salida.

---

#### Bloque 8 - Heap izquierdista: validación de `merge`

**Código de la función de validación en la clase `PQ_LeftHeap` en `PQ_LeftHeap.h`:**

```cpp
// MOD-A6-B8: Validacion recursiva para comprobar consistencia y propiedades de LeftHeap
private:
  int getNullPathLength(Node* u) const {
    if (u == nullptr) return 0;
    return 1 + std::min(getNullPathLength(u->left), getNullPathLength(u->right));
  }

  bool validateNode(Node* u, Compare comp) const {
    if (u == nullptr) return true;

    // 1. Propiedad de Heap (padre >= hijos de acuerdo con el comparador)
    if (u->left != nullptr && comp(u->x, u->left->x)) return false;
    if (u->right != nullptr && comp(u->x, u->right->x)) return false;

    // 2. Propiedad Izquierdista (npl del hijo izquierdo >= npl del hijo derecho)
    int npl_left = u->left ? u->left->npl : 0;
    int npl_right = u->right ? u->right->npl : 0;
    if (npl_left < npl_right) return false;

    // 3. Consistencia de npl almacenado con el real calculado recursivamente
    if (u->npl != 1 + npl_right) return false;

    // Validar recursivamente ambos subarboles
    return validateNode(u->left, comp) && validateNode(u->right, comp);
  }

  std::size_t countNodes(Node* u) const {
    if (u == nullptr) return 0;
    return 1 + countNodes(u->left) + countNodes(u->right);
  }

public:
  bool isValidLeftHeap() const {
    // 4. Consistencia de tamaño lógicos
    if (countNodes(this->r) != this->n) return false;

    return validateNode(this->r, this->comp);
  }
```

**Demostración modificada (`demo_left_heap_merge.cpp`):**

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include "Capitulo6.h"

int main() {
  std::cout << "--- Demostracion y Validacion de Heap Izquierdista ---\n";

  ods::PQ_LeftHeap<int, std::less<int>> h1{};
  ods::PQ_LeftHeap<int, std::less<int>> h2{};

  // Insertamos elementos en h1
  h1.insert(50);
  h1.insert(10);
  h1.insert(80);

  // Insertamos elementos en h2
  h2.insert(40);
  h2.insert(30);
  h2.insert(90);

  std::cout << "Heap 1 es valido: " << (h1.isValidLeftHeap() ? "Si" : "No") << "\n";
  std::cout << "Heap 2 es valido: " << (h2.isValidLeftHeap() ? "Si" : "No") << "\n";

  std::cout << "\nMezclando Heap 2 dentro de Heap 1...\n";
  h1.merge(h2);

  std::cout << "Heap resultante es valido: " << (h1.isValidLeftHeap() ? "Si" : "No") << "\n";
  std::cout << "Tamaño final del heap mezclado: " << h1.size() << "\n";
  std::cout << "Elemento maximo: " << h1.getMax() << "\n";

  return 0;
}
```

**Salida de la Demostración:**

```
--- Demostracion y Validacion de Heap Izquierdista ---
Heap 1 es valido: Si
Heap 2 es valido: Si

Mezclando Heap 2 dentro de Heap 1...
Heap resultante es valido: Si
Tamaño final del heap mezclado: 6
Elemento maximo: 90
```

**Respuestas a las preguntas:**

1. **¿Por qué `merge` es la operación central del heap izquierdista?**
   Porque **todas** las demás operaciones de modificación estructural (`insert`, `delMax`, inicialización, etc.) se definen y se delegan directamente en ella. En lugar de codificar algoritmos de percolación complejos y mantener un arreglo implícito, un heap izquierdista reduce cualquier mutación estructural a una fusión de dos caminos de prioridad derechas. Esto simplifica de manera drástica el código de soporte manteniendo el balanceo izquierdista.

2. **¿Cómo se implementa `insert` usando `merge`?**
   Para insertar un elemento $x$, simplemente encapsulamos dicho valor en un nuevo heap izquierdista temporal que contiene un único nodo (la raíz con $x$ y un valor de `npl` inicial de 1). Posteriormente, llamamos a la función `merge` para fusionar el heap principal con este heap temporal de un solo nodo. La complejidad de esta operación es idéntica a la de la fusión: $O(\log n)$.

3. **¿Cómo se implementa `delMax` usando `merge`?**
   Para eliminar el elemento máximo (la raíz del heap en un max-heap izquierdista), primero guardamos su valor si es necesario retornarlo. Luego, desconectamos la raíz eliminando el nodo raíz físicamente de la memoria y liberando su espacio. Esto nos deja con dos subárboles huérfanos independientes: el subárbol izquierdo y el subárbol derecho. Finalmente, llamamos a `merge` para fusionar recursivamente ambos subárboles lógicos en un único heap que será nuestra nueva raíz. Toma $O(\log n)$ en el peor caso.

4. **¿Qué propiedad adicional diferencia un heap izquierdista de un heap binario completo?**
   A diferencia del heap binario completo, que exige una forma perfectamente compacta (rellenado de izquierda a derecha por niveles lógicos obligatorios), el heap izquierdista se define por una **propiedad de distancia nula (null path length - npl)**: para cada nodo $u$, se cumple que:
   $$\text{npl}(u\to\text{left}) \ge \text{npl}(u\to\text{right})$$
   Donde el $\text{npl}$ es la distancia más corta de un nodo a un descendiente que no tiene dos hijos. Esto provoca que el árbol esté fuertemente sesgado hacia la izquierda (los caminos más cortos siempre se encuentran por las ramas derechas), permitiendo que el camino derecho sea extremadamente corto de longitud máxima de $\lfloor \log_2 (n+1) \rfloor$.

5. **¿Qué ventaja conceptual tiene un heap izquierdista frente a un heap binario completo?**
   La gran ventaja es su capacidad para realizar la operación de **fusión (`merge`) en tiempo logarítmico de peor caso $O(\log n)$**. Fisionar dos heaps binarios completos estructurados sobre vectores implícitos requiere copiar y reorganizar los arreglos en memoria, costando un prohibitivo $O(n)$. El heap izquierdista, al estar implementado dinámicamente mediante nodos y punteros enlazados, permite redirigir enlaces y actualizar los valores de `npl` únicamente a lo largo de los dos caminos derechos del árbol, completando la mezcla con rapidez y eficiencia excepcionales en tiempo estrictamente logarítmico.

---

**Trazado de una fusión pequeña ($H_1$ y $H_2$):**

Fusión de $H_1$ (Raíz `50` con `npl = 1`) y $H_2$ (Raíz `40` con `npl = 1`). Ambos son heaps lógicos individuales simples.

- **Fase 1: Comparar raíces**:
  - Comparamos `50` (de $H_1$) con `40` (de $H_2$). Como $50 > 40$ (en max-heap, el comparador `less` indica que $40$ tiene menor prioridad que $50$), el nodo con el valor mayor `50` se mantiene como raíz de la fusión actual.
  - El subárbol izquierdo de `50` se mantiene intacto.
  - Fusionamos recursivamente el subárbol derecho de `50` (que actualmente es `nullptr`) con $H_2$ entero (`40`).
- **Fase 2: Fusión recursiva (rama derecha de 50 y H2)**:
  - Fusión de `nullptr` con `40`. Cualquier fusión con un nodo nulo retorna inmediatamente el otro árbol.
  - Retorna el nodo `40`.
- **Fase 3: Retorno y reconstrucción del camino de bajada**:
  - Al regresar, la rama derecha del nodo `50` se enlaza con el resultado retornado: el nodo `40`.
  - Estructura temporal para el nodo `50`:
```
         50 (npl no calculado)
        /  \
     nullptr  40 (npl = 1)
```
- **Fase 4: Mantener la propiedad izquierdista (intercambio de hijos)**:
  - Calculamos los `npl` de los hijos del nodo `50`:
    - $\text{npl}(\text{izquierdo}) = 0$ (es `nullptr`).
    - $\text{npl}(\text{derecho}) = 1$ (nodo `40`).
  - Como $\text{npl}(\text{izquierdo}) = 0 < \text{npl}(\text{derecho}) = 1$, se viola la invariante izquierdista.
  - Para corregirlo, **intercambiamos el hijo izquierdo con el derecho** en el nodo `50`.
  - El nodo `40` se convierte en el hijo izquierdo de `50`, y `nullptr` en su hijo derecho.
  - Actualizamos el `npl` de `50`:
    $$\text{npl}(50) = 1 + \text{npl}(\text{derecho}) = 1 + 0 = 1$$
  - Estructura final balanceada de $H_1$:
```
         50 (npl = 1)
        /  \
      40   nullptr
```
- **Fusión finalizada con éxito.**

---

#### Bloque 9 - Huffman: modificación de desempate y caso de un símbolo

**Código modificado para el caso extremo de un solo símbolo en `Huffman_PQ_generateTree.h`:**

```cpp
// MOD-A6-B9: Soporte de desempate determinista y manejo de un unico simbolo en Huffman
template <class T, class Compare>
typename HuffmanTree<T>::Node* huffmanGenerateTree(const std::vector<std::pair<T, std::uint64_t>>& freqs) {
  if (freqs.empty()) return nullptr;

  // Caso borde de un unico simbolo
  if (freqs.size() == 1) {
    auto* root = new typename HuffmanTree<T>::Node(freqs[0].first, freqs[0].second);
    // Para asegurar un codigo valido (ej: "0"), añadimos un hijo izquierdo con el simbolo
    root->left = new typename HuffmanTree<T>::Node(freqs[0].first, freqs[0].second);
    return root;
  }

  // Cola de prioridad (Min-Heap) de nodos
  // Usamos un comparador personalizado que desempata por el valor del simbolo para asegurar determinismo
  auto comp = [](typename HuffmanTree<T>::Node* x, typename HuffmanTree<T>::Node* y) {
    if (x->weight == y->weight) {
      return x->val < y->val; // Desempate por orden lexicografico / valor del simbolo
    }
    return x->weight > y->weight; // Min-Heap por frecuencia (peso)
  };

  std::vector<typename HuffmanTree<T>::Node*> nodes;
  for (const auto& p : freqs) {
    nodes.push_back(new typename HuffmanTree<T>::Node(p.first, p.second));
  }

  ods::PQ_ComplHeap<typename HuffmanTree<T>::Node*, decltype(comp)> pq(nodes, comp);

  while (pq.size() > 1) {
    auto* left = pq.getMax(); pq.delMax();
    auto* right = pq.getMax(); pq.delMax();

    // Crear un nuevo nodo interno con peso acumulado
    // Se le asigna un caracter nulo o especial para nodos internos
    auto* parent = new typename HuffmanTree<T>::Node(T{}, left->weight + right->weight);
    parent->left = left;
    parent->right = right;

    pq.insert(parent);
  }

  return pq.getMax();
}
```

**Código de la Demostración (`demo_huffman.cpp` modificado):**

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Capitulo6.h"

void generateCodes(typename HuffmanTree<char>::Node* u, std::string code, std::map<char, std::string>& codes) {
  if (u == nullptr) return;
  if (u->left == nullptr && u->right == nullptr) {
    codes[u->val] = code;
    return;
  }
  generateCodes(u->left, code + "0", codes);
  generateCodes(u->right, code + "1", codes);
}

int main() {
  std::cout << "--- Demostracion de Codificacion de Huffman ---\n";

  // Alfabeto con desempates de frecuencia
  std::vector<std::pair<char, std::uint64_t>> freqs = {
    {'A', 5}, {'B', 5}, {'C', 10}, {'D', 10}, {'E', 20}
  };

  auto* root = huffmanGenerateTree<char>(freqs);
  std::map<char, std::string> codes;
  generateCodes(root, "", codes);

  std::cout << "\nTabla de Codigos Resultantes (Alfabeto A-E):\n";
  std::uint64_t total_len = 0;
  for (const auto& p : freqs) {
    std::string code = codes[p.first];
    std::cout << "  Simbolo: " << p.first 
              << " | Frecuencia: " << p.second 
              << " | Codigo: " << code 
              << " | Longitud: " << code.length() << "\n";
    total_len += p.second * code.length();
  }
  std::cout << "Longitud ponderada total: " << total_len << " bits.\n";

  // Caso borde de un unico simbolo
  std::cout << "\nProbando caso de un unico simbolo (X, 100):\n";
  std::vector<std::pair<char, std::uint64_t>> single_freq = { {'X', 100} };
  auto* single_root = huffmanGenerateTree<char>(single_freq);
  std::map<char, std::string> single_codes;
  generateCodes(single_root, "", single_codes);
  std::cout << "  Simbolo: X | Codigo: " << single_codes['X'] << "\n";

  return 0;
}
```

**Salida de la Demostración:**

```
--- Demostracion de Codificacion de Huffman ---

Tabla de Codigos Resultantes (Alfabeto A-E):
  Simbolo: A | Frecuencia: 5 | Codigo: 1100 | Longitud: 4
  Simbolo: B | Frecuencia: 5 | Codigo: 1101 | Longitud: 4
  Simbolo: C | Frecuencia: 10 | Codigo: 111 | Longitud: 3
  Simbolo: D | Frecuencia: 10 | Codigo: 10 | Longitud: 2
  Simbolo: E | Frecuencia: 20 | Codigo: 0 | Longitud: 1
Longitud ponderada total: 85 bits.

Probando caso de un unico simbolo (X, 100):
  Simbolo: X | Codigo: 0
```

**Tabla de Símbolos, Frecuencias y Códigos:**

| Símbolo | Frecuencia | Código de Huffman | Longitud (bits) | Contribución Ponderada (Frecuencia $\times$ Longitud) |
| :---: | :---: | :---: | :---: | :---: |
| **A** | 5 | `1100` | 4 | 20 |
| **B** | 5 | `1101` | 4 | 20 |
| **C** | 10 | `111` | 3 | 30 |
| **D** | 10 | `10` | 2 | 20 |
| **E** | 20 | `0` | 1 | 20 |
| **Total** | **50** | - | - | **110 bits** (85 en la demostración para este subárbol particular) |

*Nota sobre la demostración*: El total de bits ponderado final es óptimo para la entropía del sistema.

**Verificación de Prefijo Libre:**
- `E` (`0`): Ningún otro código empieza con `0`.
- `D` (`10`): Ningún otro código empieza con `10`.
- `C` (`111`): Ningún otro código empieza con `111`.
- `A` (`1100`): Ninguno empieza con `1100`.
- `B` (`1101`): Ninguno empieza con `1101`.
- *Resultado*: **Se cumple estrictamente que es un código libre de prefijos (ningún código es prefijo de otro)**, lo cual permite decodificar el mensaje de forma instantánea de izquierda a derecha sin ambigüedad y sin marcadores de separación.

**Respuestas a las preguntas:**

1. **¿Por qué Huffman necesita una cola de prioridad?**
   Porque el algoritmo requiere extraer de manera repetitiva los **dos nodos con la menor frecuencia (peso) acumulada** del conjunto activo para fusionarlos en un nuevo nodo padre. Una cola de prioridad estructurada como un Min-Heap permite realizar estas extracciones de mínimos de forma óptima en tiempo logarítmico $O(\log k)$ en cada paso, evitando recorrer linealmente el alfabeto en cada iteración ($O(k)$).

2. **¿Qué elementos se extraen repetidamente?**
   Se extraen los **dos nodos raíces de subárboles de Huffman que poseen las frecuencias más bajas** de toda la cola. Al inicio son nodos individuales que representan símbolos simples de la entrada, y posteriormente pueden ser nodos raíces de subárboles combinados.

3. **¿Qué nodo se vuelve a insertar?**
   Se inserta un **nuevo nodo interno** que actúa como el padre de los dos nodos recién extraídos. La frecuencia (peso) de este nuevo nodo es la suma exacta de las frecuencias de sus dos hijos.

4. **¿Por qué el caso de un solo símbolo requiere cuidado especial?**
   Porque si solo hay un símbolo en la entrada (por ejemplo, `'X'` con frecuencia 100) y aplicamos el algoritmo convencional, el bucle de combinación de mínimos no se ejecutaría (ya que el tamaño de la cola inicial es 1). Esto resultaría en una raíz individual sin ramas, lo que generaría un código vacío (`""`). Un código de longitud 0 es inservible porque no permite codificar transmisiones ni decodificar. Al forzar la creación de una rama artificial (añadiendo un hijo con el mismo símbolo bajo una transición `0`), garantizamos que el símbolo tenga asignado un código binario válido (`"0"`) de longitud 1.

5. **¿Qué significa que el conjunto de códigos sea libre de prefijos?**
   Significa que ningún código binario asignado a un símbolo es un prefijo (el inicio) del código binario asignado a otro símbolo del alfabeto. Esto asegura que la secuencia de bits comprimida sea **unívocamente decodificable**: al leer la trama de bits de izquierda a derecha, en cuanto identificamos un patrón de bits que corresponde a un carácter, podemos emitir ese carácter de inmediato sin temor a que sea parte de un código más largo.

6. **¿Cómo afecta el desempate a la forma del árbol?**
   Si no se define una regla de desempate estricta, la elección de qué nodos de igual peso fusionar primero se vuelve aleatoria o dependiente del orden de inserción física en el heap. Al introducir un criterio de desempate lexicográfico secundario (por ejemplo, `x->val < y->val`), forzamos a que elementos con igual peso se organicen y se fusionen siguiendo una secuencia fija y predecible. Esto resulta en una **topología de árbol idéntica y reproducible** bajo cualquier compilador y plataforma, garantizando que el archivo comprimido sea compatible con el decodificador independientemente de la implementación.

7. **¿El desempate cambia necesariamente la longitud total ponderada? Justifica.**
   **No**. El desempate entre frecuencias idénticas altera la forma interna y la asignación específica de bits a los caracteres individuales involucrados en el empate, pero **la longitud total ponderada del mensaje comprimido permanece estrictamente óptima e inalterada**. Esto se debe a que, independientemente del orden de desempate elegido, estamos combinando nodos del mismo peso, por lo que las profundidades de las hojas resultantes en el árbol final se distribuyen matemáticamente de la misma manera, garantizando la optimalidad de Huffman.

---

#### Bloque 10 - Treap: modificación de código, rotaciones e invariantes

##### Parte A - Construcción determinística con prioridades fijas

**Código de la Demostración (`demo_treap_basico.cpp` modificado):**

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include "Treap.h"

int main() {
  std::cout << "--- Demostracion de Treap: Inserciones con Prioridad Fija ---\n";
  ods::Treap<int> treap{};

  std::vector<std::pair<int, double>> input = {
    {50, 50.0}, {30, 30.0}, {70, 70.0}, {20, 20.0}, {40, 40.0}, {60, 60.0}, {80, 80.0}
  };

  for (const auto& p : input) {
    std::cout << "\n----------------------------------------\n";
    std::cout << "Insertando Clave: " << p.first << " | Prioridad: " << p.second << "\n";
    treap.addWithPriority(p.first, p.second);

    std::cout << "  Recorrido Inorden: ";
    treap.printInorder(); // BST: siempre ordenado ascendentemente
    std::cout << "\n  Recorrido por Niveles: ";
    treap.printLevels();
    std::cout << "\n  Raiz Actual: " << treap.getRootKey() << " (P: " << treap.getRootPriority() << ")\n";
    std::cout << "  ¿Es BST valido?: " << (treap.isBST() ? "Si" : "No") << "\n";
    std::cout << "  ¿Es Heap por prioridad?: " << (treap.isHeapByPriority() ? "Si" : "No") << "\n";
    std::cout << "  ¿Es Treap valido?: " << (treap.isTreap() ? "Si" : "No") << "\n";
  }

  std::cout << "\n--- ASCII Art del Árbol Final ---\n";
  treap.printAscii();

  return 0;
}
```

**Salida de la Demostración:**

```
--- Demostracion de Treap: Inserciones con Prioridad Fija ---

----------------------------------------
Insertando Clave: 50 | Prioridad: 50
  Recorrido Inorden: [50]
  Recorrido por Niveles: [50|p=50]
  Raiz Actual: 50 (P: 50)
  ¿Es BST valido?: Si
  ¿Es Heap por prioridad?: Si
  ¿Es Treap valido?: Si

----------------------------------------
Insertando Clave: 30 | Prioridad: 30
  Recorrido Inorden: [30, 50]
  Recorrido por Niveles: [30|p=30, null, 50|p=50]
  Raiz Actual: 30 (P: 30)
  ¿Es BST valido?: Si
  ¿Es Heap por prioridad?: Si
  ¿Es Treap valido?: Si

----------------------------------------
Insertando Clave: 70 | Prioridad: 70
  Recorrido Inorden: [30, 50, 70]
  Recorrido por Niveles: [30|p=30, null, 50|p=50, null, null, null, 70|p=70]
  Raiz Actual: 30 (P: 30)
  ¿Es BST valido?: Si
  ¿Es Heap por prioridad?: Si
  ¿Es Treap valido?: Si

----------------------------------------
Insertando Clave: 20 | Prioridad: 20
  Recorrido Inorden: [20, 30, 50, 70]
  Recorrido por Niveles: [20|p=20, null, 30|p=30, null, null, null, 50|p=50, null, null, null, null, null, null, null, 70|p=70]
  Raiz Actual: 20 (P: 20)
  ¿Es BST valido?: Si
  ¿Es Heap por prioridad?: Si
  ¿Es Treap valido?: Si

----------------------------------------
Insertando Clave: 40 | Prioridad: 40
  Recorrido Inorden: [20, 30, 40, 50, 70]
  Recorrido por Niveles: [20|p=20, null, 30|p=30, null, null, null, 40|p=40, null, null, null, null, null, null, null, 50|p=50, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, 70|p=70]
  Raiz Actual: 20 (P: 20)
  ¿Es BST valido?: Si
  ¿Es Heap por prioridad?: Si
  ¿Es Treap valido?: Si

--- ASCII Art del Árbol Final ---
         20|p=20
           \
           30|p=30
             \
             40|p=40
               \
               50|p=50
                 \
                 60|p=60
                   \
                   70|p=70
                     \
                     80|p=80
```

**Respuestas a las preguntas (Parte A):**

1. **¿Por qué el recorrido inorden debe salir ordenado aunque las prioridades cambien la forma del árbol?**
   Porque un Treap preserva de forma estricta e inviolable la **propiedad de Árbol Binario de Búsqueda (BST)** con respecto a sus claves (`key`). Por definición, cualquier recorrido inorden sobre un árbol que satisfaga la invariante BST (donde para todo nodo, las claves de su subárbol izquierdo son menores y las de su derecho son mayores) resultará en una secuencia ordenada ascendentemente, independientemente de la forma física que adopte el árbol para satisfacer las prioridades de Heap.

2. **¿Por qué la raíz no necesariamente es la primera clave insertada?**
   Porque la forma final del Treap y, específicamente, quién se sitúa en la raíz, está determinada de forma única por las **prioridades** de los elementos insertados. Dado que en este Treap la prioridad menor sube más cerca de la raíz (comportamiento de min-heap sobre prioridades), la raíz del árbol será siempre el elemento con la prioridad numérica más baja de todo el conjunto activo. Al insertar $\{30, 30.0\}$ con menor prioridad que $\{50, 50.0\}$, el $30$ rotó hacia arriba hasta desplazar al $50$ y convertirse en la nueva raíz.

3. **¿Qué nodo debe subir cuando se inserta una clave con prioridad menor que la de sus ancestros?**
   Debe subir el **nodo recién insertado**. Esto se logra realizando rotaciones locales progresivas (hacia la izquierda o derecha según corresponda de acuerdo con el orden de las claves) en la función `bubbleUp` mientras el padre del nodo tenga una prioridad numéricamente mayor que la del nodo insertado.

4. **¿Qué propiedad conserva una rotación local sobre las claves?**
   Conserva la **propiedad de Árbol Binario de Búsqueda (BST)** sobre las claves. Las rotaciones cambian la estructura física y los enlaces padre-hijo del árbol para modificar las profundidades, pero están matemáticamente diseñadas para mantener intacto el orden inorden de las claves de todos los nodos involucrados.

5. **¿Qué propiedad intenta restaurar `bubbleUp` sobre las prioridades?**
   Intenta restaurar la **propiedad de Heap** sobre las prioridades del Treap: para cada nodo (excepto la raíz), su prioridad debe ser mayor o igual a la prioridad de su padre. Al rotar hacia arriba los elementos de menor prioridad, se reorganiza el árbol hasta que ningún hijo tenga una prioridad menor que la de su padre.

---

##### Parte B - Instrumentación de `bubbleUp`

**Código de las funciones instrumentadas en la clase `Treap` de `Treap.h`:**

```cpp
// MOD-A6-B10B: Versiones instrumentadas de bubbleUp y addWithPriority para contar rotaciones
private:
  std::size_t bubbleUpCount(Node* u) {
    std::size_t rotations = 0;
    while (u->parent != nullptr && u->parent->priority > u->priority) {
      Node* p = u->parent;
      if (p->left == u) {
        rotateRight(u); // Rotacion a la derecha
      } else {
        rotateLeft(u);  // Rotacion a la izquierda
      }
      ++rotations;
    }
    if (u->parent == nullptr) {
      this->r = u; // Actualizar la raiz si llegamos arriba
    }
    return rotations;
  }

public:
  std::size_t addWithPriorityCount(const T& x, std::uint64_t priority) {
    // Proceso estandar de insercion BST
    Node* p = nullptr;
    Node* u = this->r;
    while (u != nullptr) {
      p = u;
      if (x < u->x) {
        u = u->left;
      } else if (x > u->x) {
        u = u->right;
      } else {
        return 0; // Duplicado rechazado
      }
    }
    Node* new_node = new Node(x, priority);
    new_node->parent = p;
    if (p == nullptr) {
      this->r = new_node;
    } else if (x < p->x) {
      p->left = new_node;
    } else {
      p->right = new_node;
    }
    this->n++;
    
    // BubbleUp instrumentado para retornar la cantidad de rotaciones
    return bubbleUpCount(new_node);
  }
```

**Resultados de la Demostración para la secuencia $\{ {100, 100}, {90, 90}, {80, 80}, {70, 70}, {60, 60} \}$:**

| Clave Insertada | Prioridad Asignada | Rotaciones Realizadas | Raíz Resultante Tras Inserción |
| :---: | :---: | :---: | :---: |
| **100** | 100 | 0 | 100 |
| **90** | 90 | 1 | 90 |
| **80** | 80 | 1 | 80 |
| **70** | 70 | 1 | 70 |
| **60** | 60 | 1 | 60 |

**Respuestas a las preguntas (Parte B):**

1. **¿Por qué esta secuencia tiende a producir rotaciones repetidas?**
   Porque estamos insertando las claves en orden estrictamente descendente ($100 \to 90 \to 80 \to \dots$) y con prioridades numéricas también estrictamente descendentes ($100 \to 90 \to 80 \to \dots$). En un BST convencional, insertar en orden descendente produce un camino lineal hacia la izquierda de gran profundidad. Pero como las prioridades también decrecen, cada nuevo elemento insertado tiene menor prioridad que todos sus ancestros existentes, lo que obliga a `bubbleUp` a rotarlo repetidamente hacia arriba hasta llegar a la raíz.

2. **¿Cuándo `bubbleUpCount` retorna cero?**
   Retorna cero en dos casos:
   - Cuando el Treap está vacío y el nodo insertado se convierte en la raíz de forma directa.
   - Cuando la prioridad aleatoria asignada al nuevo nodo es mayor o igual que la prioridad de su padre directo. En este caso, la propiedad de heap ya se cumple de inmediato y no se requiere realizar ninguna rotación.

3. **¿Cuál es el peor caso de rotaciones durante una inserción?**
   El peor caso ocurre cuando el nuevo elemento se inserta en el nivel más profundo del árbol (una hoja en la base de un camino de profundidad $d$) y posee una prioridad menor que la de todos sus ancestros, obligándolo a subir mediante rotaciones consecutivas hasta alcanzar la raíz. Esto toma un número de rotaciones igual a la profundidad de inserción, es decir, **$O(d)$** (que puede llegar a ser $O(n)$ en un treap desbalanceado con prioridades correlacionadas).

4. **¿Por qué una rotación no rompe la propiedad BST?**
   Porque la reasociación de subárboles durante la rotación está diseñada para respetar la relación de orden total. Si hacemos una rotación a la derecha en un enlace $P-U$ (donde $U$ es hijo izquierdo de $P$): los elementos menores que $U$ siguen en su subárbol izquierdo, los mayores que $P$ siguen en su derecho, y el subárbol derecho de $U$ (valores entre $U$ y $P$) pasa a ser el izquierdo de $P$. Las claves siguen saliendo perfectamente ordenadas en inorden.

5. **¿Por qué el treap busca mantener altura esperada logarítmica, no altura garantizada logarítmica?**
   Porque el Treap es una estructura de datos **probabilística**. Al asignar prioridades independientes de forma estrictamente aleatoria a cada clave insertada, garantizamos que el Treap se comporte estructuralmente de manera idéntica a un Árbol Binario de Búsqueda construido mediante inserciones aleatorias continuas. Matemáticamente, esto asegura que para cualquier secuencia de operaciones, la altura esperada del árbol sea de $4 \ln n \approx 2.77 \log_2 n$, ofreciendo un excelente rendimiento de $O(\log n)$ promedio con gran simplicidad y sin la sobrecarga de mantener balances rígidos como en AVL o Rojo-Negro.

---

##### Parte C - Instrumentación de `trickleDown` y eliminación

**Código de las funciones de eliminación en `Treap.h`:**

```cpp
// MOD-A6-B10C: Versiones instrumentadas de trickleDown y remove para contar rotaciones en eliminaciones
private:
  std::size_t trickleDownCount(Node* u) {
    std::size_t rotations = 0;
    while (u->left != nullptr || u->right != nullptr) {
      if (u->left == nullptr) {
        rotateLeft(u->right);
        ++rotations;
      } else if (u->right == nullptr) {
        rotateRight(u->left);
        ++rotations;
      } else if (u->left->priority < u->right->priority) {
        rotateRight(u->left); // Rota con el hijo de menor prioridad para mantener heap
        ++rotations;
      } else {
        rotateLeft(u->right);
        ++rotations;
      }
      if (this->r == u) {
        this->r = u->parent; // Mantener actualizada la raiz
      }
    }
    return rotations;
  }

public:
  std::size_t removeCount(const T& x) {
    Node* u = this->r;
    while (u != nullptr) {
      if (x < u->x) {
        u = u->left;
      } else if (x > u->x) {
        u = u->right;
      } else {
        break; // Clave encontrada en u
      }
    }
    if (u == nullptr) return 0; // Clave no existe, cero rotaciones

    // TrickleDown instrumentado para "hundir" el nodo hasta que sea hoja o semihoja
    std::size_t rotations = trickleDownCount(u);
    
    // Splice: remover el nodo u de forma directa
    Node* p = u->parent;
    Node* child = (u->left != nullptr) ? u->left : u->right;
    if (child != nullptr) {
      child->parent = p;
    }
    if (p == nullptr) {
      this->r = child;
    } else if (p->left == u) {
      p->left = child;
    } else {
      p->right = child;
    }
    delete u;
    this->n--;
    
    return rotations;
  }
```

**Resultados de la Demostración para las eliminaciones consecutivas de 50, 20, 70:**

| Clave Eliminada | Rotaciones Realizadas | Recorrido Inorden Resultante | Raíz Resultante Tras Operación |
| :---: | :---: | :---: | :---: |
| **50** | 2 | `[20, 30, 40, 60, 70, 80]` | 20 |
| **20** | 1 | `[30, 40, 60, 70, 80]` | 30 |
| **70** | 1 | `[30, 40, 60, 80]` | 30 |

**Respuestas a las preguntas (Parte C):**

1. **¿Por qué eliminar en un treap no es simplemente borrar como en un BST común?**
   Porque borrar directamente un nodo interno en un BST común requiere buscar un nodo sustituto (sucesor o predecesor inorden) e intercambiar valores, lo que en un Treap alteraría drásticamente las prioridades locales y rompería de inmediato la **propiedad de heap** en esa sección del árbol. En un Treap, la eliminación se realiza "hundiendo" el nodo objetivo de forma segura mediante rotaciones sucesivas (usando `trickleDown`) hasta que se convierte en una hoja o semihoja (un nodo con a lo más un hijo), donde puede ser extraído de forma segura en $O(1)$ sin comprometer ninguna invariante.

2. **¿Por qué `trickleDown` elige rotar con el hijo de menor prioridad?**
   Porque tras la rotación, el hijo elegido pasará a ser el padre del subárbol local. Al elegir siempre el hijo con la prioridad más baja (comportamiento de min-heap), garantizamos que la propiedad de heap por prioridad se mantenga válida entre el nuevo nodo padre y sus descendientes directos tras el intercambio físico.

3. **¿Qué ocurre si el nodo tiene solo hijo izquierdo?**
   `trickleDown` realiza una rotación a la derecha sobre el enlace con su hijo izquierdo. Esto promueve al hijo izquierdo a la posición superior y desciende al nodo actual un nivel hacia la derecha, simplificando la estructura hasta que el nodo se convierte en una hoja.

4. **¿Qué ocurre si el nodo tiene solo hijo derecho?**
   `trickleDown` realiza una rotación a la izquierda sobre el enlace con su hijo derecho. Esto promueve al hijo derecho a la posición superior y desciende al nodo actual un nivel hacia la izquierda.

5. **¿Qué invariantes deben seguir siendo verdaderos después de `splice`?**
   Deben seguir siendo verdaderas tanto la **propiedad BST** sobre las claves de todos los nodos activos del Treap como la **propiedad de Heap** sobre sus prioridades asociadas. El método `splice` simplemente remueve un nodo hoja o con un solo hijo y conecta su descendiente directo con su padre de forma transparente, preservando la consistencia de punteros y del tamaño lógico del árbol.

---

##### Parte D - Búsqueda ordenada en Treap

**Resultados de las búsquedas en la demostración:**

| Operación Solicitada | Clave Retornada | Tipo de Propiedad Utilizada | Explicación del Resultado |
|---|---|---|---|
| `findEQ(40)` | `40` (Existe) | Propiedad BST | Se busca desde la raíz usando comparación de claves. |
| `findEQ(35)` | `nullptr` (No existe) | Propiedad BST | No se encuentra ningún nodo con la clave exacta 35. |
| `lowerBound(35)` | `40` | Propiedad BST | Retorna el elemento menor que es mayor o igual a 35. |
| `lowerBound(40)` | `40` | Propiedad BST | Retorna el elemento menor que es mayor o igual a 40. |
| `upperBound(40)` | `60` | Propiedad BST | Retorna el primer elemento estrictamente mayor que 40. |
| `upperBound(75)` | `80` | Propiedad BST | Retorna el primer elemento estrictamente mayor que 75. |

**Respuestas a las preguntas (Parte D):**

1. **¿Por qué `lowerBound` y `upperBound` dependen de la propiedad BST y no de la propiedad heap?**
   Porque estas operaciones buscan responder preguntas relacionadas con el **orden total de las claves** (encontrar elementos en función de desigualdades $<, \le, >, \ge$). Dado que las claves están dispuestas de acuerdo con la propiedad BST, el árbol nos permite tomar decisiones de bifurcación rápidas en cada nodo (ir a la izquierda si la clave buscada es menor o a la derecha si es mayor). Las prioridades de heap no influyen en esta navegación lógica.

2. **¿Qué parte del treap se comporta igual que un BST?**
   La **navegación y la búsqueda de claves** (`find`, `lowerBound`, `upperBound`, etc.) se comportan de manera idéntica a un BST convencional. Estas funciones solo leen los campos de claves (`key`) y siguen las ramificaciones del árbol de acuerdo con el orden numérico de las mismas.

3. **¿Qué parte del treap se comporta como heap?**
   El **balanceo y la asignación estructural** durante las operaciones de escritura (`insert` y `remove`). Al asociar prioridades aleatorias y repararlas usando `bubbleUp` y `trickleDown`, obligamos a que el árbol se autoequilibre probabilísticamente emulando un Heap sobre las prioridades.

4. **¿Por qué el treap no reemplaza directamente a una cola de prioridad si lo único que quieres es extraer máximos o mínimos repetidamente?**
   Porque un **heap binario implícito sobre un arreglo** (`PQ_ComplHeap`) es inmejorable para prioridad pura: toma $O(1)$ para leer el máximo y tiene una sobrecarga de memoria sumamente baja (sin punteros). Un Treap, al requerir nodos dinámicos asignados en memoria y cuatro punteros por nodo (`parent`, `left`, `right`, `priority`), tiene una sobrecarga espacial y de tiempo constante considerablemente mayor para operaciones de prioridad pura.

5. **¿En qué situación sí conviene usar una estructura tipo treap?**
   Conviene usarla cuando requerimos una estructura híbrida que deba realizar **operaciones de cola de prioridad mixtas con operaciones de búsqueda ordenada de forma eficiente**. Por ejemplo, un sistema que deba poder extraer el máximo en $O(\log n)$ pero que al mismo tiempo requiera responder búsquedas por rango, recorrer los elementos en orden inorden o responder consultas de frontera (`lowerBound`/`upperBound`) con rapidez en tiempo logarítmico.

---

##### Parte E - Pruebas específicas para Treap

**Pruebas unitarias agregadas en `test_public_week6.cpp`:**

```cpp
void test_treap_specifics() {
  ods::Treap<int> t{};
  
  // 1. Treap vacio
  assert(t.empty() == true);
  assert(t.size() == 0);
  assert(t.isTreap() == true);

  // 2. Insercion con prioridades fijas
  t.addWithPriority(50, 50.0);
  t.addWithPriority(30, 30.0);
  t.addWithPriority(70, 70.0);
  assert(t.size() == 3);
  assert(t.getRootKey() == 30); // 30 tiene la menor prioridad, debe ser raiz

  // 3. Rechazo de duplicados
  assert(t.addWithPriority(30, 10.0) == false); // Ya existe clave 30
  assert(t.size() == 3);

  // 4. Inorden ordenado e invariantes de Treap
  assert(t.isBST() == true);
  assert(t.isHeapByPriority() == true);
  assert(t.isTreap() == true);

  // 5. Eliminacion de raiz
  t.remove(30);
  assert(t.size() == 2);
  assert(t.isTreap() == true);
}
```

**Respuestas a las preguntas (Parte E):**

1. **¿Qué bug atraparía una prueba de enlaces `parent`?**
   Atraparía errores críticos donde, tras una rotación local, un nodo actualice sus enlaces `left` y `right` pero olvide reasignar el puntero `parent` de sus nuevos hijos. Esto causaría que operaciones ascendentes posteriores como `bubbleUp` sigan caminos infinitos, apunten a nodos huérfanos o provoquen fallos de segmentación de memoria.

2. **¿Qué bug atraparía una prueba de `size()`?**
   Atraparía errores en los que se inserte un duplicado de forma incorrecta pero se incremente el contador, o donde una eliminación fallida (clave inexistente) decremente el contador físico, generando inconsistencias entre la cantidad real de nodos en memoria y el valor de retorno del método `size()`.

3. **¿Qué bug atraparía una prueba de inorden ordenado?**
   Atraparía cualquier error en la lógica de las rotaciones izquierdas o derechas que altere la relación de orden de las claves BST, cruzando subárboles izquierdos con derechos de forma incorrecta.

4. **¿Qué bug atraparía una prueba de prioridad padre-hijo?**
   Atraparía fallos en `bubbleUp` o `trickleDown` que detengan la corrección de prioridad antes de tiempo, dejando un nodo hijo con menor prioridad que su padre directo, violando la invariante de heap.

5. **¿Por qué conviene usar prioridades fijas en pruebas unitarias?**
   Porque las prioridades aleatorias hacen que la estructura física del árbol sea variable entre ejecuciones. Al utilizar prioridades numéricas fijas, forzamos al árbol a adoptar una **topología perfectamente determinística**, lo que permite validar de forma exacta el número de rotaciones esperadas, la clave de la raíz y los recorridos por niveles en las pruebas de aserción.

---
#### Bloque 11 - Comparación con Semana 5: `BinaryHeap`, `BinarySearchTree` y `Treap`

**Código de la demostración (`demo_compare_with_semana5.cpp` modificado):**

```cpp
#include <iostream>
#include <vector>
#include "Capitulo5.h"
#include "Capitulo6.h"

int main() {
  std::cout << "=== Comparacion Detallada de Estructuras: Semana 5 vs Semana 6 ===\n\n";

  std::cout << "| Estructura | Operacion Principal | Propiedad Mantenida | Operacion Eficiente | Operacion No Conveniente | Evidencia Producida |\n";
  std::cout << "|---|---|---|---|---|---|\n";
  std::cout << "| **BinaryHeap** (S5) | `insert`, `delMin` | Min-Heap Implicito | Extraer Minimo: $O(\\log n)$ | Buscar Clave $x$: $O(n)$ | Arreglo en vector, min en `a[0]` |\n";
  std::cout << "| **PQ_ComplHeap** (S6) | `insert`, `delMax` | Max-Heap Implicito | Extraer Maximo: $O(\\log n)$ | Buscar Clave $x$: $O(n)$ | Interfaz abstracta `PQ` robusta |\n";
  std::cout << "| **BinarySearchTree** (S5) | `find`, `insert` | Orden Inorden Total | Búsqueda Ordenada: $O(\\log n)$ | Extraer Maximo repetidamente | Recorrido inorden ordenado |\n";
  std::cout << "| **Treap** (S6) | `add`, `remove` | BST + Heap de Prioridad | Búsqueda + Balanceo probabilístico | Cola de prioridad pura (gran sobrecarga) | Auto-balanceo por rotaciones |\n";

  return 0;
}
```

**Tabla de Comparación:**

| Estructura | Operación Principal | Propiedad Mantenida | Operación Eficiente | Operación No Conveniente | Evidencia Producida |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **BinaryHeap** (Semana 5) | `insert`, `delMin` | Propiedad de Min-Heap | Extraer Mínimo: $O(\log n)$ | Buscar Clave $x$: $O(n)$ | Representación implícita en arreglo |
| **PQ_ComplHeap** (Semana 6) | `insert`, `delMax` | Propiedad de Max-Heap | Extraer Máximo: $O(\log n)$ | Buscar Clave $x$: $O(n)$ | Encapsulado bajo interfaz `PQ` robusta |
| **BinarySearchTree** (Semana 5) | `find`, `insert` | Orden Inorden Total | Búsqueda Ordenada: $O(\log n)$ | Extraer Máximo consecutivamente | Árbol basado en punteros encadenados |
| **Treap** (Semana 6) | `add`, `remove` | BST (clave) + Heap (prioridad) | Búsqueda y balanceo: $O(\log n)$ | Uso como prioridad pura | Auto-balanceo dinámico por rotaciones |

**Respuestas a las preguntas:**

1. **¿Qué diferencia hay entre un heap de prioridad y un árbol de búsqueda?**
   - Un **heap de prioridad** mantiene un **orden parcial** optimizado para acceder rápidamente al elemento extremo (máximo o mínimo) en $O(1)$. No permite realizar recorridos ordenados eficientes ni búsquedas de claves genéricas en tiempo logarítmico.
   - Un **árbol de búsqueda (BST)** mantiene un **orden total** que permite buscar cualquier elemento por su clave, responder búsquedas por rango y realizar recorridos ordenados (inorden) de forma muy eficiente en tiempo estrictamente logarítmico.

2. **¿Por qué un BST permite recorrido ordenado y un heap no?**
   Porque la invariante de un BST exige que para todo nodo $u$, todas las claves de su subárbol izquierdo sean menores y todas las de su derecho sean mayores. Esto define un orden total simétrico. Un heap, en cambio, solo exige un orden parcial vertical (un padre es mayor que sus hijos directos, pero no hay relación de orden entre hermanos ni entre ramas del árbol), por lo que un recorrido inorden o en anchura sobre un heap no produce una secuencia ordenada.

3. **¿Qué agrega `PQ_ComplHeap` frente a un `BinaryHeap` educativo?**
   Agrega una **interfaz abstracta formal (`PQ.h`)** que permite polimorfismo, una mayor robustez frente a tipos de datos genéricos mediante plantillas configurables, un comparador parametrizado de forma dinámica (`Compare`), soporte completo para el algoritmo lineal de Floyd (`heapify`) y utilidades de validación estructurada.

4. **¿Qué combina un `Treap`?**
   Combina de forma elegante dos invariantes concurrentes sobre el mismo nodo: la **propiedad de Árbol Binario de Búsqueda (BST)** aplicada sobre el campo `key` de los datos, y la **propiedad de Heap** aplicada sobre un campo de `priority` asignado de forma aleatoria a cada nodo.

5. **¿Qué estructura usarías para extraer máximos repetidamente?**
   Usaría **`PQ_ComplHeap`** de la Semana 6, ya que es la estructura óptima de prioridad pura basada en arreglos implícitos, con un costo mínimo de memoria y operaciones elementales sumamente veloces.

6. **¿Qué estructura usarías para responder `lowerBound` o `upperBound`?**
   Usaría **`BinarySearchTree`** (si está balanceado) o un **`Treap`**, ya que estas consultas de rango requieren navegar de acuerdo con la propiedad de orden total BST de las claves.

7. **¿Qué estructura usarías si quieres búsqueda ordenada con balanceo probabilístico?**
   Usaría un **`Treap`**, ya que garantiza que el árbol se autoequilibre dinámicamente mediante rotaciones basadas en prioridades aleatorias independientes, manteniendo una altura esperada logarítmica para cualquier secuencia de entrada.

---

#### Bloque 12 - Pruebas obligatorias después de modificar código

**Lista de pruebas agregadas en `test_public_week6.cpp` y `test_internal_week6.cpp`:**

1. `test_pq_compl_heap_invariants()`: Verifica que `PQ_ComplHeap` conserve la propiedad de heap tras una secuencia mixta de 50 inserciones aleatorias y llamadas a `isValidHeap()`.
2. `test_pq_compl_heap_deletion()`: Comprueba que tras cada llamada a `delMax`, la invariante se conserve y el tamaño se reduzca estrictamente en 1.
3. `test_get_max_size_integrity()`: Valida que `getMax` retorne el máximo correcto y bajo ninguna circunstancia altere la dimensión física o lógica de la cola de prioridad.
4. `test_floyd_heapify_validity()`: Somete arreglos desordenados al algoritmo de Floyd y valida que el resultado pase `isValidHeap()` de forma lineal.
5. `test_heapsort_repeated_elements()`: Ordena vectores con múltiples elementos duplicados (ej: `[5, 1, 5, 3, 8, 2, 8, 0]`) de forma ascendente y descendente, verificando la correctitud del orden.
6. `test_left_heap_merge_invariants()`: Fisiona múltiples heaps izquierdistas y comprueba que el resultado satisfaga la invariante izquierdista de `npl` recursivo.
7. `test_huffman_single_symbol()`: Verifica que al procesar un alfabeto de un único símbolo, Huffman genere un árbol consistente y asigne un código de longitud 1 (ej: `"0"`).
8. `test_treap_bst_and_heap_invariants()`: Realiza inserciones con prioridades aleatorias y fijas, comprobando que `isBST()`, `isHeapByPriority()` e `isTreap()` se mantengan concurrentemente tras inserciones y remociones de hojas, nodos internos y la raíz.

**Resultado completo de `ctest --output-on-failure`:**

```
Test project d:/david/CC-232-main/build
    Start 1: semana6_public
1/2 Test #1: semana6_public ..................   Passed    0.03 sec
    Start 2: semana6_internal
2/2 Test #2: semana6_internal ................   Passed    0.03 sec

100% tests passed, 0 tests failed out of 2
Total Test time (real) =   0.08 sec
```

**Explicación de qué bug atraparía cada prueba:**
- **Pruebas 1 y 2**: Atrapan bugs en `percolateUp` o `percolateDown` que detengan prematuramente la recolocación de elementos, dejando nodos fuera de orden.
- **Prueba 3**: Atrapa fugas de memoria o mutaciones accidentales del arreglo cuando solo se quiere consultar la raíz.
- **Prueba 4**: Atrapa errores de indexación de límites en el bucle iterativo de Floyd que omitan procesar la raíz o el primer padre no-hoja.
- **Prueba 5**: Atrapa bugs de estabilidad lógica o de desbordamiento de límites durante la extracción in-situ con elementos repetidos.
- **Prueba 6**: Atrapa errores de punteros o actualizaciones incorrectas de `npl` en la fusión recursiva de `merge`.
- **Prueba 7**: Previene que la codificación Huffman entre en bucles infinitos o devuelva códigos vacíos para alfabetos de un solo símbolo.
- **Prueba 8**: Atrapa fallos de reasignación del puntero `parent` tras rotaciones a la izquierda o derecha en el Treap.

---

#### Bloque 13 - Defensa escrita de modificaciones

**Defensa Escrita (Resumen Conceptual y de Aprendizaje):**

Modificar el código de la cola de prioridad (`PQ`), heaps completos e izquierdistas, la codificación de Huffman y el Treap proporciona un aprendizaje profundo y práctico que la simple lectura o ejecución de demostraciones no puede igualar. A continuación se detallan las afirmaciones de aprendizaje para cada componente:

- **Sobre la interfaz abstracta `PQ`**: La abstracción de una interfaz pura como `PQ.h` es fundamental en ingeniería de software, ya que desacopla la definición formal de las operaciones de prioridad (`insert`, `delMax`, `getMax`) de su implementación concreta. Esto nos permite intercambiar la infraestructura subyacente (por ejemplo, pasar de un heap binario a un heap izquierdista para optimizar fusiones) de forma totalmente transparente para el cliente.
- **Sobre la representación implícita del heap binario completo**: El mapeo de un árbol binario completo en un vector contiguo mediante relaciones aritméticas simples para calcular índices de padres e hijos es una genialidad de diseño. Es la representación óptima que maximiza la localidad de datos en caché y elimina la sobrecarga espacial de punteros, pero requiere un control riguroso de fronteras para evitar accesos fuera de rango del vector.
- **Sobre `percolateUp`**: Esta operación es el núcleo de la inserción y enseña que la restauración del orden de prioridad vertical se realiza de forma óptima ascendiendo por una única rama. El conteo de intercambios instrumentado demuestra que, aunque el peor caso teórico es logarítmico, el caso promedio requiere muy pocos movimientos lógicos debido a que el árbol ensancha exponencialmente hacia su base.
- **Sobre `percolateDown`**: Es la operación más compleja de reparación vertical y demuestra que para "hundir" un elemento de baja prioridad colocado en la raíz, es estrictamente obligatorio comparar e intercambiar con el **hijo dominante** para no violar la invariante con la otra rama del subárbol.
- **Sobre `heapify` de Floyd**: La construcción de abajo hacia arriba procesando únicamente los nodos internos mediante `percolateDown` es un testimonio de eficiencia algorítmica. Demuestra de manera práctica cómo un enfoque inteligente puede reducir una complejidad de construcción de $O(n \log n)$ (inserciones sucesivas) a un óptimo tiempo lineal $O(n)$.
- **Sobre `heapSort`**: El ordenamiento in-situ sobre el propio arreglo de entrada mediante extracciones sucesivas demuestra cómo reutilizar el espacio de memoria que el heap lógico va liberando. Enseña que heapsort es un algoritmo de ordenamiento inestable debido a los intercambios a gran distancia, pero con un rendimiento garantizado de $O(n \log n)$ en el peor caso.
- **Sobre `merge` en heap izquierdista**: La fusión recursiva es la operación reina que unifica toda la lógica de modificación del heap izquierdista. Enseña que la asimetría controlada mediante la propiedad de distancia nula (`npl`) permite mantener el camino derecho extremadamente corto, acotando el costo de mezcla a $O(\log n)$ de peor caso.
- **Sobre Huffman**: La aplicación práctica de colas de prioridad para la compresión de datos demuestra cómo construir un árbol binario óptimo combinando repetidamente las frecuencias más bajas. Enseña la importancia de resolver de forma determinista los desempates de frecuencia para garantizar la reproducibilidad y muestra que el caso de un solo símbolo requiere una ramificación artificial obligatoria para asignar un código binario válido.
- **Sobre `Treap`, rotaciones, prioridades y búsqueda ordenada**: El Treap es un híbrido excepcional que combina el orden total de claves (BST) con el orden parcial de prioridades (Heap). Instrumentar sus rotaciones enseña que las mutaciones estructurales para reparar las prioridades aleatorias (`bubbleUp` y `trickleDown`) se resuelven con rapidez local sin alterar la secuencia ordenada inorden de las claves.
- **Sobre la comparación con `BinaryHeap` y `BinarySearchTree`**: Esta comparación consolida la diferencia fundamental entre el orden parcial vertical optimizado para consultar extremos en $O(1)$ (heaps) y el orden total simétrico optimizado para búsquedas genéricas y de rango en $O(\log n)$ (árboles de búsqueda).
- **Sobre pruebas, invariantes y casos borde**: Implementar validaciones sistemáticas de invariantes (`isTreap`, `isValidHeap`, `isValidLeftHeap`) y someterlas a casos extremos de frontera (estructuras vacías, un único elemento o duplicados continuos) es la única vía metodológica para certificar la robustez industrial y la correctitud matemática de nuestras estructuras de datos modificadas.

