// Librerías principales para entrada/salida, vectores, cola BFS, números aleatorios, funciones de tiempo y cronómetro.
// "< >" los signos de mayor y menor buscan la libreria en directorios del sistema. 

#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <chrono>

// Con usin namespace ahorramos muchisimas lineas de codigo. 
// Sin ella, cada elemento de la biblioteca estándar de C++ debe llevar el prefijo std::.
using namespace std;

// Estructura para coordenadas del laberinto - (agrupa x,y en un solo tipo de dato (Pos)).
// " : "lista de inicialización de miembros, inicializa los miembros con el valor de los parametros.
// Si no se requiere lógica extra  el bloque { } puede quedar vacío y el constructor sigue siendo totalmente válido.

struct Pos { 
    int x, y; 
    Pos(int a=0, int b=0) : x(a), y(b) {}  // Constructor con valores por defecto
};

// Definimos una clase llamada Laberinto, con el proposito de agrupar todas las funciones y datos relacionados con el laberinto.
class Laberinto {
    // Atributos de la clase Laberinto.
    // Variables privadas - datos internos protegidos.
    // Solo los propios metodos de la clase tienen acceso a los atributos privados.

    vector<vector<int>> grid;              // Matriz 2D de enteros: 0=libre, 1=muro. (Grid"Mapa").
    int filas, cols;                        // Dimensiones del laberinto
    int dx[4] = {-1,1,0,0}, dy[4] = {0,0,-1,1};  // Direcciones: arriba, abajo, izq, der

public:
    vector<Pos> camino;  // Vector público para almacenar camino solución.(Atributo publico)
    
    // Constructor: inicializa matriz y semilla aleatoria
    Laberinto(int f, int c) : filas(f), cols(c), grid(f, vector<int>(c)) {
        srand(time(0));  // Semilla única para paredes aleatorias
    }

    // declarar como metodo publico esta funcion para generar el laberinto.
    // “arma” el laberinto dentro del objeto, dejando lista la matriz con caminos y obstáculos.
    void generar() {
        // Paso 1: Crear bordes del laberinto
        for(int i=0; i<filas; i++)
            for(int j=0; j<cols; j++)
        // Todo lo que está antes del ? → es la condición que vamos a evaluar (si es true o false).
        // Lo que está después de : → es el valor que se toma si la condición es falsa.
                grid[i][j] = (i==0 || j==0 || i==filas-1 || j==cols-1) ? 1 : 0;
        
        // Paso 2: Crear camino garantizado en forma de "L".
        // Asignamos el valor de 0(camino libre) en la columna 1 y en la ante ultima fila.

        for(int i=0; i<filas-1; i++) grid[i][1] = 0;        // Pasillo vertical libre hasta la penultima fila.
        for(int j=1; j<cols; j++) grid[filas-2][j] = 0;     // Pasillo horizontal libre hasta la ante ultima columna.
        grid[0][0] = grid[filas-1][cols-1] = 0;             // Entrada y salida libres
        
        // Paso 3: Agregar paredes aleatorias sin bloquear camino principal
        for(int i=0; i<filas*cols/4 ; i++) { // El bucle se ejecutará aproximadamente (total de celdas) ÷ 8 veces.
            int f = rand()%(filas-2)+1, c = rand()%(cols-2)+1; // Se calcula un número aleatorio(Posicion) dentro del rango interior de la matriz, excluyendo los bordes.
            if(f!=1 && f!=filas-2) grid[f][c] = 1;  // Evita bloquear camino garantizado (La columna 1 y la ante ultima fila).
        }
    }


    
// bool es un tipo de dato booleano solo puede devolver un valor True o False.
// su proposito es usar el algorimo Bfs para devolver un camino a la salida del laberinto. Retorna True si encontro una solucion
    bool resolver() {
        camino.clear();  // Limpiar solución anterior
        
        // Matrices de control para BFS
        // matriz 2D de valores true/false. inicializados en false por defecto.
        vector<vector<bool>> visitados(filas, vector<bool>(cols));   // Registro de Celdas visitadas.
        
        // Matriz 2D de objetos Pos(coordenadas). inicializamos para guardar el “padre” de cada celda.
        vector<vector<Pos>> parent(filas, vector<Pos>(cols, Pos(-1,-1))); // Para reconstruir camino desde el final al inicio.
        queue<Pos> cola;  // Cola FIFO para algoritmo BFS
        
        // Inicializar BFS desde entrada (0,0)
        cola.push(Pos(0,0));
        visitados[0][0] = true;
        
        // Algoritmo BFS principal
        // front() Devuelve la celda que está al frente de la cola.
        // pop() Elimina la celda que acabamos de tomar de la cola, porque ya la estamos procesando.
        while(!cola.empty()) {
            Pos actual = cola.front(); cola.pop();
            
            // Esta línea pregunta si llegamos a la meta (la esquina inferior derecha del laberinto).
            // Si la condición se cumple, normalmente se detiene la búsqueda y se comienza a reconstruir el camino.
            if(actual.x == filas-1 && actual.y == cols-1) {
                // Reconstruir camino desde salida hasta entrada
                while(actual.x != -1) { // Se repite mientras la fila actual no sea una celda visitada (-1)
                    camino.insert(camino.begin(), actual); // Añade la celda actual al inicio de la lista para que el camino se construya.(inicio a fin)
                    actual = parent[actual.x][actual.y]; // Devuelve la celda desde la que llegamos a actual.
                                                         //Al asignarlo a actual, el bucle puede continuar siguiendo los padres hacia el inicio del laberinto.
                }
                return true;  // Solución encontrada
            }
            
            // Explorar 4 direcciones (arriba, abajo, izq, der).
            // Se calcula la posición de las 4 celdas vecinas de la celda actual para revisarlas y decidir si se pueden visitar o agregar a la cola de BFS.
            for(int i=0; i<4; i++) {
                int nx = actual.x + dx[i], ny = actual.y + dy[i];
                
                // Validar: dentro de límites, no visitado, no es muro
                if(nx>=0 && nx<filas && ny>=0 && ny<cols && !visitados[nx][ny] && !grid[nx][ny]) {
                    visitados[nx][ny] = true;       // Marcar como visitado la celda para no procesarla de nuevo.
                    parent[nx][ny] = actual;    // Guarda la celda desde la que llegamos, útil para reconstruir el camino después.
                    cola.push(Pos(nx,ny));       // Agrega la celda a la cola para explorarla mas adelante.
                }
            }
        }
        return false;  // No hay solución
    }

// Este metodo del objeto su proposito es convertir los numeros(0,1) a simbolos visuales ("#"," ","E","S)".
// "grid" tiene numeros: 0=libre, 1=muro y "display" tiene simbolos: ' '=camino libre, "#"= Muro, "E" a entrada, "S" a salida.
// mostrar() solo afecta a display, no al grid original de la clase.
// Crea una matriz temporal de filas × cols de caracteres para mostrar el laberinto sin tocar la original.
    void mostrar(bool conSolucion = false) {
        // Crear matriz de visualización(caracteres) llamada display.
        vector<vector<char>> display(filas, vector<char>(cols));
        
        // Convertir números a símbolos: 0→' ', 1→'#'
        for(int i=0; i<filas; i++)
            for(int j=0; j<cols; j++)
// "?" Es un operador ternario es una forma abreviada de if-else. 
// Si grid[i][j] vale 1 (muro) → es verdadero. Si vale 0 (camino) → es falso. 
// Si es distinto de 0, se considera true. Si es 0, se considera false.           
                display[i][j] = grid[i][j] ? '#' : ' ';
        
        // Marcar entrada y salida
        display[0][0] = 'E';
        display[filas-1][cols-1] = 'S';
        
        // Mostrar camino con asteriscos si se solicita
        // Solo se ejecuta si hay solucion y el camino no esta vacio.(Camino calculado a la meta)
        // Recorre todas las posiciones del camino excepto el inicio (i=0) y la meta (i=camino.size()-1).
        if(conSolucion && !camino.empty())
            for(int i=1; i < camino.size()-1; i++)
                display[camino[i].x][camino[i].y] = '*'; // Marca la celda del camino en display con '*', indicando que forma parte de la solución.
        
        // Imprimir laberinto
        cout << "\n";
        for(int i=0; i<filas; i++) {
            for(int j=0; j<cols; j++) cout << display[i][j] << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    void estadisticas() {
        // Contar muros del laberinto
        int muros = 0;
        for(int i=0; i<filas; i++)
            for(int j=0; j<cols; j++)
                if(grid[i][j]) muros++;
        
        // Mostrar estadísticas
        cout << "Tamaño: " << filas << "x" << cols << " | Muros: " << muros 
             << " (" << muros*100.0/(filas*cols) << "%)" << endl; // Multiplica el número de muros por 100. 
                                                                 // Divide entre el total de celdas (filas*cols).
                                                                 // Esto da el porcentaje de celdas que son muros.
        if(!camino.empty()) cout << "Camino: " << camino.size() << " pasos\n";
    }
};

// "argc" Cuenta cuántas cosas escribiste al ejecutar el programa. El nombre del programa (siempre cuenta como 1)
// "argv" Guarda todas las cosas que escribiste (LISTA DE COSAS).
// Para que tu programa reciba ÓRDENES desde afuera. Sirve Para personalizar tu programa SIN modificar el código:
int main(int argc, char* argv[]) {
    
    // Configuración inicial con argumentos de línea de comandos
    int filas = 10, columnas = 10;  // Valores por defecto
    if(argc == 3) {
        filas = atoi(argv[1]); columnas = atoi(argv[2]);  // Convertir strings a enteros
        if(filas < 5 || columnas < 5) { 
            cout << "Mínimo 5x5\n"; 
            return 1; 
        }
    }
    
    // Crear objeto laberinto y variables de control
    Laberinto lab(filas, columnas);
    int opcion_user; // Almacena la opción que el usuario elija en un menú.
    bool generado = false;  // Control de estado del laberinto. 
                            //Se usa para saber si el laberinto ya fue generado, evitando intentar mostrar o resolver uno vacío.
    
    cout << "=== LABERINTO MAESTRO ===\n";
    
    // Menú principal con cronómetro
    do {
        cout << "\n1.Generar 2.Mostrar 3.Resolver 4.Estadisticas 5.Cambiar tamaño 0.Salir\nOpción: ";
        cin >> opcion_user;
        
        auto inicio = chrono::high_resolution_clock::now();  // Iniciar cronómetro
        
        switch(opcion_user) {
            case 1:  // Generar nuevo laberinto
                lab.generar(); 
                generado = true; 
                lab.mostrar(); 
                break;
                
            case 2:  // Mostrar laberinto actual
                if(generado) lab.mostrar(); 
                else cout << "Genera primero\n"; 
                break;
                
            case 3:  // Resolver laberinto
                if(!generado) { 
                    cout << "Genera primero\n"; 
                    break; 
                }
                if(lab.resolver()) cout << "¡Resuelto!\n";
                else cout << "Sin solución\n";
                if(!lab.camino.empty()) lab.mostrar(true);  // Solo imprime el laberinto si ya se calculó un camino.
                                                          // Lo imprime mostrando la ruta desde inicio hasta meta.
                break;
                
            case 4:  // Mostrar estadísticas
                if(generado) lab.estadisticas(); 
                else cout << "Genera primero\n"; 
                break;
                
            case 5:  // Cambiar tamaño
                cout << "Nuevo tamaño (filas cols): ";
                cin >> filas >> columnas;
                if(filas<5 || columnas<5) { 
                    cout << "Mínimo 5x5\n"; 
                    filas=10; columnas=10; 
                }
                else { 
                    lab = Laberinto(filas, columnas); // Si es válido, crea un laberinto nuevo y marca que aún no se ha generado.
                    generado = false; 
                }
                break;
                
            case 0: cout << "¡Adiós!\n"; break;
            default: cout << "Opción inválida\n";
        }
        
        // Mostrar tiempo de ejecución para operaciones principales, solo se ejecuta el cronometro para 4 opciones.
        if(opcion_user >= 1 && opcion_user <= 4) {
            auto fin = chrono::high_resolution_clock::now();
            cout << "Tiempo: " << chrono::duration_cast<chrono::milliseconds>(fin-inicio).count() << "ms\n";
        }
        
    } while(opcion_user != 0);  // Repetir hasta que usuario elija salir
    
    return 0;  // Programa terminado exitosamente
}