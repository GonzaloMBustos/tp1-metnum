Set de instancias de prueba con sus respectivos ranking de Page:
- test_aleatorio: Un grafo aleatorio de 5x5 con los arcos ordenados según el par (i, j). (p = 0.85)
- test_aleatorio_desordenado: El mismo grafo de test_aleatorio pero con los arcos sin estar ordenados por (i, j). (p = 0.76)
- test_trivial: Grafo trivial (1 nodo) (p = 0.3)
- test_completo: Grafo completo de 5 nodos (p = 0.5)
- test_sin_links: Grafo de 5 nodos sin arcos (p = 0.64)
- test_15_segundos: Grafo que debería tardar alrededor de 15 segundos con una implementación de matriz esparsa y eliminación gaussiana. (p = 0.9)
- test_30_segundos: Grafo que debería tardar alrededor de 30 segundos con una implementación de matriz esparsa y eliminación gaussiana. (p = 0.8)

(*) Todos los resultados tienen como primera linea el p que se utilizó.

INSTRUCCIONES PARA COMPILAR:
$ cd [RUTA_PROYECTO]/src
$ make

(Con el comando make debería ser suficiente para compilar el código)

INSTRUCCIONES PARA CORRER EL CÓDIGO (luego de compilado):
$ ./tp [RUTA_DEL_ARCHIVO_DE_INPUT] [VALOR_DE_P]

===== Ejemplos de compilación y corrida del código ===

# Ejemplo 1:
$ cd /home/Metnum/TPs/tp1-metnum/src
$ make
$ ./tp /home/Metnum/TPs/tp1-metnum/tests/test_completo.txt 0.5

>>> Output
P = 0.5
Archivo: /home/Metnum/TPs/tp1-metnum/tests/test_completo.txt
===== Matriz Input ====
|  0|  1|  1|  1|  1|
|  1|  0|  1|  1|  1|
|  1|  1|  0|  1|  1|
|  1|  1|  1|  0|  1|
|  1|  1|  1|  1|  0|

===== Matriz Identidad ====
|  1|  0|  0|  0|  0|
|  0|  1|  0|  0|  0|
|  0|  0|  1|  0|  0|
|  0|  0|  0|  1|  0|
|  0|  0|  0|  0|  1|

===== Matriz D ====
|0.25|  0|  0|  0|  0|
|  0|0.25|  0|  0|  0|
|  0|  0|0.25|  0|  0|
|  0|  0|  0|0.25|  0|
|  0|  0|  0|  0|0.25|

===== PageRank result ====
[2, 2, 2, 2, 2, ]
===== Normalized result ====
[0.2, 0.2, 0.2, 0.2, 0.2, ]

# Ejemplo 2:
$ cd /home/Metnum/TPs/tp1-metnum/src
$ make
$ ./tp /home/Metnum/TPs/tp1-metnum/tests/test_trivial.txt 0.8

>>> Output
P = 0.8
Archivo: /home/dell/Desktop/Gonza/University/Year-3/Metnum/TPs/tp1-metnum/tests/test_trivial.txt
===== Matriz Input ====
|  0|

===== Matriz Identidad ====
|  1|

===== Matriz D ====
|  0|

===== PageRank result ====
[1, ]
===== Normalized result ====
[1, ]
