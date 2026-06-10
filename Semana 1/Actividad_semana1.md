## Actividad 1- CC232

### Integrantes
- Luis David Sanchez Cirilo

#### BLOQUE 1

1. Diferencia entre problema, algoritmo, ADT e implementación

- **Problema:**  
  El problema sería lo que se quiere hacer, pero sin detalles de como(ej. ordenar datos).

- **Algoritmo:**  
  El algoritmo sería el plan para resolverlo usando pasos concretos y un procedimiento lógico. Secuencia de pasos matemáticos para resolver el problema.

- **ADT (Abstract Data Type):**  
  Son tipos de datos que pueden participar en las soluciones de un problema. El contrato o interfaz (operaciones permitidas), sin importar cómo se almacenan los datos.

- **Implementación:**  
  La implementación es el programa real que ejecuta algoritmo y ADT, se materializa en memoria, datos e instrucciones. El código real (estructuras de datos en memoria, lenguaje específico).


2. En `bubble_sort.cpp`, ¿qué observable conecta correctitud y costo?

El observable clave es:

- `lastSwapIndex`
- `changed`

**Conexión:**

La correctitud matemática indica que todo lo que está a la derecha del último intercambio ya está ordenado.  
La versión optimizada aprovecha esto para reducir el costo, acortando el rango de iteración en cada pasada.

- Mejor caso: $O(n)$ cuando la lista está casi ordenada.


3. En `power.cpp`, ¿por qué mejora frente a la versión ingenua?
Power es más eficiente porque convierte las operaciones redundantes de multiplicar una vez por cada unidad en n en un proceso logarítmico donde cada paso dobla la base (cuadratura) y consume un bit.
En la práctica, para grandes n la diferencia es enorme (n vs log n).
Mejora el rendimiento al pasar de:

- Complejidad lineal: $O(n)$  
- A complejidad logarítmica: $O(\log n)$  

Esto se logra mediante **exponenciación binaria** (técnica de divide y vencerás).


4. En `fibonacci.cpp`, ¿por qué puede ser correcta pero mala en la práctica?

La versión recursiva:

- Es **correcta matemáticamente**
- Pero **ineficiente**

Porque recalcula subproblemas repetidamente:

- Complejidad: $O(2^n)$ (exponencial)

Las versiones iterativas:

- Guardan estado previo
- Complejidad: $O(n)$  
- Son viables en la práctica


5. En `count_ones.cpp`, ¿por qué el tamaño de entrada no coincide con el valor numérico?

El tamaño de entrada ($N$) no es el valor del número, sino:

- La cantidad de **bits necesarios para representarlo**

Ejemplo:

- Un número grande puede representarse en 32 bits → tamaño fijo

Por eso:

- Algunos algoritmos dependen de los bits (no del valor)
- Complejidad ≈ $O(1)$ o proporcional al número de bits encendidos


6. En `demo_adt_secuencia.cpp`, ¿por qué la misma interfaz permite distintas representaciones?

Gracias a la **abstracción (polimorfismo)**. El código cliente interactúa solo con un "contrato" estándar (add, remove, get). Esto permite que internamente una clase use un arreglo estático de tamaño fijo y otra use un arreglo dinámico (std::vector), sin que el cliente note la diferencia.

#### BLOQUE 2
Tabla 

| Archivo                | Salida observable        | Idea algorítmica                                           | Argumento de costo                                      |
|-----------------------|--------------------------|------------------------------------------------------------|----------------------------------------------------------|
| `demo_bubblesort.cpp` | `lastSwapIndex`          | Omitir la porción del arreglo que ya está ordenada         | Baja de $O(n^2)$ a $O(n)$ si hay orden parcial           |
| `demo_power.cpp`      | `powerBF == power`       | Exponenciación binaria (Divide y Vencerás)                 | Reduce multiplicaciones de $O(n)$ a $O(\log n)$          |
| `demo_fibonacci.cpp`  | Uso de variable `prev`   | Memorizar cálculos previos para evitar recomputación       | Baja de $O(2^n)$ a $O(n)$                                |
| `demo_countones.cpp`  | Binario con `bitset<16>` | Operar sobre bits activos o usar máscaras                  | Costo fijo por bits: $O(1)$                              |

Respuestas
1. En `demo_bubblesort.cpp`, ¿qué salida sirve para defender costo y no solo resultado?

El índice lastSwapIndex demuestra empíricamente que el algoritmo detecta la porción ya ordenada y no la vuelve a procesar, probando la reducción del costo a O(n).

2. En `demo_power.cpp`, ¿qué comparación concreta muestra una mejora algorítmica?

Imprimir ambas funciones confirma que producen el mismo resultado, pero la versión optimizada lo logra con saltos exponenciales, evidenciando la caída del costo de O(n) a O(logn).

3. `En demo_fibonacci.cpp`, ¿qué crecimiento se vuelve defendible?


El arrastre del estado (prev) demuestra cómo evitar el recálculo masivo de subproblemas, convirtiendo una explosión exponencial inútil O(2^n) en una ejecución lineal O(n) defendible en la práctica.

4. En `demo_countones.cpp`, ¿qué ejemplo ayuda más a distinguir valor numérico de tamaño en bits?

El uso de std::bitset hace visualmente obvio que el algoritmo iterará como máximo la cantidad de bits del tipo de dato (ej. 32 veces), operando en tiempo O(1), sin importar si el número es 10 o 1,000,000.

#### BLOQUE 3

1. ¿Qué funciones o ideas están verificando las pruebas públicas?

Están verificando la correctitud de casos base o "felices" para algoritmos matemáticos (potencias, Fibonacci, MCM), recursivos (Hanói, Inversión), y de búsqueda/ordenamiento (Bubble Sort, Max).


2. ¿Qué sí demuestra una prueba pública?

Demuestra únicamente que el código no se rompe y produce la respuesta correcta para las entradas exactas y limitadas que el profesor escribió en el test (ej. fib(10) == 55).


3. ¿Qué no demuestra una prueba pública?

No demuestra la correctitud matemática universal (puede fallar con casos borde, negativos, o listas inmensas) y no demuestra la eficiencia teórica (un código O(2^n) y uno O(1) pueden pasar la misma prueba).


4. Elijan una pregunta de preguntas_semana1.md y respóndanla bien. 

Notaciones Asintóticas y Casos

- **O grande:** El "techo" (peor escenario); el algoritmo no tardará más que esto.  
- **Ω grande:** El "piso" (mejor escenario); el algoritmo tardará al menos esto.  
- **Θ grande:** Límite exacto; ocurre cuando el "techo" y el "piso" coinciden.  

- **Peor caso:** La entrada que obliga al algoritmo a hacer el máximo trabajo posible.  
- **Mejor caso:** La entrada que requiere el mínimo trabajo posible.  
- **Caso promedio:** El tiempo esperado considerando estadísticamente todas las entradas posibles.  

**¿Por qué dos correctos no son iguales?**  
Porque uno puede resolver el problema en microsegundos (O(n)) y el otro, aunque correcto, tardar milenios (O(2^n)).

**Crecimiento de Bubble Sort:**  
Es cuadrático (O(n^2)). Si duplicas los datos a ordenar, el tiempo de espera se multiplica por cuatro.


5. Autoevaluación (Nivel: Logrado)

- **Comprensión conceptual:** Definimos con claridad y sin ambigüedades O, Ω, Θ y los tipos de casos.  

- **Sustentación de correctitud:** Entendimos perfectamente la limitación de probar con asserts aislados versus la garantía teórica universal.  

- **Análisis de eficiencia:** Relacionamos matemáticamente el costo de Bubble Sort (O(n^2)) con su impacto físico.


#### BLOQUE 4

 1. ¿Qué diferencia observable deja demo_const_refs.cpp entre lectura, modificación y copia?

La diferencia es cómo las distintas funciones afectan (o no) al espacio de memoria del vector original:

- **Lectura (sum_readonly):**  
  No hay cambios en el vector original. La función solo lee los datos para calcular la suma.  
  El vector sigue siendo: `{1, 2, 3}`

- **Modificación (append_in_place):**  
  El vector original sufre un cambio directo e irreversible.  
  Al pasarse como referencia mutable (`std::vector<int>&`), se modifica el mismo bloque de memoria.  
  El vector pasa a ser: `{1, 2, 3, 4}`

- **Copia (appended_copy):**  
  El vector original permanece intacto (`{1, 2, 3, 4}`).  
  La función crea y devuelve una nueva lista independiente en otro espacio de memoria con el `99` añadido.  
  Cambios en `copied` no afectan a `original`.


 2. En bench_vector_growth.cpp, ¿qué cambia con reserve?

Lo que cambia es la gestión y reasignación de memoria dinámica:

- **Sin `reserve`:**  
  Más lento. El vector se queda sin espacio y debe reasignar memoria múltiples veces, copiando los datos repetidamente.

- **Con `reserve`:**  
  Más rápido. Se asigna toda la memoria necesaria desde el inicio, evitando realocaciones costosas.


 3. En bench_vector_ops.cpp, ¿por qué push_back, insert(begin()) e insert(middle) no cuestan lo mismo?

Porque `std::vector` almacena elementos de forma contigua en memoria:

- **push_back (al final):**  
  Muy rápido. Usa el siguiente espacio disponible.

- **insert (al medio):**  
  Lento. Debe mover aproximadamente la mitad de los elementos.

- **insert (al inicio):**  
  El más lento. Debe mover todos los elementos en cada inserción.


 4. En bench_cache_effects.cpp, ¿qué intuición deja sobre localidad de memoria?

Demuestra que el rendimiento depende de cómo la CPU interactúa con la caché:

- **Vector secuencial (Rápido):**  
  Datos contiguos → mejor uso de caché.

- **Lista enlazada (Lenta):**  
  Datos dispersos → mala predicción de caché.

- **Vector con acceso aleatorio (Muy lento):**  
  Aunque contiguo, los accesos caóticos generan fallos de caché (*cache misses*).


#### BLOQUE 5

 1. Según Ejercicios0.md, ¿cuál es el orden correcto antes de optimizar?

1. Elegir el algoritmo correcto.  
2. Verificar la correctitud del código.  
3. Medir rendimiento.  
4. Aplicar optimizaciones de compilador (`-O2`, `-O3`, etc.).


 2. ¿Qué quiere mostrar stl_optimizacion_demostracion.cpp?

Que el diseño algorítmico supera al microajuste del compilador:

- **reserve:** Evita realocaciones dinámicas costosas.  
- **nth_element:** Encuentra el k-ésimo elemento en `O(n)` (mejor que `O(n log n)` de `sort`).  
- **partial_sort:** Obtiene el Top-K sin ordenar todo.  
- **lower_bound:** Búsqueda binaria en `O(log n)` con alta eficiencia de caché.


 3. ¿Qué tipo de evidencia puede producir resolver_ejercicios0_v4.2.sh?

- **Reporte final:** Markdown con tablas comparativas.  
- **Métricas:** Tiempos de ejecución y tamaño de binarios.  
- **Trazabilidad:** Logs de compilación, ejecución y warnings.  
- **Artefactos avanzados:** Coverage (`gcov`) y profiling (`gprof`).


 4. ¿Qué limitaciones de entorno menciona INSTRUCCIONES_Ejercicios0_v4.2.md?

Entornos como Git Bash o MSYS2 presentan limitaciones:

- Fallan al enlazar *sanitizers*.  
- Problemas con `gcov` y `gprof`.  

Se recomienda:

- Usar **UCRT64** para compilaciones limpias.  
- O migrar a **WSL/Linux nativo** para herramientas avanzadas.


 5. ¿Por qué esta parte no reemplaza la discusión de correctitud de Semana 1?

- **Semana 0 (Herramientas):**  
  Correctitud mecánica/dinámica.  
  Usa herramientas (sanitizers, coverage) para detectar errores técnicos.

- **Semana 1 (Teoría):**  
  Correctitud lógica/formal.  
  Requiere razonamiento matemático (invariantes, pruebas, casos).  

> Las herramientas detectan errores, pero no prueban que un algoritmo sea correcto.

#### BLOQUE 6

**Afirmación de especificación:**
La especificación es una descripción informal del problema (ej. "ordenar un arreglo"), y se defiende que el algoritmo la satisface mediante argumentos lógicos. Con evidencia experimental, se compara cómo implementaciones distintas cumplen la misma especificación en escenarios reales, verificando consistencia observable en pruebas concretas.

**Afirmación de correctitud:**
La correctitud básica se justifica con invariantes y pruebas formales (ej. "el sufijo queda ordenado"), asegurando que el algoritmo termina con la salida correcta para cualquier entrada válida. La evidencia experimental muestra correctitud en casos probados (ej. asserts en tests), pero no garantiza para todos los inputs posibles, ya que depende de datos específicos y entornos.

**Afirmación de costo:**
El costo es teórico y asintótico (ej. Θ(n²) para bubble sort), basado en conteo de operaciones. Con evidencia experimental, se mide costo real (tiempo en segundos, operaciones contadas) en benchmarks, revelando diferencias prácticas entre implementaciones (ej. powerBF vs power en tiempo de ejecución).

**Afirmación de representación o memoria:**
La representación es abstracta (ADT como IntSequence), enfocada en operaciones sin detalles internos. Experimentalmente, se compara cómo representaciones concretas (arreglo fijo vs std::vector) afectan uso de memoria (ej. capacidad vs tamaño real), mostrando trade-offs en crecimiento dinámico o límites fijos.

**Advertencia metodológica:**
La evidencia experimental es contextual y dependiente del entorno (máquina, compilador, datos de prueba), por lo que no es universal ni reemplaza el análisis teórico; puede ocultar fallos en casos no probados o variar con hardware, mientras que la correctitud básica es formal y general.
