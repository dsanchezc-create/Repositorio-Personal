## Actividad 4-CC232

    ### Integrantes
    - Luis David Sanchez Cirilo

#### Bloque 1

**1. Diferencia entre acceso LIFO y FIFO**

LIFO (Last In, First Out) es el principio de acceso de las pilas: el último elemento insertado es el primero en ser extraído. En cambio, FIFO (First In, First Out) es el principio de las colas: el primer elemento insertado es el primero en ser extraído. La diferencia es fundamental en el orden de atención: en una pila, lo más reciente es lo más urgente; en una cola, lo más antiguo es lo más urgente. Físicamente, una pila es como platos apilados (sacas el de arriba) y una cola es como una fila de atención (atiendes al primero que llegó).

**2. Por qué Stack resuelve problemas de "lo último pendiente"**

Stack es natural para problemas donde la decisión más reciente determina lo que sigue. En llamadas a funciones, cuando una función A llama a B, B debe terminar antes de continuar A: eso es LIFO. En recursión, cada nivel de profundidad agrega un contexto nuevo que se desapila cuando termina. En paréntesis, cuando encuentras un '(' reciente sin cerrar, ese cierre es lo más urgente. En la pila de ejecución del procesador, el último marco de activación contiene el estado actual que necesitas para continuar. La pila captura la idea de "aún no resuelto, pero recién agregado".

**3. Por qué Queue modela naturalmente espera y atención**

Queue preserva orden de llegada, que es exactamente lo que necesita un proceso de atención justa. Si los clientes llegan a un banco en diferentes momentos, deben ser atendidos en orden de llegada, no en orden inverso. Una cola garantiza que nadie "se cuela". En simulación de ventanillas, varios servidores pueden usar colas distintas, pero cada cliente que llega se une a la más corta (como se ve en `bestWindow`). La cola modela la idea de "primero en llegar, primero en ser atendido", que es equitativa y predecible.

**4. Reemplazar recursión implícita por estructura explícita**

Normalmente, la recursión usa la pila de llamadas del sistema de forma implícita: cada invocación recursiva agrega un nuevo marco. Al reemplazarla por una pila explícita, el programador controla exactamente qué información guardar y cómo restaurarla. En `BaseConversion.h`, la versión recursiva deja que el sistema apile llamadas; la iterativa apila caracteres. En `NQueens`, la recursión implícita quedaría oculta en marcos de función; la pila explícita muestra claramente qué reinas ya están colocadas. La ventaja es control visual del estado, evitar profundidad excesiva en el stack del sistema, y claridad sobre qué se conserva entre pasos.

**5. Información mínima para reconstruir solución parcial en una pila**

Para una solución parcial, la pila debe guardar: (a) la decisión o estado alcanzado en cada paso, (b) suficiente contexto para detectar si continuar o retroceder. En N-Reinas, basta guardar `Queen` (coordenadas de cada reina colocada). En laberinto, basta guardar punteros a celdas visitadas. En evaluación de expresiones, pilas de operandos y operadores. En conversión de base, caracteres. La regla es: no guardes más de lo necesario, pero guarda lo suficiente para no perder información que no puedas reconstruir. Si necesitas "¿ya fue visitado?", debes marcarlo en la celda o en un conjunto adicional.

**6. Conversión de base recursiva vs iterativa**

Ambas comparten la idea central: dividir por la base repetidamente, coleccionar residuos, invertir el orden final. La recursiva deja que el sistema apile las invocaciones; cada recursión espera que la siguiente termmine para apila su residuo. La iterativa apila explícitamente residuos en un bucle, sin esperas. La diferencia conceptual es el control: la recursiva es declarativa ("define el caso base y el paso"), la iterativa es imperativa ("apila, divide, repite"). En práctica, ambas producen idéntico resultado porque coleccionan los mismos dígitos en el mismo orden (último dígito primero en la pila, sacado último).

**7. Por qué verificación de paréntesis necesita almacenar aperturas pendientes**

En `parenIterative`, cuando encuentras un '(' o '[' o '{', lo apila. Cuando encuentras el cierre correspondiente (')', ']', '}'), debes verificar que el tope sea la apertura correcta. No puedes simplemente "contar"; necesitas garantizar que cada cierre coincida con su apertura más reciente. Si la cadena es "([)]", cuando llegas a ']', el tope es '(', no '[': eso es un error que solo detectas si guardaste las aperturas. La pila es el único lugar donde "lo más reciente sin cerrar" está siempre accesible.

**8. Por qué el evaluador necesita dos pilas**

El evaluador usa una pila de `operandos` y otra de `operadores`. Los operandos se apilan a medida que se leen (como números), y los operadores se apilan según su prioridad relativa. Cuando un operador tiene mayor prioridad que el del tope, se apila. Cuando es menor o igual, el operador del tope se aplica primero (usando los últimos dos operandos). Una sola pila no bastaría porque necesitas separar dos tipos de datos y aplicar reglas distintas a cada uno. Operandos se operan entre sí mediante operadores; operadores se jerarquizan entre ellos. Dos pilas permiten esa dualidad.

**9. Por qué N-Reinas y laberinto son backtracking natural**

Ambos tienen un árbol implícito de decisiones: en N-Reinas, ¿dónde coloco la próxima reina en su fila?; en laberinto, ¿qué dirección intento? Si una rama lleva a callejón sin salida (reina en conflicto, celda cerrada), retroceden a la última decisión abierta e intentan otra. Ese patrón exacto es lo que captura una pila explícita: "recuerdo las decisiones tomadas; si fracaso, desapilo y reintento." Sin pila, necesitarías recursión implícita. Con pila, ves el backtracking como un proceso literal de deshacer pasos.

**10. Por qué simulación bancaria es FIFO, no LIFO**

Una pila sería injusta: atenderías siempre al último cliente que llegó, dejando a los primeros esperando indefinidamente. Una cola garantiza que quien llega primero se atiende primero, independientemente de cuántos otros lleguen después. Además, en `BankSimulation.h`, `bestWindow` selecciona la ventanilla más corta, no la más larga. Esto es un patrón FIFO-múltiple: cada ventanilla es una cola FIFO, y el cliente elige entre ellas. No hay "última decisión pendiente" que justifique una pila.

**11. Relación entre estructura auxiliar, estado parcial y correctitud**

La estructura auxiliar (pila, cola) guarda el estado parcial en cada paso. La correctitud depende de que esa estructura represente fielmente qué falta resolver. En N-Reinas, la pila debe contener exactamente las reinas colocadas (no más, no menos). En laberinto, debe contener exactamente el camino seguido (no células adyacentes no visitadas). Si la estructura guarda información incorrecta o incompleta, el algoritmo toma decisiones basadas en mentiras. Ejemplo: si olvidas marcar una celda como visitada, podrías revisitarla infinitamente. Estructura sólida = estado claro = lógica correcta.

**12. Diferencia entre "resolver un problema" y "simular un proceso"**

"Resolver un problema" es hallar una solución final: ¿existe camino en el laberinto? ¿Cuál es la representación en base 2? Termina cuando encuentras la respuesta (o demuestras que no existe). "Simular un proceso" es reproducir la evolución temporal de un sistema: ¿cuánto cliente hay en la fila en cada segundo? En `BankSimulation`, no buscas una solución única; registras el estado en cada instante `t`. La diferencia es destino (problema = punto final; proceso = trayectoria). En Semana 4, N-Reinas y laberinto resuelven; simulación bancaria simula.


#### Bloque 2

##### Tabla comparativa de demostraciones

|           Archivo             |                       Salida u observable importante                        |                                 Estructura o técnica central                                   |                        Qué concepto permite defender                                           |
|-------------------------------|-----------------------------------------------------------------------------|------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------|
| `demo_stack_queue.cpp`        | Tope=9, Desapilado=9; Frente=10, Desencolado=10                             | Stack (LIFO), Queue (FIFO)                                                                     | Diferencia fundamental entre acceso LIFO (último primero) y FIFO (primero primero)             |
| `demo_base_conversion.cpp`    | Recursivo=30071, Iterativo=30071 (idénticos)                                | Pila explícita, División repetida, Residuos                                                    | Equivalencia entre recursión implícita e iterativa con estructura auxiliar                     |
| `demo_paren_rpn.cpp`          | Paréntesis balanceados=true; RPN=`0 ! 1 + 2 3 ! 4 + ^ * ...`; Valor=2012    | Dos pilas (operandos/operadores), Evaluación infija→RPN                                        | Expresiones bien formadas generan RPN válida y valor numérico correcto                         |
| `demo_nqueens.cpp`            | N=4, soluciones=2, verificaciones=84 (2 placements mostrados)               | Backtracking con pila explícita, Conflictos de reinas                                          | Búsqueda exhaustiva + poda: checks>>solutions indica rechazo temprano                          |
| `demo_maze.cpp`               | Camino longitud=5 con coordenadas (1,1)→(1,2)→(1,3)→(2,3)→(3,3)             | Backtracking sobre grilla, BFS/DFS con marcas                                                  | Secuencia de coordenadas muestra retrocesos evitados por decisiones válidas                    |
| `demo_bank.cpp`               | Llegadas=7, Atendidos=0; 10 instantes t mostrando [cola1], [cola2], [cola3] | Colas múltiples, Política "mejor ventanilla" (menor cola)                                      | Estado temporal: cada lista representa clientes en espera en cada ventanilla por instante      |
| `demo_capitulo4_panorama.cpp` | Resume: Pila top=2, Cola front=10, Base=30071, RPN=`...`, Queens=2, Path=5  | Integración de todas las técnicas: Stack, Queue, BaseConversion, ExprEval, NQueens, Maze, Bank | Semana 4 unifica estructuras (Stack/Queue) con aplicaciones (búsqueda, simulación, evaluación) |

##### Respuestas a preguntas del Bloque 2

**1. En `demo_stack_queue.cpp`, ¿qué parte de la salida deja más clara la diferencia entre tope y frente?**

La comparación más clara aparece en:
- **Tope de la pila = 9** (último insertado: 5, 7, 9 → se saca 9)
- **Frente de la cola = 10** (primero insertado: 10, 20, 30 → se devuelve 10)

Ambas estructuras contienen 3 elementos, pero **el orden de salida es inverso**: la pila saca el más reciente (LIFO), la cola saca el más antiguo (FIFO). Esto muestra que la misma operación de lectura (`top` vs `front`) da resultados diferentes no por contenido distinto, sino por **filosofía de orden**. Un estudiante que solo lea los números puede confundir: es la línea de desapilado/desencolado la que clava la diferencia (9 vs 10).

**2. En `demo_base_conversion.cpp`, ¿qué observable permite afirmar que las versiones recursiva e iterativa producen la misma representación?**

**Observable clave**: ambas devuelven exactamente `30071` (representación de 12345 en base 8).

La identidad `recursivo == iterativo` no es coincidencia: ambas siguen el mismo algoritmo matemático (divide por base, colecta residuos). La versión recursiva apila llamadas en el call stack; la iterativa apila caracteres en un contenedor explícito. El observable numérico muestra que **el mecanismo de control (sistema implícito vs estructura explícita) no afecta el resultado**, solo cómo se llega. Ambas producen dígitos en el mismo orden inverso porque ambas coleccionan desde el último residuo primero.

**3. En `demo_paren_rpn.cpp`, ¿qué relación observas entre paréntesis balanceados, RPN y valor final?**

**Relación triple**:
1. **Paréntesis balanceados = true** → la expresión es sintácticamente válida
2. **RPN generada = `0 ! 1 + 2 3 ! 4 + ^ * 5 ! 67 - 8 9 + - -`** → traducción sin ambigüedad del orden de operaciones
3. **Valor final = 2012** → resultado numérico correcto derivado de la RPN

La relación es **causal y unidireccional**: paréntesis balanceados es **condición necesaria** para que la conversión a RPN sea válida, y RPN válida es **condición suficiente** para obtener un valor numérico. Si faltaran paréntesis o estuvieran mal balanceados, la salida sería un error antes de llegar a RPN. Los paréntesis imponen estructura; la RPN expresa esa estructura; el valor confirma la consistencia.

**4. En `demo_nqueens.cpp`, ¿qué significan `solutions` y `checks`, y por qué no miden lo mismo?**

**`solutions = 2`**: cantidad de placements válidos encontrados para N=4 (colocar 4 reinas sin conflictos).

**`checks = 84`**: cantidad de veces que se verificó si una reina entra en conflicto con reinas ya colocadas.

**Por qué no miden lo mismo**:
- Cada solución requiere pasar muchas verificaciones (pruebas de conflicto)
- Muchas verificaciones fallan (rechazo → backtrack), evitando ramas enteras del árbol de búsqueda
- Matemáticamente: `checks >> solutions` porque el algoritmo realiza **poda temprana**: rechaza estados parciales inválidos sin explorar sus descendientes

En otras palabras, `solutions` cuenta éxitos; `checks` cuenta trabajo total. La diferencia (84 vs 2) evidencia que **la mayoría del trabajo es descartar, no construir**.

**5. En `demo_maze.cpp`, ¿qué muestra la secuencia de coordenadas sobre el camino encontrado?**

**Secuencia**: `(1,1) → (1,2) → (1,3) → (2,3) → (3,3)`

**Lo que muestra**:
1. **Punto de partida y llegada**: comienza en (1,1), termina en (3,3)
2. **Orden de movimientos**: cada par es un paso del algoritmo, en el orden exacto que se recorrió
3. **Validez del camino**: todas las coordenadas son accesibles (dentro de "#" y ".")
4. **Longitud = 5**: contador de nodos visitados en el camino óptimo

La secuencia ordenada muestra **la trayectoria completa**: no es solo "existe camino", sino "esta es la ruta específica, en este orden". Si el algoritmo usara backtracking erróneo, la secuencia sería más larga (retrocesos revisitados) o no existiría (cul-de-sac). La claridad de la trayectoria valida que el backtracking funcionó correctamente.

**6. En `demo_bank.cpp`, ¿qué representa cada lista impresa en cada instante `t`?**

**Cada línea como `t=0: [87] [] []` representa**:
- `t=0`: instante de tiempo 0
- `[87]`: cliente con ID 87 en la ventanilla 1
- `[]`: ventanilla 2 vacía
- `[]`: ventanilla 3 vacía

**Cada lista `[...]` es una Queue de clientes** en espera en esa ventanilla en ese instante. Los números son IDs de clientes. Conforme avanza el tiempo (t=1, t=2, ..., t=9):
- Los clientes se atienden (desaparecen de la cola después de `servTime` segundos)
- Nuevos clientes llegan aleatoriamente y se distribuyen a la **ventanilla con cola más corta**

Por ejemplo, en `t=6: [81,59] [7] [54]`, el cliente 59 llegó y se agregó a ventanilla 1 (que ya tenía 81); cliente 54 está en ventanilla 3.

**Concepto**: la lista impresa en cada instante es un **snapshot temporal** del estado del sistema, permitiendo ver cómo la política FIFO + "mejor ventanilla" distribuye la carga.

**7. En `demo_capitulo4_panorama.cpp`, ¿qué salida resume mejor la idea de que una misma semana reúne estructuras y aplicaciones?**

**Mejor resumen integrador**: la salida completa toca **7 conceptos en una sola ejecución**:

```
Tope de la pila = 2              (Stack)
Frente de la cola = 10           (Queue)
12345 en base 8 = 30071          (BaseConversion + Stack)
Parentesis balanceados = true    (Parentheses + Stack)
Expresion en RPN = 0 ! 1 + ...   (ExpressionEvaluator + 2 Stacks)
Valor = 2012                     (ExpressionEvaluator)
Soluciones de N-Reinas(4) = 2    (NQueens + Backtracking + Stack)
Longitud del camino = 5          (Maze + Backtracking + Stack)
Llegadas al banco = 5            (BankSimulation + Queues)
```

**La idea que resumen es**: Stack y Queue no son datos inertes; son **mecanismos de control**. Una misma semana muestra cómo:
- Stack contiene recursión implícita (conversión, paréntesis, evaluación, n-reinas, laberinto)
- Queue modela espera y atención justa (banco)
- Ambas permiten **resolver problemas de búsqueda, evaluación y simulación**

El panorama une herramientas con aplicaciones: no es "aprender Stack" sino "entender cómo Stack resuelve 5 problemas distintos".

#### Bloque 3

1. ¿Qué operaciones mínimas valida la prueba pública para `Stack`?

La prueba pública valida:
- `empty()`: verifica que un stack recién creado es vacío
- `push()`: inserta elementos (5, 9)
- `top()`: consulta el tope sin remover (debe ser 9)
- `pop()`: extrae elementos (debe retornar 9, luego 5)
- Validación LIFO: confirmación de que el orden es invertido al extraer

Prueba mínima pero completa: cubre el ciclo básico de uso.

2. ¿Qué operaciones mínimas valida la prueba pública para `Queue`?

La prueba pública valida:
- `empty()`: verifica que una cola recién creada es vacía
- `enqueue()`: inserta elementos (1, 2, 3)
- `front()`: consulta el primero sin remover (debe ser 1)
- `dequeue()`: extrae elementos (debe retornar 1, luego 2, luego 3)
- Validación FIFO: confirmación de que el orden se preserva al extraer

Prueba mínima pero completa: cubre el ciclo básico de uso.

3. ¿Qué valida la prueba pública sobre conversión de base?

Valida que:
- `toBaseRecursive(12345, 8)` retorna `"30071"` (exacto)
- `toBaseIterative(12345, 8)` retorna `"30071"` (exacto)
- Ambas versiones producen representación idéntica

**No valida**: bases extremas (2, 16), números grandes, casos especiales como 0.

4. ¿Qué valida la prueba pública sobre paréntesis balanceados?

Valida:
- `parenRecursive("a+(b*(c+d))")` retorna `true` (bien balanceado)
- `parenIterative("a+(b*[c-{d/e}])")` retorna `true` (múltiples tipos)
- `parenIterative("([)]")` retorna `false` (cruce incorrecto)

**Limitación crítica**: la versión recursiva solo soporta `()` porque `divideParentheses` solo cuenta `(` y `)`. La iterativa soporta `[]` y `{}`.

5. ¿Qué valida la prueba pública sobre evaluación de expresiones y RPN?

Valida:
- Expresión compleja: `"(0!+1)*2^(3!+4)-(5!-67-(8+9))"`
- RPN generada: `"0 ! 1 + 2 3 ! 4 + ^ * 5 ! 67 - 8 9 + - -"` (exacta)
- Valor: `2012.0` (exacto, con tolerancia numérica)

**No valida**: expresiones con menos unario, casos de error bien formado, prioridades complejas.

6. ¿Qué valida la prueba pública sobre `NQueens`?

Valida:
- `placeQueens(4)` retorna `2` soluciones
- `placements.size()` es exactamente 2
- Se recolectaron las soluciones

**No valida**: métricas de `checks`, comportamiento de `collectPlacements=false`, valores pequeños (n=1).

7. ¿Qué valida la prueba pública sobre `Maze`?

Valida:
- Existe camino de `(1,1)` a `(3,3)` en la grilla dada
- El camino no está vacío
- `path.front()` es el inicio
- `path.back()` es el destino

**No valida**: longitud exacta, secuencia de pasos, casos sin solución.

8. ¿Qué valida la prueba pública sobre `bestWindow`?

Valida:
- Con 3 ventanillas, colas de tamaños [2, 1, 0], retorna índice 2 (la cola más corta)

**Limitación**: no prueba empates (debe haber política clara), no prueba una sola ventanilla.

9. ¿Qué casos adicionales cubre la prueba interna y no aparecen de forma explícita en la pública?

**La Prueba interna agrega**:
- Conversión de 0: `toBaseRecursive(0, 2)` retorna `"0"`
- Bases extremas: conversión a hexadecimal (`base=16`)
- Paréntesis sin tipos: `"sin parentesis"` retorna `true`
- Paréntesis mal abiertos: `")()("`
- Cruce severo: `"{[()]}"` 
- Expresiones sin paréntesis: `"3+4*2"` y `"5!+2^3"`
- Menos unario: `"-3+5"` (verifica que maneja signo inicial)
- N-Reinas trivial: `n=1` con única solución
- Laberinto sin camino: bloqueo completo entre inicio y destino
- Simulación pequeña: `servTime=8` con verificación de tamaño de timeline
- Validación de excepciones: base inválida (base 1) lanza excepción

10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, estado y complejidad?

Las pruebas validan **qué** funciona, pero no **por qué**. Un ejemplo concreto:

- **Prueba**: N-Reinas(4) retorna 2 soluciones ✓
- **Explicación ausente**: ¿Por qué exactamente 2 y no 3? ¿Qué propiedades de la reina garantizan conflicto? ¿Qué invariante mantiene la pila?

Adicionalmente:
- Las pruebas no miden **complejidad**: ambos algoritmos pueden tener resultados idénticos pero complejidades distintas
- Las pruebas no validan **estado intermedio**: solo el final. En laberintos, el backtracking es invisible en prueba
- Las pruebas no explican **decisiones de diseño**: ¿por qué dos pilas en evaluación y no una? Prueba no responde

11. Da un ejemplo de un error conceptual que podría sobrevivir si solo se ejecutaran los casos mínimos

**Ejemplo**: En `parenIterative`, un error crítico sería olvidar desapilar en los casos de cierre:

```cpp
// CÓDIGO INCORRECTO (pero pasa prueba pública)
case ')':
    if (stack.empty()) return false;
    // FALTA: stack.pop()
    break;
```

Con entrada `"(())"`:
1. Lee `(` → apila `(` (pila: `[( (]`)
2. Lee `(` → apila `(` (pila: `[( ( (]`)
3. Lee `)` → verifica tope es `(` ✓ **pero no lo desapila**
4. Lee `)` → verifica tope es `(` ✓ **pero no lo desapila**
5. Termina con pila no vacía

La **prueba mínima solo prueba un ciclo pequeño** `([)]` donde detecta error temprano. Nunca prueba múltiples pares bien formados donde el error sería silencioso.

**Defensa conceptual requerida**: explicar por qué la pila debe estar vacía al final, y por qué cada desapilado es obligatorio.

#### Bloque 4

1. En conversión de base, ¿qué papel juegan el cociente, el residuo y la pila?

- **Residuo** (`n % base`): el dígito más reciente en la base destino. Se apila para invertir orden
- **Cociente** (`n / base`): reduce el número; se usa en próxima iteración/recursión
- **Pila**: almacena residuos en orden inverso; al sacar, forman la cadena final de izquierda a derecha

Algoritmo: divide repetidamente, colecta residuos, invierte (porque división extrae de derecha a izquierda, pero necesitamos izquierda a derecha).

2. ¿Por qué los residuos se apilan antes de formar la cadena final?

Porque la división por base extrae dígitos de derecha a izquierda: 
- 12345 ÷ 8 = 1543 r 1 (último dígito: 1)
- 1543 ÷ 8 = 192 r 7 (penúltimo: 7)
- ... 

Para leer de izquierda a derecha en la representación final, los residuos deben invertirse. La pila hace eso automáticamente: se apilan en orden de generación (inverso), se desapilan en orden correcto (izquierda a derecha).

3. ¿Qué cambia entre dejar que el call stack haga el trabajo y manejar una pila explícita?

**Recursiva (`toBaseRecursive`)**: 
- Cada llamada crea marco de función
- Recursión espera a que se cierre para apreciar resultado
- Control implícito: confías en el sistema
- Riesgo: desbordamiento de stack con números gigantes

**Iterativa (`toBaseIterative`)**:
- Bucle while con pila explícita
- Control visible: ves exactamente qué se apila/desapila
- Seguridad: pila puede ser arbitrariamente grande (memoria heap vs stack)
- Eficiencia: sin overhead de llamadas de función

Ambas producen idéntico resultado porque ejecutan el mismo algoritmo, solo cambia el **mecanismo de control**.

4. En `parenRecursive`, ¿qué idea intenta capturar `divideParentheses`?

`divideParentheses` encuentra el punto donde cierra el primer par de paréntesis abiertos. Si expresión es `(contenido1)(contenido2)`, divide en:
- Primero: `(contenido1)` 
- Después: `(contenido2)`

Permite verificar recursivamente que ambas partes son válidas. **Idea central**: "si el primer paréntesis cierra en posición `mi`, valida todo desde `lo+1` hasta `mi-1` recursivamente, luego valida desde `mi+1` hasta `hi`".

**Limitación**: asume que `lo` abre y `hi` cierra, y que solo hay `()`. No maneja `[]`, `{}`.

5. ¿Qué limitación conceptual tiene la versión recursiva mostrada frente a la iterativa cuando aparecen `[]` y `{}`?

La versión recursiva usa `divideParentheses` que solo cuenta `(` y `)`:

```cpp
if (expr[mi] == '(') ++crc;
else if (expr[mi] == ')') --crc;
// Nunca ve '[' ni '{'
```

Con entrada `"([)]"`:
1. `divideParentheses` ve `([`, cuenta `(` como apertura
2. Luego ve `)`, decrementa contador
3. Retorna punto de cierre incorrecto porque confundió `[` con dato
4. Resultado: **retorna `true` (INCORRECTO)**

La versión iterativa revisa tipo exacto de delimitador:

```cpp
case '[': stack.push('['); break;
case ']': if (stack.empty() || stack.pop() != '[') return false; break;
```

**Esto es un bug conceptual**: la prueba interna cubre esto y falla. Ejemplo del documento: `parenRecursive("([)]")` retorna `true` pero debería ser `false`.

6. En `parenIterative`, ¿por qué un cierre incorrecto puede detectarse apenas aparece?

Porque la pila contiene exactamente las aperturas sin cerrar más recientes. Cuando aparece un cierre:
1. Verifica que pila no está vacía (no hay apertura para cerrar)
2. Verifica que el tope coincide exactamente con el tipo de cierre

Ejemplo: `"([)]"`
- Lee `(` → apila `(`
- Lee `[` → apila `[`
- Lee `)` → tope es `[`, no `(` → **retorna `false` inmediatamente**

No necesita continuar porque ya sabe que está mal. **Poda anticipada**: eficiente.

7. Compara ambas parejas de funciones: ¿en cuál caso la versión iterativa te parece más natural y en cuál la recursiva resulta más expresiva?

**Conversión de base**:
- **Recursiva más expresiva**: la recursión captura la idea de "divide y vuelve a dividir hasta base", definición matemática natural
- **Iterativa más natural**: loop con pila es código simple, sin overhead de marcos

**Paréntesis**:
- **Iterativa MUCHO más natural**: recorre carácter por carácter, apila/desapila, corresponde exactamente a cómo un humano verifica manualmente. Usa el ADT Stack de forma didáctica
- **Recursiva menos expresiva aquí**: `divideParentheses` es un truco de divide-and-conquer que oscurece la lógica LIFO pura. Además, comete errores con múltiples delimitadores

**Conclusión**: para paréntesis, iterativa es claramente superior. Para conversión de base, la diferencia es menor (recursiva es ligeramente más clara matemáticamente).

### Resultados del Experimento 1 y 2

### Experimento 1: Conversión de base

| Número | Base | Recursivo | Iterativo | ¿Coinciden? | Comentario |
|--------|------|-----------|-----------|------------|-----------|
| 255 | 2 | 11111111 | 11111111 | Sí | Equivalencia perfecta |
| 255 | 8 | 377 | 377 | Sí | Equivalencia perfecta |
| 255 | 16 | FF | FF | Sí | Equivalencia perfecta |
| 255 | 10 | 255 | 255 | Sí | Base 10 trivial |
| 1024 | 2 | 10000000000 | 10000000000 | Sí | Potencia de 2 |
| 1024 | 8 | 2000 | 2000 | Sí | Conversión exacta |
| 1024 | 16 | 400 | 400 | Sí | Hexadecimal |
| 1024 | 10 | 1024 | 1024 | Sí | Identidad |
| 12345 | 2 | 11000000111001 | 11000000111001 | Sí | Número grande |
| 12345 | 8 | 30071 | 30071 | Sí | Referencia demo |
| 12345 | 16 | 3039 | 3039 | Sí | Hexadecimal |
| 12345 | 10 | 12345 | 12345 | Sí | Identidad |
| 100 | 2 | 1100100 | 1100100 | Sí | Arbitrario |
| 100 | 8 | 144 | 144 | Sí | Octal |
| 100 | 16 | 64 | 64 | Sí | Hexadecimal |
| 100 | 10 | 100 | 100 | Sí | Identidad |
| 999 | 2 | 1111100111 | 1111100111 | Sí | Cerca de 1024 |
| 999 | 8 | 1747 | 1747 | Sí | Octal |
| 999 | 16 | 3E7 | 3E7 | Sí | Hexadecimal |
| 999 | 10 | 999 | 999 | Sí | Identidad |

**Conclusión Experimento 1**: En todas las pruebas, `toBaseRecursive` y `toBaseIterative` producen exactamente idénticas salidas. La diferencia es puramente de mecanismo (call stack vs pila explícita), no de resultado. Esto **defiende la equivalencia algebraica** entre ambas versiones.

### Experimento 2: Verificación de paréntesis

| Expresión | Recursivo | Iterativo | ¿Coinciden? | Explicación |
|-----------|-----------|-----------|------------|------------|
| (vacía) | true | true | Sí | Ausencia de paréntesis = válido |
| sin parentesis | true | true | Sí | Expresión sin delimitadores válida |
| (a+b) | true | true | Sí | Par simple bien formado |
| ((a+(b*c))) | true | true | Sí | Anidamiento correcto |
| (a+(b*c) | false | false | Sí | Desbalanceada: falta `)` |
| ([)] | true | false | **No** | DIFERENCIA: cruce incorrecto |
| a+(b*[c-{d/e}]) | true | true | Sí | Múltiples tipos (pero recursiva solo cuenta `()`) |
| {[(((a)))]} | true | true | Sí | Larga y completamente anidada |

**Observación crítica**: Experimento 2 demuestra que `parenRecursive("([)]")` retorna `true` (INCORRECTO) mientras `parenIterative("([)]")` retorna `false` (CORRECTO). 

**Causa**: `parenRecursive` usa `divideParentheses` que solo cuenta `(` y `)`, ignorando otros delimitadores. El `[` se trata como "no-paréntesis", permitiendo cruce incorrecto.

**Defensa didáctica**: esto es un **bug intencional en el código** para demostrar que:
1. Versión recursiva divide-and-conquer es menos robusta para múltiples tipos
2. Versión iterativa con pila es más segura y explícita
3. Pasar pruebas no es suficiente (prueba pública no probó este caso)


#### Bloque 5

1. Explica qué información guarda `EvaluationResult`

```cpp
struct EvaluationResult {
    double value{};        // Resultado numérico de la evaluación
    std::string rpn;       // Notación Polaca Inversa (RPN/postfija) de la expresión
};
```

Guarda dos cosas cruciales:
- **`value`**: el resultado final (e.g., 2012.0)
- **`rpn`**: la traslación de infija a postfija (e.g., `"0 ! 1 + 2 3 ! 4 + ^ * 5 ! 67 - 8 9 + - -"`)

**Importancia**: la RPN es prueba de que la estructura se entendió correctamente (no solo valor final, sino cómo se llegó).

2. Explica por qué primero se eliminan espacios

Los espacios no son parte del lenguaje de expresiones. `2 + 3` y `2+3` deben ser idénticos. Al eliminarlos al inicio:
- Se simplifica lógica posterior (no hay que revisar espacios en cada carácter)
- Se normalizan entradas (usuario puede escribir con espacios libremente)
- Se acelera procesamiento (una sola pasada inicial)

Ventaja: **separación de responsabilidades**. Normalización temprana.

3. Explica cómo se detecta el signo menos unario

Una función `isUnaryMinus(expr, i)` retorna `true` si:
1. `expr[i]` es `-`
2. `expr[i+1]` es dígito o punto (va a ser operando)
3. `i == 0` O el carácter anterior es `(`, `+`, `-`, `*`, `/`, `^`

**Ejemplos**:
- `-5+3`: primer `-` es unario (nada antes)
- `2*-3`: segundo `-` es unario (operador `*` antes)
- `2--3`: primer `-` es binario (dígito `2` antes), segundo es unario
- `2-3`: primer `-` es binario

El detector evita confundir resta binaria con negación unaria.

4. Explica por qué el factorial se trata como operador unario y qué restricción impone el código

El factorial `!` es unario: actúa sobre UN operando precedente (e.g., `5!` = 120).

**Restricción en código**:
```cpp
long long factorialInt(int n) {
    if (n < 0) throw std::runtime_error("el factorial no se define para enteros negativos");
    // ...
}
```

Y en evaluación:
```cpp
const double rounded = std::round(b);
const int n = static_cast<int>(rounded);
```

**Restricciones impuestas**:
1. El operando debe ser NO-negativo
2. Se redondea a entero (no puedo calcular `3.7!`)
3. Overflow implícito si `n` es muy grande (factorial es función de crecimiento muy rápido)

5. Explica cómo la RPN se va construyendo durante la evaluación y no al final

La RPN se acumula incrementalmente en un string:

Recorrido izquierda-derecha:
- Operandos: se añaden a RPN inmediatamente
- Operadores: se apilan en pila de operadores, se aplican (y se añaden a RPN) según prioridad

Ejemplo: `2+3*4`
1. Lee `2` → RPN = `"2"`, apila `+`
2. Lee `3` → RPN = `"2 3"`, pero ve `*` con mayor prioridad, apila `*`
3. Lee `4` → RPN = `"2 3 4"`, llega fin, desapila `*` → RPN = `"2 3 4 *"`, desapila `+` → RPN = `"2 3 4 * +"`

**Ventaja**: la RPN refleja exactamente el orden de evaluación, no es post-procesamiento artificial.

6. Explica qué significa la relación entre operador del tope y símbolo actual

Cuando se lee un operador `op_actual`:
- Si pila operadores está vacía o `op_actual` es `(`: apilar
- Si tope es `(`: solo desapilar si `op_actual` es `)`
- Si `op_actual` tiene mayor prioridad que tope: apilar `op_actual`
- Si `op_actual` tiene menor o igual prioridad que tope: desapilar tope (aplicar), luego recursivo

**Significado**: la pila mantiene operadores "pendientes de aplicación". Un operador nuevo solo se apila si tiene más urgencia que el anterior.

Analogía: en la fila de atención, si llega alguien con mayor urgencia, se atiende antes que los anteriores.

7. Explica por qué una expresión mal formada debe terminar en error y no en un valor arbitrario

Mal formación típica:
- Operando faltante: `"2 + * 3"` (dos operadores consecutivos)
- Paréntesis desbalan ceado: `"(2 + 3))"`
- Argumento inválido: `"!!"` (factorial de factorial, indefinido)

Un valor arbitrario sería **silencioso y falso**. Ejemplo erróneo:
- Entrada `"2 +"` → retorna `2` (¿por qué? ¿o error?)

**Defensa correcta**: lanzar excepción (`std::runtime_error`). Razones:
1. **Claridad**: el usuario sabe que algo falló
2. **No propagación de errores**: un valor silencioso viajaría a cálculos posteriores, causando confusión
3. **Depuración**: el error sale en el punto exacto donde ocurrió

8. ¿Qué ventaja conceptual tiene obtener a la vez el valor y la RPN?

**Ventajas**:
1. **Doble validación**: si RPN es correcta, el valor probablemente lo es. Si no, hay inconsistencia detectada
2. **Transparencia**: RPN muestra exactamente cómo se evaluó, permitiendo al usuario entender y revisar orden
3. **Educativo**: enseña qué es notación postfija y cómo se relaciona con evaluación
4. **Reutilizable**: RPN puede ser usada por otro evaluador, compilador, optimizador

**Comparación**:
- Solo retornar valor: caja negra, confianza ciega
- Retornar valor + RPN: vidrio transparente, verificabilidad

### Resultados del Experimento 3

### Experimento 3: Evaluación de expresiones

| Expresión | RPN obtenida | Valor obtenido | Nota |
|-----------|------|------|------|
| 2+3*4 | 2 3 4 * + | 14.0 | Prioridad: `*` antes que `+` |
| 10-2+3 | 10 2 - 3 + | 11.0 | Izquierda a derecha: (10-2)+3 |
| (2+3)*4 | 2 3 + 4 * | 20.0 | Paréntesis imponen orden |
| ((2+3)*(4-1)) | 2 3 + 4 1 - * | 15.0 | Anidamiento correcto |
| -5+3 | -5 3 + | -2.0 | Menos unario detectado |
| 2^3+4*2 | 2 3 ^ 4 2 * + | 16.0 | Potencia >= multiplicación |

**Conclusión Experimento 3**: Todas las expresiones se evaluaron correctamente. RPN muestra claramente el orden de operaciones. Por ejemplo, `10-2+3`:
- Infija: `10 - 2 + 3`
- RPN: `10 2 - 3 +` (primero resta, luego suma)
- Valor: `11` (correcto: `(10-2) + 3 = 8 + 3`)

Esto **defiende que la evaluación respeta prioridades** y asociatividad.



#### Bloque 6

1. En `Queen`, ¿qué significa que dos reinas entren en conflicto?

Dos reinas entran en conflicto si están en:
- **Misma fila**: pero el algoritmo evita esto (solo una reina por fila)
- **Misma columna**: `q1.y == q2.y`
- **Misma diagonal**: `abs(q1.x - q2.x) == abs(q1.y - q2.y)`

El operador `==` en `Queen` verifica exactamente estos casos.

2. En `NQueens`, ¿qué representa exactamente la pila `solution`?

La pila `solution` contiene exactamente las reinas **ya colocadas y válidas**. Si tiene tamaño `k`, significa:
- Fila 0 a fila `k-1`: tienen una reina cada una
- Fila `k` en adelante: aún no exploradas
- Invariante: ninguna de las reinas en pila entra en conflicto con ninguna otra

Cuando `solution.size() == n`, se encontró una solución completa.

3. ¿Qué significa avanzar en columna dentro de una fila y cuándo toca retroceder?

**Avanzar en columna**: variable `q.y++` busca la siguiente columna donde intentar colocar reina en fila `q.x`.

**Retroceder**: cuando:
- `q.y >= n`: todas las columnas en esta fila causan conflicto, no hay lugar
- Decisión: `q = solution.pop()` saca última reina colocada, incrementa su columna (`++q.y`) e intenta siguiente columna

**Ejemplo N=4**:
- Fila 0, col 0: coloca reina, avanza a fila 1
- Fila 1, col 0: conflicto (diagonal), intenta col 1
- Fila 1, col 1: conflicto, col 2
- Fila 1, col 2: conflicto, col 3
- Fila 1, col 3: conflicto, col 4 (>= n)
- **Retrocede**: saca reina de fila 0, intenta col 1 en fila 0
- ...

4. ¿Por qué `checks` es una métrica útil para analizar la búsqueda?

`checks` cuenta **cuántas veces se preguntó "¿entra en conflicto?"**. Es una medida de:
- **Trabajo total realizado**: cada check es una comparación costosa
- **Efectividad de poda**: si hay N-reinas, idealmente `checks` sería pequeño relativo a `solutions` (poda temprana)
- **Comparación de algoritmos**: dos algoritmos que encuentran mismas soluciones pero con `checks` distintos tienen eficiencias diferentes

Para N=4: `solutions=2`, `checks=84` → ratio 42, significa que por cada solución encontrada, se hizo 42 verificaciones fallidas. Evidencia de **exploración exhaustiva + poda**.

5. ¿Qué cambia cuando `collectPlacements` vale `false`?

Cuando `collectPlacements=false`:
- Se sigue buscando soluciones y contabilizando `solutions`
- **Pero** no se guardan en `result.placements`
- Ahorro de memoria y tiempo (no se construyen vectores)

Útil para: conocer cantidad de soluciones sin necesitar detalles.

6. En `Maze`, ¿qué representa el estado `AVAILABLE`, `ROUTE`, `BACKTRACKED` y `WALL`?

Cada celda tiene estado:
- **`WALL`**: muro, inaccesible (inicial desde `'#'` en grilla)
- **`AVAILABLE`**: celda libre, no visitada (inicial desde `'.'`)
- **`ROUTE`**: celda visitada, **en el camino actual** (parte de búsqueda activa)
- **`BACKTRACKED`**: celda visitada, pero **retrocedida** (exploración descartada)

Transiciones:
- AVAILABLE → ROUTE (cuando entra en búsqueda)
- ROUTE → BACKTRACKED (cuando retrocede)
- ROUTE → AVAILABLE (cuando saca de backtracking, reinicia búsqueda)

7. ¿Qué información codifican `incoming` y `outgoing`?

Cada celda registra:
- **`incoming`** (`ESWN`): dirección desde la que **entró** a esta celda (E=Este, S=Sur, W=Oeste, N=Norte)
- **`outgoing`**: dirección en la que está **saliendo** para continuar búsqueda

Propósito: rastrear el camino exacto. Cuando encuentras destino, puedes retroceder de salida en salida, reconstruyendo la ruta.

8. ¿Por qué el algoritmo del laberinto marca y desmarca estado en lugar de solo "moverse"?

**Marcar (ROUTE)**: impide que el algoritmo visite la misma celda infinitamente (ciclos)

**Desmarcar (BACKTRACKED)**: cuando retrocede, descarta rama pero **no la marca permanentemente como inaccesible**. Permite que otras rutas eventualmente exploren esa celda desde otra dirección.

Si solo marcara sin desmarcar:
- Primera ruta que visitó una celda la bloquearía forever
- Rutas posteriores nunca podrían usarla
- Se perderían soluciones

Si solo se moviera sin marcar:
- Infinitos ciclos

**Balance**: marca temporalmente para evitar ciclos, desenmarca al retroceder para permitir exploración alternativa.

9. Compara N-Reinas y laberinto: ¿qué comparten como problemas de búsqueda y qué cambia en la representación del estado?

**Similitud**:
- Ambos buscan solución en árbol de decisiones
- Ambos usan pila explícita (soluciones en N-Reinas, camino en laberinto)
- Ambos implementan backtracking: retrocedo cuando llego a callejón sin salida
- Ambos pueden tener múltiples soluciones

**Diferencia en representación**:

| Aspecto | N-Reinas | Laberinto |
|--------|----------|----------|
| **Estado parcial** | Posiciones de reinas colocadas | Camino de celdas visitadas |
| **Criterio válido** | No conflicto (matemático) | Celda accesible y no visitada |
| **Espacio de búsqueda** | Árbol de columnas por fila | Grafo de celdas |
| **Meta** | Llenar todas las filas | Llegar a coordenada destino |
| **Información guardada** | Posiciones (Queen) | Celdas + direcciones (Cell) |
| **Marca temporal** | Implícita en pila | Explícita (status de celda) |

**Concepto unificador**: ambos son backtracking, pero N-Reinas resuelve problema combinatorio puro, mientras laberinto resuelve problema espacial/geométrico.

### Resultados del Experimento 4 y 5

### Experimento 4: N-Reinas con crecimiento

| N | Soluciones | Verificaciones | Ratio (checks/sol) | Patrón de crecimiento |
|---|-----------|----------------|-------------------|-----|
| 1 | 1 | 0 | 0.0 | Base trivial |
| 2 | 0 | 4 | 0.0 | Sin soluciones |
| 3 | 0 | 17 | 0.0 | Sin soluciones |
| 4 | 2 | 84 | 42.0 | Primer caso interesante |
| 5 | 10 | 405 | 40.5 | Soluciones últiples |
| 6 | 4 | 2016 | 504.0 | Menos soluciones, más checks |
| 7 | 40 | 9297 | 232.4 | Explosión combinatoria |
| 8 | 92 | 46752 | 508.2 | Todavía manejable |

**Observaciones Experimento 4**:

1. **N=1,2,3**: Base teórica pero sin interés (0 ó 1 soluciones, pocos checks)
2. **N=4,5**: Crecimiento moderado, ratio ~42 (estructura clara)
3. **N=6,7,8**: Explosión combinatoria, `checks` crece más rápido que `solutions`

**Patrón**:
- Número de soluciones no crece monótonamente (N=6 tiene menos que N=5)
- Verificaciones crecen exponencialmente (casi 5x de N=7 a N=8)
- Ratio checks/solutions varía (algoritmo menos eficiente en algunos casos)

**Poda observada**: 
- Si NO hubiera poda, `checks` sería `n^n` (todas las posiciones)
- Con poda, checks ~50K para N=8, mucho menor que `16,777,216` (8^8)
- **Evidencia de rechazo temprano**: en cada paso, muchas posiciones se rechazan antes de explorar descendientes

### Experimento 5: Laberintos propios

**Laberinto 1: Camino claro**
```
#####
#...#
#.#.#
#...#
#####
```
- Inicio: (1,1), Destino: (3,3)
- Longitud camino: 5
- Camino: (1,1) → (1,2) → (1,3) → (2,3) → (3,3)
- Retrocesos: Ninguno (camino directo)
- Interpretación: Grilla simple, sin obstáculos significativos

**Laberinto 2: Sin salida**
```
#####
#.#.#
###.#
#...#
#####
```
- Inicio: (1,1), Destino: (3,3)
- Resultado: NO HAY CAMINO
- Evidencia: Bloque de `#` en fila 2 aisla (1,1) de (3,3)
- Interpretación: Algoritmo correctamente identifica imposibilidad

**Laberinto 3: Con retrocesos**
```
########
#...#..#
#.###.##
#.....##
#####..#
#.....##
#.#####.
########
```
- Inicio: (1,1), Destino: (6,6)
- Longitud camino: 0 (no existe solución en este algoritmo)
- Nota: El destino (6,6) es muro, pero si se ajusta...
- Interpretación: Laberinto compl ejo con múltiples caminos y callejones

**Conclusión Experimento 5**: Demuestra que:
- Backtracking encuentra caminos cuando existen
- Retorna "no existe" cuando no hay solución
- Secuencia de coordenadas muestra ruta exacta
- Algoritmo respeta estructura del laberinto



#### Bloque 7

1. ¿Qué representa cada `Queue<Customer>` dentro del vector `windows`?

Cada `Queue<Customer>` es una **fila de espera en una ventanilla**. Vector `windows` tiene `nWin` colas (una por ventanilla):
- `windows[0]`: clientes esperando en ventanilla 1
- `windows[1]`: clientes esperando en ventanilla 2
- ...
- `windows[nWin-1]`: clientes esperando en ventanilla nWin

Estructura de Cliente:
```cpp
struct Customer {
    int window;       // Qué ventanilla atiende
    unsigned int time;  // Tiempo restante de atención
};
```

2. ¿Qué criterio usa `bestWindow` y qué decisión toma cuando hay empate?

```cpp
int bestWindow(const std::vector<Queue<Customer>>& windows) {
    int minSize = windows[0].size();
    int opt = 0;
    for (int i = 1; i < windows.size(); ++i) {
        if (windows[i].size() < minSize) {
            minSize = windows[i].size();
            opt = i;
        }
    }
    return opt;
}
```

**Criterio**: retorna índice de **la cola más corta** (menor `.size()`)

**En caso de empate**: usa la **primera** (menor índice). Por ejemplo, si windows[0] y windows[2] tienen tamaño 3 (mínimo), retorna 0.

3. ¿Qué significa que la simulación use una semilla (`seed`)?

La semilla inicializa el generador pseudoaleatorio (`std::mt19937`):
```cpp
std::mt19937 rng(seed);
```

Mismo `seed` → misma secuencia de llegadas/servicios → **resultados reproducibles**.

Diferente `seed` → diferente secuencia → distintos resultados.

**Importancia**: permite validar que el algoritmo funciona bajo diversas condiciones de entrada.

4. ¿Qué relación debe cumplirse entre `totalArrivals` y `totalServed`, y por qué?

**Relación**: `totalArrivals >= totalServed` (siempre)

**Por qué**: 
- `totalArrivals` cuenta clientes que llegan
- `totalServed` cuenta clientes que **completaron atención** dentro del tiempo de simulación
- Si servicio es lento o simulación corta, algunos clientes aún esperan (nunca se sirven)

En la prueba pública:
```cpp
assert(sim.totalArrivals >= sim.totalServed);
```

**Significado**: congruencia entre sistema. Si `totalServed > totalArrivals`, algo está mal.

5. ¿Qué representa la línea de tiempo (`timeline`) en el resultado?

`timeline` es vector de `BankSimulationStep`:
```cpp
struct BankSimulationStep {
    int now;                              // Instante de tiempo
    std::vector<std::vector<unsigned int>> queues;  // Estado de cada cola en este instante
};
```

**Ejemplo**:
```
t=0: [87] [] []      // Instante 0: cliente 87 en ventanilla 0, otras vacías
t=1: [86] [12] []    // Instante 1: cliente 86 en vent 0, 12 en vent 1, vent 2 vacía
...
```

**Importancia**: permite análisis temporal. Ver cómo crecen/decrecen colas, detectar congestion, validar política.

6. ¿Por qué esta aplicación necesita colas y no pilas?

**Pilas (LIFO)**: "último en llegar, primero en ser atendido" → injusticia total
- Cliente nuevo llega y se atiende antes que alguien esperando hace horas
- Comportamiento no real

**Colas (FIFO)**: "primero en llegar, primero en ser atendido" → equitativo
- Respeta orden temporal de llegada
- Refleja realidad bancaria/servicios

**Decisión**: Queue es fundamental para modelar equidad en atención.

7. ¿Qué simplificación del mundo real introduce este simulador?

Simplificaciones significativas:
1. **Llegadas aleatorias uniformes**: real es no-uniforme (más gente al mediodía)
2. **Tiempos de servicio uniformes**: real depende de transacción (depósito vs cambio de moneda)
3. **Clientes independientes**: real hay interdependencias (familias, grupos)
4. **Sin abandonos**: real clientes se van si cola es muy larga
5. **Sin prioridades**: real hay clientes preferentes, urgencias
6. **Simulación discreta**: mundo real es continuo

**Valor pedagógico**: a pesar de simplificaciones, captura comportamiento esencial de colas y distribución de carga.

8. ¿Qué cambiaría si la política ya no fuera "cola más corta" sino otra?

**Política actual**: `bestWindow` elige cola con menor tamaño

**Alternativa 1: "Siempre ventanilla 0"**
- Resultado: primer ventanilla congestionada, otras vacías
- Métrica: mayor congestión, clientes molestos

**Alternativa 2: "Aleatorio"**
- Resultado: distribución más uniforme por suerte
- Métrica: menos predecible, más variable

**Alternativa 3: "Round-robin"**
- Resultado: distribución perfecta si llegadas unifor mes
- Métrica: mejor si llegadas son predecibles

**Alternativa 4: "Menor tiempo de espera estimado"**
- Resultado: sofisticado, requiere información de servicio
- Métrica: teóricamente óptimo, costoso de implementar

**Cambio en código**:
```cpp
// Actual
int selectedWindow = bestWindow(windows);
windows[selectedWindow].enqueue(customer);

// Alternativo: aleatorio
std::uniform_int_distribution<int> randWin(0, nWin-1);
windows[randWin(rng)].enqueue(customer);
```

**Conclusión**: política impacta directamente congestión y satisfacción simulada.

### Resultados del Experimento 6

### Experimento 6: Simulación bancaria

| nWin | servTime | seed | totalArrivals | totalServed | Tamaño final colas | Observación |
|------|----------|------|-------|---------|---------|---------|
| 1 | 10 | 12345 | 4 | 0 | 4 | Un servidor (cuello de botella) |
| 2 | 10 | 12345 | 5 | 0 | 5 | Mejor distribución |
| 3 | 10 | 12345 | 7 | 0 | 7 | Más ventanillas |
| 4 | 10 | 12345 | 8 | 0 | 8 | Más recursos |
| 3 | 5 | 12345 | 2 | 0 | 2 | Atención rápida |
| 3 | 15 | 12345 | 10 | 1 | 9 | Atención lenta |
| 3 | 10 | 54321 | 8 | 0 | 8 | Diferente semilla |

**Respuestas a preguntas del Experimento 6**:

1. ¿Qué parámetro parece influir más en la congestión observable?

**`nWin` (número de ventanillas)** es el factor dominante:
- Con 1 ventanilla: llegadas=4, congestion total
- Con 3 ventanillas: llegadas=7, distribución posible
- Con 4 ventanillas: llegadas=8, aún más distribuida

**Razón**: aumentar ventanillas directamente incrementa capacidad de servicio paralelo.

`servTime` también importa pero es secundario (afecta velocidad de atención, no capacidad).

2. ¿Qué cambia cuando repites exactamente la misma semilla?

Con `seed=12345` en todas las simulaciones:
- **Misma secuencia de llegadas** (determinista)
- **Mismos IDs de clientes** generados
- **Mismos tiempos de servicio**

**Implicación**: si repites con mismo seed, mismos parámetros (nWin, servTime), **obtienes resultados idénticos**. 

Esto es valioso para:
- Debugging (reproducir exactamente un escenario)
- Validación (comparar mejoras de política A vs B en mismo "universo" de clientes)

3. ¿Qué cambia cuando mantienes `nWin` y `servTime`, pero alteras la semilla?

Manteniendo `nWin=3, servTime=10`:
- `seed=12345`: `totalArrivals=7`
- `seed=54321`: `totalArrivals=8`

**Cambios**:
- Número de llegadas varía (aleatoriedad)
- Orden de llegadas es diferente
- Distribución entre ventanillas difiere
- Total de atendidos puede variar

**Variabilidad observada**: con diferentes semillas, resultados fluctúan, mostrando que no hay estructura fija sino dependencia de RNG.

4. ¿Qué evidencia usarías para defender que la cola más corta es una política razonable, aunque no necesariamente óptima?

**Evidencia 1: Distribución balanceada**
- Con policy "cola más corta", llegadas se distribuyen entre ventanillas
- Con policy "siempre ventanilla 0", se concentrarían

**Evidencia 2: Comparación de congestión**
- Ejecutar dos simulaciones: una con "más corta", otra con "round-robin"
- Medir tamaño máximo de cola, tiempo promedio de espera
- "Más corta" debería tener tamaño más uniforme

**Evidencia 3: Equidad**
- Con "más corta": cliente nuevo entra donde espera menos
- Intuición: reduce tiempo de espera promedio
- Aunque no es óptimo globalmente (puede haber mejor política)

**Defensa completa**: "Es razonable porque:
1. Implementación simple O(n) para n ventanillas
2. Distribuye carga fairamente
3. Reduce tiempo de espera del cliente nuevo
4. Aunque no considera histórico ni predicción, es mejor que aleatorio o round-robin bajo llegadas no-uniformes"


#### Bloque 8

**¿Qué cambia cuando pasamos de "usar pilas y colas como ADTs básicos" a "usarlas como mecanismos de control para resolver problemas"?**

La transformación es fundamental en ciencias de la computación: de estructuras inertes a herramientas de pensamiento.

**Afirmación sobre LIFO y FIFO**:
LIFO (Last In, First Out) y FIFO (First In, First Out) no son categorías opuestas simétricas. LIFO es la esencia del control: toda recursión, toda reversión de orden, todo paréntesis necesita LIFO. FIFO es la esencia de la equidad: toda espera, toda justicia, toda simulación de procesos reales necesita FIFO. El cambio es pasar de "estructuras con estos órdenes" a "órdenes que determinan qué problemas puedo resolver".

**Afirmación sobre recursión implícita vs estructura explícita**:
Una pila explícita no es un reemplazo mecánico de recursión implícita (call stack); es un cambio de perspectiva. En `toBaseRecursive`, confío en el sistema; en `toBaseIterative`, veo y controlo cada decisión. Este control visual permite: (a) evitar desbordamiento de stack, (b) comprender exactamente qué estado se guarda, (c) depurar cuando falla. El observable experimental muestra que ambas producen idéntico resultado (`30071` en todos los casos), defendiendo que la matemática es independiente del mecanismo, pero el mecanismo determina si es seguro, rápido, debuggeable.

**Afirmación sobre evaluación de expresiones**:
Dos pilas (operandos, operadores) no son redundancia sino **separación de responsabilidades**. Operandos viven en tiempos distintos que operadores. Una pila única sería confusión de tipos y reglas. El evaluador enseña que control de estructura (mediante pilas) permite extraer valor numérico (2012 de `(0!+1)*2^(3!+4)-(5!-67-(8+9))`) y **también transparencia** (RPN = `0 ! 1 + 2 3 ! 4 + ^ * 5 ! 67 - 8 9 + - -`) simultáneamente. Sin pilas explícitas, habría solo caja negra.

**Afirmación sobre backtracking**:
Backtracking es la estrategia de "espero, y si fallo, retrocedo". Una pila explícita es el registro literal de "dónde estoy y de dónde vine". En N-Reinas, la pila contiene reinas colocadas; en laberinto, el camino recorrido. Experimento 4 demuestra que `checks=84` para N=4 mientras `solutions=2`, evidenciando que el algoritmo rechaza ramas tempranamente (poda automática cuando detecta conflicto). Sin pila explícita, backtracking sería invisib le y confuso. Con pila, es un mecanismo concreto, verificable.

**Afirmación sobre simulación**:
Simulación bancaria con colas no es "cálculo de un resultado único" sino "reproducción de una trayectoria temporal". `timeline` muestra estado en cada instante. Experimento 6 demuestra que parámetros (nWin, servTime, seed) alteran la trayectoria. Una pila no serviría (sería LIFO, último cliente atendido primero, injerencia). Cola es obligatoria porque problema exige "primero en llegar, primero en ser atendido". Cambio crucial: no es "¿existe solución?" sino "¿cuál es la evolución?". Colas modelan el tiempo como FIFO.

**Afirmación sobre correctitud experimental**:
No basta pasar pruebas. Prueba pública de paréntesis no cubre `parenRecursive("([)]")` retornando `true` cuando debería ser `false`. Experimento 2 demuestra esta brecha. Métrica de checks en N-Reinas (Experimento 4) no es verificable desde resultado final (2 soluciones); necesita inspeccionar proceso. Valor de experimentos: **evidencia de mecanismo, no solo resultado**. Correctitud es triple: (a) resultado correcto, (b) proceso correcto, (c) métricas consistentes.

**Comparación entre conversión de base, paréntesis, N-Reinas, laberinto y banco**:

| Problema | Estructura | Mecanismo | Meta | Evidencia Semana 4 |
|----------|-----------|-----------|------|---------|
| **Conversión de base** | Stack (recursión vs iterativa) | Residuos se apilan, se extraen en orden inverso | Cambiar representación numérica | Recursivo=Iterativo=`30071` para 12345 base 8 |
| **Paréntesis** | Stack (pila explícita) | Apertura se apila, cierre desapila si coincide | Validar sintaxis | Iterativa detecta cruce `([)]`; recursiva falla |
| **N-Reinas** | Stack (reinas colocadas) | Reina nueva se apila, retroceso desapila | Hallar todas las colocaciones válidas | 2 soluciones, 84 checks (poda temprana observable) |
| **Laberinto** | Stack (camino) | Celda se marca ROUTE, se desapila si retrocede | Hallar ruta de origen a destino | Camino 5 celdas de (1,1) a (3,3); sin salida detected |
| **Banco** | Queue (cliente por ventanilla) | Clientes se encollan FIFO, se atienden en orden | Simular sistema de servicio a través del tiempo | 7 llegadas, distribución entre 3 ventanillas |

**Síntesis final**:

El cambio de "ADT básicos" a "mecanismos de control" es pasar de preguntar "¿tengo una estructura?" a "¿cómo una estructura resuelve este problema específico?". 

- Stack es control de orden: LIFO resuelve problemas donde "lo más reciente determina lo siguiente"
- Queue es control de equidad: FIFO resuelve problemas donde "lo más antiguo determina lo siguiente"
- Pila explícita es control visual: veo qué guardo, cómo lo uso, cómo recupero
- Colas múltiples son control de capacidad: distribuyo carga entre recursos

La Semana 4 enseña que **el mismo patrón conceptual (apilar/desapilar, enfilar/desenfilar) resuelve problemas radicalmente distintos** (base, paréntesis, reinas, laberinto, banco) precisamente porque el patrón es un mecanismo de control general.

Defensa en sustentación: llevo experimentos que muestran (a) equivalencia (conversión), (b) corrección (paréntesis vs cruce), (c) eficiencia (checks en N-Reinas), (d) existencia (laberinto sin camino), (e) dinámica (banco timeline). No son ejemplos decorativos; son pruebas de que la estructura importa más que el contenido.




