/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Grafo.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class CaminosDFS {
private:
	vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	vector<int> componente; // ant[v] = último vértice antes de llegar a v

	vector<int> tam_comp;

	int dfs(Grafo const& G, int v) {
		visit[v] = true;
		componente[v] = tam_comp.size();
		int tam = 1;
		for (int w : G.ady(v)) {
			if (!visit[w]) {
				tam += dfs(G, w);
			}
		}
		return tam;
	}
public:
	CaminosDFS(Grafo const& g) : visit(g.V(), false), componente(g.V()) {
		for (int v = 0; v < g.V(); v++) {
			if (!visit[v]) {
				int tam = dfs(g, v);
				tam_comp.push_back(tam);
			}
		}
	}
	inline int tam_comv(int v) { return tam_comp[componente[v]]; };
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int p, g;
	cin >> p;
	if (!std::cin)  // fin de la entrada
		return false;
	cin >> g;

	Grafo gr(p);

	for (int i = 0; i < g; i++) {
		int v;
		cin >> v;
		if (v > 0) {
			int x, y;
			cin >> x;

			for (int j = 1; j < v; j++) {
				cin >> y;
				gr.ponArista(x - 1, y - 1);
				x = y;
			}
		}
	}
	// resolver el caso posiblemente llamando a otras funciones

	CaminosDFS c(gr);
	for (int i = 0; i < p; i++) {
		cout << c.tam_comv(i) << " ";
	}
	cout << "\n";
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
