
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
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
            else // no tomamos m�s monedas de tipo i
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

    // escribir la soluci�n

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
