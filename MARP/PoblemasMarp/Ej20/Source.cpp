
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Digrafo.h"    // propios o los de las estructuras de datos de clase

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
	int min, act;
public:
	CaminoMenor(const Digrafo& g, int v) : visit(v, false), min(v + 1), act(0) {
		dfs(g, 0);
	}

	void dfs(const Digrafo& g, int v) {
		visit[v] = true;
		act++;
		if (act < min) {
			for (int w : g.ady(v)) {
				if (w == (visit.size()-1)) 
					min = act;
				else if (!visit[w])
					dfs(g, w);
			}
		}
		visit[v] = false;
		act--;
	}
	int getMin() { return min; };
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int n, k, s, e;
	cin >> n >> k >> s >> e;
	if (n == 0 && k == 0 && s == 0 && e == 0)
		return false;

	Digrafo g(n * n);
	for (int i = 0; i < n*n; i++) {
		for (int j = 0; j < k; j++) {
			if (j < n*n) g.ponArista(i, j);
		}
	}

	int x, y;
	for (int i = 0; i < s + e; i++) {
		cin >> x >> y;
		g.ponArista(--x, --y);
	}
	// resolver el caso posiblemente llamando a otras funciones
	CaminoMenor m(g, n * n);
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
