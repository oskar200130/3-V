
/*@ <answer>
 *
 * Nombre y Apellidos: Oscar García
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void resuelveCaso() {
    int volt, pilas;
    cin >> pilas >> volt;

    vector<int> cantPilas(pilas);

    // leer los datos de la entrada
    for (int& x : cantPilas) {
        cin >> x;
    }
    sort(cantPilas.begin(), cantPilas.end());

    // resolver el caso posiblemente llamando a otras funciones
    int coches = 0, prim = 0, ult=pilas-1;
    while (prim < ult) {
        if (cantPilas[ult] >= volt) {
            coches++;
            ult--;
            prim++;
        }
        else if (cantPilas[prim] + cantPilas[ult] >= volt) {
            coches++;
            prim++;
            ult--;
        }
        else
            prim++;
    }
    
    cout << coches << "\n";
    // escribir la solución
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
