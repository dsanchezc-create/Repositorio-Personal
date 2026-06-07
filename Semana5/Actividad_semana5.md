## Actividad 5-CC232

    ### Integrantes
    - Luis David Sanchez Cirilo

##### Bloque 1

1. Árbol enlazado:
-Cada nodo es una estructura con punteros: parent, left, right.
-Los nodos están dispersos en memoria.
-Memoria: cada nodo ocupa espacio adicional para 3 punteros + dato + altura.
-Acceso: requiere seguir punteros (más lentos que acceso directo).
-Flexibilidad: puedes modificar la forma del árbol sin reorganizar memoria.

Árbol implícito en arreglo (como BinaryHeap en Semana 5):
-Los datos se guardan en un std::vector<T> data_.
-La estructura se deduce de índices: left(i) = 2*i + 1, right(i) = 2*i + 2, parent(i) = (i-1)/2.
-Memoria: solo el dato, sin punteros.
-Acceso: O(1) para acceder padre/hijos (cálculo de índices).
-Restricción: el árbol debe ser completo (todos los niveles llenos excepto posiblemente el último).

2. BinNode guarda:
data: El valor que almacena el nodo.
parent: Permite subir hacia la raíz (necesario para succ(), pred(), actualización de alturas ascendente).
left, right: Permiten descender hacia los subárboles.
height: Almacena la altura del subárbol. En un árbol balanceado (como AVL), determina si hay desequilibrio.

3. Sin parent, no podrías subir para encontrar el primer ancestro donde este nodo está en el subárbol izquierdo.
Después de insertar o eliminar, necesitas recalcular alturas desde el nodo afectado hacia la raíz. Solo con parent puedes hacerlo.

4. BinTree es una estructura de contenedor:
-Mantiene referencia a la raíz: Node* root_.
-Mantiene el tamaño total: int size_.
Responsabilidades:
    - Gestión de memoria: crear, destruir y reorganizar nodos.
    - Actualización global: cuando insertas, debes actualizar alturas hacia la raíz.
    - Operaciones de árbol completo: insertAsRoot(), insertAsLC(parent, ...), attachAsLC(), removeSubtree(), secede().
Invariantes: garantizar que el árbol sea válido (sin ciclos, enlaces coherentes).

5. BinaryTree hereda de BinTree y agrega:
*Iteradores:
    iterator: camina por el árbol inorden (usa succ()).
    node_iterator: camina visitando nodos, no datos.
    begin(), end(), nodesBegin(), nodesEnd().

*Funciones de navegación:
    depth(node): calcula profundidad subiendo por parent.
    height(node): calcula altura bajando recursivamente.
    subtreeSize(node): calcula tamaño del subárbol.
    firstNode(), lastNode(): nodo mínimo y máximo inorden.
    nextNode(), prevNode(): sucesor y predecesor.

*Recorridos internos múltiples (preorden, inorden, postorden, por niveles).

*Utilidad visual: asciiArt() para imprimir el árbol en texto.

6. La propiedad BST: Para todo nodo u:
Todo nodo en el subárbol izquierdo de u tiene valor menor que u->data.
Todo nodo en el subárbol derecho de u tiene valor mayor que u->data.

7. Propiedad de min-heap: Para todo nodo en índice i:
El valor en i es menor o igual que el valor en 2*i + 1 (hijo izquierdo).
El valor en i es menor o igual que el valor en 2*i + 2 (hijo derecho).

8.
|       Aspecto        |                            BST                     |               Min-Heap                |
|----------------------|----------------------------------------------------|---------------------------------------|
|Propiedad             |	Orden total: izq < padre < der	                  |Orden parcial: padre < hijos           |
|Búsqueda              |	O(log n) balanceado, O(n) degenerado	            |No hay búsqueda eficiente              |
|Recorrido ordenado    |	Inorden da secuencia ordenada                     |	No hay recorrido ordenado sin destruir|
|Mínimo                |	Requiere buscar (nodo más a la izquierda)	        |O(1)): siempre en la raíz              |
|Inserción             |	O(log n) balanceado, O(n) degenerado	            |O(log n) siempre (bubbleUp)            |
|Eliminación del mínimo|	O(log n) balanceado, compleja (caso 2 hijos)	    |O(log n) siempre (trickleDown)         |
|Representación        |	Enlazada (con punteros)	                          |Implícita (arreglo)                    |
|Caso de uso           |	Búsqueda, rango, inorden	                        |Colas de prioridad, heapsort           |

9.
El recorrido inorden visita: izquierda → nodo → derecha.
Todos en subárbol izquierdo son menores: Por la propiedad BST, todo nodo en subárbol izquierdo tiene valor < padre.
El nodo es mayor que su subárbol izquierdo: Por construcción.
Todos en subárbol derecho son mayores: Por la propiedad BST.
El nodo es menor que su subárbol derecho: Por construcción.

Por inducción, si los subárboles izquierdo y derecho producen secuencias ordenadas cuando se recorren inorden, entonces:
-Inorden del subárbol izquierdo: todos < padre.
-Padre.
-Inorden del subárbol derecho: todos > padre.

10. Un heap solo se preocupa por mantener el mínimo en la raíz. No organiza los demás elementos en orden.

Un heap puede verse así:
       1 (mínimo)
      / \
     3   2
    / \
   5   4

Si se hiciera un recorrido "normal" visitando: izquierda → nodo → derecha, obtendrías:
5, 3, 1, 4, 2

Pero los números reales en orden son:
1, 2, 3, 4, 5

No coinciden. El heap no está "construido" para que un recorrido simple te dé orden.


##### Bloque 2

1. Estas son funciones booleanas que consultan la estructura:

-bool hasLeft() const { return left != nullptr; }      // ¿Tiene hijo izquierdo?
-bool hasRight() const { return right != nullptr; }    // ¿Tiene hijo derecho?
-bool isRoot() const { return parent == nullptr; }     // ¿Es la raíz (sin padre)?
-bool isLeaf() const { return left == nullptr && right == nullptr; }  // ¿Es hoja (sin hijos)?
-bool isLeftChild() const { return parent != nullptr && parent->left == this; }  // ¿Es hijo izquierdo de su padre?
-bool isRightChild() const { return parent != nullptr && parent->right == this; } // ¿Es hijo derecho de su padre?

Sirven para evitar escribir comparaciones largas. 


2.
Node* succ() {
  Node* s = this;
  if (right != nullptr) {           // Si tiene subárbol derecho
    s = right;                       // Baja al hijo derecho
    while (s->left != nullptr) {     // Busca el nodo más a la izquierda
      s = s->left;
    }
    return s;                        // Ese es el sucesor
  }
  // ... resto del código
}

Un ejemplo visualizado:    
       7
      / \
     3   10        Si estoy en 7 y quiero sucesor:
    / \ / \        - Tiene derecho (10)
   1  5 8 12       - Bajo a 10
                   - Busco izquierda: 8 está a la izquierda
                   - 8 no tiene izquierda, me detengo
                   - sucesor(7) = 8 ✓


Por qué funciona: En un recorrido inorden, después de visitar un nodo, visitas todo su subárbol derecho comenzando por el más pequeño del subárbol derecho (que es el nodo más a la izquierda).


3. 
Node* succ() {
  Node* s = this;
  if (right != nullptr) {
    // ... (caso anterior)
  }
  // Si NO tiene subárbol derecho, sube
  while (s->isRightChild()) {        // Mientras sea hijo derecho de su padre
    s = s->parent;                   // Sube
  }
  return s->parent;                  // El padre es el sucesor
}

Un ejemplo visualizado:
       7
      / \
     3   10
    / \ / \
   1  5 8 12

Si estoy en 5 y quiero sucesor:
- 5 no tiene subárbol derecho
- 5 es hijo derecho de 3, subo a 3
- 3 es hijo izquierdo de 7, me detengo
- El padre de 3 es 7
- sucesor(5) = 7 ✓

Si estoy en 6 (hijo derecho de 5):
- 6 no tiene subárbol derecho
- 6 es hijo derecho de 5, subo a 5
- 5 es hijo derecho de 3, subo a 3
- 3 es hijo izquierdo de 7, me detengo
- El padre de 3 es 7
- sucesor(6) = 7 ✓

Por qué funciona: Cuando un nodo no tiene subárbol derecho, su sucesor es el primer ancestro donde el nodo está en el subárbol izquierdo (es decir, donde dejamos de ser "hijo derecho").


**4. `pred()` - Simétrico de `succ()`**

- Si el nodo tiene hijo izquierdo: baja a `left`, sigue bajando por `right` hasta hoja
- Si el nodo NO tiene hijo izquierdo: sube por `parent` hasta encontrar nodo que es hijo derecho de su padre, el padre es predecesor

**5. Árbol de 9 nodos con sucesor/predecesor de 3 nodos**

```
         7
       /   \
      3     10
     / \   /  \
    1   5 8   12
       / \
      4   6
```

Sucesor/predecesor:
- Nodo 5: sucesor=6, predecesor=4
- Nodo 3: sucesor=4, predecesor=1
- Nodo 10: sucesor=12, predecesor=8

**6. `depth(u)` - Distancia de nodo a raíz**

`depth(u)` = número de pasos desde `u` hasta raíz.

**Implementación subiendo por `parent`**:
```cpp
int depth(Node* u) {
    int d = 0;
    while (!u->isRoot()) {
        u = u->parent;
        ++d;
    }
    return d;
}
```

**Razón**: con `parent` puedes subir; sin ella, tendrías que partir de raíz (O(n) en peor caso).

**7. `height(u)` - Altura del subárbol en `u`**

`height(u)` = número de pasos desde `u` hasta la hoja más lejana de su subárbol.

**Implementación bajando recursivamente**:
```cpp
int height(Node* u) {
    if (u->isLeaf()) return 0;
    int left_h = u->hasLeft() ? height(u->left) : -1;
    int right_h = u->hasRight() ? height(u->right) : -1;
    return 1 + std::max(left_h, right_h);
}
```

**Razón**: necesitas explorar subárbol para saber profundidad de hojas.

**8. `subtreeSize(u)` - Cantidad de nodos en subárbol**

`subtreeSize(u)` = número total de nodos en el subárbol enraizado en `u`.

```cpp
std::size_t size(Node* u) {
    std::size_t ls = u->hasLeft() ? u->left->size() : 0;
    std::size_t rs = u->hasRight() ? u->right->size() : 0;
    return 1 + ls + rs;
}
```

En el árbol ejemplo: 
- `subtreeSize(5)` = 1 + 1 + 1 = 3 (nodos 4, 5, 6)
- `subtreeSize(3)` = 1 + 1 + 3 = 5 (nodos 1, 3, 4, 5, 6)

**9. Demostración de `depth(u) + height(u) <= height(T)`**

Sea `u` un nodo, `T` el árbol completo.
- `depth(u)` = pasos desde `u` hasta raíz
- `height(u)` = pasos desde `u` hasta hoja más lejana en su subárbol
- `height(T)` = pasos desde raíz hasta hoja más lejana del árbol

**Camino máximo desde raíz a hoja**: raíz → ... → u → ... → hoja
- Este camino tiene `depth(u) + height(u)` pasos
- Debe ser ≤ `height(T)` (el máximo del árbol)

**Conclusión**: `depth(u) + height(u) <= height(T)` por definición de altura.

**10. Condición para igualdad `depth(u) + height(u) == height(T)`**

**Condición**: `u` está en un camino **máximo** desde raíz a hoja (el camino que determina `height(T)`).

En el árbol ejemplo:
- Nodo 4: depth=3, height=0, suma=3=height(T) ✓ (camino máximo)
- Nodo 8: depth=2, height=0, suma=2<3 ✗ (no es camino máximo)

**Conclusión**: igualdad si y solo si existe camino raíz-a-hoja que pasa por `u` y tiene longitud exactamente `height(T)`.

#### Resultados del Experimento Bloque 2

**Profundidades observadas**:
- Nodo 7 (raíz): depth=0
- Nodo 3: depth=1
- Nodo 5: depth=2
- Nodo 4: depth=3

**Alturas observadas**:
- Árbol completo: height=3
- Nodo 7 (raíz): height=3
- Nodo 3: height=2
- Nodo 5: height=1
- Nodo 4 (hoja): height=0

**Verificación propiedad**:
- `depth(4) + height(4) = 3 + 0 = 3 = height(T)` ✓ (nodo 4 está en camino máximo)

**Tamaños de subárbol**:
- Subárbol en raíz: 9 nodos
- Subárbol en nodo 3: 5 nodos
- Subárbol en nodo 5: 3 nodos
- Subárbol en nodo 4 (hoja): 1 nodo



##### Bloque 3

Arbol de ejemplo:
           7
          / \
         3   10
        / \ / \
       1  5 8  12
        / \
       4   6



| Recorrido | Versión revisada | Estructura auxiliar usada | Secuencia producida | Argumento de correctitud y costo |
|-----------|------------------|--------------------------|---------------------|----------------------------------|
| Preorden | Recursivo | Pila de llamadas implícita | `7, 3, 1, 5, 4, 6, 10, 8, 12` | Visita nodo antes de subárboles. Cada nodo visitado una vez. **O(n) tiempo, O(h) espacio** |
| Preorden | Iterativo | `std::stack<Node*>` | `7, 3, 1, 5, 4, 6, 10, 8, 12` | Apila derecha primero, izquierda después (LIFO simula recursión). **O(n) tiempo, O(h) espacio** |
| Inorden | Recursivo | Pila de llamadas implícita | `1, 3, 4, 5, 6, 7, 8, 10, 12` | Visita izquierda, nodo, derecha. En BST produce orden ascendente. **O(n) tiempo, O(h) espacio** |
| Inorden | Iterativo #1 | `std::stack<Node*>` | `1, 3, 4, 5, 6, 7, 8, 10, 12` | Baja izquierda apilando, desapila y visita, va a derecha. **O(n) tiempo, O(h) espacio** |
| Inorden | Iterativo #2 | Punteros `prev`, `curr` sin estructura | `1, 3, 4, 5, 6, 7, 8, 10, 12` | Rastrear transición (padre→hijo, izq→nodo, der→padre). Requiere `parent`. **O(n) tiempo, O(1) espacio auxiliar, lógica más compleja** |
| Inorden | Iterativo #3 | `succ()` sin estructura auxiliar | `1, 3, 4, 5, 6, 7, 8, 10, 12` | Iterar `succ()` desde mínimo hasta nulo. Respeta inorden. **O(n) tiempo, O(1) espacio, pero `succ()` toma O(h) por llamada** |
| Postorden | Recursivo | Pila de llamadas implícita | `1, 4, 6, 5, 3, 8, 12, 10, 7` | Visita subárboles antes del nodo. Útil para eliminar. **O(n) tiempo, O(h) espacio** |
| Postorden | Iterativo | `std::stack<Node*> s1, s2` (dos pilas) | `1, 4, 6, 5, 3, 8, 12, 10, 7` | Primera pila preorden; segunda invierte. **O(n) tiempo, O(n) espacio (peor caso)** |
| Por niveles | BFS con cola | `std::queue<Node*>` | `7, 3, 10, 1, 5, 8, 12, 4, 6` | Procesa por nivel (FIFO). **O(n) tiempo, O(w) espacio donde w = ancho máximo ≤ n** |

1. Preorden significa visitar un nodo antes de recorrer sus subárboles (antes de descender). El orden es: nodo → subárbol izquierdo → subárbol derecho.

En el árbol de ejemplo:
-Visito 7 (la raíz) primero.
-Luego todo el subárbol izquierdo (3, 1, 5, 4, 6).
-Luego todo el subárbol derecho (10, 8, 12).


2. Inorden significa visitar un nodo entre sus subárboles. El orden es: subárbol izquierdo → nodo → subárbol derecho.

En el árbol de ejemplo:
-Primero todo lo de la izquierda de 7: recorro 3 (y su izquierda: 1; y su derecha: 5, 4, 6).
-Luego 7 mismo.
-Luego todo lo de la derecha de 7: recorro 10 (y su izquierda: 8; y su derecha: 12).

3. Postorden significa visitar un nodo después de recorrer sus subárboles (después de descender). El orden es: subárbol izquierdo → subárbol derecho → nodo.

En el árbol de ejemplo:
-Visito todo el subárbol izquierdo: 1, 4, 6, 5, 3.
-Visito todo el subárbol derecho: 8, 12, 10.
-Finalmente visito la raíz: 7.

4. Recorrido por niveles (BFS, Breadth-First Search) visita los nodos nivel por nivel, de izquierda a derecha. Es como leer el árbol horizontalmente.

En el árbol de ejemplo:
Nivel 0: 7
Nivel 1: 3, 10
Nivel 2: 1, 5, 8, 12
Nivel 3: 4, 6


5. Porque cada nodo se visita exactamente una vez.
-Cada nodo hace un llamada recursiva.
-Cada nodo ejecuta el trabajo de visita (O(1)).
-No hay trabajo redundante (no revisitas nodos). 
No importa si el árbol es balanceado o degenerado: siempre visitas todos los n nodos una sola vez.


6. Por la misma razón: cada nodo se procesa exactamente una vez.
-Cada nodo se apila exactamente una vez.
-Cada nodo se desapila exactamente una vez.
-Cuando se desapila, ejecutas el trabajo de visita (O(1)) y posiblemente apila sus hijos (O(1) por hijo).

Ejemplo: En inorden iterativo #1:
-Cada nodo se apila cuando bajamos por la izquierda.
-Se desapila, se visita, y vamos a la derecha.
-Los hijos se apilan después.


7. En un árbol balanceado, la profundidad es O(log(n)).
Cada nivel de recursión usa espacio en la pila de llamadas. La profundidad máxima es la altura del árbol: 
h = O(log(n))

Memoria auxiliar: 
O(logn) (profundidad × tamaño de cada marco de activación, que es O(1)).


8. En un árbol degenerado (lista enlazada), la profundidad es O(n).
Cada nodo profundiza un nivel más en la recursión. La pila de llamadas crece hasta tener O(n) marcos simultáneamente.

Memoria auxiliar: 
O(n) (peor caso: profundidad × O(1) por marco).

**Conclusión**: la pila explícita es más segura que recursión para árboles degenerados.

**9. Diferencia: pila explícita vs pila de llamadas**

| Aspecto | Pila de llamadas | Pila explícita |
|--------|-----------------|---|
| **Control** | Implícito (sistema) | Explícito (programador) |
| **Límite** | Stack size fijo (~MB) | Heap dinámico (GB disponibles) |
| **Overhead** | Mayor (marcos de función) | Menor (solo datos) |
| **Debugging** | Backtrace automático | Manual |
| **Seguridad** | Riesgo de overflow con árboles degenerados | Manejo explícito de errores |

**Resumen**: ambas son O(n) en tiempo, pero la pila explícita es más segura y escalable.

**10. ¿Por qué la cola en BFS crece más en árbol completo que degenerado?**

**Árbol completo** (todas capas llenas):
- Nivel k tiene 2^k nodos
- En nivel máximo (altura h), cola contiene 2^h nodos
- Máximo: 2^(h+1) - 1 nodos, pero la cola puede tener hasta 2^h = O(n/2)

**Árbol degenerado** (cadena):
- Cada nivel tiene 1 nodo
- Cola siempre contiene 1 elemento
- Máximo: O(1)

**Razón**: árbol completo explota el ancho; degenerado es profundo pero estrecho.

#### Resultados del Experimento Bloque 3

Árbol de prueba: raíz 7, izq 3, der 10, con subárbol izquierdo de 3 siendo 1, 5 (donde 5 tiene 4, 6), y subárbol derecho siendo 8, 12.

**Recorridos ejecutados**:
- Preorden recursivo = Preorden iterativo = `7 3 1 5 4 6 10 8 12`
- Inorden recursivo = Inorden iterativo #1 = Inorden iterativo #2 = Inorden iterativo #3 = `1 3 4 5 6 7 8 10 12` (ordenado)
- Postorden recursivo = Postorden iterativo = `1 4 6 5 3 8 12 10 7`
- Niveles = `7 3 10 1 5 8 12 4 6`

**Observación**: todas las versiones (recursiva e iterativas) producen secuencias idénticas, defendiendo correctitud.



##### Bloque 4

##### Tabla de Demostraciones

| Archivo | Salida observable importante | Idea estructural | Argumento de costo/diseño |
|---------|------|------|------|
| `demo_binary_tree.cpp` | Preorden/Inorden/Postorden/Niveles (todas coinciden recursiva con iterativa) | Recorridos múltiples, sucesor/predecesor, altura, profundidad | O(n) para cada recorrido; pila auxiliar O(log n) a O(n) según forma |
| `demo_bst.cpp` | Inorden=`1 3 4 5 6 7 8 10 12` (ordenado); rotaciones preservan ordenamiento | Búsqueda binaria, eliminación, rotaciones locales | Búsqueda O(log n) promedio si balanceado, O(n) peor |
| `demo_heap.cpp` | Heapify=`1 3 2 7 5 8 10`; extracción repetida=`0 1 2 3 5 7 8 10` (ordenada) | Representación implícita en vector, bubbleUp/trickleDown | Add O(log n), remove O(log n), heapify O(n) |
| `demo_capitulo5_panorama.cpp` | Heap mínimo=1; BST raíz=9, altura=2; iterador STL produce inorden | Integración: árbol enlazado + BST + heap, iteradores | Generalidad de estructuras |

**Respuestas a preguntas del Bloque 4**:

**1. En `demo_binary_tree.cpp`, ¿qué salida permite verificar orden esperado?**

Las líneas:
```
Preorden recursivo: 7 3 1 5 4 6 10 8 12
Preorden iterativo: 7 3 1 5 4 6 10 8 12
...
Inorden recursivo: 1 3 4 5 6 7 8 10 12
Inorden iterativo #1-#3: [idéntico]
Sucesor de 5: 6
Predecesor de 5: 4
```

**Defensa**: coincidencia exacta entre recursivo e iterativo valida correctitud. Sucesor/predecesor confirman inorden.

**2. ¿Qué parte permite defender `succ()` y `pred()`?**

```
Sucesor de 5: 6
Predecesor de 5: 4
Iteracion por sucesor: 1 3 4 5 6 7 8 10 12
```

El recorrido por sucesor produce exactamente la secuencia inorden. Si `succ()` estuviera roto, la secuencia sería desordenada.

**3. ¿Qué evidencia produce ASCII?**

La representación visual muestra:
- Estructura exacta del árbol
- Relaciones padre-hijo
- Profundidad de cada nodo
- Facilita verificación manual de propiedades

**4. En `demo_bst.cpp`, ¿qué permite defender inorden ordenado?**

```
BST inorden: 1 3 4 5 6 7 8 10 12
Tras remove(3): 1 4 5 6 7 8 10 12
Tras rotateLeft: [mantiene ordenamiento]
```

La secuencia está ordenada numéricamente. Tras operaciones (remove, rotate), sigue ordenada. Esto defiende que la propiedad BST se mantiene.

**5. ¿Qué operaciones de búsqueda se distinguen mejor?**

```
findEQ(5): 5 (encontró exacto)
lowerBound(9): 10 (primer >= 9)
upperBound(8): 10 (primer > 8)
findLast(9): 8 (último < 9)
```

`lowerBound` y `upperBound` se distinguen claramente: uno incluye igualdad, otro es estrictamente mayor. Son operaciones distintas, ambas útiles.

**6. En `demo_heap.cpp`, ¿qué permite defender mínimo en raíz?**

```
Heapify: 1 3 2 7 5 8 10
isHeap: si
```

El primer elemento (índice 0) es 1 (mínimo de {7,3,10,1,5,8,2}). Heapify verificó la propiedad. Esto defiende que la estructura garantiza raíz = mínimo.

**7. ¿Evidencia entre `add()` y `heapify()`?**

```
Heapify: 1 3 2 7 5 8 10
Tras add(0): 0 1 2 3 5 8 10 7
```

Ambas dejan un heap válido, pero en diferente forma. `add()` inserta y restaura incrementalmente; `heapify()` lo hace de arriba hacia abajo. Resultado: ambos válidos.

**8. En panorama, ¿qué resume mejor la semana?**

El output combina:
- Heap mínimo en O(1): `top()` devuelve 1
- BST búsqueda ordenada: `isBST()` valida
- Iterador `range-for`: `for (int x : bst)` produce `2 4 7 9 10 12 15` (inorden)

**Resumen**: la semana une tres estructuras árbol que resuelven distintos problemas (prioridad, búsqueda, acceso secuencial).


##### Bloque 5

1. ¿Qué operaciones del BST valida la prueba pública?
En `test_public_week5.cpp` se validan las siguientes operaciones de `BinarySearchTree`:
* **Inserción**: `add(x)` para añadir nuevas claves y verificar el rechazo de duplicados.
* **Recorridos**: `inorder()` recursivo y tres variantes iterativas (`Iterative1`, `Iterative2`, `Iterative3`).
* **Búsqueda exacta**: `findEQ(x)` para localizar un nodo con la clave precisa.
* **Búsquedas aproximadas y de frontera**: `find(x)`, `lowerBound(x)` y `upperBound(x)`.
* **Extremos**: `minNode()` y `maxNode()` para identificar los elementos menor y mayor.
* **Eliminación**: `remove(x)` para descartar claves existentes y comprobar su remoción física con `contains(x)`.
* **Construcción y balanceo**: `buildBalancedFromSorted(v)` para inicializar un árbol con altura mínima a partir de un arreglo ordenado.
* **Consistencia e Iteración**: `isBST()`, `checkParentLinks()` y soporte para iteración por rango (*range-for*).

2. ¿Qué casos validan que el BST no acepta duplicados?
La restricción de claves duplicadas se verifica al inicio de la prueba pública. Tras poblar el árbol con un conjunto de claves (dentro de las cuales ya se encuentra el valor `5`), se ejecuta la siguiente aserción:
```cpp
expect(!bst.add(5), "BST no debe aceptar duplicados");
```

3. ¿Qué se verifica al comparar el inorden recursivo con las versiones iterativas?
Se verifica que las tres estrategias iterativas implementadas en la biblioteca (`InorderStrategy::Iterative1`, `Iterative2` y `Iterative3`) produzcan el mismo recorrido ordenado que la llamada recursiva estándar de `inorder()`. Esto asegura la correctitud de los algoritmos de recorrido iterativos (los cuales pueden usar pilas explícitas, enlaces `parent` o enhebrado/sucesores) sin consumir espacio en la pila de llamadas del sistema, previniendo posibles desbordamientos de pila (*stack overflow*) ante árboles de gran altura.

 4. ¿Qué se espera de `findEQ(8)` en la prueba pública?
Se espera que la llamada a `findEQ(8)` retorne un puntero no nulo a un nodo del árbol cuya clave interna (`data`) sea exactamente `8`.

```cpp
expect(bst.findEQ(8) != nullptr && bst.findEQ(8)->data == 8, "findEQ debe ubicar una clave exacta");
```
5. ¿Qué se espera de `lowerBound(9)` y `upperBound(8)`?
* **`lowerBound(9)`**: Se espera que localice el nodo con la clave más pequeña que sea mayor o igual que `9`. En el árbol de prueba actual, el elemento que satisface esta condición es `10`.
* **`upperBound(8)`**: Se espera que retorne el nodo con la clave más pequeña que sea estrictamente mayor que `8`. En el contexto del árbol poblado, el resultado correcto es `10`.

6. ¿Qué propiedad se valida con `isBST()`?
Se valida la **invariante de orden del Árbol Binario de Búsqueda**: para cada nodo del árbol, todas las claves contenidas en su subárbol izquierdo deben ser estrictamente menores que la clave del nodo actual, y todas las claves en su subárbol derecho deben ser estrictamente mayores.

7. ¿Qué se valida después de eliminar un nodo con `remove()`?
Tras la llamada a `bst.remove(3)`, las pruebas públicas validan consecutivamente que:
1. La función devuelva `true` (confirmando que el nodo se borró exitosamente).
2. El recorrido `inorder()` del BST siga saliendo ordenado y ya no incluya el elemento `3`.
3. `contains(3)` retorne `false` (validando la exclusión real del nodo).
4. `checkParentLinks()` siga retornando `true`, lo que certifica que el proceso de reestructuración (sea por remoción de hoja, de nodo con un hijo, o sustitución por sucesor) mantuvo íntegros los punteros a los padres.

8. ¿Qué valida `checkParentLinks()` después de borrar, separar o adjuntar subárboles?
Valida la **consistencia bidireccional de los punteros en la estructura**. Verifica de manera exhaustiva que para cada nodo hijo `u` apuntado por un nodo padre `p` (ya sea por la izquierda o la derecha), se cumpla estrictamente que `u->parent == p`. Este chequeo garantiza que ninguna operación de modificación estructural (como la remoción en BST, inserciones, divisiones con `secede` o uniones con `attachAsRC`) deje referencias corruptas o rotas que puedan degradar la navegación ascendente.

9. ¿Qué operaciones del heap valida la prueba pública?
Se evalúan las siguientes operaciones de `BinaryHeap`:
* **Construcción lineal (*heapify*)**: Creación de la estructura en tiempo lineal $O(n)$ a partir de un vector desordenado de enteros.
* **Verificación de invariante**: Comprobación con `isHeap()` para asegurar la consistencia del min-heap recién construido.
* **Extracción de extremos**: Llamadas sucesivas a `remove()` para retirar el elemento mínimo actual de la estructura.
* **Verificación abstracta**: El método estático `BinaryHeap<int>::isHeapArray(...)` que comprueba si un arreglo arbitrario representa un heap binario válido.

10. ¿Qué demuestra extraer repetidamente de un min-heap hasta vaciarlo?
Demuestra que los elementos extraídos se recuperan en un **orden ascendente estricto** (`[1, 2, 3, 5, 7, 8, 10]`). Esto valida de forma práctica que:
1. El elemento con la prioridad mínima siempre se encuentra ubicado en la raíz (índice 0).
2. La operación de remoción extrae el mínimo y promueve el último nodo a la raíz para luego aplicar una filtración descendente (`trickleDown` / `percolateDown`) correcta.
3. El heap se auto-organiza en tiempo $O(\log n)$ en cada paso, lo que fundamenta el correcto funcionamiento del algoritmo *Heap Sort*.

11. ¿Qué operaciones de `BinTree` se validan con `attachAsRC`, `secede` y `removeSubtree`?
* **`attachAsRC(root, extra)`**: Valida la inserción de un subárbol entero en la posición de hijo derecho. Se constata que el tamaño acumulado del árbol anfitrión se incremente consistentemente (`host.size() == 4`) y que el árbol anexado quede limpio y vacío (`extra.empty()`).
* **`secede(node)`**: Valida la extracción de un subárbol completo a partir de un nodo específico. Se verifica que el árbol receptor disminuya su tamaño, que el subárbol removido retenga sus nodos originales (`detached.size() == 3`) y que conserve sus enlaces parentales válidos.
* **`removeSubtree(node)`**: Valida la desasignación recursiva y segura de un subárbol en la memoria, asegurando que no queden pérdidas de memoria y que el árbol final quede completamente vacío.

12. ¿Qué agregan las pruebas internas respecto a rotaciones, `bubbleUp`, `trickleDown`, profundidad, altura, sucesor y predecesor?
Las pruebas internas (`test_internal_week5.cpp`) se diseñaron para evaluar métodos críticos de bajo nivel o de acceso restringido en producción:
* **Rotaciones (`rotateRight` y `rotateLeft`)**: Verifican que las rotaciones locales alteren de forma controlada la raíz del subárbol involucrado sin quebrantar la propiedad inorden del BST ni corromper los enlaces parentales.
* **`bubbleUp`**: Valida que la inserción de elementos en un heap ejecute la filtración ascendente adecuada, llevando el valor mínimo (`1`) a la raíz.
* **`trickleDown`**: Comprueba que la extracción de la raíz descienda de forma correcta el nodo provisional y deje el nuevo mínimo (`2`) en el tope del heap.
* **Profundidad y Altura**: Aseguran que `depth()` e `height()` computen valores correctos respecto a los niveles de profundidad del árbol y que la función interna `updateHeightAbove` mantenga actualizadas las alturas al mutar nodos.
* **Navegación por Sucesores/Predecesores**: Valida que las funciones no recursivas de sucesor y predecesor (`succ()` y `pred()`) permitan recorrer ordenadamente el árbol hacia adelante (`iterateBySuccessor()`) o hacia atrás (`iterateByPredecessor()`).

13. ¿Qué sí demuestra pasar las pruebas públicas?
Demuestra que la interfaz pública expuesta por el TAD (Tipo Abstracto de Datos) cumple con los requisitos y escenarios de uso estándar provistos en los casos de prueba seleccionados. Asegura que bajo las entradas dadas, el programa no genera fallos del sistema o resultados inválidos en las operaciones básicas de consulta, inserción y remoción.

14. ¿Qué no demuestra pasar las pruebas públicas?
No demuestra:
* **La total ausencia de fugas de memoria** (*memory leaks*) u otros problemas de desasignación dinámica que solo analizadores dinámicos de código (como Valgrind o AddressSanitizer) pueden detectar.
* **La estabilidad del código frente a casos límite** no modelados (ej. árboles degenerados que simulen listas enlazadas que puedan desbordar la pila de llamadas ante recorridos recursivos).
* **El cumplimiento de la complejidad de peor caso**: un BST desbalanceado con operaciones que degraden a $O(n)$ puede pasar las pruebas de funcionalidad si el tamaño $n$ de los datos es reducido.
* **La seguridad ante accesos concurrentes** (*thread safety*) en entornos multiproceso.

15. ¿Por qué una defensa correcta debe mencionar invariantes y complejidad además de resultados observables?
Una argumentación basada únicamente en "las pruebas pasaron" es incompleta en ciencias de la computación debido a que:
* **Invariantes estructurales**: Son las condiciones lógicas y matemáticas que garantizan el correcto funcionamiento de una estructura en cualquier momento (ej. la relación de orden en BST, o el balance de caminos izquierdistas en `LeftHeap`). Comprenderlas y defenderlas explica por qué la estructura conserva su correctitud tras sufrir modificaciones estructurales complejas.
* **Complejidad algorítmica**: Representa la garantía del comportamiento del sistema a gran escala. Aprobar un test funcional con un número pequeño de elementos no asegura la viabilidad práctica de la estructura cuando $n$ crece. Explicar y justificar el costo de tiempo (ej. por qué buscar o remover cuesta $O(\log n)$ y no $O(n)$) valida que la estructura está implementada de manera eficiente para soportar cargas de producción.

##### Bloque 6 

1. En `BinNode`, ¿qué invariantes deben mantenerse entre `parent`, `left` y `right`?

Las invariantes fundamentales de `BinNode` son:

1. **Bidireccionalidad padre-hijo**: Si `u->left == v`, entonces `v->parent == u`. Si `u->right == v`, entonces `v->parent == u`.
2. **Unicidad del padre**: Cada nodo tiene exactamente un padre (excepto la raíz con `parent == nullptr`).
3. **No ciclos**: Siguiendo `parent` desde cualquier nodo se llega eventualmente a la raíz (`nullptr`).
4. **Consistencia de altura**: `height = 1 + max(stature(left), stature(right))`. La altura debe reflejar la estructura real del subárbol.
5. **Sin auto-referencias**: Un nodo no puede ser su propio padre, hijo izquierdo ni hijo derecho.

Estas invariantes son verificadas por `checkParentLinks()` en `BinTree`, que recorre recursivamente confirmando que cada `node->parent` coincide con el padre esperado.

2. ¿Por qué `insertAsLC` e `insertAsRC` deben rechazar una inserción cuando el hijo correspondiente ya existe?

```cpp
Node* insertAsLC(const T& value) {
  if (left != nullptr) {
    throw std::logic_error("El hijo izquierdo ya existe");
  }
  left = new Node(value, this);
  return left;
}
```

**Razones**:
1. **Protección contra memory leaks**: Si se permitiera sobrescribir, se perdería la referencia al subárbol anterior sin liberar su memoria.
2. **Preservación de la estructura**: Un árbol binario enlazado bien formado no debe tener "orphan subtrees" (subárboles sin referencia desde el padre pero aún enlazados).
3. **Control explícito**: Si el programador quiere reemplazar un subárbol, debe usar `removeSubtree()` o `secede()` primero — operaciones que manejan explícitamente la memoria y los punteros.
4. **Detección temprana de errores**: Lanzar una excepción en lugar de sobrescribir silenciosamente ayuda a detectar bugs de lógica.

3. Explica cómo `size()` de `BinNode` recorre el subárbol

```cpp
std::size_t size() const {
  const std::size_t ls = (left == nullptr) ? 0U : left->size();
  const std::size_t rs = (right == nullptr) ? 0U : right->size();
  return 1U + ls + rs;
}
```

Es una **recursión postorden**:
1. Si el hijo izquierdo existe, llama recursivamente a `left->size()` (obtiene el tamaño del subárbol izquierdo)
2. Si el hijo derecho existe, llama recursivamente a `right->size()` (obtiene el tamaño del subárbol derecho)
3. Retorna `1 + tamañoIzquierdo + tamañoDerecho`

**Costo**: O(n) donde n es el número de nodos en el subárbol — visita cada nodo exactamente una vez. No usa caché ni campo precalculado; cada llamada recalcula desde cero.

**Nota importante**: `BinTree` mantiene un campo `size_` a nivel de árbol, pero `size()` de `BinNode` es independiente y recorre el subárbol cada vez. Esto es útil para verificación (ej. tras `secede`, comparar `node->size()` con `tree.size_`).

4. Explica cómo funcionan `leftmost()` y `rightmost()`

**`leftmost()`** — encuentra el nodo más a la izquierda del subárbol:
```cpp
Node* leftmost() {
  Node* u = this;
  while (u->left != nullptr) {
    u = u->left;
  }
  return u;
}
```
- Comienza en `this`
- Mientras exista hijo izquierdo, avanza hacia la izquierda
- Retorna el nodo sin hijo izquierdo (el mínimo en inorden del subárbol)
- **Costo**: O(h) donde h es la altura del subárbol

**`rightmost()`** — simétrico, encuentra el nodo más a la derecha:
```cpp
Node* rightmost() {
  Node* u = this;
  while (u->right != nullptr) {
    u = u->right;
  }
  return u;
}
```
- Avanza por `right` hasta que no haya más
- Retorna el máximo en inorden del subárbol

**Uso**: `firstNode()` de `BinaryTree` llama a `root_->leftmost()` (primer nodo en inorden). `lastNode()` llama a `root_->rightmost()` (último nodo en inorden). También se usan en `succ()` y `pred()`.

5. Explica paso a paso cómo funciona `succ()`

```cpp
Node* succ() {
  Node* s = this;
  if (right != nullptr) {           // Caso 1: tiene hijo derecho
    s = right;                      // Baja al hijo derecho
    while (s->left != nullptr) {    // Luego todo a la izquierda
      s = s->left;
    }
    return s;                       // Ese es el sucesor
  }
  while (s->isRightChild()) {       // Caso 2: no tiene hijo derecho
    s = s->parent;                  // Sube mientras sea hijo derecho
  }
  return s->parent;                 // El padre del primer giro izquierdo
}
```

**Caso 1 — Tiene hijo derecho** (ej. nodo 5 con hijo derecho 6 y nieto izquierdo de 6):
1. Baja a `right` (nodo 6)
2. Sigue bajando por `left` hasta que no haya más (llega a la hoja más izquierda del subárbol derecho)
3. Ese nodo es el sucesor — el siguiente en inorden

**Caso 2 — No tiene hijo derecho** (ej. nodo 4, hoja izquierda):
1. Sube por `parent` mientras el nodo actual sea hijo derecho de su padre
2. Cuando encuentra un nodo que es hijo izquierdo (o llega a la raíz), se detiene
3. El padre de ese nodo es el sucesor
4. Si llega a la raíz y nunca fue hijo izquierdo, `s->parent` es `nullptr` (no hay sucesor — es el último nodo)

**Ejemplo concreto en el árbol de prueba (7 raíz, 3 izq, 10 der...)**:
- `succ(4)`: no tiene derecho, sube: 4 es hijo izq de 5 → `succ(4) = 5`
- `succ(6)`: no tiene derecho, sube: 6 es hijo der de 5, 5 es hijo der de 3, 3 es hijo izq de 7 → `succ(6) = 7`
- `succ(12)`: no tiene derecho, 12 es hijo der de 10, 10 es hijo der de 7 → `succ(12) = nullptr`

6. Explica paso a paso cómo funciona `pred()`

```cpp
Node* pred() {
  Node* s = this;
  if (left != nullptr) {            // Caso 1: tiene hijo izquierdo
    s = left;                       // Baja al hijo izquierdo
    while (s->right != nullptr) {   // Luego todo a la derecha
      s = s->right;
    }
    return s;                       // Ese es el predecesor
  }
  while (s->isLeftChild()) {        // Caso 2: no tiene hijo izquierdo
    s = s->parent;                  // Sube mientras sea hijo izquierdo
  }
  return s->parent;                 // El padre del primer giro derecho
}
```

Es el **simétrico exacto** de `succ()`:

**Caso 1 — Tiene hijo izquierdo**: baja al hijo izquierdo, luego todo a la derecha. El nodo más a la derecha del subárbol izquierdo es el predecesor inorden.

**Caso 2 — No tiene hijo izquierdo**: sube por `parent` mientras sea hijo izquierdo. El padre del primer nodo que es hijo derecho es el predecesor.

**Ejemplo en el árbol de prueba**:
- `pred(5)`: tiene hijo izq (4), baja y va todo a la derecha → `pred(5) = 4`
- `pred(8)`: no tiene izq, 8 es hijo izq de 10 → `pred(8) = 7` (padre de 10)
- `pred(1)`: no tiene izq, 1 es hijo izq de 3, 3 es hijo izq de 7 → `pred(1) = nullptr`

7. En `BinTree`, ¿qué papel cumplen `root_` y `size_`?

```cpp
protected:
  std::size_t size_{0};
  Node* root_{nullptr};
```

**`root_`** (`Node*`):
- Puntero al nodo raíz del árbol
- `nullptr` significa árbol vacío
- Es el punto de entrada para todos los recorridos y operaciones
- Se modifica en: `insertAsRoot()`, `clear()`, `attachAsLC/RC` (indirectamente), `secede()` (indirectamente), `removeSubtree()` (indirectamente vía `fromParentTo`)

**`size_`** (`std::size_t`):
- Número total de nodos en el árbol
- Se mantiene como **contador explícito** (no se recalcula cada vez)
- Se incrementa en: `insertAsRoot()` (+1), `insertAsLC/RC()` (+1), `attachAsLC/RC()` (+subtree.size_)
- Se decrementa en: `removeSubtree()` (-removed), `secede()` (-detached), `clear()` (= 0), `splice()` (-1 en BST)
- **Invariante**: `size_` debe ser igual a `root_->size()` (aunque esto no se verifica automáticamente)

8. Explica qué hace `updateHeight(Node*)`

```cpp
int updateHeight(Node* node) {
  if (node == nullptr) {
    return -1;
  }
  node->height = 1 + std::max(stature(node->left), stature(node->right));
  return node->height;
}
```

- Calcula la altura del nodo como `1 + max(alturaHijoIzquierdo, alturaHijoDerecho)`
- `stature()` es un helper que retorna `-1` para `nullptr` y `node->height` para nodos existentes
- Actualiza el campo `height` del nodo con el valor calculado
- **Una hoja** tiene `height = 1 + max(-1, -1) = 0`
- **Un nodo con una hoja como hijo** tiene `height = 1 + max(0, -1) = 1`
- **No actualiza ancestros** — solo el nodo pasado como argumento

9. Explica qué hace `updateHeightAbove(Node*)` y por qué sube hacia la raíz

```cpp
void updateHeightAbove(Node* node) {
  while (node != nullptr) {
    updateHeight(node);
    node = node->parent;
  }
}
```

- Comienza en `node` y **sube hacia la raíz** siguiendo `parent`
- En cada paso, recalcula la altura del nodo actual con `updateHeight()`
- Se detiene cuando `node == nullptr` (llegó arriba de la raíz)

**Por qué sube**: Cuando insertas o eliminas un nodo en un subárbol, solo los ancestros de ese nodo pueden ver su altura afectada. Los nodos en otras ramas no cambian. Subir por `parent` es **O(h)** en lugar de recorrer todo el árbol **O(n)**.

**Ejemplo**: insertar una hoja en el subárbol izquierdo de un nodo profundo → solo los ancestros de ese nodo (incluyendo la raíz) necesitan recalcular altura. Sin `parent`, tendrías que empezar desde la raíz cada vez.

10. Explica cómo `attachAsLC` o `attachAsRC` transfieren un subárbol desde un árbol hacia otro

```cpp
Node* attachAsRC(Node* parent, BinTree<T>& subtree) {
  if (parent == nullptr) throw ...;
  if (parent->right != nullptr) throw ...;
  if (subtree.root_ == nullptr) return nullptr;

  parent->right = subtree.root_;    // (1) Conectar padre → hijo
  subtree.root_->parent = parent;   // (2) Conectar hijo → padre (bidireccional)
  size_ += subtree.size_;           // (3) Sumar tamaños
  updateHeightAbove(parent);        // (4) Actualizar alturas

  Node* attached = parent->right;
  subtree.root_ = nullptr;          // (5) Desconectar del árbol fuente
  subtree.size_ = 0;                // (6) Vaciar el árbol fuente
  return attached;
}
```

**Paso a paso**:
1. El puntero `right` (o `left`) del padre apunta a la raíz del subárbol
2. El `parent` de la raíz del subárbol se actualiza para apuntar al nuevo padre
3. El tamaño del árbol anfitrión aumenta en `subtree.size_`
4. Se recalculan alturas desde el padre hacia arriba
5. El árbol fuente se desconoce de los nodos: `root_ = nullptr`, `size_ = 0`
6. **Los nodos no se copian** — es una transferencia de propiedad (move semantics)

11. Explica qué diferencia hay entre `removeSubtree` y `secede`

| Aspecto | `removeSubtree(node)` | `secede(node)` |
|---------|----------------------|----------------|
| **Efecto** | Destruye el subárbol (libera memoria) | Desprende el subárbol (lo conserva) |
| **Retorno** | `std::size_t` (cantidad de nodos eliminados) | `BinTree<T>` (nuevo árbol con los nodos desprendidos) |
| **Memoria** | Llama a `destroy(node)` → `delete` recursivo | Los nodos **no se liberan**, se transfieren |
| **Uso** | Cuando ya no necesitas el subárbol | Cuando quieres mover un subárbol a otro árbol |
| **Implementación** | `destroy(node)` + `size_ -= removed` | Crea nuevo `BinTree`, asigna `root_` y `size_`, desconecta del original |

**En el código**:
```cpp
// removeSubtree: destruye
std::size_t removeSubtree(Node* node) {
  // ... desconecta node del padre ...
  destroy(node);         // delete recursivo
  size_ -= removed;
  updateHeightAbove(parent);
  return removed;
}

// secede: conserva
BinTree<T> secede(Node* node) {
  BinTree<T> out;
  // ... desconecta node del padre ...
  out.root_ = node;      // transfiere propiedad al nuevo árbol
  out.size_ = detached;
  size_ -= detached;
  updateHeightAbove(parent);
  return out;            // el nuevo árbol es responsable de la memoria
}
```

12. Explica por qué `secede` no debe destruir los nodos desprendidos

Porque `secede` **transfiere la propiedad** de los nodos a un nuevo árbol. El propósito es permitir **reutilizar** el subárbol — por ejemplo, mover una rama completa de un árbol a otro sin copiar datos.

Si `secede` destruyera los nodos:
- El `BinTree` retornado estaría vacío o con dangling pointers
- No se podría hacer `attachAsLC`/`attachAsRC` con el resultado de `secede`
- Se perdería la capacidad de reestructurar árboles eficientemente (operación clave para árboles balanceados)

**Quién es responsable de la memoria**: el `BinTree` retornado por `secede`. Cuando ese árbol se destruye (sale de scope), su destructor llama a `clear()` → `destroy(root_)` que libera recursivamente.

13. Explica por qué `removeSubtree` sí debe liberar nodos

Porque `removeSubtree` expresa la intención de **eliminar permanentemente** un subárbol. El retorno es solo un contador (`std::size_t`), no un nuevo árbol. Si no liberara la memoria:

1. **Memory leak**: los nodos quedarían inaccesibles pero ocupando memoria
2. **Inconsistencia semántica**: el nombre "remove" implica destrucción; "secede" implica separación
3. **Sin dueño**: al desconectar el subárbol del árbol original y no transferirlo a nadie, los nodos quedarían huérfanos

La implementación llama a `destroy(node)`, que es una función recursiva:
```cpp
static void destroy(Node* node) {
  if (node == nullptr) return;
  destroy(node->left);   // postorden: primero hijos
  destroy(node->right);
  delete node;           // luego el nodo
}
```

14. Explica qué verifica `checkParentLinks()`

```cpp
bool checkParentLinks() const {
  return checkParentLinks(root_, nullptr);
}

static bool checkParentLinks(const Node* node, const Node* parent) {
  if (node == nullptr) return true;
  if (node->parent != parent) return false;             // Verifica bidireccionalidad
  return checkParentLinks(node->left, node)             // Recursión izquierda
      && checkParentLinks(node->right, node);           // Recursión derecha
}
```

**Qué verifica, recursivamente**:
1. Para cada nodo `node`, su `parent` debe ser exactamente el nodo `parent` pasado como argumento
2. La raíz debe tener `parent == nullptr` (se pasa `nullptr` inicialmente)
3. Recorre en **preorden**: verifica el nodo actual, luego recursa a hijos

**Qué no verifica** (limitaciones):
- No verifica que `size_` sea correcto
- No verifica alturas
- No verifica que no haya ciclos (aunque la verificación de parent consistency indirectamente lo cubre)
- No verifica propiedad BST (eso lo hace `isBST()`)

15. En `BinaryTree`, explica cómo se implementan `firstNode`, `lastNode`, `nextNode` y `prevNode`

```cpp
Node* firstNode() const {
  return root_ == nullptr ? nullptr : root_->leftmost();
}
```
- Si el árbol está vacío, retorna `nullptr`
- Si no, retorna `root_->leftmost()` — el nodo más a la izquierda del árbol (mínimo inorden)
- **Complejidad**: O(h)

```cpp
Node* lastNode() const {
  return root_ == nullptr ? nullptr : root_->rightmost();
}
```
- Simétrico: retorna el nodo más a la derecha (máximo inorden)

```cpp
Node* nextNode(Node* node) const {
  return node == nullptr ? nullptr : node->succ();
}
```
- Wrapper seguro sobre `succ()`
- Si `node` es `nullptr`, retorna `nullptr`
- Avanza al siguiente nodo en inorden

```cpp
Node* prevNode(Node* node) const {
  return node == nullptr ? nullptr : node->pred();
}
```
- Wrapper seguro sobre `pred()`
- Retrocede al nodo anterior en inorden

16. Explica por qué un iterador basado en `succ()` produce recorrido inorden

El iterador de `BinaryTree`:
```cpp
class iterator {
  explicit iterator(Node* node) : current_(node) {}
  iterator& operator++() {
    current_ = (current_ == nullptr) ? nullptr : current_->succ();
    return *this;
  }
};
```

**Por qué produce inorden**:
1. `begin()` retorna `iterator(firstNode())` = el nodo más a la izquierda del árbol = el **primer nodo en inorden**
2. Cada `++` llama a `succ()` = avanza al **siguiente nodo en inorden**
3. `end()` retorna `iterator(nullptr)` = centinela después del último nodo
4. La secuencia: `firstNode() → succ() → succ() → ... → lastNode() → succ()=nullptr`

**Propiedad clave**: por definición, el sucesor inorden de un nodo es exactamente el siguiente nodo visitado en un recorrido inorden. Así que iterar con `succ()` produce la secuencia inorden.

**Ejemplo**: en el árbol `{7,3,10,1,5,8,12,4,6}`:
- `firstNode()` = 1
- `succ(1)` = 3, `succ(3)` = 4, ..., `succ(10)` = 12, `succ(12)` = nullptr
- Secuencia: `1, 3, 4, 5, 6, 7, 8, 10, 12` ✓

17. Explica qué aporta `asciiArt()` para depuración y sustentación

```cpp
std::string asciiArt() const {
  if (root_ == nullptr) return "(arbol vacio)\n";
  std::vector<std::string> lines;
  buildAscii(root_, "", true, lines);
  // ...
}
```

**Qué produce**: una representación textual del árbol como:
```
┌── 12
│   └── 10
│       └── 8
7
│   ┌── 6
│   │   └── 5
└── 4
    └── 3
        └── 1
```

**Qué aporta**:
1. **Visualización inmediata de la estructura**: permite ver la forma del árbol (balanceado, degenerado, etc.) sin dibujar a mano
2. **Verificación de inserción/eliminación**: tras `add()` o `remove()`, puedes ver que el nodo está en la posición correcta
3. **Depuración de rotaciones**: tras `rotateLeft/Right`, la salida ASCII muestra si la rotación se aplicó correctamente
4. **Sustentación oral**: puedes mostrar la estructura antes/después de operaciones, haciendo visible lo abstracto
5. **No requiere herramientas externas**: es texto puro, funciona en cualquier terminal, no necesita Graphviz ni GUI

**Cómo funciona** (`buildAscii`):
- Recorre en **inorden inverso** (derecha, raíz, izquierda) para dibujar el árbol "volteado" (raíz a la izquierda, ramas hacia la derecha)
- Usa prefijos como `"│   "` y `"    "` para dibujar conectores verticales
- Usa `"└── "` y `"┌── "` para los conectores horizontales

---

##### Bloque 7

1. Define formalmente la propiedad BST

Sea `T` un árbol binario. Para todo nodo `u` en `T` con valor `u.data`:

1. Para todo nodo `v` en el subárbol izquierdo de `u`: `v.data < u.data`
2. Para todo nodo `v` en el subárbol derecho de `u`: `v.data > u.data`

**En el código**, la propiedad se implementa con comparador genérico:
```cpp
bool isBST(const Node* node, const T* low, const T* high) const {
  if (node == nullptr) return true;
  if (low != nullptr && !comp_(*low, node->data)) return false;   // low >= node
  if (high != nullptr && !comp_(node->data, *high)) return false;  // node >= high
  return isBST(node->left, low, &node->data)
      && isBST(node->right, &node->data, high);
}
```
- `low`: cota inferior (todos los nodos deben ser > `low`)
- `high`: cota superior (todos los nodos deben ser < `high`)
- Para la raíz: `low = nullptr`, `high = nullptr` (sin restricción)
- Al bajar a la izquierda: `high = node->data` (todo debe ser < nodo actual)
- Al bajar a la derecha: `low = node->data` (todo debe ser > nodo actual)

2. Explica por qué el recorrido inorden de un BST debe producir una secuencia no decreciente

**Demostración por inducción estructural**:

**Caso base**: un árbol vacío produce secuencia vacía (trivialmente ordenada).

**Paso inductivo**: para un nodo `u`:
- `inorden(u) = inorden(izquierdo) + [u.data] + inorden(derecho)`
- Por propiedad BST: todo en izquierdo < `u.data` < todo en derecho
- Por hipótesis inductiva: `inorden(izquierdo)` está ordenado, `inorden(derecho)` está ordenado
- Concatenación: [...menores que u.data...] + [u.data] + [...mayores que u.data...] → ordenada

**En este BST** (sin duplicados), la secuencia es **estrictamente creciente**. Si se permitieran duplicados (ej. insertar a la derecha), sería **no decreciente**.

3. Explica la diferencia entre `find`, `findEQ`, `lowerBound` y `upperBound`

| Método | Retorna | Si el valor existe | Si el valor no existe |
|--------|---------|-------------------|----------------------|
| `findEQ(x)` | Primer nodo con `data == x` | El nodo exacto | `nullptr` |
| `find(x)` | Alias de `lowerBound(x)` | Primer nodo ≥ x (el mismo) | Primer nodo > x |
| `lowerBound(x)` | Primer nodo con `data >= x` | El nodo exacto | Primer nodo > x o `nullptr` |
| `upperBound(x)` | Primer nodo con `data > x` | Primer nodo > x | Primer nodo > x o `nullptr` |

**Implementación en el código**:
- `find()` es simplemente `return lowerBound(value);` — son idénticos
- `findEQ()` busca igualdad estricta, retorna `nullptr` si no encuentra
- `lowerBound()` mantiene un `candidate` que se actualiza cada vez que va a la izquierda (el nodo actual podría ser ≥ x)
- `upperBound()` actualiza `candidate` cuando va a la izquierda, pero **también** cuando `data == x` (porque busca estrictamente mayor)

4. Explica por qué `findEQ(x)` puede fallar aunque `lowerBound(x)` no falle

Supongamos un BST con valores `{1, 4, 5, 6, 7, 8, 10, 12}` y buscamos `x = 9`:

- **`findEQ(9)`**: busca igualdad estricta. Recorre el árbol, nunca encuentra `9`, retorna `nullptr`. **Falla**.
- **`lowerBound(9)`**: busca el primer valor ≥ 9. Recorre el árbol, encuentra que `10 > 9`, y como va a la izquierda desde 10, registra 10 como candidato. Retorna nodo con `data = 10`. **No falla**.

**La diferencia fundamental**: `lowerBound` es una búsqueda **relajada** — no exige igualdad exacta. Encuentra la "posición donde debería estar" el valor. `findEQ` es una búsqueda **estricta** — solo éxito con coincidencia exacta.

**Esto es útil**: `lowerBound` te dice dónde insertar un nuevo valor. `findEQ` te dice si ya existe.

5. Construye manualmente el BST que se obtiene al insertar: `7, 3, 10, 1, 5, 8, 12, 4, 6`

Insertando en orden:

```
Paso 1: insert 7 → raíz = 7

    7

Paso 2: insert 3 → 3 < 7, hijo izquierdo

      7
     /
    3

Paso 3: insert 10 → 10 > 7, hijo derecho

      7
     / \
    3   10

Paso 4: insert 1 → 1 < 7, 1 < 3, hijo izquierdo de 3

        7
       / \
      3   10
     /
    1

Paso 5: insert 5 → 5 < 7, 5 > 3, hijo derecho de 3

        7
       / \
      3   10
     / \
    1   5

Paso 6: insert 8 → 8 > 7, 8 < 10, hijo izquierdo de 10

        7
       / \
      3   10
     / \  /
    1   5 8

Paso 7: insert 12 → 12 > 7, 12 > 10, hijo derecho de 10

        7
       / \
      3   10
     / \  / \
    1   5 8  12

Paso 8: insert 4 → 4 < 7, 4 > 3, 4 < 5, hijo izquierdo de 5

        7
       / \
      3   10
     / \  / \
    1   5 8  12
       /
      4

Paso 9: insert 6 → 6 < 7, 6 > 3, 6 > 5, hijo derecho de 5

        7
       / \
      3   10
     / \  / \
    1   5 8  12
       / \
      4   6
```

**Árbol final**:
```
          7
        /   \
       3     10
      / \   /  \
     1   5 8   12
        / \
       4   6
```

6. Escribe el inorden, preorden, postorden y recorrido por niveles de ese árbol

- **Inorden** (izq → raíz → der): `1, 3, 4, 5, 6, 7, 8, 10, 12`
- **Preorden** (raíz → izq → der): `7, 3, 1, 5, 4, 6, 10, 8, 12`
- **Postorden** (izq → der → raíz): `1, 4, 6, 5, 3, 8, 12, 10, 7`
- **Por niveles** (BFS): `7, 3, 10, 1, 5, 8, 12, 4, 6`

7. Simula `lowerBound(9)` y `upperBound(8)` paso a paso

**`lowerBound(9)`** en el árbol `{7,3,10,1,5,8,12,4,6}`:

```
Inicio: w = 7 (raíz), candidate = nullptr

Paso 1: w = 7, comp_(9, 7) → false (9 no es < 7)
        comp_(7, 9) → true  (7 < 9) → w = w->right = 10

Paso 2: w = 10, comp_(9, 10) → true (9 < 10)
        candidate = 10 (registramos 10 como posible respuesta)
        w = w->left = 8

Paso 3: w = 8, comp_(9, 8) → false (9 no es < 8)
        comp_(8, 9) → true (8 < 9) → w = w->right = nullptr

Paso 4: w = nullptr → fin del ciclo
        Retorna candidate = 10 ✓
```

**`upperBound(8)`** en el mismo árbol:

```
Inicio: w = 7 (raíz), candidate = nullptr

Paso 1: w = 7, comp_(8, 7) → false (8 no es < 7)
        w = w->right = 10              // NOTA: no usa comp_ en la rama else

Paso 2: w = 10, comp_(8, 10) → true (8 < 10)
        candidate = 10
        w = w->left = 8

Paso 3: w = 8, comp_(8, 8) → false (8 no es < 8)
        w = w->right = nullptr          // Tratado como > (aunque son iguales)

Paso 4: w = nullptr → fin del ciclo
        Retorna candidate = 10 ✓
```

**Diferencia clave**: en `upperBound`, cuando `value == w->data` (paso 3 con w=8), el código va a la derecha sin actualizar candidato. Esto garantiza que 8 no sea retornado (es estrictamente mayor).

8. Explica qué casos de eliminación existen en un BST: hoja, un hijo, dos hijos

**Caso 1: Nodo hoja** (sin hijos)
- Ejemplo: eliminar `1` en el árbol de prueba
- `splice(1)`: `child = nullptr`, se desconecta del padre (`3->left = nullptr`)
- Se hace `delete node`
- El árbol sigue siendo BST válido

**Caso 2: Nodo con un solo hijo**
- Ejemplo: eliminar `5` si solo tuviera hijo izquierdo `4`
- `splice(5)`: `child = 4`, se conecta `4` como hijo donde estaba `5`
- Se hace `delete node`
- El hijo "sube" a ocupar la posición

**Caso 3: Nodo con dos hijos** (el más complejo)
- Ejemplo: eliminar `3` en el árbol de prueba (tiene hijos `1` y `5`)
- **Estrategia del código**: no se elimina el nodo físicamente, se **reemplaza su valor** por el del sucesor inorden y se elimina el sucesor
- `w = node->succ()` → `w = 4` (sucesor inorden de 3)
- `node->data = w->data` → `3->data = 4`
- `splice(w)` → elimina el nodo `4` original (que es hoja, caso 1)
- `delete w`
- **Por qué funciona**: el sucesor inorden de un nodo con dos hijos siempre tiene a lo sumo un hijo (nunca dos, porque es el mínimo del subárbol derecho)

9. Explica qué papel cumple `splice` durante una eliminación

```cpp
void splice(Node* node) {
  Node* child = (node->left != nullptr) ? node->left : node->right;
  Node* parent = node->parent;

  if (node == root_) {
    root_ = child;
  } else if (node->isLeftChild()) {
    parent->left = child;
  } else {
    parent->right = child;
  }

  if (child != nullptr) {
    child->parent = parent;
  }

  --size_;
  updateHeightAbove(parent);
}
```

**`splice` "puentea" (bypass) un nodo**:
1. Determina el hijo que sobrevive (`child`): si hay izquierdo, ese; si no, el derecho (o `nullptr`)
2. Actualiza el enlace desde el padre (o la raíz) para que apunte a `child` en lugar de `node`
3. Si `child` existe, actualiza su `parent`
4. Decrementa `size_` y actualiza alturas

**Es llamado desde `remove()`**:
- Para casos 1 y 2 (hoja o un hijo): `splice` se aplica directamente al nodo a eliminar
- Para caso 3 (dos hijos): `splice` se aplica al **sucesor** (que tiene ≤ 1 hijo), después de copiar su valor al nodo original

**No hace `delete`**: `splice` solo reconecta punteros. El `delete` lo hace `remove()` después de llamar a `splice`.

10. Después de eliminar una clave, ¿qué invariantes deben seguir siendo ciertos?

1. **Propiedad BST**: para todo nodo, izquierdo < nodo < derecho
2. **Bidireccionalidad de punteros**: `checkParentLinks()` debe pasar
3. **Sin duplicados**: la clave eliminada no debe aparecer en ningún nodo
4. **Consistencia de tamaño**: `size_` refleja el número real de nodos
5. **Alturas actualizadas**: `updateHeightAbove(parent)` asegura que todos los ancestros tengan altura correcta
6. **Sin memory leaks**: el nodo eliminado fue `delete`-ado
7. **Sin dangling pointers**: ningún nodo restante apunta al nodo eliminado
8. **El inorden sigue ordenado**: la secuencia inorden es estrictamente creciente y no contiene la clave eliminada

### 11. Explica por qué `remove(3)` en las pruebas debe conservar el inorden ordenado

Árbol original (inorden): `1, 3, 4, 5, 6, 7, 8, 10, 12`

`remove(3)`:
1. `findEQ(3)` encuentra el nodo con `data = 3`
2. El nodo 3 tiene dos hijos (1 y 5) → caso 3
3. `succ(3)` = 4 (el mínimo del subárbol derecho)
4. `3->data = 4` (reemplaza el valor)
5. `splice(4)` elimina el nodo 4 original (hoja)
6. El nodo que antes era 3 ahora tiene valor 4, con hijos 1 y 5

Árbol resultante (inorden esperado): `1, 4, 5, 6, 7, 8, 10, 12`

**Por qué sigue ordenado**: la propiedad BST se preserva porque:
- El nuevo valor 4 es > todo en subárbol izquierdo (1) ✓
- El nuevo valor 4 es < todo en subárbol derecho (5, 6) ✓
- Los ancestros (7) siguen teniendo consistentemente valores menores a la izquierda y mayores a la derecha ✓
- El sucesor inorden es el **único** valor que puede reemplazar al nodo eliminado sin violar la propiedad BST

12. Explica qué hace `rotateLeft`

```cpp
void rotateLeft(Node* u) {
  Node* w = u->right;
  // (1) w toma el parent de u
  w->parent = u->parent;
  if (u->parent == nullptr) root_ = w;
  else if (u->isLeftChild()) u->parent->left = w;
  else u->parent->right = w;

  // (2) el hijo izquierdo de w pasa a ser hijo derecho de u
  u->right = w->left;
  if (u->right != nullptr) u->right->parent = u;

  // (3) u pasa a ser hijo izquierdo de w
  w->left = u;
  u->parent = w;

  // (4) actualizar alturas
  updateHeight(u);
  updateHeight(w);
  updateHeightAbove(w->parent);
}
```

**Visualmente**:
```
Antes:           Después:
    u                w
   / \              / \
  A   w      →     u   C
     / \          / \
    B   C        A   B
```

- `u` baja a la izquierda
- `w` (hijo derecho de `u`) sube a la posición de `u`
- El subárbol `B` cambia de ser hijo izquierdo de `w` a ser hijo derecho de `u`

13. Explica qué hace `rotateRight`

```cpp
void rotateRight(Node* u) {
  Node* w = u->left;
  w->parent = u->parent;
  if (u->parent == nullptr) root_ = w;
  else if (u->isLeftChild()) u->parent->left = w;
  else u->parent->right = w;

  u->left = w->right;
  if (u->left != nullptr) u->left->parent = u;

  w->right = u;
  u->parent = w;

  updateHeight(u);
  updateHeight(w);
  updateHeightAbove(w->parent);
}
```

Es el **simétrico exacto** de `rotateLeft`:

```
Antes:           Después:
      u              w
     / \            / \
    w   C    →     A   u
   / \                / \
  A   B              B   C
```

- `u` baja a la derecha
- `w` (hijo izquierdo de `u`) sube a la posición de `u`
- El subárbol `B` cambia de ser hijo derecho de `w` a ser hijo izquierdo de `u`

14. Demuestra que una rotación local preserva la propiedad BST

**Para `rotateLeft(u)`:**

Antes de la rotación (propiedad BST):
- `A < u < B < w < C`

Después de la rotación:
- `u` está en el subárbol izquierdo de `w` → necesitamos `u < w` ✓ (se cumple por propiedad original)
- `A` y `B` están en el subárbol izquierdo de `u` → `A < u` ✓ y `B < u` ✓ (originalmente `B < w`, y `u < w`, transitivamente)
- `C` está en el subárbol derecho de `w` → `w < C` ✓ (propiedad original)
- `B` pasa a ser hijo derecho de `u` → necesitamos `u < B` ✓ (originalmente `B` estaba entre `u` y `w`)

**La clave**: la rotación solo reordena **localmente** los nodos `u` y `w`, pero el orden relativo de todos los valores se preserva. El recorrido inorden antes y después de la rotación es **idéntico**:
- Antes: `A, u, B, w, C`
- Después: `A, u, B, w, C`

**Para `rotateRight`**: demostración simétrica con `A < w < B < u < C`.

**La prueba interna lo confirma**:
```cpp
bst.rotateRight(bst.root());
expect((bst.inorder() == std::vector<int>{1, 2, 3}), "La rotacion no debe romper el orden del BST");
```

15. Explica para qué sirve construir un BST balanceado desde un arreglo ordenado

```cpp
static BinarySearchTree buildBalancedFromSorted(const std::vector<T>& sorted, Compare cmp = {}) {
  // ...
}
```

**Implementación**: divide y vencerás
```cpp
static Node* buildBalancedRecursive(const std::vector<T>& sorted, int lo, int hi, Node* parent) {
  if (lo >= hi) return nullptr;
  const int mid = lo + (hi - lo) / 2;
  Node* node = new Node(sorted[mid], parent);
  node->left = buildBalancedRecursive(sorted, lo, mid, node);
  node->right = buildBalancedRecursive(sorted, mid + 1, hi, node);
  node->height = 1 + std::max(stature(node->left), stature(node->right));
  return node;
}
```

**Para qué sirve**:
1. **Garantiza balance perfecto**: altura = ⌊log₂(n)⌋. Para 7 nodos, altura = 2.
2. **Búsqueda garantizada O(log n)**: a diferencia de insertar secuencialmente (que puede producir árbol degenerado O(n))
3. **Inicialización eficiente**: O(n) para construir, vs O(n log n) para insertar uno por uno (en el peor caso sin balanceo)
4. **Base para árboles balanceados**: es el punto de partida para AVL, Red-Black (si se necesita balanceo dinámico después)
5. **Pruebas determinísticas**: produce siempre la misma estructura para el mismo input, facilitando testing

**Aplicación práctica**: cuando tienes datos ya ordenados y necesitas un BST eficiente para búsquedas, `buildBalancedFromSorted` es la forma correcta de construirlo.

16. Compara el costo de búsqueda en un BST balanceado y en un BST degenerado

| Aspecto | BST Balanceado | BST Degenerado (cadena) |
|---------|---------------|------------------------|
| **Forma** | Árbol completo/compacto | Lista enlazada |
| **Altura** | O(log n) | O(n) |
| **`find(x)`** | O(log n) | O(n) |
| **`findEQ(x)`** | O(log n) | O(n) |
| **`add(x)`** | O(log n) | O(n) |
| **`remove(x)`** | O(log n) | O(n) |
| **Ejemplo** | `buildBalancedFromSorted({1..7})` | Insertar `{1,2,3,4,5,6,7}` en orden |

**Árbol degenerado** (insertar en orden):
```
1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
           \
            7
```
- Buscar `7` requiere 7 comparaciones (visitar todos los nodos)
- Es indistinguible de una búsqueda secuencial en lista

**Árbol balanceado** (construido desde ordenado):
```
        4
       / \
      2   6
     / \ / \
    1  3 5  7
```
- Buscar `7` requiere 3 comparaciones (4→6→7)
- Altura = ⌊log₂(7)⌋ = 2

**Conclusión**: sin balanceo, un BST puede degradarse a O(n). Por eso existen árboles auto-balanceables (AVL, Red-Black) que mantienen O(log n) mediante rotaciones. `buildBalancedFromSorted` es una solución estática (construcción inicial balanceada), no dinámica.

---

##### Bloque 8

1. Explica por qué un heap binario puede almacenarse en un `std::vector` sin punteros

Un heap binario es un árbol binario que cumple con el invariante de ser **estructuralmente completo o casi completo** (todos los niveles están llenos excepto, posiblemente, el último, que se llena de izquierda a derecha de forma compacta).

Esta regularidad absoluta elimina cualquier "hueco" en la disposición de los nodos en un recorrido por niveles. Por lo tanto, podemos establecer una correspondencia biunívoca exacta entre la posición lógica de un nodo en el árbol y su índice físico en un arreglo contiguo (`std::vector<T>`).

**Ventajas clave**:
1. **Ahorro masivo de memoria**: Se elimina el overhead de almacenar punteros (`parent`, `left`, `right`). En arquitecturas de 64 bits, cada puntero ocupa 8 bytes; un solo nodo con 3 punteros y enteros gasta al menos 24-32 bytes adicionales de overhead en puro direccionamiento. Con un vector, solo pagamos el tamaño de `T` por elemento.
2. **Localidad de datos y caché**: Al estar almacenados en posiciones contiguas de memoria, se minimizan los cache misses de la CPU. En árboles basados en punteros, los nodos pueden estar dispersos en el heap (memoria dinámica), lo que ralentiza el acceso debido a saltos de punteros.

---

2. Demuestra las fórmulas de navegación base cero

```cpp
left(i) = 2*i + 1
right(i) = 2*i + 2
parent(i) = (i - 1) / 2
```

**Demostración**:
Supongamos un árbol binario perfecto indexado por niveles en base 0:
- El nivel $d$ (donde la raíz está en $d = 0$) comienza en el índice absoluto $I_{start}(d) = 2^d - 1$ y contiene $2^d$ nodos.
- Si un nodo está en el índice absoluto $i$, su posición relativa (de izquierda a derecha en base 0) dentro de su nivel $d$ es $k = i - (2^d - 1)$, con $0 \leq k < 2^d$.
- En el siguiente nivel $d+1$, que comienza en el índice absoluto $I_{start}(d+1) = 2^{d+1} - 1$, los descendientes directos de este nodo ocuparán las posiciones relativas $2k$ (hijo izquierdo) y $2k + 1$ (hijo derecho) dentro de dicho nivel.

Calculando el índice absoluto del **hijo izquierdo**:
$$\text{left}(i) = I_{start}(d+1) + 2k$$
$$\text{left}(i) = (2^{d+1} - 1) + 2(i - 2^d + 1)$$
$$\text{left}(i) = 2^{d+1} - 1 + 2i - 2^{d+1} + 2$$
$$\text{left}(i) = 2i + 1 \quad \blacksquare$$

Para el **hijo derecho**, al estar inmediatamente al lado del izquierdo:
$$\text{right}(i) = \text{left}(i) + 1 = 2i + 2 \quad \blacksquare$$

Para deducir el **padre**, despejamos $p$ (índice del padre) a partir del índice del hijo $i$:
1. Si $i$ es un hijo izquierdo (un número impar):
   $$i = 2p + 1 \implies 2p = i - 1 \implies p = \frac{i - 1}{2}$$
2. Si $i$ es un hijo derecho (un número par):
   $$i = 2p + 2 \implies 2p = i - 2 \implies p = \frac{i - 2}{2}$$

Utilizando la aritmética de división entera de C++ (que descarta la parte decimal truncando hacia cero):
- Si $i$ es impar, $\frac{i-1}{2}$ es una división exacta.
- Si $i$ es par, $\frac{i-1}{2}$ dará exactamente el mismo resultado que $\frac{i-2}{2}$. Por ejemplo, si $i = 2$ (hijo derecho de la raíz $0$):
  $$\text{parent}(2) = \lfloor (2 - 1) / 2 \rfloor = \lfloor 1 / 2 \rfloor = 0$$

Por ende, para cualquier nodo $i > 0$, su padre se encuentra de manera general en:
$$\text{parent}(i) = \frac{i - 1}{2} \quad \blacksquare$$

---

3. Define la propiedad de min-heap

La propiedad de **prioridad o de min-heap** establece que para cada nodo $i$ diferente de la raíz ($i > 0$), el valor del nodo padre es menor o igual al valor del nodo actual:
$$\text{data\_}[\text{parent}(i)] \leq \text{data\_}[i]$$

O equivalentemente, para todo nodo $i$ que posea hijos válidos dentro de los límites del vector:
$$\text{data\_}[i] \leq \text{data\_}[\text{left}(i)] \quad \text{y} \quad \text{data\_}[i] \leq \text{data\_}[\text{right}(i)]$$

Esto representa un **ordenamiento parcial**: no garantiza ningún orden entre hermanos u otros nodos de un mismo nivel, solo la subordinación obligatoria de prioridad de ancestros sobre descendientes.

---

4. Explica por qué `top()` devuelve el mínimo

Por la propiedad de min-heap y transitividad de la relación de orden parcial:
$$\forall i > 0, \quad \text{data\_}[0] \leq \text{data\_}[\text{parent}(i)] \leq \dots \leq \text{data\_}[i]$$

Al ser la raíz (índice `0`) el ancestro de absolutamente todos los nodos del heap, su valor debe ser obligatoriamente menor o igual que cualquier otro elemento del arreglo. Como `top()` retorna la primera posición contigua `data_.front()` (el índice `0`), la consulta del mínimo está garantizada en tiempo constante $O(1)$.

---

5. Explica paso a paso cómo `bubbleUp(i)` restaura la propiedad de heap después de insertar

Cuando se inserta un nuevo elemento mediante `add(value)`, este se añade al final del vector en el índice $i = \text{size} - 1$, lo que podría violar el invariante de min-heap si es menor que su padre. `bubbleUp(i)` flota el elemento hacia arriba:

1. Se verifica si $i > 0$. Si es la raíz ($i = 0$), el proceso termina.
2. Se obtiene el índice del padre: $p = \text{parent}(i)$.
3. Se evalúa si el elemento en $i$ cumple con la prioridad frente al padre: si `!comp_(data_[i], data_[p])` (es decir, $\text{data\_}[i] \geq \text{data\_}[p]$), la propiedad de heap se cumple a partir de este punto. El proceso termina (`break`).
4. Si $\text{data\_}[i] < \text{data\_}[p]$, se intercambian los valores en los índices $i$ y $p$ usando `std::swap`.
5. Se actualiza la posición del elemento: $i \leftarrow p$ y se vuelve al paso 1.

**Complejidad**: Puesto que en cada paso subimos un nivel en el árbol, el número máximo de comparaciones e intercambios es proporcional a la altura del árbol, es decir, $O(\log n)$ en el peor caso.

---

6. Explica paso a paso cómo `trickleDown(i)` restaura la propiedad de heap después de eliminar la raíz

`trickleDown(i)` repara la propiedad de min-heap cuando el nodo en el índice $i$ es mayor que sus hijos (lo que ocurre tras reemplazar la raíz por el último elemento):

1. Se inicializa una variable `best = i` para registrar la posición del elemento más pequeño entre el nodo actual y sus hijos directos.
2. Se calculan los índices de los hijos: `l = left(i)` y `r = right(i)`.
3. Si el hijo izquierdo existe (`l < data_.size()`) y es menor que el candidato actual (`comp_(data_[l], data_[best])`), se actualiza `best = l`.
4. Si el hijo derecho existe (`r < data_.size()`) y es menor que el candidato en `best` (`comp_(data_[r], data_[best])`), se actualiza `best = r`.
5. Si `best == i`, significa que el nodo actual ya es menor o igual que sus hijos sobrevivientes. La propiedad de heap está satisfecha, por lo que salimos del ciclo.
6. Si `best != i`, se intercambian `data_[i]` con `data_[best]` para que el menor de ellos ascienda.
7. Se actualiza el índice a seguir analizando: $i \leftarrow \text{best}$ y se repite desde el paso 1.

**Complejidad**: En cada iteración bajamos un nivel en el árbol. La altura máxima del árbol es $\lfloor\log_2 n\rfloor$, por lo que la complejidad del peor caso es $O(\log n)$.

---

7. Explica por qué `remove()` debe mover el último elemento a la raíz antes de aplicar `trickleDown(0)`

Para que una estructura sea un heap binario, se deben mantener simultáneamente dos propiedades:
1. **Propiedad Estructural**: El árbol debe ser binario completo.
2. **Propiedad de Orden**: Cumplir el invariante de prioridad de min-heap.

Si elimináramos el valor mínimo directamente de la raíz en el índice 0, dejaríamos un "vacío" en el vector. Tratar de rellenar ese hueco desplazando todos los elementos siguientes a la izquierda tomaría un tiempo lineal de $O(n)$, destrozando la eficiencia del heap.

La única posición del vector que se puede eliminar en $O(1)$ sin romper la propiedad estructural de árbol binario completo es el **último elemento** (índice $\text{size}-1$). Por lo tanto:
- Copiamos el último elemento a la raíz: `data_.front() = data_.back();`
- Eliminamos la última posición física: `data_.pop_back();`
- Esto preserva perfectamente la completitud del árbol en tiempo $O(1)$. No obstante, la raíz ahora tiene un valor arbitrario que probablemente viola la propiedad de orden.
- Se ejecuta `trickleDown(0)` para hundir este valor a su posición correcta, restaurando la propiedad de orden en tiempo logarítmico $O(\log n)$.

---

8. Explica qué verifica `isHeap()`

`isHeap()` es una función de validación que llama a `isHeapArray(data_, comp_)`. Este método auxiliar recorre linealmente el arreglo de izquierda a derecha. Para cada elemento $i$ desde $0$ hasta $n-1$:
- Calcula los índices de sus hijos $l = 2i+1$ y $r = 2i+2$.
- Si $l$ está dentro de los límites del arreglo y se cumple que `comp(data[l], data[i])` (es decir, el hijo es estrictamente menor que el padre), se viola la propiedad de min-heap y retorna `false`.
- Si $r$ está dentro de los límites del arreglo y se cumple que `comp(data[r], data[i])`, retorna `false`.
- Si se recorre todo el arreglo sin detectar ninguna anomalía, retorna `true`.

Su costo es estrictamente lineal $O(n)$ en tiempo y $O(1)$ en memoria auxiliar.

---

9. Compara construir un heap insertando `n` elementos con construirlo usando `heapify()`

Existen dos estrategias para construir un heap a partir de una secuencia desordenada de $n$ elementos:

- **Inserciones secuenciales**: Se inicia con un heap vacío y para cada uno de los $n$ elementos se ejecuta `add()`, lo cual hace un `push_back` y luego un `bubbleUp()`.
- **Estrategia `heapify()`**: Se cargan todos los elementos directamente en el arreglo contiguo de forma desordenada en $O(n)$. Luego, se recorren los nodos desde la mitad hacia atrás, es decir, comenzando en el primer nodo interno que tiene hijos (en el índice $\lfloor n/2 \rfloor - 1$) hasta el índice 0 (la raíz), aplicando `trickleDown(i)` en cada paso.

---

10. Justifica por qué insertar `n` elementos uno por uno cuesta `O(n log n)` en el peor caso

En un árbol binario completo de $n$ elementos, la inmensa mayoría de los nodos (aproximadamente la mitad, $\approx n/2$) se concentran en el nivel inferior (hojas) y un cuarto en el nivel inmediatamente superior.

Cuando construimos un heap mediante inserciones sucesivas (`add()`), cada nodo nuevo se inserta como hoja al final del vector y asciende hacia la raíz mediante `bubbleUp()`.
En el peor de los casos (por ejemplo, si insertamos datos en orden estrictamente decreciente en un min-heap), cada nuevo elemento insertado en el nivel $d$ tendrá que subir hasta la raíz realizando $d$ operaciones.

Matemáticamente, el costo total es la sumatoria de las alturas a las que se insertan los nodos:
$$T(n) = \sum_{i=1}^{n} \lfloor \log_2 i \rfloor \geq \sum_{i=n/2}^{n} \log_2(n/2) = \frac{n}{2} (\log_2 n - 1) = \Omega(n \log n)$$

Por lo tanto, la cota del peor caso es estrictamente $O(n \log n)$.

---

11. Justifica por qué `heapify()` puede ejecutarse en `O(n)`

En la construcción ascendente mediante `heapify()`, los nodos se procesan de abajo hacia arriba aplicando `trickleDown()`.
- Los nodos en los niveles más bajos (que constituyen la gran mayoría de la estructura, $O(n)$) se hunden como máximo una distancia muy pequeña (0 o 1 paso), ya que tienen pocos o ningún nivel por debajo.
- Únicamente los pocos nodos ubicados en los niveles más altos (cerca de la raíz, $O(1)$) pueden llegar a hundirse distancias proporcionales a la altura completa de la estructura $\log n$.

Formalmente, un árbol binario completo de altura $h$ contiene a lo sumo $\lceil n / 2^{k+1} \rceil$ nodos a una altura $k$ (donde las hojas están a altura 0 y la raíz a altura $h$). El costo de hundir un nodo a altura $k$ es a lo sumo $k$ operaciones. El trabajo total de `heapify()` está acotado por:
$$W(n) = \sum_{k=0}^{h} \left\lceil \frac{n}{2^{k+1}} \right\rceil O(k) \leq n \sum_{k=0}^{\infty} \frac{k}{2^{k+1}}$$

La sumatoria infinita es una serie aritmético-geométrica convergente:
$$\sum_{k=0}^{\infty} \frac{k}{2^{k+1}} = \frac{0}{2} + \frac{1}{4} + \frac{2}{8} + \frac{3}{16} + \dots = 1$$

Por lo tanto, el trabajo total es lineal:
$$W(n) \leq n \cdot 1 = O(n) \quad \blacksquare$$

Esto representa una optimización teórica y práctica fundamental para la inicialización de heaps y para el algoritmo de ordenamiento Heap Sort.

---

12. Ejecuta una extracción completa del heap construido con `{7, 3, 10, 1, 5, 8, 2}`

Hagamos la simulación matemática rigurosa de las operaciones:

#### Fase 1: `heapify()` de `{7, 3, 10, 1, 5, 8, 2}`
- El arreglo inicial desordenado tiene tamaño $n = 7$.
- El primer nodo interno a procesar está en el índice $\lfloor 7/2 \rfloor - 1 = 2$. Los índices de nodos internos son `2`, `1` y `0`.

1. **`trickleDown(2)`** (Elemento en índice 2 es `10`, sus hijos son los índices 5 (`8`) y 6 (`2`)):
   - El hijo menor es `2` (índice 6). Como $2 < 10$, intercambiamos `10` y `2`.
   - El arreglo queda: `{7, 3, 2, 1, 5, 8, 10}`.
2. **`trickleDown(1)`** (Elemento en índice 1 es `3`, sus hijos son los índices 3 (`1`) y 4 (`5`)):
   - El hijo menor es `1` (índice 3). Como $1 < 3$, intercambiamos `3` y `1`.
   - El arreglo queda: `{7, 1, 2, 3, 5, 8, 10}`.
3. **`trickleDown(0)`** (Elemento en índice 0 es `7`, sus hijos son los índices 1 (`1`) y 2 (`2`)):
   - El hijo menor es `1` (índice 1). Como $1 < 7$, intercambiamos `7` y `1`.
   - El arreglo queda temporalmente: `{1, 7, 2, 3, 5, 8, 10}`.
   - Continuamos el hundimiento del elemento `7` que ahora está en el índice 1 (hijos en índices 3 (`3`) y 4 (`5`)):
   - El hijo menor es `3` (índice 3). Como $3 < 7$, intercambiamos `7` y `3`.
   - El arreglo queda: `{1, 3, 2, 7, 5, 8, 10}`.

**Resultado de Heapify**: El arreglo `{1, 3, 2, 7, 5, 8, 10}` es un min-heap perfectamente estructurado.

#### Fase 2: Extracciones sucesivas de `remove()`

- **Extracción 1**:
  - Extraemos el valor de la raíz: `1`.
  - Movemos el último elemento `10` a la raíz y hacemos pop: arreglo es `{10, 3, 2, 7, 5, 8}`.
  - Aplicamos `trickleDown(0)`: El hijo menor de la raíz `10` es `2` (índice 2). Intercambiamos: `{2, 3, 10, 7, 5, 8}`.
  - El elemento `10` está en el índice 2, su único hijo es `8` (índice 5). Intercambiamos: `{2, 3, 8, 7, 5, 10}`.
  - **Salida**: `1`.

- **Extracción 2**:
  - Extraemos la raíz: `2`.
  - Movemos el último `10` a la raíz: arreglo es `{10, 3, 8, 7, 5}`.
  - Aplicamos `trickleDown(0)`: El menor hijo es `3` (índice 1). Intercambiamos: `{3, 10, 8, 7, 5}`.
  - El elemento `10` está en el índice 1, sus hijos son `7` (índice 3) y `5` (índice 4). El menor es `5`. Intercambiamos: `{3, 5, 8, 7, 10}`.
  - **Salida**: `2`.

- **Extracción 3**:
  - Extraemos la raíz: `3`.
  - Movemos el último `10` a la raíz: arreglo es `{10, 5, 8, 7}`.
  - Aplicamos `trickleDown(0)`: El menor hijo es `5` (índice 1). Intercambiamos: `{5, 10, 8, 7}`.
  - El elemento `10` en el índice 1 tiene como único hijo a `7` (índice 3). Intercambiamos: `{5, 7, 8, 10}`.
  - **Salida**: `3`.

- **Extracción 4**:
  - Extraemos la raíz: `5`.
  - Movemos el último `10` a la raíz: arreglo es `{10, 7, 8}`.
  - Aplicamos `trickleDown(0)`: El menor hijo es `7` (índice 1). Intercambiamos: `{7, 10, 8}`.
  - **Salida**: `5`.

- **Extracción 5**:
  - Extraemos la raíz: `7`.
  - Movemos el último `8` a la raíz: arreglo es `{8, 10}`.
  - Aplicamos `trickleDown(0)`: El único hijo es `10` (índice 1). Como $8 < 10$, no hay intercambios.
  - **Salida**: `7`.

- **Extracción 6**:
  - Extraemos la raíz: `8`.
  - Movemos el último `10` a la raíz: arreglo es `{10}`.
  - **Salida**: `8`.

- **Extracción 7**:
  - Extraemos la raíz: `10`. Arreglo queda vacío `{}`.
  - **Salida**: `10`.

**Secuencia total de salida**: `1, 2, 3, 5, 7, 8, 10`.
**Explicación**: El resultado sale perfectamente ordenado de menor a mayor porque el min-heap garantiza por su propiedad de orden que la raíz es siempre el mínimo de la estructura. Al extraer recursivamente la raíz y restaurar la propiedad de orden tras cada paso, la estructura produce sucesivamente el menor de los elementos restantes.

---

13. Compara el heap con el BST: ¿cuál estructura conviene para consultar mínimo repetidamente y cuál conviene para búsquedas ordenadas?

- **Para consultar el mínimo repetidamente**: El **min-heap** es la mejor opción. Permite consultar el mínimo en $O(1)$ con `top()` y eliminarlo/restaurarlo en $O(\log n)$ en el peor caso. Además, no tiene el overhead de memoria de punteros y tiene una fantástica localidad de caché al implementarse implícitamente en un vector contiguo.
- **Para búsquedas generales y operaciones ordenadas**: El **BST** (Árbol Binario de Búsqueda) es infinitamente superior. El BST impone un orden total que permite buscar cualquier elemento arbitrario en tiempo promedio $O(\log n)$ y recorrer todos los elementos en un orden estrictamente creciente en $O(n)$ usando inorden. En cambio, en un heap no hay orden total; para buscar un elemento arbitrario debemos realizar una búsqueda lineal $O(n)$, y para recorrer el heap en orden sin destruir la estructura tendríamos que hacer una copia completa y vaciarla paso a paso con costo $O(n \log n)$ en tiempo y $O(n)$ en espacio.

---

##### Bloque 9

### ¿Qué cambia cuando pasamos de estudiar listas, pilas y colas a diseñar árboles binarios, heaps y árboles binarios de búsqueda?

El paso de estructuras lineales (listas, pilas y colas) a estructuras jerárquicas y de prioridad (árboles binarios, heaps y BSTs) representa un cambio de paradigma fundamental en las ciencias de la computación, que modifica profundamente cómo conceptualizamos la memoria, la complejidad algorítmica y la organización de la información:

1. **Sobre la representación enlazada con nodos y punteros**: En las listas enlazadas tradicionales, la navegación es estrictamente secuencial unidireccional o bidireccional. Al diseñar árboles binarios enlazados con `BinNode`, entramos a una ramificación multidimensional. Cada nodo se convierte en el pivote de múltiples subárboles mediante punteros explícitos a `left`, `right` y `parent`, permitiendo modelar relaciones jerárquicas directas donde los datos fluyen en múltiples direcciones.
2. **Sobre la representación implícita en arreglo**: Mientras que una pila o cola en un arreglo es un buffer lineal indexado secuencialmente, el `BinaryHeap` rompe este esquema lineal demostrando cómo un arreglo contiguo puede representar un árbol binario completo perfectamente balanceado sin usar un solo puntero. Esto se logra mediante el mapeo matemático de relaciones de parentesco a través de fórmulas aritméticas simples de índices en $O(1)$ (`left(i) = 2i + 1`, `right(i) = 2i + 2`), optimizando drásticamente la huella de memoria y explotando al máximo la localidad espacial de la memoria caché del procesador.
3. **Sobre la diferencia entre propiedad estructural y de orden**: En estructuras lineales, la forma es trivial (una secuencia). En estructuras de árbol, distinguimos tajantemente entre la **propiedad estructural** (la topología y forma física del árbol, como la completitud compacta que exige un heap para poder mapearse en un vector) y la **propiedad de orden** (los invariantes de valores, como el orden total estrictamente mayor/menor en un BST o el orden de prioridad parcial de ancestro-descendiente en un min-heap). Ambas deben coexistir y ser defendidas celosamente por los métodos modificadores de la clase.
4. **Sobre los recorridos y la secuenciación**: Los recorridos de árboles (preorden, inorden, postorden y niveles) actúan como "aplanadores" (*flatteners*) dimensionales de un espacio jerárquico no lineal hacia una secuencia de salida unidimensional. Cada recorrido representa un contrato y un orden de procesamiento diferente (por ejemplo, postorden para la liberación ordenada de memoria de subárboles con `destroy()`, o por niveles para búsquedas en anchura mediante colas).
5. **Sobre el mantenimiento de alturas y enlaces `parent`**: El puntero `parent` en un árbol enlazado es el cordón umbilical que permite la navegación ascendente. En lugar de vernos obligados a descender recursivamente desde la raíz principal en operaciones de costo lineal $O(n)$, el enlace `parent` nos permite reaccionar localmente e irradiar información de manera ascendente hacia la raíz en tiempo proporcional a la altura del árbol $O(h)$ (como en `updateHeightAbove()` tras una inserción o eliminación).
6. **Sobre el BST, la búsqueda ordenada y el inorden**: El Árbol Binario de Búsqueda (BST) unifica la rapidez de la búsqueda binaria con la flexibilidad de inserción de las estructuras dinámicas. La propiedad formal del BST (subárbol izquierdo menor, subárbol derecho mayor) se traduce de forma matemática y directa en que su recorrido inorden produce una secuencia estrictamente ordenada sin ningún esfuerzo de ordenación adicional, permitiendo búsquedas, cotas inferiores (`lowerBound`) y superiores (`upperBound`) sumamente ágiles.
7. **Sobre el heap, la prioridad y los costos asintóticos**: El heap binario es una obra maestra del diseño de estructuras de datos orientadas a la prioridad. Mientras que insertar $n$ elementos de forma individual mediante la flotación ascendente `add()` tiene un costo de peor caso de $O(n \log n)$ debido a que la mayoría de nodos residen en el nivel inferior y deben subir grandes distancias; la técnica de `heapify()` invierte la dirección de procesamiento y ejecuta un hundimiento descendente recursivo de abajo hacia arriba que aprovecha la naturaleza geométrica del árbol para lograr una construcción asintóticamente perfecta en tiempo lineal $O(n)$. Las operaciones individuales de inserción (`add`) y remoción de prioridad (`remove`) operan de manera garantizada y consistente en $O(\log n)$.
8. **Sobre la evidencia para defender la correctitud en una sustentación**: La solidez de nuestro software no se asume; se demuestra rigurosamente utilizando un arsenal complementario de evidencias:
   - **Pruebas Unitarias**: Verificación formal de casos de borde (árboles vacíos, sin duplicados, borrado de raíz, etc.).
   - **Demos Ejecutables**: Evidencia observable de comportamiento en tiempo real de recorridos y rotaciones preservando invariantes.
   - **Invariantes Estructurales**: Verificaciones de sanidad en vivo del estado interno de punteros con `checkParentLinks()` y de orden con `isBST()` o `isHeap()`.
   - **Trazados Manuales**: Simulaciones detalladas paso a paso del estado de la estructura que prueban que comprendemos la mecánica interna de los punteros y los índices del vector.
   - **Análisis de Complejidad Asintótica**: Justificación teórica de por qué nuestro código escala eficientemente bajo las reglas de la notación Big-O tanto en tiempo como en espacio.

---

## Autoevaluación breve

### Qué puedo defender con seguridad
- La mecánica y diferencias clave de los recorridos de árboles tanto recursivos como iterativos de las 3 variantes (preorden, inorden, postorden).
- La demostración matemática precisa de las fórmulas de índices del heap y por qué `heapify()` es una operación lineal $O(n)$ a diferencia de $n$ inserciones secuenciales.
- La preservación de las propiedades del BST bajo operaciones complejas como la eliminación (usando `splice` con el sucesor) y las rotaciones izquierda y derecha.

### Qué todavía confundo
- En ocasiones puede requerir un momento extra de análisis trazar mentalmente el recorrido iterativo de postorden sin usar marcas de color de nodos, debido a la necesidad de verificar si se regresa desde el hijo derecho. Sin embargo, el uso de pilas auxiliares limpias o la lógica bidireccional con `parent` mitiga esta confusión.

### Qué evidencia usaría en una sustentación
- Mostraría el renderizado textual del árbol utilizando el método `asciiArt()` antes y después de aplicar una rotación o una eliminación para evidenciar de forma inmediata la correctitud del cambio estructural.
- Presentaría el paso de las pruebas públicas y de las pruebas internas completas en la consola como prueba de robustez general frente a regresiones.
- Detallaría el análisis de la serie aritmético-geométrica para demostrar la linealidad de la construcción de Heaps con `heapify`.

### Qué parte del código me parece más importante para revisar otra vez
- La implementación precisa de `BinarySearchTree::splice()` y su interacción con `remove()` en el caso de un nodo con dos hijos, prestando especial atención a cómo se transfiere el valor del sucesor y cómo se reconectan los enlaces de alturas hacia arriba (`updateHeightAbove`).


