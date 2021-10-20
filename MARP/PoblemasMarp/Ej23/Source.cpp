
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
