# 🌀 Proyecto: Laberinto Maestro — C++ & BFS Algorithm

Este proyecto es una aplicación de consola de alto rendimiento desarrollada en **C++** que genera laberintos aleatorios y utiliza algoritmos de teoría de grafos para encontrar la ruta óptima entre dos puntos.

## 📖 Descripción

El programa permite crear laberintos de dimensiones personalizadas, garantizando siempre una solución válida mediante una lógica de pasillos predefinidos. Incluye un motor de resolución automática y un sistema de métricas para evaluar la densidad de obstáculos y el tiempo de respuesta del procesador.

---

## 🛠️ Tecnologías Utilizadas

* **Lenguaje:** C++ (Estándar moderno).
* **Estructuras de Datos:** * `std::vector`: Matrices dinámicas para el tablero.
    * `std::queue`: Gestión de nodos para la búsqueda (FIFO).
    * `struct`: Definición de coordenadas y estados.
* **Librerías Clave:** * `<chrono>`: Medición de rendimiento en milisegundos con alta precisión.
    * `<cstdlib>` y `<ctime>`: Motores de aleatoriedad para la generación procedimental.

---

## 🧠 Lógica y Arquitectura

Este proyecto destaca por su enfoque en la **Programación Orientada a Objetos (POO)** y el procesamiento eficiente de datos:

### 1. Algoritmo BFS (Breadth-First Search)
Es el núcleo del sistema de resolución. A diferencia de otros algoritmos, la búsqueda en anchura:
* **Garantiza el camino más corto:** Explora nivel por nivel todos los movimientos posibles.
* **Reconstrucción de Ruta:** Utiliza una matriz de "padres" (`parent matrix`) para rastrear el camino desde la salida (**S**) hasta la entrada (**E**) una vez alcanzada la meta.



### 2. Generación Procedimental
* **Seguridad de Solución:** El algoritmo asegura la jugabilidad creando un pasillo libre en los ejes principales antes de poblar el resto del mapa con paredes aleatorias.
* **Bordes Automáticos:** Implementa lógica perimetral para evitar que el algoritmo se salga de los límites de la memoria.

### 3. Gestión de Rendimiento
Incluye un cronómetro de alta resolución que mide el tiempo de ejecución en milisegundos. Esta métrica es vital para demostrar la eficiencia del algoritmo BFS sobre matrices de gran tamaño.

---

## 🚀 Cómo Ejecutarlo

### 1. Compilación
Utiliza un compilador de C++ (como `g++`):
```bash
g++ -o laberinto laberinto.cpp
