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
