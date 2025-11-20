#include <iostream>
#include <vector>
using namespace std;

bool puedeMoverse(const vector<vector<int>>& grid, int x, int y, char dir) {
    int nx = x, ny = y;

    // TODO: según dir ('W','S','A','D') modifica nx y ny

    if(dir == 'W' || dir == 'w') {
        nx--;

    } else if(dir == 'S'|| dir == 's') {
        nx++;
    
    } else if(dir == 'A' || dir == 'a') {
        ny--;

    } else if(dir == 'D' || dir == 'd') {
        ny++;
    }



    // TODO: comprueba que nx,ny están en rango
    if(nx < 0 && nx >= grid.size() && ny < 0 && ny >= grid[0].size())
        return true; 

    // TODO: comprueba que grid[nx][ny] == 0 (camino libre)
    if(grid[nx][ny] != 0) return false;

    return true; // cambia por true si cumple
}


int main() {
    vector<vector<int>> grid = {
        {0,0,1},
        {1,0,0},
        {0,0,0}
    };
    int x=1, y=1;
    char dir;
    cout << "Movimiento (W/A/S/D): ";
    cin >> dir;
    if (puedeMoverse(grid, x, y, dir))
        cout << "Movimiento válido\n";
    else
        cout << "Bloqueado\n";
}


#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    int n, m;
    cout << "Filas y columnas: ";
    cin >> n >> m;

    // TODO: reservar memoria int** matriz
    int** matriz;

    matriz = new int*[n];
    
    for(int i = 0; i < n; i++)
        matriz[i] = new int[m];

    srand(time(0));

    // TODO: llenar con valores aleatorios 0–9
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            matriz[i][j] = rand() % 10;
        }
    } 


    // TODO: imprimir la matriz
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++){
            cout << matriz[i][j] << " ";
        }
    cout << endl;
    }

    // TODO: liberar la memoria
    for(int i = 0; i < n; i++)
        delete[] matriz[i];

    delete[] matriz;

    return 0;

        



}
