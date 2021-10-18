
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Digrafo.h"    // propios o los de las estructuras de datos de clase
#include <queue>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int bfs(int n, int k, const vector<int>& saltos) {
	std::queue<int> q;
	int dest = n * n;
	vector<int> dist(dest + 1, -1);

	dist[1] = 0;
	q.push(1);

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 1; i <= k && v + i <= dest; i++) {
			int w = saltos[v + i];
			if (dist[w] == -1) {
				dist[w] = dist[v] + 1;
				if (w == dest)
					return dist[dest];
				q.push(w);
			}
		}
	}
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int n, k, s, e;
	cin >> n >> k >> s >> e;
	if (n == 0 )
		return false;

	vector<int> saltos(n * n + 1);
	for (int i = 0; i <= n * n; i++) {
		saltos[i] = i;
	}

	int x, y;
	for (int i = 0; i < s + e; i++) {
		cin >> x >> y;
		saltos[x] = y;
	}
	// resolver el caso posiblemente llamando a otras funciones
	cout << bfs(n, k, saltos) << "\n";
	// escribir la solución

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
