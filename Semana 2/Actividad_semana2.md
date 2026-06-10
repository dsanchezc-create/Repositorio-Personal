## Actividad 2-CC232

## Actividad 2-CC232

### Integrantes
- Luis David Sanchez Cirilo

#### Bloque 1

1. Usar memoria contigua es cuando los elementos de un arreglo están almacenados uno al lado del otro en la memoria. Esto permite un acceso rápido a los elementos, ya que se pueden calcular las direcciones de memoria de manera eficiente. Sin embargo, esto también puede llevar a problemas de fragmentación y limitaciones en el tamaño del arreglo.

2. Acceder a `A[i]` es una operación de costo `O(1)` porque el acceso a un elemento específico en un arreglo se realiza mediante un cálculo directo de la dirección de memoria. Dado que los elementos están almacenados de manera contigua, se puede calcular la dirección del elemento `i` utilizando la fórmula: `dirección_base + (i * tamaño_elemento)`, lo que permite acceder al elemento en tiempo constante.

3. La diferencia entre `size` y `capacity` es que `size` se refiere al número actual de elementos almacenados en el arreglo, mientras que `capacity` se refiere al número máximo de elementos que el arreglo puede almacenar sin necesidad de redimensionarlo. El `size` puede ser menor o igual al `capacity`, pero no puede exceder el `capacity`.

4. El método `resize()` es necesario en un arreglo dinámico porque permite ajustar la capacidad del arreglo cuando se alcanza su límite. Cuando el número de elementos almacenados en el arreglo alcanza su capacidad máxima, el método `resize()` se encarga de crear un nuevo arreglo con una capacidad mayor, copiar los elementos existentes al nuevo arreglo y liberar la memoria del arreglo antiguo. Esto permite que el arreglo dinámico pueda crecer según sea necesario sin perder datos.

5. Duplicar la capacidad del arreglo permite defender un costo amortizado `O(1)` para inserciones al final porque, aunque la operación de redimensionamiento puede ser costosa (con un costo de `O(n)` debido a la necesidad de copiar todos los elementos al nuevo arreglo), esta operación solo ocurre después de cada `n` inserciones. Por lo tanto, el costo total de `n` inserciones es `O(n)` para las inserciones normales más `O(n)` para el redimensionamiento, lo que da un costo promedio de `O(1)` por inserción a lo largo del tiempo.

6. `ArrayStack` y `DengVector` comparten la idea de ser estructuras de datos basadas en arreglos dinámicos que permiten almacenar elementos de manera contigua. 
    Sin embargo, `DengVector` se presenta como una versión más didáctica y detallada, con una interfaz más completa y explicaciones adicionales sobre su funcionamiento interno. 
    Mientras que `ArrayStack` se enfoca en la funcionalidad básica de una pila, `DengVector` busca proporcionar una comprensión más profunda de cómo funcionan los arreglos dinámicos y sus operaciones.

7. `FastArrayStack` mejora respecto a `ArrayStack` al optimizar el proceso de redimensionamiento. 
    En lugar de simplemente duplicar la capacidad, `FastArrayStack` puede implementar estrategias adicionales para minimizar el número de redimensionamientos necesarios, como aumentar la capacidad en factores mayores o utilizar técnicas de amortización más eficientes. Esto puede resultar en un rendimiento mejorado para ciertas cargas de trabajo, especialmente cuando se realizan muchas inserciones al final del arreglo.

8. `RootishArrayStack` es una estructura de datos que utiliza una organización de memoria basada en bloques para almacenar elementos. 
    En lugar de almacenar todos los elementos en un solo bloque contiguo, `RootishArrayStack` divide los elementos en bloques de tamaño creciente (por ejemplo, el primer bloque puede contener 1 elemento, el segundo bloque 2 elementos, el tercer bloque 3 elementos, etc.). 
    Esto permite una gestión más eficiente de la memoria y puede reducir la cantidad de espacio desperdiciado en comparación con un arreglo dinámico tradicional. 
    Además, `RootishArrayStack` puede ofrecer un rendimiento mejorado para ciertas operaciones debido a su estructura de bloques.

9. `RootishArrayStack` utiliza bloques de tamaños `1, 2, 3, ...` para aprovechar la propiedad de que la suma de los primeros `k` números enteros es igual a `k(k + 1) / 2`. 
    Esto significa que el bloque `k` puede contener `k` elementos, y el bloque `k + 1` puede contener `k + 1` elementos, lo que permite una organización eficiente de la memoria y facilita el cálculo de la posición de los elementos dentro de los bloques.

10. La relación entre representación, costo temporal y desperdicio espacial en estas estructuras es que la forma en que se representan los datos (por ejemplo, utilizando bloques de tamaño creciente en `RootishArrayStack`) puede afectar tanto el costo temporal de las operaciones (como inserciones y accesos) como el desperdicio espacial (la cantidad de memoria no utilizada).
    Por ejemplo, un arreglo dinámico tradicional puede tener un costo temporal de `O(1)` para accesos y `O(n)` para redimensionamientos, pero puede desperdiciar espacio si la capacidad es mucho mayor que el tamaño actual. 
    En contraste, `RootishArrayStack` puede reducir el desperdicio espacial al organizar los elementos en bloques de tamaño creciente, aunque esto puede introducir cierta complejidad adicional en el acceso a los elementos. 
    En general, hay un equilibrio entre la eficiencia temporal y el uso eficiente de la memoria que debe ser considerado al diseñar estas estructuras de datos.

#### Bloque 2

|                   Archivo              | Salida u observable importante                                                                            | Idea estructural                                                                  | Argumento de costo o espacio |
|----------------------------------------|-----------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------|
| `demo_array_basico.cpp`                | Muestra cómo se asigna memoria para un arreglo y cómo se accede a sus elementos.                          | Arreglo básico con memoria contigua.                                              | Costo de acceso `O(1)` y asignación de memoria.                                              |
| `demo_arraystack_explicado.cpp`        | Muestra el proceso de inserción y eliminación en un `ArrayStack`, incluyendo el costo de desplazamientos. | Implementación de una pila basada en un arreglo dinámico.                         | Costo de inserción y eliminación, con énfasis en el costo de desplazamientos.                |
| `demo_fastarraystack.cpp`              | Muestra una implementación optimizada de `ArrayStack` con mejoras en el proceso de redimensionamiento.    | Optimización del proceso de redimensionamiento para mejorar el rendimiento.       | Costo de inserción mejorado, aunque la complejidad asintótica sigue siendo `O(1)` amortizado.|
| `demo_rootisharraystack_explicado.cpp` | Explica el mapeo de índice lógico a bloque y offset en `RootishArrayStack`.                               | Estructura de datos basada en bloques de tamaño creciente.                        | Costo de acceso y gestión de memoria, con énfasis en la eficiencia espacial.                 |
| `demo_deng_vector.cpp`                 | Muestra el crecimiento de `capacity` en un `DengVector` y cómo se maneja el redimensionamiento.           | Implementación detallada de un vector dinámico con explicaciones adicionales.     | Costo de inserción y redimensionamiento, con énfasis en la gestión de capacidad.             |
| `demo_stl_vector_contraste.cpp`        | Compara la implementación de `std::vector` con `DengVector`, mostrando similitudes conceptuales.          | Contraste entre una implementación estándar y una didáctica de un vector dinámico.| Costo de inserción y redimensionamiento, destacando similitudes en la gestión de capacidad.  |

1. En `demo_array_basico.cpp`, se deja claro que un arreglo es una estructura de datos que almacena elementos de manera contigua en la memoria, y que la longitud del arreglo se define al momento de su creación. 
    Además, se muestra cómo se asigna memoria para el arreglo y cómo se accede a sus elementos utilizando índices.

2. En `demo_arraystack_explicado.cpp`, la operación que muestra mejor el costo por desplazamientos es la eliminación de elementos del `ArrayStack`.
    Cuando se elimina un elemento, los elementos restantes deben ser desplazados para llenar el espacio vacío, lo que puede resultar en un costo de `O(n)` en el peor caso si se eliminan elementos desde el principio del stack.

3. En `demo_fastarraystack.cpp`, lo que cambia en la implementación es la estrategia de redimensionamiento.
    En lugar de simplemente duplicar la capacidad, `FastArrayStack` puede implementar técnicas adicionales para minimizar el número de redimensionamientos necesarios, lo que puede mejorar el rendimiento en ciertas situaciones.

4. En `demo_rootisharraystack_explicado.cpp`, el ejemplo que explica mejor el mapeo de índice lógico a bloque y offset es el que muestra cómo se calcula la posición de un elemento dado su índice lógico.
    Se muestra cómo se determina a qué bloque pertenece el elemento y cuál es su posición dentro de ese bloque, lo que ayuda a entender la estructura de bloques de `RootishArrayStack`.

5. En `demo_deng_vector.cpp`, el observable que permite defender el crecimiento de `capacity` es la demostración de cómo el vector maneja el redimensionamiento cuando se alcanza la capacidad máxima.
    Se muestra cómo se crea un nuevo arreglo con una capacidad mayor, se copian los elementos existentes y se libera la memoria del arreglo antiguo, lo que permite que el vector pueda crecer según sea necesario.

6. En `demo_stl_vector_contraste.cpp`, la similitud conceptual que se observa con `DengVector` es que ambos implementan un vector dinámico que permite almacenar elementos de manera contigua y manejar el crecimiento de la capacidad de manera eficiente.
    Ambos utilizan estrategias de redimensionamiento para asegurar que las operaciones de inserción al final del vector tengan un costo amortizado de `O(1)`.

7. La demo que sirve mejor para defender **amortización** es `demo_deng_vector.cpp`, ya que muestra claramente cómo el vector maneja el crecimiento de la capacidad y cómo las inserciones al final del vector pueden tener un costo amortizado de `O(1)` a pesar de los costos de redimensionamiento ocasionales.
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 44dae70 (Avance del bloque 3)
    La demo que sirve mejor para defender **uso de espacio** es `demo_rootisharraystack_explicado.cpp`, ya que muestra cómo la estructura de bloques de `RootishArrayStack` puede reducir el desperdicio espacial en comparación con un arreglo dinámico tradicional, al organizar los elementos en bloques de tamaño creciente.

#### Bloque 3

1. La prueba pública para ArrayStack (de test_public_week2.cpp) valida:

add(T x) – insertar al final (operación de conveniencia)
add(int i, T x) – insertar en posición específica
size() – obtener el tamaño actual
get(int i) – acceder a un elemento por índice
remove(int i) – remover un elemento y retornar su valor

2. La prueba pública para FastArrayStack (de test_public_week2.cpp) valida las mismas operaciones:

add(int i, T x) – insertar en posición (con uso de s.size())    
size() – tamaño
get(int i) – acceso por índice
remove(int i) – remoción

3. La prueba pública para RootishArrayStack (de test_public_week2.cpp) también valida las mismas operaciones:

add(int i, T x) – insertar en posición (con uso de s.size())
size() – tamaño 
get(int i) – acceso por índice
remove(int i) – remoción

4. Una prueba pública sobre una estructura de datos demuestra que la implementación cumple con las especificaciones de la interfaz para un conjunto de casos de prueba predefinidos. 
    Esto significa que la estructura de datos se comporta correctamente en esas situaciones específicas, pero no garantiza que la implementación sea correcta en todos los casos posibles. 
    Las pruebas públicas son útiles para validar la funcionalidad básica y detectar errores evidentes, pero no pueden cubrir todas las combinaciones posibles de entradas y estados internos, por lo que no pueden garantizar la corrección total de la estructura de datos.

5. Una prueba pública no demuestra la corrección total de una estructura de datos, ya que solo valida un conjunto limitado de casos de prueba. 
    Para demostrar la corrección total, se necesitaría una prueba formal que cubra todas las posibles combinaciones de entradas y estados internos, lo cual es generalmente impracticable. 
    Sin embargo, las pruebas públicas son valiosas para detectar errores evidentes y validar la funcionalidad básica de la estructura de datos en situaciones comunes.

6. Las pruebas de stress, como `resize_stress_week2.cpp`, son importantes para evaluar el rendimiento y la estabilidad de una estructura de datos bajo condiciones extremas o con grandes volúmenes de datos. 
    Estas pruebas pueden revelar problemas de rendimiento, como tiempos de respuesta excesivos o fallos debido a limitaciones de memoria, que no serían evidentes en pruebas más pequeñas o limitadas. 
    Las pruebas de stress ayudan a garantizar que la estructura de datos pueda manejar cargas de trabajo reales y situaciones imprevistas sin fallar o degradar significativamente su rendimiento.

<<<<<<< HEAD
7. * Las pruebas no reemplazan la necesidad de una justificación formal de la corrección, ya que solo validan un conjunto limitado de casos de prueba. 
   * Los invariantes prueban que la estructura de datos se mantiene en un estado válido durante toda su ejecución, las pruebas solo muestran que la implementación funciona para ciertos casos.
   * La complejidad temporal y espacial se analizan mediante argumentos formales basados en la estructura de la implementación, no solo en la observación de resultados de pruebas. 
     Por lo tanto, aunque las pruebas son útiles para validar la funcionalidad básica, no pueden garantizar la corrección total ni proporcionar una comprensión completa del rendimiento de la estructura de datos.
   * Una prueba correcta no garantiza que la implementación sea eficiente o que se mantenga correcta bajo todas las condiciones posibles, por lo que es esencial complementar las pruebas con análisis formales y justificaciones basadas en invariantes y complejidad.

#### Bloque 4

1. En DengVector.h :
    _size es una variable que almacena el número actual de elementos en el vector. Define el rango válido de índices para acceder a los elementos del vector, ya que los índices van desde [0, _size). Se actualiza cada vez que se agregan o eliminan elementos del vector.
    _capacity es una variable que almacena la capacidad total del vector, es decir, el número máximo de elementos que el vector puede contener sin necesidad de redimensionarlo. Se utiliza para determinar cuándo es necesario realizar un redimensionamiento del vector al agregar nuevos elementos.
    _elem es un puntero a un arreglo dinámico que almacena los elementos del vector. Se asigna en constructores, se reasigna en expand(), se libera en destructores.
    El invariante principal de DengVector es que el número de elementos almacenados (_size) no puede exceder la capacidad total del vector (_capacity), y que los elementos válidos están almacenados en el arreglo apuntado por _elem en las posiciones [0, _size).
                                            0<=_size<=_capacity

2.  expand() se ejecuta cuando se intenta agregar un elemento al vector y el número actual de elementos (_size) ha alcanzado la capacidad total del vector (_capacity). 
    En este caso, expand() se encarga de crear un nuevo arreglo con una capacidad mayor (generalmente el doble de la capacidad actual), copiar los elementos existentes al nuevo arreglo, actualizar el puntero _elem para que apunte al nuevo arreglo y liberar la memoria del arreglo antiguo. 
    Esto permite que el vector pueda crecer según sea necesario sin perder datos.

3.  insert(r, e) necesita desplazar elementos porque se está insertando un nuevo elemento en una posición específica (r), lo que requiere mover todos los elementos que están después de esa posición para hacer espacio. 
    Por ejemplo, si se inserta un elemento en la posición 2 de un vector que ya tiene elementos en las posiciones 0, 1, 2, 3, etc., los elementos en las posiciones 2, 3, etc. deben ser desplazados a las posiciones 3, 4, etc. para hacer espacio para el nuevo elemento en la posición 2. 
    Este proceso de desplazamiento es necesario para mantener la contigüidad de los elementos en el vector y garantizar que el nuevo elemento se inserte correctamente en la posición deseada.

4. La diferencia conceptual entre remove(r) y remove(lo, hi) es que remove(r) se utiliza para eliminar un solo elemento en la posición r, mientras que remove(lo, hi) se utiliza para eliminar un rango de elementos desde la posición lo hasta la posición hi (exclusivo). 
    En remove(r), solo se elimina el elemento en la posición r y los elementos posteriores se desplazan para llenar el espacio vacío. 
    En remove(lo, hi), se eliminan todos los elementos en el rango especificado y los elementos posteriores se desplazan para llenar el espacio vacío dejado por el rango eliminado.

5. La evidencia de copia profunda en la demo de DengVector se puede observar en el constructor de copia y el operador de asignación.DengVector(const DengVector<T>& V) {
    copyFrom(V._elem, 0, V._size);  // Crea NUEVO arreglo, copia datos
    }

    void copyFrom(const T* A, int lo, int hi) {
        const int n = hi - lo;
        _capacity = (n * 2 > DEFAULT_CAPACITY) ? (n * 2) : DEFAULT_CAPACITY;
        _elem = new T[_capacity];        // NUEVO bloque de memoria
        _size = 0;
        while (lo < hi) {
            _elem[_size++] = A[lo++];    // Copia cada elemento
        }
    }

    DengVector<T>& operator=(const DengVector<T>& V) {
       if (this != &V) {
           delete[] _elem;              // Libera el arreglo ANTERIOR
           copyFrom(V._elem, 0, V._size);  // Crea NUEVO arreglo
       }
       return *this;
    }
    En el constructor de copia, se crea un nuevo arreglo y se copian los elementos del vector original al nuevo arreglo, lo que garantiza que el nuevo vector tenga su propia copia de los datos.
    En el operador de asignación, se libera la memoria del arreglo actual, se asigna un nuevo arreglo y se copian los elementos del vector original al nuevo arreglo, lo que también garantiza que el vector asignado tenga su propia copia de los datos.
    Esta implementación asegura que cada instancia de DengVector maneje su propia memoria y evita problemas de aliasing que podrían surgir con una copia superficial.

6. a. Separa iteración de procesamiento: traverse() permite aplicar una función a cada elemento sin preocuparse por la lógica de iteración, lo que simplifica el código del cliente.
   b. Permite encapsular la lógica de recorrido: traverse() puede manejar diferentes formas de recorrer el vector (por ejemplo, en orden, en orden inverso, etc.) sin que el cliente tenga que preocuparse por los detalles.
   c. Facilita la reutilización de código: al tener una función dedicada para recorrer el vector, se puede reutilizar esa función en diferentes contextos sin duplicar la lógica de iteración.
   d. Evita exposición innecesaria de índices: al usar traverse(), el cliente no necesita acceder directamente a los índices del vector, lo que puede reducir errores relacionados con el manejo de índices y mejorar la seguridad del código.
   // ❌ Enfoque bajo nivel (requiere saber índices)
    for (int i = 0; i < v.size(); ++i) {
        visit(v[i]);
    }

    // ✓ Enfoque alto nivel (abstrae la iteración)
    v.traverse(visit);
    
    e. Muestra dos técnicas de generalización: se puede usar traverse() con diferentes funciones de visita para realizar diversas operaciones sobre los elementos del vector, lo que demuestra la flexibilidad y generalidad de esta interfaz.
        *Puntero a función:
          void increaseByOne(int& x) { ++x; }
          v.traverse(increaseByOne);
        *Objeto con operador de función:
          struct IncreaseByOne {
              void operator()(int& x) { ++x; }
          };
          v.traverse(IncreaseByOne());

7. Implementar un vector propio antes de depender de std::vector tiene varias ventajas:
   a. Comprensión profunda: Implementar un vector propio permite entender en detalle cómo funcionan los arreglos dinámicos, incluyendo la gestión de memoria, el redimensionamiento y las operaciones básicas. Esto proporciona una base sólida para comprender otras estructuras de datos y algoritmos.
   b. Personalización: Al implementar un vector propio, se tiene la libertad de personalizar la funcionalidad y el comportamiento del vector según las necesidades específicas de un proyecto o aplicación, lo que puede no ser posible con std::vector.
   c. Control total: Implementar un vector propio brinda un control total sobre la implementación, lo que permite optimizar el rendimiento, la eficiencia y el uso de memoria de acuerdo con los requisitos específicos del proyecto.
   d. Aprendizaje práctico: La implementación de un vector propio es una excelente oportunidad para aplicar conceptos teóricos en la práctica, lo que puede mejorar la comprensión de los principios de diseño de estructuras de datos y algoritmos, así como desarrollar habilidades de programación y resolución de problemas.
   e. Evitar dependencias externas: En algunos casos, puede ser deseable evitar depender de bibliotecas externas como std::vector, ya sea por razones de rendimiento, compatibilidad o simplemente para tener un mayor control sobre la implementación. Implementar un vector propio permite lograr esto sin sacrificar la funcionalidad básica de un vector dinámico.


#### Bloque 5
1. En `RootishArrayStack`: ArrayStack<T*> blocks;  // ArrayStack de punteros a bloques
                           int n;                  // Número total de elementos
    Los elementos se distribuyen entre bloques de tamaño creciente. El primer bloque puede contener 1 elemento, el segundo bloque puede contener 2 elementos, el tercer bloque puede contener 3 elementos, y así sucesivamente. 
    Esto significa que el bloque `k` puede contener `k` elementos, lo que permite una organización eficiente de la memoria y facilita el cálculo de la posición de los elementos dentro de los bloques.

2. Con `r` bloques, la capacidad total es `r(r + 1) / 2` porque la suma de los primeros `r` números enteros es igual a `r(r + 1) / 2`. 
    Esto se debe a que el bloque 1 puede contener 1 elemento, el bloque 2 puede contener 2 elementos, el bloque 3 puede contener 3 elementos, y así sucesivamente hasta el bloque `r`, que puede contener `r` elementos. 
    Por lo tanto, la capacidad total del `RootishArrayStack` con `r` bloques es la suma de los primeros `r` números enteros, lo que se calcula como `r(r + 1) / 2`.

3. La función `i2b(i)` resuelve el problema de determinar a qué bloque pertenece un elemento dado su índice lógico `i`.
    Dado un índice lógico `i`, `i2b(i)` calcula el bloque `b` al que pertenece el elemento en la posición `i` utilizando la fórmula `b = ceil((-1 + sqrt(1 + 8*i)) / 2)`.
    Esta fórmula se deriva de la relación entre el número de elementos y el número de bloques, y permite determinar de manera eficiente el bloque correspondiente para cualquier índice lógico `i` en el `RootishArrayStack`.

4. En RootishArrayStackExplicado.h:
        std::pair<int, int> locate(int i) const {
            const int b = i2b(i);
            const int j = i - b * (b + 1) / 2;
            return {b, j};
        }
    locate(i) en la versión explicada produce la información de qué bloque `b` contiene el elemento en la posición `i` y cuál es el offset dentro de ese bloque. 
    Es decir, dado un índice lógico `i`, locate(i) devuelve el bloque `b` al que pertenece el elemento y el offset dentro de ese bloque, lo que permite acceder al elemento de manera eficiente utilizando la estructura de bloques del `RootishArrayStack`.

5. En comparación con `ArrayStack`, `RootishArrayStack` puede reducir el desperdicio espacial al organizar los elementos en bloques de tamaño creciente, lo que permite una gestión más eficiente de la memoria. En un `ArrayStack`, la capacidad se duplica cada vez que se alcanza el límite, lo que puede resultar en un desperdicio de espacio significativo si el número de elementos es mucho menor que la capacidad. 
    En contraste, `RootishArrayStack` utiliza bloques de tamaño creciente, lo que puede reducir el desperdicio espacial al permitir que el número de bloques se ajuste de manera más flexible a la cantidad de elementos almacenados. En resumen, `RootishArrayStack` reduce desperdicio de O(n) a O(sqrt(n)).

6.  // ArrayStack
    ods::ArrayStack<int> s;
    s.add(0, 5);
    int x = s.get(0);
    s.remove(0);
    
    // RootishArrayStack
    ods::RootishArrayStack<int> s;
    s.add(0, 5);  // MISMO código
    int x = s.get(0);  // MISMO código
    s.remove(0);  // MISMO código
    
En `RootishArrayStack`, la implementación interna cambió radicalmente (de 1 bloque a múltiples bloques), pero la interfaz pública permanece igual. Esto permite:
Intercambiabilidad: Cambiar de ArrayStack a RootishArrayStack solo alterando el tipo, sin tocar el código cliente.
Pruebas reutilizables: Las mismas pruebas validan ambas estructuras.
Polimorfismo: Ambas podrían heredar de una clase base List<T> y ser usadas de forma genérica.

Lo que cambió internamente:
- get(i) ahora llama locate(i) para mapear a (bloque, offset)
- add(i, x) usa set() repetidamente en lugar de desplazamientos de memoria contigua
- grow() agrega un nuevo bloque en lugar de duplicar capacidad total

7. La parte más difícil de defender oralmente puede ser el mapeo de índice lógico a bloque y offset, ya que implica comprender la relación entre el número de elementos, el número de bloques y cómo se calcula la posición de un elemento dado su índice lógico. 
    El análisis espacial también puede ser desafiante, ya que requiere entender cómo la estructura de bloques afecta el uso de memoria y cómo se compara con otras estructuras como `ArrayStack`. 
    El costo amortizado de `grow/shrink` puede ser más fácil de defender, ya que se basa en conceptos más comunes de redimensionamiento y gestión de capacidad que son familiares para muchos programadores. 
    En general, el mapeo y el análisis espacial pueden requerir una explicación más detallada y visual para que sea completamente claro para todos.


#### Bloque 6

1. operator[] proporciona dos cosas simultáneamente:
-   Naturalidad sintáctica: Recupera la notación familiar del arreglo (v[i] en lugar de v.get(i)), haciendo el código más legible e intuitivo.
-   Encapsulación sin sacrificio: Aunque estemos utilizando la sintaxis cómoda del arreglo, el vector mantiene control total sobre acceso, validación y gestión interna de memoria.
Muestra que la abstracción no tiene por qué ser menos conveniente que la sintaxis directa, y que es posible ofrecer una interfaz amigable sin exponer detalles internos.

2.  a. Supone que la igualdad es decidible: Para comparar dos objetos de tipo T, el operador de igualdad (==) debe estar definido y ser capaz de determinar si dos objetos son iguales o no.
    b. Requiere que T sea copiable: Para almacenar elementos en el vector, el tipo T debe ser copiable, lo que significa que debe tener un constructor de copia o un operador de asignación definido para permitir la creación de copias de los objetos almacenados.
    c. No impone restricciones adicionales sobre T: A diferencia de otras estructuras de datos que pueden requerir que T implemente ciertas interfaces o tenga ciertas propiedades (como ser comparable o tener un orden), el vector solo requiere que T sea copiable y tenga un operador de igualdad definido, lo que lo hace más flexible en términos de los tipos de datos que puede almacenar.

3. Muestra: 
    a. La separación de responsabilidades: El vector se encarga de la gestión de memoria, el redimensionamiento y la validación de índices, mientras que el cliente solo interactúa con una interfaz simple y familiar.
    b. La importancia de la abstracción: El vector oculta los detalles de implementación y proporciona una interfaz clara, lo que permite a los usuarios centrarse en el uso del vector sin preocuparse por cómo funciona internamente.
        // Bajo nivel (el usuario maneja iteración):
        for (int i = 0; i < v.size(); ++i) {
            visit(v[i]);
        }
    
        // Alto nivel (la estructura maneja iteración):
        v.traverse(visit);

    c. La flexibilidad de la implementación: Al implementar un vector propio, se tiene la libertad de personalizar su comportamiento y optimizarlo según las necesidades específicas, lo que puede no ser posible con una implementación estándar como std::vector.
    d. La necesidad de una justificación formal: Aunque la implementación de un vector puede parecer sencilla, es importante ser capaz de justificar formalmente su corrección, eficiencia y uso de memoria, lo que requiere un análisis cuidadoso de los invariantes, la complejidad temporal y espacial, y la gestión de memoria.

4.  a. La Lectura4-Deng describe conceptos (capacidad, expansión, análisis amortizado, copia profunda). DengVector.h es la implementación de esos conceptos.
        Leer primero la teoría, luego ver el código, refuerza la comprensión.
    b. Conecta abstracción con implementación: La lectura explica la lógica detrás de las decisiones de diseño, mientras que el código muestra cómo se implementan esas ideas en la práctica.
    c. Nos muestra como los invariantes y análisis formal se reflejan en el código real, lo que ayuda a entender la importancia de esos conceptos para garantizar la corrección y eficiencia de la estructura de datos.
    d. Es una base para ArrayStack y RootishArrayStack: Al entender DengVector, se pueden apreciar mejor las mejoras y diferencias en las otras estructuras, así como la importancia de la gestión de capacidad y el análisis amortizado en todas ellas.


#### Bloque 7

Al pasar de simplemente usar un arreglo a diseñar una estructura dinámica, el cambio fundamental radica en que dejamos de manipular celdas de memoria estática para implementar un Tipo Abstracto de Datos (TAD). Este TAD actúa como una abstracción de secuencia que encapsula reglas de crecimiento y garantías de desempeño.

1. Fundamentos del Diseño Dinámico

    Representación
    En lugar de un arreglo de tamaño fijo, mantenemos una representación con **estado lógico** ($n$) y **almacenamiento físico adaptable** (capacidad). La clave es la separación entre el índice que percibe el usuario y la ubicación real en memoria, gestionada mediante una función de mapeo (ej. `index -> data[index]`).

    Correctitud
    La estructura se considera correcta si sus operaciones (`get`, `set`, `add`, `remove`) preservan los **invariantes de representación**. Estos incluyen asegurar que $0 \le i < n$, que siempre exista capacidad suficiente antes de una inserción y que, en estructuras complejas como `RootishArrayStack`, el mapeo por bloques sea consistente tras cada cambio.

    Costo Amortizado
    El diseño dinámico permite que operaciones costosas (como redimensionar y copiar $n$ elementos) ocurran con poca frecuencia. Al usar un factor de crecimiento geométrico, el costo de estas redistribuciones se distribuye entre muchas operaciones "baratas", resultando en un costo de **$O(1)$ amortizado** para insertar o eliminar al final.

    Uso de Espacio:
    A diferencia del arreglo estático, las estructuras dinámicas introducen **"espacio ocioso" (slack)**. El diseño busca un equilibrio: suficiente espacio libre para evitar redimensionamientos constantes, pero no tanto como para desperdiciar memoria innecesariamente.



2. Comparativa de Implementaciones en C++

A continuación se comparan tres variantes comunes bajo el estándar de eficiencia en C++:

| Estructura            | Mecanismo de Memoria                               | Particularidad en C++                                                                 | Eficiencia de Espacio             |
| :-------------------- | :------------------------------------------------- | :------------------------------------------------------------------------------------ | :-------------------------------- |
| **ArrayStack**        | Un solo bloque contiguo que se duplica/contrae.    | Implementación estándar con `new[]` / `delete[]`.                                     | $O(n)$ de desperdicio.            |
| **FastArrayStack**    | Igual al ArrayStack pero optimizado.               | Utiliza `std::copy` o `std::copy_backward` para mover bloques a nivel de bits.        | $O(n)$ de desperdicio.            |
| **RootishArrayStack** | Memoria dividida en bloques de tamaño $1, 2, 3...$ | El mapeo de índice a bloque usa la fórmula: $b = \lceil(-3 + \sqrt{9 + 8i})/2\rceil$. | **$O(\sqrt{n})$** de desperdicio. |
=======
    La demo que sirve mejor para defender **uso de espacio** es `demo_rootisharraystack_explicado.cpp`, ya que muestra cómo la estructura de bloques de `RootishArrayStack` puede reducir el desperdicio espacial en comparación con un arreglo dinámico tradicional, al organizar los elementos en bloques de tamaño creciente.
>>>>>>> d49df78 (Correción)
=======
7. * Las pruebas no reemplazan la necesidad de una justificación formal de la corrección, ya que solo validan un conjunto limitado de casos de prueba. 
   * Los invariantes prueban que la estructura de datos se mantiene en un estado válido durante toda su ejecución, las pruebas solo muestran que la implementación funciona para ciertos casos.
   * La complejidad temporal y espacial se analizan mediante argumentos formales basados en la estructura de la implementación, no solo en la observación de resultados de pruebas. 
     Por lo tanto, aunque las pruebas son útiles para validar la funcionalidad básica, no pueden garantizar la corrección total ni proporcionar una comprensión completa del rendimiento de la estructura de datos.
   * Una prueba correcta no garantiza que la implementación sea eficiente o que se mantenga correcta bajo todas las condiciones posibles, por lo que es esencial complementar las pruebas con análisis formales y justificaciones basadas en invariantes y complejidad.
>>>>>>> 44dae70 (Avance del bloque 3)

#### Bloque 4

1. En DengVector.h :
    _size es una variable que almacena el número actual de elementos en el vector. Define el rango válido de índices para acceder a los elementos del vector, ya que los índices van desde [0, _size). Se actualiza cada vez que se agregan o eliminan elementos del vector.
    _capacity es una variable que almacena la capacidad total del vector, es decir, el número máximo de elementos que el vector puede contener sin necesidad de redimensionarlo. Se utiliza para determinar cuándo es necesario realizar un redimensionamiento del vector al agregar nuevos elementos.
    _elem es un puntero a un arreglo dinámico que almacena los elementos del vector. Se asigna en constructores, se reasigna en expand(), se libera en destructores.
    El invariante principal de DengVector es que el número de elementos almacenados (_size) no puede exceder la capacidad total del vector (_capacity), y que los elementos válidos están almacenados en el arreglo apuntado por _elem en las posiciones [0, _size).
                                            0<=_size<=_capacity

2.  expand() se ejecuta cuando se intenta agregar un elemento al vector y el número actual de elementos (_size) ha alcanzado la capacidad total del vector (_capacity). 
    En este caso, expand() se encarga de crear un nuevo arreglo con una capacidad mayor (generalmente el doble de la capacidad actual), copiar los elementos existentes al nuevo arreglo, actualizar el puntero _elem para que apunte al nuevo arreglo y liberar la memoria del arreglo antiguo. 
    Esto permite que el vector pueda crecer según sea necesario sin perder datos.

3.  insert(r, e) necesita desplazar elementos porque se está insertando un nuevo elemento en una posición específica (r), lo que requiere mover todos los elementos que están después de esa posición para hacer espacio. 
    Por ejemplo, si se inserta un elemento en la posición 2 de un vector que ya tiene elementos en las posiciones 0, 1, 2, 3, etc., los elementos en las posiciones 2, 3, etc. deben ser desplazados a las posiciones 3, 4, etc. para hacer espacio para el nuevo elemento en la posición 2. 
    Este proceso de desplazamiento es necesario para mantener la contigüidad de los elementos en el vector y garantizar que el nuevo elemento se inserte correctamente en la posición deseada.

4. La diferencia conceptual entre remove(r) y remove(lo, hi) es que remove(r) se utiliza para eliminar un solo elemento en la posición r, mientras que remove(lo, hi) se utiliza para eliminar un rango de elementos desde la posición lo hasta la posición hi (exclusivo). 
    En remove(r), solo se elimina el elemento en la posición r y los elementos posteriores se desplazan para llenar el espacio vacío. 
    En remove(lo, hi), se eliminan todos los elementos en el rango especificado y los elementos posteriores se desplazan para llenar el espacio vacío dejado por el rango eliminado.

5. La evidencia de copia profunda en la demo de DengVector se puede observar en el constructor de copia y el operador de asignación.DengVector(const DengVector<T>& V) {
    copyFrom(V._elem, 0, V._size);  // Crea NUEVO arreglo, copia datos
    }

    void copyFrom(const T* A, int lo, int hi) {
        const int n = hi - lo;
        _capacity = (n * 2 > DEFAULT_CAPACITY) ? (n * 2) : DEFAULT_CAPACITY;
        _elem = new T[_capacity];        // NUEVO bloque de memoria
        _size = 0;
        while (lo < hi) {
            _elem[_size++] = A[lo++];    // Copia cada elemento
        }
    }

    DengVector<T>& operator=(const DengVector<T>& V) {
       if (this != &V) {
           delete[] _elem;              // Libera el arreglo ANTERIOR
           copyFrom(V._elem, 0, V._size);  // Crea NUEVO arreglo
       }
       return *this;
    }
    En el constructor de copia, se crea un nuevo arreglo y se copian los elementos del vector original al nuevo arreglo, lo que garantiza que el nuevo vector tenga su propia copia de los datos.
    En el operador de asignación, se libera la memoria del arreglo actual, se asigna un nuevo arreglo y se copian los elementos del vector original al nuevo arreglo, lo que también garantiza que el vector asignado tenga su propia copia de los datos.
    Esta implementación asegura que cada instancia de DengVector maneje su propia memoria y evita problemas de aliasing que podrían surgir con una copia superficial.

6. a. Separa iteración de procesamiento: traverse() permite aplicar una función a cada elemento sin preocuparse por la lógica de iteración, lo que simplifica el código del cliente.
   b. Permite encapsular la lógica de recorrido: traverse() puede manejar diferentes formas de recorrer el vector (por ejemplo, en orden, en orden inverso, etc.) sin que el cliente tenga que preocuparse por los detalles.
   c. Facilita la reutilización de código: al tener una función dedicada para recorrer el vector, se puede reutilizar esa función en diferentes contextos sin duplicar la lógica de iteración.
   d. Evita exposición innecesaria de índices: al usar traverse(), el cliente no necesita acceder directamente a los índices del vector, lo que puede reducir errores relacionados con el manejo de índices y mejorar la seguridad del código.
   // ❌ Enfoque bajo nivel (requiere saber índices)
    for (int i = 0; i < v.size(); ++i) {
        visit(v[i]);
    }

    // ✓ Enfoque alto nivel (abstrae la iteración)
    v.traverse(visit);
    
    e. Muestra dos técnicas de generalización: se puede usar traverse() con diferentes funciones de visita para realizar diversas operaciones sobre los elementos del vector, lo que demuestra la flexibilidad y generalidad de esta interfaz.
        *Puntero a función:
          void increaseByOne(int& x) { ++x; }
          v.traverse(increaseByOne);
        *Objeto con operador de función:
          struct IncreaseByOne {
              void operator()(int& x) { ++x; }
          };
          v.traverse(IncreaseByOne());

7. Implementar un vector propio antes de depender de std::vector tiene varias ventajas:
   a. Comprensión profunda: Implementar un vector propio permite entender en detalle cómo funcionan los arreglos dinámicos, incluyendo la gestión de memoria, el redimensionamiento y las operaciones básicas. Esto proporciona una base sólida para comprender otras estructuras de datos y algoritmos.
   b. Personalización: Al implementar un vector propio, se tiene la libertad de personalizar la funcionalidad y el comportamiento del vector según las necesidades específicas de un proyecto o aplicación, lo que puede no ser posible con std::vector.
   c. Control total: Implementar un vector propio brinda un control total sobre la implementación, lo que permite optimizar el rendimiento, la eficiencia y el uso de memoria de acuerdo con los requisitos específicos del proyecto.
   d. Aprendizaje práctico: La implementación de un vector propio es una excelente oportunidad para aplicar conceptos teóricos en la práctica, lo que puede mejorar la comprensión de los principios de diseño de estructuras de datos y algoritmos, así como desarrollar habilidades de programación y resolución de problemas.
   e. Evitar dependencias externas: En algunos casos, puede ser deseable evitar depender de bibliotecas externas como std::vector, ya sea por razones de rendimiento, compatibilidad o simplemente para tener un mayor control sobre la implementación. Implementar un vector propio permite lograr esto sin sacrificar la funcionalidad básica de un vector dinámico.


#### Bloque 5
1. En `RootishArrayStack`: ArrayStack<T*> blocks;  // ArrayStack de punteros a bloques
                           int n;                  // Número total de elementos
    Los elementos se distribuyen entre bloques de tamaño creciente. El primer bloque puede contener 1 elemento, el segundo bloque puede contener 2 elementos, el tercer bloque puede contener 3 elementos, y así sucesivamente. 
    Esto significa que el bloque `k` puede contener `k` elementos, lo que permite una organización eficiente de la memoria y facilita el cálculo de la posición de los elementos dentro de los bloques.

2. Con `r` bloques, la capacidad total es `r(r + 1) / 2` porque la suma de los primeros `r` números enteros es igual a `r(r + 1) / 2`. 
    Esto se debe a que el bloque 1 puede contener 1 elemento, el bloque 2 puede contener 2 elementos, el bloque 3 puede contener 3 elementos, y así sucesivamente hasta el bloque `r`, que puede contener `r` elementos. 
    Por lo tanto, la capacidad total del `RootishArrayStack` con `r` bloques es la suma de los primeros `r` números enteros, lo que se calcula como `r(r + 1) / 2`.

3. La función `i2b(i)` resuelve el problema de determinar a qué bloque pertenece un elemento dado su índice lógico `i`.
    Dado un índice lógico `i`, `i2b(i)` calcula el bloque `b` al que pertenece el elemento en la posición `i` utilizando la fórmula `b = ceil((-1 + sqrt(1 + 8*i)) / 2)`.
    Esta fórmula se deriva de la relación entre el número de elementos y el número de bloques, y permite determinar de manera eficiente el bloque correspondiente para cualquier índice lógico `i` en el `RootishArrayStack`.

4. En RootishArrayStackExplicado.h:
        std::pair<int, int> locate(int i) const {
            const int b = i2b(i);
            const int j = i - b * (b + 1) / 2;
            return {b, j};
        }
    locate(i) en la versión explicada produce la información de qué bloque `b` contiene el elemento en la posición `i` y cuál es el offset dentro de ese bloque. 
    Es decir, dado un índice lógico `i`, locate(i) devuelve el bloque `b` al que pertenece el elemento y el offset dentro de ese bloque, lo que permite acceder al elemento de manera eficiente utilizando la estructura de bloques del `RootishArrayStack`.

5. En comparación con `ArrayStack`, `RootishArrayStack` puede reducir el desperdicio espacial al organizar los elementos en bloques de tamaño creciente, lo que permite una gestión más eficiente de la memoria. En un `ArrayStack`, la capacidad se duplica cada vez que se alcanza el límite, lo que puede resultar en un desperdicio de espacio significativo si el número de elementos es mucho menor que la capacidad. 
    En contraste, `RootishArrayStack` utiliza bloques de tamaño creciente, lo que puede reducir el desperdicio espacial al permitir que el número de bloques se ajuste de manera más flexible a la cantidad de elementos almacenados. En resumen, `RootishArrayStack` reduce desperdicio de O(n) a O(sqrt(n)).

6.  // ArrayStack
    ods::ArrayStack<int> s;
    s.add(0, 5);
    int x = s.get(0);
    s.remove(0);
    
    // RootishArrayStack
    ods::RootishArrayStack<int> s;
    s.add(0, 5);  // MISMO código
    int x = s.get(0);  // MISMO código
    s.remove(0);  // MISMO código
    
En `RootishArrayStack`, la implementación interna cambió radicalmente (de 1 bloque a múltiples bloques), pero la interfaz pública permanece igual. Esto permite:
Intercambiabilidad: Cambiar de ArrayStack a RootishArrayStack solo alterando el tipo, sin tocar el código cliente.
Pruebas reutilizables: Las mismas pruebas validan ambas estructuras.
Polimorfismo: Ambas podrían heredar de una clase base List<T> y ser usadas de forma genérica.

Lo que cambió internamente:
- get(i) ahora llama locate(i) para mapear a (bloque, offset)
- add(i, x) usa set() repetidamente en lugar de desplazamientos de memoria contigua
- grow() agrega un nuevo bloque en lugar de duplicar capacidad total

7. La parte más difícil de defender oralmente puede ser el mapeo de índice lógico a bloque y offset, ya que implica comprender la relación entre el número de elementos, el número de bloques y cómo se calcula la posición de un elemento dado su índice lógico. 
    El análisis espacial también puede ser desafiante, ya que requiere entender cómo la estructura de bloques afecta el uso de memoria y cómo se compara con otras estructuras como `ArrayStack`. 
    El costo amortizado de `grow/shrink` puede ser más fácil de defender, ya que se basa en conceptos más comunes de redimensionamiento y gestión de capacidad que son familiares para muchos programadores. 
    En general, el mapeo y el análisis espacial pueden requerir una explicación más detallada y visual para que sea completamente claro para todos.


#### Bloque 6

1. operator[] proporciona dos cosas simultáneamente:
-   Naturalidad sintáctica: Recupera la notación familiar del arreglo (v[i] en lugar de v.get(i)), haciendo el código más legible e intuitivo.
-   Encapsulación sin sacrificio: Aunque estemos utilizando la sintaxis cómoda del arreglo, el vector mantiene control total sobre acceso, validación y gestión interna de memoria.
Muestra que la abstracción no tiene por qué ser menos conveniente que la sintaxis directa, y que es posible ofrecer una interfaz amigable sin exponer detalles internos.

2.  a. Supone que la igualdad es decidible: Para comparar dos objetos de tipo T, el operador de igualdad (==) debe estar definido y ser capaz de determinar si dos objetos son iguales o no.
    b. Requiere que T sea copiable: Para almacenar elementos en el vector, el tipo T debe ser copiable, lo que significa que debe tener un constructor de copia o un operador de asignación definido para permitir la creación de copias de los objetos almacenados.
    c. No impone restricciones adicionales sobre T: A diferencia de otras estructuras de datos que pueden requerir que T implemente ciertas interfaces o tenga ciertas propiedades (como ser comparable o tener un orden), el vector solo requiere que T sea copiable y tenga un operador de igualdad definido, lo que lo hace más flexible en términos de los tipos de datos que puede almacenar.

3. Muestra: 
    a. La separación de responsabilidades: El vector se encarga de la gestión de memoria, el redimensionamiento y la validación de índices, mientras que el cliente solo interactúa con una interfaz simple y familiar.
    b. La importancia de la abstracción: El vector oculta los detalles de implementación y proporciona una interfaz clara, lo que permite a los usuarios centrarse en el uso del vector sin preocuparse por cómo funciona internamente.
        // Bajo nivel (el usuario maneja iteración):
        for (int i = 0; i < v.size(); ++i) {
            visit(v[i]);
        }
    
        // Alto nivel (la estructura maneja iteración):
        v.traverse(visit);

    c. La flexibilidad de la implementación: Al implementar un vector propio, se tiene la libertad de personalizar su comportamiento y optimizarlo según las necesidades específicas, lo que puede no ser posible con una implementación estándar como std::vector.
    d. La necesidad de una justificación formal: Aunque la implementación de un vector puede parecer sencilla, es importante ser capaz de justificar formalmente su corrección, eficiencia y uso de memoria, lo que requiere un análisis cuidadoso de los invariantes, la complejidad temporal y espacial, y la gestión de memoria.

4.  a. La Lectura4-Deng describe conceptos (capacidad, expansión, análisis amortizado, copia profunda). DengVector.h es la implementación de esos conceptos.
        Leer primero la teoría, luego ver el código, refuerza la comprensión.
    b. Conecta abstracción con implementación: La lectura explica la lógica detrás de las decisiones de diseño, mientras que el código muestra cómo se implementan esas ideas en la práctica.
    c. Nos muestra como los invariantes y análisis formal se reflejan en el código real, lo que ayuda a entender la importancia de esos conceptos para garantizar la corrección y eficiencia de la estructura de datos.
    d. Es una base para ArrayStack y RootishArrayStack: Al entender DengVector, se pueden apreciar mejor las mejoras y diferencias en las otras estructuras, así como la importancia de la gestión de capacidad y el análisis amortizado en todas ellas.


#### Bloque 7

Al pasar de simplemente usar un arreglo a diseñar una estructura dinámica, el cambio fundamental radica en que dejamos de manipular celdas de memoria estática para implementar un Tipo Abstracto de Datos (TAD). Este TAD actúa como una abstracción de secuencia que encapsula reglas de crecimiento y garantías de desempeño.

1. Fundamentos del Diseño Dinámico

    Representación
    En lugar de un arreglo de tamaño fijo, mantenemos una representación con **estado lógico** ($n$) y **almacenamiento físico adaptable** (capacidad). La clave es la separación entre el índice que percibe el usuario y la ubicación real en memoria, gestionada mediante una función de mapeo (ej. `index -> data[index]`).

    Correctitud
    La estructura se considera correcta si sus operaciones (`get`, `set`, `add`, `remove`) preservan los **invariantes de representación**. Estos incluyen asegurar que $0 \le i < n$, que siempre exista capacidad suficiente antes de una inserción y que, en estructuras complejas como `RootishArrayStack`, el mapeo por bloques sea consistente tras cada cambio.

    Costo Amortizado
    El diseño dinámico permite que operaciones costosas (como redimensionar y copiar $n$ elementos) ocurran con poca frecuencia. Al usar un factor de crecimiento geométrico, el costo de estas redistribuciones se distribuye entre muchas operaciones "baratas", resultando en un costo de **$O(1)$ amortizado** para insertar o eliminar al final.

    Uso de Espacio:
    A diferencia del arreglo estático, las estructuras dinámicas introducen **"espacio ocioso" (slack)**. El diseño busca un equilibrio: suficiente espacio libre para evitar redimensionamientos constantes, pero no tanto como para desperdiciar memoria innecesariamente.



2. Comparativa de Implementaciones en C++

A continuación se comparan tres variantes comunes bajo el estándar de eficiencia en C++:

| Estructura            | Mecanismo de Memoria                               | Particularidad en C++                                                                 | Eficiencia de Espacio             |
| :-------------------- | :------------------------------------------------- | :------------------------------------------------------------------------------------ | :-------------------------------- |
| **ArrayStack**        | Un solo bloque contiguo que se duplica/contrae.    | Implementación estándar con `new[]` / `delete[]`.                                     | $O(n)$ de desperdicio.            |
| **FastArrayStack**    | Igual al ArrayStack pero optimizado.               | Utiliza `std::copy` o `std::copy_backward` para mover bloques a nivel de bits.        | $O(n)$ de desperdicio.            |
| **RootishArrayStack** | Memoria dividida en bloques de tamaño $1, 2, 3...$ | El mapeo de índice a bloque usa la fórmula: $b = \lceil(-3 + \sqrt{9 + 8i})/2\rceil$. | **$O(\sqrt{n})$** de desperdicio. |
