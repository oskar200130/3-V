
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
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

vector<int> minTiradas(vector<int> c, int L) {
    vector<EntInf> cant(L + 1, Infinito);
    for (int i = 0; i < c.size(); i++) {
        cant[0] = 0;
        for (int j = c[i]; j <= L; j++) {
            EntInf x = cant[j];
            cant[j] = min(cant[j], cant[j - c[i]] + 1);
        }
    }

    vector<int> sol;

    if (cant[L] != Infinito) {
        int i = c.size(), j = L;
        while (j > 0) { // no se ha pagado todo
            if (c[i - 1] <= j && cant[j] == cant[j - c[i - 1]] + 1) {
                // tomamos una moneda de tipo i
                sol.push_back(c[i - 1]);
                j = j - c[i - 1];
            }
            else // no tomamos más monedas de tipo i
                --i;
        }
    }

    return sol;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int L, n;

    cin >> L >> n;

    if (!cin)  // fin de la entrada
        return false;
    // resolver el caso posiblemente llamando a otras funciones
    vector<int> c(n);

    for (int i=0; i<n; i++)
        cin >> c[i];

    vector<int> sol = minTiradas(c, L);
    if (sol.size() > 0) {
        cout << sol.size() << ": ";
        for (auto a : sol)
            cout << a << " ";
    }
    else
        cout << "Imposible";
    cout << "\n";

    // escribir la solución

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
