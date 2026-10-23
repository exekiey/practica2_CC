# Práctica 2 - Complejidad Computacional

Este proyecto implementa un simulador de una Máquina de Turing determinista (multicinta) en C++, diseñado bajo principios de orientación a objetos. El programa lee la configuración de una Máquina de Turing desde un fichero de texto, procesa cadenas de entrada y determina si son aceptadas o rechazadas, mostrando la evolución de la cinta y la posición de la cabeza de lectura/escritura.

## Funcionalidades

- Lectura y movimientos simultáneos
- Movimientos: L, R y S
- Cinta infinita en ambas direcciones
## Máquinas de Turing diseñadas

El proyecto incluye la definición y los grafos de las siguientes Máquinas de Turing:

1. Reconocimiento del lenguaje L = { a^n b^m | m >= n, n > 0 }
   - Fichero de configuración: ```turing_machines/Design1.txt```

2. Transformación de cadenas de a y b a recuento 1^n (con separador 0 en ausencia)
   - Fichero de configuración: ```turing_machines/Design2.txt```

## Estructura del Proyecto

- main.cpp: Punto de entrada del programa y gestor de argumentos por línea de comandos.
- include/: Carpeta contenedora de los archivos de cabecera (.h).
- reader.cpp: Módulo de lectura y validación de la configuración de la MT y de los ficheros de entrada.
- solver.cpp: Lógica de resolución y motor de ejecución de las transiciones de la máquina.
- tape.cpp: Implementación de la cinta bidireccional infinita mediante estructura de nodos doblemente enlazados.
- state.cpp: Representación formal de los estados de la máquina.
- symbol.cpp: Representación de los símbolos del alfabeto y gestión del símbolo blanco.
- transition.cpp: Definición formal de las funciones de transición.
- tools.cpp: Funciones auxiliares de procesamiento de cadenas y tokens.
- Makefile: Automatización de la compilación del proyecto (genera los objetos en build/).
- automata.txt: Configuración de la MT para el Problema 1.
- automata2.txt: Configuración de la MT para el Problema 2.
- input.txt: Ejemplo de cadenas de entrada a comprobar.


## Formato del Fichero de Configuración

El archivo de configuración sigue la estructura especificada, admitiendo comentarios mediante #:
```
# Comentarios explicativos
q1 q2 q3        # Conjunto de estados Q
a b             # Alfabeto de entrada Sigma
a b _           # Alfabeto de cinta Gamma (incluyendo el símbolo blanco)
q1              # Estado inicial s
_               # Símbolo blanco (b)
q3              # Estados finales F
1               # Número de cintas
q1 a q2 b R     # Transición: delta(q1, a) = (q2, b, R)
```

## Compilación

Para compilar el proyecto y generar el ejecutable main, ejecute desde la raíz del proyecto:
```
make
```
Para limpiar los ficheros objeto generados y el ejecutable:
```
make clean
```

## Ejecución

El programa acepta las siguientes opciones por línea de comandos:

- ```-config <f>```: Fichero de texto con la configuración de la MT (obligatorio).
- ```-in <f>```: Fichero de texto con las cadenas de entrada a comprobar (opcional).

### Ejemplos de ejecución:

Ejecución con fichero de entradas:

```./main -config automata.txt -in input.txt```
