
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
class CaminoMenor {
private:
	vector<bool> visit;
	vector<int> ant;
	vector<int> dist;
	int ini, k;
public:
	CaminoMenor(const Digrafo& g, int v, int K) : visit(g.V(), false), ant(g.V()), ini(v), dist(g.V(), 0), k(K) {
		bfs(g);
	}

	void bfs(const Digrafo& g) {
		std::queue<int> q;
 		visit[ini] = true;
		q.push(ini);


		while (!q.empty()) {
			int v = q.front();
			q.pop();
			int i = 0;
			for (int w : g.ady(v)) {
				i++;
				if (!visit[w]) {
					visit[w] = true;
					dist[w] = dist[v];
					if (i <= k)
						dist[w]++;
					q.push(w);
				}
				if (w == g.V() - 1) return;
			}
		}
	}
	int getMin() { return dist[dist.size() - 1]; };
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int n, k, s, e;
	cin >> n >> k >> s >> e;
	if (n == 0 && k == 0 && s == 0 && e == 0)
		return false;

	Digrafo g(n * n);
	for (int i = 0; i < n * n; i++) {
		for (int j = 1; j <= k; j++) {
			if (j + i < n * n) g.ponArista(i, j + i);
		}
	}

	int x, y;
	for (int i = 0; i < s + e; i++) {
		cin >> x >> y;
		if (x < n * n && y < n * n)g.ponArista(--x, --y);
	}
	// resolver el caso posiblemente llamando a otras funciones
	CaminoMenor m(g, 0, k);
	cout << m.getMin() << "\n";
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
