#include <iostream>
using namespace std;

// MINI EJERCICIO 1: CREAR MATRIZ DINÁMICA CON PUNTEROS
// Objetivo: Completar la función para crear una matriz 5x5 con memoria dinámica

// TODO: Completa esta función
// Debe crear una matriz dinámica de 5x5 e inicializar todo en 0
int** crearMatriz5x5() {
    int** matriz = nullptr;
    int filas = 5;
    int cols = 5;
    
    // TU CÓDIGO AQUÍ:
    // 1. Asignar memoria para 5 punteros de fila
    

    matriz = new int*[filas];

    // 2. Para cada fila, asignar memoria para 5 enteros
    for(int i = 0; i < filas; i++) 
        matriz[i] = new int[cols];

    // 3. Inicializar todas las posiciones en 0
    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < cols; j++) {
            matriz[i][j] = 0;
        }
    } 
    
    
    return matriz;
}

// TODO: Completa esta función para liberar la memoria
void liberarMatriz(int** matriz, int filas) {
    // TU CÓDIGO AQUÍ:
    // 1. Verificar que matriz no sea nullptr
    if(matriz != nullptr)


    // 2. Liberar cada fila individualmente
    for(int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }


    // 3. Liberar el array principal de punteros
    
    delete[] matriz;
}

// Función auxiliar ya implementada
void mostrarMatriz(int** matriz, int filas, int cols) {
    if (!matriz) {
        cout << "Matriz no existe\n";
        return;
    }
    
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    cout << "=== MINI EJERCICIO 1: CREAR MATRIZ CON PUNTEROS ===\n\n";
    // Crear matriz 5x5
    int** tablero = crearMatriz5x5();
    
    cout << "Matriz 5x5 creada e inicializada:\n";
    mostrarMatriz(tablero, 5, 5);
    
    // Poner algunos valores de prueba
    if (tablero) {
        tablero[0][0] = 1;
        tablero[2][2] = 5;
        tablero[4][4] = 9;
        
        cout << "Después de modificar algunas posiciones:\n";
        mostrarMatriz(tablero, 5, 5);
    }
    
    // Liberar memoria
    liberarMatriz(tablero, 5);
    cout << "Memoria liberada correctamente.\n";
    
    return 0;
}

/*
RESULTADO ESPERADO:
Matriz 5x5 creada e inicializada:
0 0 0 0 0 
0 0 0 0 0 
0 0 0 0 0 
0 0 0 0 0 
0 0 0 0 0 

Después de modificar algunas posiciones:
1 0 0 0 0 
0 0 0 0 0 
0 0 5 0 0 
0 0 0 0 0 
0 0 0 0 9 

Memoria liberada correctamente.
*/