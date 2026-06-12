### PC3 - CC232

#### Estudiante
- Nombre: Sanchez Cirilo Luis David
- Código: 20210134H
- Problema asignado: 27. Kattis - Cookie Selection
- Enlace oficial: https://open.kattis.com/problems/cookieselection

#### Referencia oficial
- CSV oficial: https://github.com/kapumota/CC-232/blob/main/Practicas/Practica3_CC232/Problemas-Evaluacion3.csv

#### Relación con Semanas 4-6
- Semana principal: Semana 6
- Estructura usada: Binary Heap (Montículo Binario doble)
- Estructura de la librería `cc232` relacionada: Implementación de Heap implícito en arreglos (`percolateUp`, `percolateDown`).

#### Resumen de la solución
El problema nos exige entregar la mediana dinámica de un flujo continuo de valores y retirarla rápidamente. Para evitar re-ordenamientos lentos O(N^2), usamos una estrategia de Dos Heaps: Un Max-Heap que guarda la mitad inferior de las galletas, y un Min-Heap que guarda la mitad superior. La mediana siempre residirá en el tope del Min-Heap, extrayéndola en O(1) y balanceando la estructura en O(log N).

#### Invariante principal
El balanceo entre ambos heaps. El Min-Heap siempre tiene el mismo tamaño que el Max-Heap, o exactamente un elemento más (`min_heap.size() == max_heap.size()` o `min_heap.size() == max_heap.size() + 1`). Esto asegura que el elemento central de la distribución de galletas siempre esté disponible de inmediato.

#### Complejidad
- Tiempo por operación: O(log N) para insertar y extraer.
- Tiempo total: O(N log N) donde N es el total de entradas.
- Espacio: O(N) para alojar a los N elementos en los vectores subyacentes.

#### Archivos relevantes
- `include/BinaryHeap.h`: Implementación transparente del montículo desde cero.
- `include/CookieMedian.h`: Estructura que coordina los dos montículos.
- `src/main.cpp`: Código de ejecución y I/O directo.
- `tests/test_cookieselection.cpp`: Casos de prueba propios.
- `demos/demo_cookieselection.cpp`: Script usado para el reto de grabación sin cortes.
- `docs/respuestas_obligatorias.md`: Justificación técnica de la rúbrica.
- `docs/bitacora.md`: Proceso de desarrollo diario.
- `resultados/`: Ejecuciones y logs.

#### Limpieza del repositorio
El repositorio cumple estrictamente con no versionar basuras, ejecutables ni builds gracias al uso de `.gitignore`.
Comando sugerido de verificación de pureza del repo:
`git ls-files | grep -E "(^build/|cmake-build|\.exe$|\.out$|\.o$|\.obj$|CMakeCache.txt|CMakeFiles|__pycache__)"` (No devuelve nada ilícito).

#### Compilación
```bash
cd Practicas/Practica_Calificada3-CC232
cmake -S . -B build
cmake --build build