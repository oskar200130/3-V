
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Digrafo.h" // propios o los de las estructuras de datos de clase
#include <queue>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Sumidero {
public:
	bool sum = false;
	Sumidero(const Digrafo& g, int v) {
		if (g.ady(v).size() == 0) sum = true;
	}
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int vert, aris;

	cin >> vert >> aris;

	if (!std::cin)  // fin de la entrada
		return false;

	Digrafo g(vert);
	vector<int> entrantes(vert, 0);
	vector<int> salidas(vert, 0);
	int e = 0, s = 0;

	for (int i = 0; i < aris; i++) {
		int x, y;
		cin >> x >> y;
		g.ponArista(x, y);
		entrantes[y]++;
		salidas[x]++;
	}
	// resolver el caso posiblemente llamando a otras funciones

	vector<int> sol;
	for (int i = 0; i<entrantes.size(); i++) 
		if (entrantes[i] == vert - 1 && salidas[i] == 0) sol.push_back(i);
	
	bool si = false;
	for (int i : sol) {
		Sumidero o(g, i);
		if (o.sum) cout << "SI " << i << "\n";
		return true;
	}

	if(!si) cout << "NO\n";

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