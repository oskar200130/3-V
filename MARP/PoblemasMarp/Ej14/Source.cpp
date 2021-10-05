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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>
class CaminosDFS {
private:
	std::vector<bool> visit; // visit[v] = �hay camino de s a v?
	//std::vector<int> ant; // ant[v] = �ltimo v�rtice antes de llegar a v
	int s; // v�rtice origen
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
