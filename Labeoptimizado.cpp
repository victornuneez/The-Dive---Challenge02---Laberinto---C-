#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

struct Pos { int x, y; Pos(int a=0, int b=0) : x(a), y(b) {} };

class Laberinto {
    vector<vector<int>> grid;
    int rows, cols;
    int dx[4] = {-1,1,0,0}, dy[4] = {0,0,-1,1};

public:
    vector<Pos> path;  // AHORA ES PÚBLICO
    
    Laberinto(int r, int c) : rows(r), cols(c), grid(r, vector<int>(c)) {
        srand(time(0));
    }

    void generar() {
        // Llenar de muros
        for(int i=0; i<rows; i++)
            for(int j=0; j<cols; j++)
                grid[i][j] = (i==0 || j==0 || i==rows-1 || j==cols-1) ? 1 : 0;
        
        // Camino garantizado: L-shape desde entrada a salida
        for(int i=0; i<rows-1; i++) grid[i][1] = 0;        // Columna 1
        for(int j=1; j<cols; j++) grid[rows-2][j] = 0;     // Fila penúltima
        grid[0][0] = grid[rows-1][cols-1] = 0;             // Entrada y salida
        
        // Añadir paredes aleatorias (evitando el camino principal)
        for(int i=0; i<rows*cols/8; i++) {
            int r = rand()%(rows-2)+1, c = rand()%(cols-2)+1;
            if(r!=1 && r!=rows-2) grid[r][c] = 1;
        }
    }

    bool resolver() {
        path.clear();
        vector<vector<bool>> vis(rows, vector<bool>(cols));
        vector<vector<Pos>> parent(rows, vector<Pos>(cols, Pos(-1,-1)));
        queue<Pos> q;
        
        q.push(Pos(0,0));
        vis[0][0] = true;
        
        while(!q.empty()) {
            Pos curr = q.front(); q.pop();
            
            if(curr.x == rows-1 && curr.y == cols-1) {
                // Reconstruir camino
                while(curr.x != -1) {
                    path.insert(path.begin(), curr);
                    curr = parent[curr.x][curr.y];
                }
                return true;
            }
            
            for(int i=0; i<4; i++) {
                int nx = curr.x + dx[i], ny = curr.y + dy[i];
                if(nx>=0 && nx<rows && ny>=0 && ny<cols && !vis[nx][ny] && !grid[nx][ny]) {
                    vis[nx][ny] = true;
                    parent[nx][ny] = curr;
                    q.push(Pos(nx,ny));
                }
            }
        }
        return false;
    }

    void mostrar(bool conSolucion = false) {
        vector<vector<char>> display(rows, vector<char>(cols));
        
        for(int i=0; i<rows; i++)
            for(int j=0; j<cols; j++)
                display[i][j] = grid[i][j] ? '#' : ' ';
        
        display[0][0] = 'E';
        display[rows-1][cols-1] = 'S';
        
        if(conSolucion && !path.empty())
            for(int i=1; i<path.size()-1; i++)
                display[path[i].x][path[i].y] = '*';
        
        cout << "\n";
        for(int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) cout << display[i][j] << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    void stats() {
        int muros = 0;
        for(int i=0; i<rows; i++)
            for(int j=0; j<cols; j++)
                if(grid[i][j]) muros++;
        
        cout << "Tamaño: " << rows << "x" << cols << " | Muros: " << muros 
             << " (" << muros*100.0/(rows*cols) << "%)" << endl;
        if(!path.empty()) cout << "Camino: " << path.size() << " pasos\n";
    }
};

int main(int argc, char* argv[]) {
    int filas = 10, columnas = 10;
    if(argc == 3) {
        filas = atoi(argv[1]); columnas = atoi(argv[2]);
        if(filas < 5 || columnas < 5) { cout << "Mínimo 5x5\n"; return 1; }
    }
    
    Laberinto lab(filas, columnas);
    int op; bool generado = false;
    
    cout << "=== LABERINTO MAESTRO ===\n";
    
    do {
        cout << "\n1.Generar 2.Mostrar 3.Resolver 4.Stats 5.Cambiar tamaño 0.Salir\nOpción: ";
        cin >> op;
        
        auto inicio = chrono::high_resolution_clock::now();
        
        switch(op) {
            case 1: 
                lab.generar(); 
                generado = true; 
                lab.mostrar(); 
                break;
            case 2: 
                if(generado) lab.mostrar(); 
                else cout << "Genera primero\n"; 
                break;
            case 3: 
                if(!generado) { 
                    cout << "Genera primero\n"; 
                    break; 
                }
                if(lab.resolver()) cout << "¡Resuelto!\n";
                else cout << "Sin solución\n";
                if(!lab.path.empty()) lab.mostrar(true);
                break;
            case 4: 
                if(generado) lab.stats(); 
                else cout << "Genera primero\n"; 
                break;
            case 5:
                cout << "Nuevo tamaño (filas cols): ";
                cin >> filas >> columnas;
                if(filas<5 || columnas<5) { cout << "Mínimo 5x5\n"; filas=10; columnas=10; }
                else { lab = Laberinto(filas, columnas); generado = false; }
                break;
            case 0: cout << "¡Adiós!\n"; break;
            default: cout << "Opción inválida\n";
        }
        
        if(op >= 1 && op <= 4) {
            auto fin = chrono::high_resolution_clock::now();
            cout << "Tiempo: " << chrono::duration_cast<chrono::milliseconds>(fin-inicio).count() << "ms\n";
        }
        
    } while(op != 0);
    
    return 0;
}