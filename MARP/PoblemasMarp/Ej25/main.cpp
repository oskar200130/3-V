/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Nombre y Apellidos:Oscar García Castro
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
using namespace std;


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
	Valor coste;
	int numAe;
public:
	Valor costeARM() const {
		return coste;
	}

	int getNumAe() const { 
		return numAe; 
	}

	ARM_Kruskal(GrafoValorado<Valor> const& g, int av) : coste(0), numAe(0) {
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		ConjuntosDisjuntos cjtos(g.V());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w) && a.valor() < av) {
				cjtos.unir(v, w);
				coste += a.valor();
			}
		}
		coste += cjtos.num_cjtos() * av;
		numAe = cjtos.num_cjtos();
	}
};

bool resuelveCaso() {

	// leemos la entrada
	int N, M, A;
	cin >> N >> M >> A;
	if (!cin)
		return false;

	// leer el resto del caso y resolverlo
	GrafoValorado<int> g(N);

	for (int i = 0; i < M; i++) {
		int x, y, c;
		cin >> x >> y >> c;
		g.ponArista(Arista<int>(--x, --y, c));
	}

	ARM_Kruskal<int> kr(g, A);

	cout << kr.costeARM() << " " << kr.getNumAe() << "\n";
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

	// Resolvemos
	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
