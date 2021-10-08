/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Nombre y Apellidos:
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
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

class MenorAdyacente {
private:
	vector<int> precio;
	int dfs(Grafo const& G, int v, int p) {
		precio[v] = p;
		int min = 0;
		for (int w : G.ady(v)) {
			if (precio[w]==-1 || precio[w] > p) {
				precio[w] = dfs(G, w, p);
				min = precio[w];
			}
			else {
				precio[v] = precio[w];
				min = precio[v];
			}
		}
		return min;
	}
public:
	MenorAdyacente(Grafo const& g) : precio(g.V(), -1) {
	}

	void addSuper(Grafo const& g, int s, int p) {
		dfs(g, s, p);
	}

	int getPrecio(int s)const { return precio[s]; }
};

bool resuelveCaso() {

	// leemos la entrada
	int N, C;
	cin >> N >> C;
	if (!cin)
		return false;

	// leer el resto del caso y resolverlo
	Grafo g(N);

	for (int i = 0; i < C; i++) {
		int x, y;
		cin >> x >> y;
		g.ponArista(--x, --y);
	}

	int casos;
	cin >> casos;


	MenorAdyacente mad(g);

	int x, y;
	for (int i = 0; i < casos; i++) {
		cin >> x >> y;
		mad.addSuper(g, --x, y);
	}

	int consultas;
	cin >> consultas;

	for (int i = 0; i < consultas; i++) {
		cin >> x;
		int min = mad.getPrecio(--x);
		if(min == -1) cout << "MENUDO MARRON\n";
		else cout << min << "\n";
	}

	cout << "---\n";
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
