
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

	// escribir la soluci�n
	cout << numTun << "\n";
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
