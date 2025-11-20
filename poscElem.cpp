#include <iostream>
using namespace std;

// MINI EJERCICIO 3: VALIDAR MOVIMIENTOS
// Objetivo: Completar funciones para validar si un movimiento es posible

const int SIZE = 5;

struct Posicion {
    int x, y;
    Posicion(int a = 0, int b = 0) : x(a), y(b) {}
};

// TODO: Completa esta función
// Debe verificar si una posición está dentro de los límites del tablero
bool dentroLimites(int x, int y) {
    // TU CÓDIGO AQUÍ:
    // Verificar que x e y estén entre 0 y SIZE-1 (inclusive)

    (x >= 0 && x < SIZE && y >= 0 && y < SIZE);
    
    
    return false;
}

// TODO: Completa esta función  
// Debe verificar si una casilla está libre (valor 0) para moverse ahí
bool esCasillaLibre(int tablero[SIZE][SIZE], int x, int y) {
    // TU CÓDIGO AQUÍ:
    // 1. Primero verificar que esté dentro de límites
    // 2. Luego verificar que el valor en tablero[x][y] sea 0
    bool dentro = dentroLimites(x,y);

    

    if(!dentroLimites (x,y)) {
        return false;
    }
    
    
    return (tablero[x][y] == 0);
}

// TODO: Completa esta función
// Debe validar si un movimiento desde (xActual,yActual) hacia (xNuevo,yNuevo) es válido
// Movimientos válidos: solo una casilla en 4 direcciones (arriba/abajo/izq/der)
bool esMovimientoValido(int tablero[SIZE][SIZE], int xActual, int yActual, int xNuevo, int yNuevo) {
    // TU CÓDIGO AQUÍ:
    // 1. Verificar que la nueva posición esté dentro de límites
    

    // 2. Verificar que la nueva casilla esté libre
    // 3. Verificar que solo se mueva 1 casilla en una dirección:
    //    - Diferencia en X debe ser -1, 0 o 1
    //    - Diferencia en Y debe ser -1, 0 o 1  
    //    - Solo una de las dos diferencias puede ser != 0 (no diagonal)
    //    - No puede quedarse en el mismo lugar
    
    
    
    return false;
}

// TODO: Completa esta función
// Debe retornar todas las posiciones válidas desde la posición actual
// Direcciones: arriba(-1,0), abajo(1,0), izquierda(0,-1), derecha(0,1)
int obtenerMovimientosValidos(int tablero[SIZE][SIZE], int x, int y, Posicion* movimientos) {
    int count = 0;
    
    // TU CÓDIGO AQUÍ:
    // 1. Definir las 4 direcciones posibles
    // 2. Para cada dirección, calcular nueva posición
    // 3. Si es válida, agregarla al array 'movimientos' e incrementar count
    // 4. Retornar el número total de movimientos válidos
    
    
    
    return count;
}

// Función auxiliar ya implementada
void mostrarTablero(int tablero[SIZE][SIZE], int jugadorX, int jugadorY) {
    cout << "\nTablero (P=jugador, #=muro, .=libre):\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == jugadorX && j == jugadorY) {
                cout << "P ";
            } else if (tablero[i][j] == 1) {
                cout << "# ";
            } else {
                cout << ". ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    cout << "=== MINI EJERCICIO 3: VALIDAR MOVIMIENTOS ===\n";
    
    // Crear tablero con algunos muros
    int tablero[SIZE][SIZE] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0}
    };
    
    int jugadorX = 2, jugadorY = 2;  // Jugador en el centro
    
    mostrarTablero(tablero, jugadorX, jugadorY);
    
    // Probar validaciones básicas
    cout << "=== PRUEBAS DE VALIDACIÓN ===\n";
    cout << "¿(0,0) está dentro de límites? " << (dentroLimites(0,0) ? "SÍ" : "NO") << "\n";
    cout << "¿(5,5) está dentro de límites? " << (dentroLimites(5,5) ? "SÍ" : "NO") << "\n";
    cout << "¿(0,2) es casilla libre? " << (esCasillaLibre(tablero,0,2) ? "SÍ" : "NO") << "\n";
    cout << "¿(1,1) es casilla libre? " << (esCasillaLibre(tablero,1,1) ? "SÍ" : "NO") << "\n";
    
    // Probar movimientos específicos
    cout << "\n=== PRUEBAS DE MOVIMIENTO ===\n";
    cout << "¿Puede moverse de (2,2) a (1,2)? " << (esMovimientoValido(tablero,2,2,1,2) ? "SÍ" : "NO") << "\n";
    cout << "¿Puede moverse de (2,2) a (2,1)? " << (esMovimientoValido(tablero,2,2,2,1) ? "SÍ" : "NO") << "\n";
    cout << "¿Puede moverse de (2,2) a (1,1)? " << (esMovimientoValido(tablero,2,2,1,1) ? "SÍ" : "NO") << " (diagonal)\n";
    
    // Obtener todos los movimientos válidos
    cout << "\n=== MOVIMIENTOS DISPONIBLES DESDE (2,2) ===\n";
    Posicion movimientos[4];
    int numMovimientos = obtenerMovimientosValidos(tablero, jugadorX, jugadorY, movimientos);
    
    cout << "Movimientos válidos encontrados: " << numMovimientos << "\n";
    for (int i = 0; i < numMovimientos; i++) {
        cout << "- Puede moverse a (" << movimientos[i].x << "," << movimientos[i].y << ")\n";
    }
    
    return 0;
}

/*
RESULTADO ESPERADO:
- (0,0) dentro de límites: SÍ
- (5,5) dentro de límites: NO
- Movimientos diagonales: NO
- Lista de 2-3 movimientos válidos desde el centro
*/