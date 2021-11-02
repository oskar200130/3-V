
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
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

bool resuelveCaso() {

	// leer los datos de la entrada
	int n;
	cin >> n;

	if (!cin)  // fin de la entrada
		return false;

	vector<int> ciudades(n);
	vector<int> defensas(n);

	for (int i = 0; i < n; i++)
		cin >> ciudades[i];
	for (int i = 0; i < n; i++)
		cin >> defensas[i];

	sort(ciudades.begin(), ciudades.end());
	sort(defensas.begin(), defensas.end());
	// resolver el caso posiblemente llamando a otras funciones

	int defensor = 0, wins = 0;
	for (int i = 0; i < n && defensor < n; i++) {
		if (ciudades[i] <= defensas[defensor]) 
			wins++;
		else
			i--;
		defensor++;
	}

	// escribir la solución
	cout << wins << "\n";

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
