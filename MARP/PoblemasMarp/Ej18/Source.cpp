
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Digrafo.h" // propios o los de las estructuras de datos de clase
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

class OrdenTopologico {
private:
	deque<int> orden;
	vector<bool> visit;
	vector<bool> camino;
	public:
	OrdenTopologico(const Digrafo& g, int v) : visit(v, false), camino(v, false) {
		for (int i = 0; i < v; i++) {
			if(!visit[i])
				dfs(g, i);
		}
	}

	deque<int> getOrden() const { return orden; };

	int dfs(const Digrafo& g, int v) {
		visit[v] = true;
		camino[v] = true;
		for (int w : g.ady(v)) {
			if (!visit[w]) {
				visit[w] = camino[w] = true;
				dfs(g, w);
				camino[w] = false;
			}
			else if(camino[w]) {
				for (int o : orden) orden.pop_front();
				return -1;
			}
		}
		orden.push_back(v);
		camino[v] = false;
		return 0;
	}
};


bool resuelveCaso() {

	// leer los datos de la entrada
	int tareas, depen;

	cin >> tareas >> depen;

	if (!std::cin)  // fin de la entrada
		return false;

	Digrafo g(tareas);
	for (int i = 0; i < depen; i++) {
		int x, y;
		cin >> x >> y;
		g.ponArista(--y, --x);
	}
	// resolver el caso posiblemente llamando a otras funciones

	OrdenTopologico o(g, tareas);

	deque<int> sol = o.getOrden();
	if (sol.size() == tareas) {
		for (int i : sol) {
			cout << sol.front()+1 << " ";
			sol.pop_front();
		}
		cout << "\n";
	}
	else
		cout << "Imposible\n";

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