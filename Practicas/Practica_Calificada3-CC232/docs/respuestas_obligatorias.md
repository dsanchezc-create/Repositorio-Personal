# Respuestas Obligatorias - Práctica Calificada 3

## Preguntas Comunes Obligatorias

1. **¿Cuál es el problema exacto asignado?**
   El problema es "Cookie Selection" de Kattis (ID: cookieselection). Nos pide procesar un flujo de galletas entrantes y, cada vez que llega una solicitud representada por `#`, debemos entregar y retirar la galleta que representa la mediana del diámetro de todas las galletas disponibles.

2. **¿Qué recibe la entrada y qué produce la salida?**
   Recibe una secuencia de strings. Si el string es un número, representa el diámetro de una nueva galleta. Si el string es un `#`, es una consulta. La salida debe imprimir en cada `#` el diámetro de la galleta mediana extraída.

3. **¿Cuál es la restricción que vuelve insuficiente una solución ingenua?**
   La solución debe manejar inserciones dinámicas y búsquedas de mediana continuas. Mantener un arreglo y ordenarlo en cada consulta toma mucho tiempo por consulta, lo que daría *Time Limit Exceeded* para flujos grandes de datos.

4. **¿Cuál sería la solución ingenua y cuál es su complejidad?**
   Usar un `std::vector`, insertar elementos al final en $O(1)$ y, cada vez que llega `#`, usar `std::sort()` para ordenar el vector y sacar la mediana. La complejidad total sería de $O(N^2 \log N)$ en el peor de los casos (insertar y consultar intercaladamente).

5. **¿Qué estructura de datos elegiste?**
   Elegí el uso de **Dos Heaps (Montículos)**: Un Min-Heap para la mitad superior de los datos y un Max-Heap para la mitad inferior.

6. **¿Qué estructura de la librería `cc232` se parece más?**
   Se apoya directamente en la implementación del `BinaryHeap` de la Semana 6, usando un arreglo implícito (vector) y las operaciones críticas `percolateUp` y `percolateDown`.

7. **¿Qué operación domina el tiempo?**
   Las operaciones `percolateUp` y `percolateDown` al insertar o extraer elementos, las cuales toman un tiempo de $O(\log N)$.

8. **¿Qué invariante mantiene tu estructura?**
   El invariante principal de equilibrio: El Min-Heap siempre tiene la misma cantidad de elementos que el Max-Heap, o exactamente 1 elemento más. Esto garantiza que el tope del Min-Heap sea SIEMPRE la mediana.

9. **¿Dónde se actualiza ese invariante en el código?**
   Se actualiza en el método `balance()` de la clase `CookieMedian`, el cual se llama religiosamente al final de `addCookie()` y de `getMedianAndRemove()`.

10. **¿Qué caso borde puede romper una solución superficial?**
    Que el flujo empiece directamente con un `#` cuando no hay galletas ingresadas, o pedir la mediana cuando la estructura queda vacía. Lo manejo lanzando y capturando un `std::out_of_range`.

11. **¿Cómo manejas duplicados, empates o elementos obsoletos?**
    Los heaps binarios manejan elementos duplicados de forma natural. Simplemente se insertan y el criterio `<` o `>` los acomoda sin problemas en el árbol.

12. **¿Cuál es la complejidad temporal por operación?**
    Tanto insertar una galleta como extraer la mediana toman $O(\log N)$.

13. **¿Cuál es la complejidad total?**
    Para $N$ operaciones, la complejidad total será $O(N \log N)$.

14. **¿Cuál es la complejidad espacial?**
    $O(N)$, ya que todas las $N$ galletas se almacenan divididas entre los arreglos subyacentes de los dos Heaps.

15. **¿Qué parte del código sería más fácil de romper?**
    El cálculo de los índices en el `percolateDown` (hijo izquierdo `hole * 2 + 1`, etc.). Un error en el `<` o en los límites del vector generaría accesos a memoria inválida (Segmentation Fault).

16. **¿Qué alternativa de estructura existe y qué perderías con ella?**
    Se podría usar un *Treap aumentado (Order Statistic Tree)* guardando el tamaño de cada subárbol para buscar el elemento en la posición `k = N/2`. Aunque la complejidad teórica es igual $O(\log N)$, perdería velocidad real (la constante de tiempo) porque los punteros y el balanceo por rotaciones son más lentos y ocupan más memoria que el arreglo plano de un Heap.

17. **¿Qué prueba propia escribiste?**
    Escribí `test2_even_number` para validar cuál de las dos galletas centrales extrae si la cantidad de galletas es par (el problema dicta que extrae la mayor de las dos menores).

18. **¿Qué cambiaste durante el bloque sin cortes?**
    Agregué una secuencia extrayendo medianas consecutivas para probar que la estructura se rebalancea dinámicamente y el nuevo tope del Min-Heap siempre se actualiza.

19. **¿Cómo sabes que el cambio no rompió la solución?**
    Porque re-compilé en vivo y ejecuté el archivo `demo_cookieselection`, mostrando la impresión lógica (`printHeap`) y confirmando la correcta actualización.

20. **¿Qué demuestra que no es una solución de caja negra?**
    No usé `std::priority_queue`. Implementé mi propia clase genérica `BinaryHeap` detallando la lógica matemática de arreglos de los árboles binarios (`percolateUp` / `percolateDown`), tal cual la semana 6 del curso.



## Preguntas Específicas: 27. Kattis - Cookie Selection

1. **¿Qué heap contiene la mitad inferior?**
   El Max-Heap (`max_heap`). Su raíz es el elemento más grande de la mitad pequeña.
2. **¿Qué heap contiene la mitad superior?**
   El Min-Heap (`min_heap`). Su raíz es el elemento más pequeño de la mitad grande (la Mediana).
3. **¿Cómo se reequilibra después de insertar o extraer?**
   Mediante la función `balance()`. Si el Max-Heap es más grande, su raíz pasa al Min-Heap. Si el Min-Heap le saca más de 1 elemento de ventaja al Max-Heap, su raíz pasa al Max-Heap.