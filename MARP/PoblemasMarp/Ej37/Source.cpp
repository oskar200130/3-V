
/*@ <answer>
 *
 * Nombre y Apellidos: Oscar Garc�a
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
    // escribir la soluci�n
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
