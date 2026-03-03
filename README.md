🌀 Proyecto: Laberinto Maestro - C++ & BFS Algorithm

Este proyecto es una aplicación de consola desarrollada en C++ que genera laberintos aleatorios y utiliza algoritmos de búsqueda para encontrar el camino más corto entre dos puntos.

📖 Descripción

El programa permite crear laberintos de dimensiones personalizadas, garantizando siempre que exista una solución mediante un camino en "L". Además, implementa una lógica de resolución automática y proporciona estadísticas detalladas sobre la densidad de obstáculos y el tiempo de procesamiento.

🛠️ Tecnologías Utilizadas

Lenguaje: C++ (Estándar moderno)
Estructuras de Datos: std::vector (matrices dinámicas), std::queue (colas FIFO), struct.
Librerías Clave: * <chrono> para medición de rendimiento en milisegundos.
<cstdlib> y <ctime> para la generación de números aleatorios.

🧠 Lógica y Arquitectura (Paso a Paso)

Este proyecto destaca por su enfoque en la Programación Orientada a Objetos (POO) y algoritmos de grafos:
Algoritmo BFS (Breadth-First Search): * Es el núcleo del resolvedor. Utiliza una búsqueda en anchura para explorar el laberinto nivel por nivel.
Garantiza encontrar el camino más corto posible.
Utiliza una matriz de parent (padres) para reconstruir la ruta desde la salida (S) hasta la entrada (E) una vez encontrada la meta.

Generación Procedural:

Crea bordes perimetrales automáticamente.
Asegura la jugabilidad creando un pasillo libre en los ejes principales antes de colocar paredes aleatorias.

Gestión de Rendimiento:

Implementa un cronómetro de alta resolución para medir cuánto tarda el procesador en generar o resolver el laberinto, una métrica vital en el desarrollo de sistemas eficientes.

Interfaz Dinámica:

Permite pasar parámetros de tamaño (filas y columnas) directamente desde la línea de comandos (argc, argv).

🚀 Cómo Ejecutarlo
Compila el código con un compilador de C++ (como g++):

Bash

g++ -o laberinto laberinto.cpp

Ejecuta el programa (opcionalmente definiendo el tamaño):

Bash
./laberinto 15 20
Sigue el menú interactivo para generar, mostrar y resolver.
