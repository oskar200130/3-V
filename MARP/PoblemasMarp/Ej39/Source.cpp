
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
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
struct Cordel {
	int l;
	int val;
};

int64_t numFormas(vector<Cordel> c, int L) {
	vector<int64_t> cant(L+1, 0);
	for (int i = 0; i < c.size(); i++) {
		cant[0] = 1;
		for (int j = L; j >= c[i].l; j--) {
			cant[j] += cant[j - c[i].l];
		}
	}

	return cant[L];
}

EntInf minCuerdPos(vector<Cordel> c, int L) {
	vector<EntInf> cant(L + 1, Infinito);
	for (int i = 0; i < c.size(); i++) {
		cant[0] = 0;
		for (int j = L; j >= c[i].l; j--) {
			cant[j] = min(cant[j], cant[j - c[i].l] + 1);
		}
	}

	return cant[L];
}

EntInf minCoste(vector<Cordel> c, int L) {
	vector<EntInf> coste(L + 1, Infinito);
	for (int i = 0; i < c.size(); i++) {
		coste[0] = 0;
		for (int j = L; j >= c[i].l; j--) {
			coste[j] =min(coste[j], coste[j - c[i].l] + c[i].val);
		}
	}

	return coste[L];
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int N, L;

	cin >> N >> L;

	if (!cin)  // fin de la entrada
		return false;

	vector<Cordel> cordeles(N);
	for (int i = 0; i < N; i++) {
		Cordel aux;
		cin >> aux.l >> aux.val;
		cordeles[i] = aux;
	}
	// resolver el caso posiblemente llamando a otras funciones

	int64_t numF = numFormas(cordeles, L);

	if (numF > 0) 
		cout << "SI " << numF << " " << minCuerdPos(cordeles, L) << " " << minCoste(cordeles, L) << " \n";
	else
		cout << "NO\n";
	// escribir la solución

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
