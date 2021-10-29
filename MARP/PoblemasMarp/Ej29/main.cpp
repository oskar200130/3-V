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
#include <limits>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <deque>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Planteando el problema como  una grafo dirigido valorado, en el que los nodos son las casas y las aristas las calles que las unen, la solución se 
 consigue mediante el algoritmo de Dijkstra, sumando la distancia resultante de este algoritmo para las P casas que esperan su paquete ese día. Para la 
 vuelta al origen deberemos realizar otra vez Dijkstra sobre el grafo inverso y sumarle a la solución la distancia a cada una de las casas, que indica
 el coste de volver de cada una, por lo que el coste del algoritmo sería del O(2*C*log(N)+P), siendo C número de calles, N número de casas, y P número 
 de paquetes.

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>
using Camino = std::deque<AristaDirigida<Valor>>;
template <typename Valor>
class Dijkstra {
private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
public:
	Dijkstra(DigrafoValorado<Valor> const& g, int o) : origen(o),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}
	bool hayCamino(int v) const { return dist[v] != INF; }
	Valor distancia(int v) const { return dist[v]; }
};

bool resuelveCaso() {

	// leemos la entrada
	int N, C;
	cin >> N >> C;
	if (!cin)
		return false;

	DigrafoValorado<int> g(N);

	for (int i = 0; i < C; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		g.ponArista(AristaDirigida<int>(x - 1, y - 1, z));
	}

	DigrafoValorado<int> gn = g.inverso();

	int O, P;
	cin >> O >> P;

	Dijkstra<int> dj(g, O - 1);
	Dijkstra<int> djn(gn, O - 1);
	int sol = 0;

	int paq;
	for (int i = 0; i < P; i++) {
		cin >> paq;
		paq--;
		if (sol != -1 && dj.hayCamino(paq) && djn.hayCamino(paq)) {
			sol += dj.distancia(paq);
			sol += djn.distancia(paq);
		}
		else
			sol = -1;
	}
	// leer el resto del caso y resolverlo


	if (sol != -1)
		cout << sol << "\n";
	else
		cout << "Imposible\n";

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
