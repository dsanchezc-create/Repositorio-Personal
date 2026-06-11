# Bitácora de Desarrollo - PC3 y Actividades Previas

* **Día 1 - Migración y Reestructuración del Repositorio:**
  * Me di cuenta de que mantener un fork directo del repositorio del curso era desordenado. 
  * Decidí crear y estructurar un repositorio personal limpio y organizado, diseñado específicamente para alojar las prácticas calificadas y las actividades de las semanas 4, 5 y 6, separando correctamente las carpetas como dicta la rúbrica.

* **Día 2 - Trabajo en Actividad 5:**
  * Tuve que rehacer la Actividad 5 (Árboles y BST) para asegurarme de dominar las estructuras de datos y tener mi repositorio al día.
  * Implementé las operaciones de búsqueda y validación, asegurando que el código compilara sin depender de binarios externos.

* **Día 3 - Trabajo en Actividad 6:**
  * Rehice la Actividad 6 (Heaps y Priority Queues).
  * Este paso fue fundamental porque me permitió entender a profundidad cómo funciona internamente un montículo en un arreglo (`percolateUp` y `percolateDown`), lo cual sería clave para no usar `std::priority_queue` en la PC3.

* **Día 4 - Inicio de Práctica Calificada 3 (Ayer - 9 de Junio):**
  * Leí y analicé el problema asignado "27. Kattis - Cookie Selection".
  * Descarté la idea de ordenar un vector con `std::sort` en cada consulta por el Time Limit.
  * Decidí usar el enfoque de Dos Heaps. Para evitar la penalización de "caja negra" de la rúbrica, programé mi propia clase genérica `BinaryHeap.h` aplicando lo aprendido en la Actividad 6.

* **Día 5 - Integración y Pruebas locales (Hoy - 10 de Junio):**
  * Implementé `CookieMedian.h` con la lógica de balanceo (manteniendo el Min-Heap siempre igual o un elemento mayor que el Max-Heap).
  * Escribí el `main.cpp` con I/O optimizado (`std::cin.tie`).
  * Creé los casos de prueba unitarios en `test_cookieselection.cpp`, manejando casos pares, impares y duplicados. Validé que todas las aserciones pasaran.

* **Día 6 - Documentación y Preparación del Video (Mañana - 11 de Junio):**
  * Preparé el archivo `demo_cookieselection.cpp` añadiendo la función `printHeap()` para cumplir el reto de la modificación grabada sin cortes del video.
  * Redacté la documentación obligatoria final (`README.md`, `respuestas_obligatorias.md` y `bitacora.md`).
  * Generé los archivos de texto en la carpeta `resultados/` capturando las salidas de consola.
  * Revisé exhaustivamente con `.gitignore` que ninguna carpeta `build/` o archivo autogenerado se filtrara en el repositorio final.