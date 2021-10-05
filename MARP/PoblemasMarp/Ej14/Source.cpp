/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Grafos.cpp"

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
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	//std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
	int s; // vértice origen
	int vis;
	int per;
	void dfs(Grafo const& G, int v) {
		visit[v] = true;
		for (int w : G.ady(v)) {
			if (!visit[w]) {
				if (w < per) vis++;
				dfs(G, w);
			}
		}
	}
public:
	CaminosDFS(Grafo const& g, int s, int p) : visit(g.V(), false),
		s(s), vis(1), per(p) {
		dfs(g, s);
	}
	inline int getNumVis() const { return vis; }
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int p, g;
	cin >> p;
	if (!std::cin)  // fin de la entrada
		return false;
	cin >> g;

	Grafo* gr = new Grafo(p + g);

	for (int i = 0; i < g; i++) {
		int v;
		cin >> v;
		for (int j = 0; j < v; j++) {
			int x;
			cin >> x;
			if (x == 1)
				cout << "";
			gr->ponArista(--x, p + i);
		}
	}
	// resolver el caso posiblemente llamando a otras funciones

	for (int i = 0; i < p; i++) {
		CaminosDFS* c = new CaminosDFS(*gr, i, p);
		cout << c->getNumVis() << " ";
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
