
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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
struct Edificio {
	int ini, fin;
	bool operator<(Edificio b) { return this->fin < b.fin; };
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int edificios;
	cin >> edificios;

	if (edificios == 0)
		return false;

	vector<Edificio> playa;

	for (int i = 0; i < edificios; i++) {
		Edificio aux;
		cin >> aux.ini >> aux.fin;
		playa.push_back(aux);
	}

	sort(playa.begin(), playa.end());

	int numTun = 0, lastTun = -1;

	for (int i = 0; i < edificios; i++) {
		if (playa[i].ini > lastTun) {
			lastTun = playa[i].fin - 1;
			numTun++;
		}
	}
	// resolver el caso posiblemente llamando a otras funciones

	// escribir la solución
	cout << numTun << "\n";
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
