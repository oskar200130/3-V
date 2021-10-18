
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Digrafo.h"    // propios o los de las estructuras de datos de clase
#include <queue>

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
	// escribir la soluci�n

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
