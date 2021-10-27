
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <limits>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <deque>
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
using Camino = deque<AristaDirigida<Valor>>;
template <typename Valor>
class Dijkstra {
private:
	const Valor INF = numeric_limits<Valor>::max();
	int origen;
	vector<pair<Valor, Valor>> dist;
	vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w].second > dist[v].second + a.valor()) {
			dist[w].second = dist[v].second + a.valor();
			ulti[w] = a;
			pq.update(w, dist[w].second);
			dist[w].first = dist[v].first;
		}
		else if (dist[w].second == dist[v].second + a.valor())
			dist[w].first += dist[v].first;
	}
public:
	Dijkstra(DigrafoValorado<Valor> const& g) : origen(0),
		dist(g.V(), std::make_pair(INF, INF)), ulti(g.V()), pq(g.V()) {
		dist[origen].first = 1;
		dist[origen].second = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}
	bool hayCamino(int v) const { return dist[v].first != INF; }
	Valor distancia(int v) const { return dist[v].second; }
	int caminos(int v) const { return dist[v].first; }
	Camino<Valor> camino(int v) const {
		Camino<Valor> cam;
		// recuperamos el camino retrocediendo
		AristaDirigida<Valor> a;
		for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
			cam.push_front(a);
		cam.push_front(a);
		return cam;
	}
};

bool resuelveCaso() {

	int n;
	cin >> n;

	if (!cin)  // fin de la entrada
		return false;

	DigrafoValorado<int> g(n);

	int m;
	cin >> m;

	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		g.ponArista(AristaDirigida<int>(x - 1, y - 1, z));
		g.ponArista(AristaDirigida<int>(y - 1, x - 1, z));
	}
	Dijkstra<int> d(g);
	// escribir la solución

	if (d.hayCamino(n - 1))
		cout << d.caminos(n - 1) << "\n";
	else
		cout << "0\n";
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
