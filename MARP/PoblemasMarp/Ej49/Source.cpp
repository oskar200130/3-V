
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Matriz.h"
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

bool resuelveCaso() {

	// leer los datos de la entrada
	int L, N;
	cin >> L >> N;

	if (L == 0)
		return false;

	vector<int> cortes(N + 2);
	cortes[0] = 0;
	cortes[N + 1] = L;
	for (int i = 1; i <= N; i++) {
		cin >> cortes[i];
	}

	Matriz<EntInf> coste(N + 2, N + 2, 0);
	// resolver el caso posiblemente llamando a otras funciones
	for (int i = N + 1; i >= 0; i--) {
		for (int j = i + 2; j < N + 2; j++) {
			EntInf mini = Infinito;
			for (int k = i + 1; k < j; k++) {
				mini = min(coste[i][k] + coste[k][j], mini);
			}
			if (mini == Infinito) mini = 0;
			coste[i][j] = mini + (cortes[j] - cortes[i])*2;
		}
	}

	// escribir la solución
	cout << coste[0][N + 1] << "\n";
	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
