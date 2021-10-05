//Recorrer para saber si es conexo y luego A=V-1 para ver ciclos(o comprobar si se ha visitado 2 veces un v�rtice distinto de su padre)


/*@ <answer>

  Nombre y Apellidos:

 @ </answer> */

#include <iostream>
#include <fstream>
#include "Grafos.cpp"
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
class CaminosDFS {
private:
	std::vector<bool> visit; // visit[v] = �hay camino de s a v?
	//std::vector<int> ant; // ant[v] = �ltimo v�rtice antes de llegar a v
	int s; // v�rtice origen
	int vis;
	void dfs(Grafo const& G, int v) {
		visit[v] = true;
		for (int w : G.ady(v)) {
			if (!visit[w]) {
				vis++;
				dfs(G, w);
			}
		}
	}
public:
	CaminosDFS(Grafo const& g, int s) : visit(g.V(), false),
		s(s), vis(1) {
		dfs(g, s);
	}
	inline bool isConexo() { return vis==visit.size(); }
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int v;
	cin >> v;

	if (!std::cin)  // fin de la entrada
		return false;

	Grafo* gr = new Grafo(v);

	int a;
	cin >> a;
	for (int i = 0; i < a; i++) {
		int x, y;
		cin >> x >> y;
		gr->ponArista(x, y);
	}
	// resolver el caso posiblemente llamando a otras funciones
	CaminosDFS c(*gr, 0);
	if (c.isConexo() && a == v - 1) cout << "SI\n";
	else cout << "NO\n";
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
