
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"
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
struct Tesoro {
	int P;
	int V;
};

int sumergir(const vector<Tesoro>& t, int T, vector<Tesoro>& sol) {
	Matriz<int> s(t.size() + 1, T + 1, 0);
	for (int i = 1; i <= t.size(); i++) {
		for (int j = 1; j <= T; j++) {
			if (j >= t[i - 1].P)
				s[i][j] = max(s[i - 1][j], s[i - 1][j - t[i - 1].P] + t[i - 1].V);
			else
				s[i][j] = s[i - 1][j];
		}
	}

	if (s[t.size()][T] != 0) {
		int i = t.size(), j = T;
		while (i > 0 && j >= 0) { // no se ha pagado todo
			if (t[i - 1].P <= j && s[i][j] == s[i - 1][j - t[i - 1].P] + t[i - 1].V) {
				// tomamos una moneda de tipo i
				sol.push_back(t[i - 1]);
				j = j - t[i - 1].P;
			}
			--i;
		}
	}

	return s[t.size()][T];
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int T;

	cin >> T;

	if (!cin)  // fin de la entrada
		return false;

	int i;
	cin >> i;

	vector<Tesoro> tes(i);
	for (int j = 0; j < i; j++) {
		Tesoro aux;
		cin >> aux.P >> aux.V;
		aux.P *= 3;
		tes[j] = aux;
	}
	// resolver el caso posiblemente llamando a otras funciones

	vector<Tesoro> sol;

	cout << sumergir(tes, T, sol) << "\n";
	cout << sol.size() << "\n";
	for (int i = sol.size()-1; i >= 0; i--) {
		cout << sol[i].P/3 << " " << sol[i].V << "\n";
	}
	// escribir la soluci�n

	cout << "---\n";
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
