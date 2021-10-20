
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>
class ARM_Kruskal {
private:
	std::vector<Arista<Valor>> _ARM;
	ConjuntosDisjuntos cjtos;
	bool conected;
public:
	Valor costeARM() const {
		return coste;
	}
	std::vector<Arista<Valor>> const& ARM() const {
		return _ARM;
	}
	bool isConexo() const { return conected; };

	ARM_Kruskal(GrafoValorado<Valor> const& g) : cjtos(g.V()), conected(false) {
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				cjtos.unir(v, w);
				_ARM.push_back(a); 
				if (_ARM.size() == g.V() - 1) break;
			}
		}
	}
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int v;
	cin >> v;

	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<int> g(v);

	int c;
	cin >> c;

	for (int i = 0; i < c; i++) {
		int o, d, anch;
		cin >> o >> d >> anch;
		g.ponArista(Arista<int>(o, d, anch));
	}
	// resolver el caso posiblemente llamando a otras funciones

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
