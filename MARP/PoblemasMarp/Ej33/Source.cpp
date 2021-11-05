
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
struct Pelicula {
	int ini;
	int fin;
	bool operator<(Pelicula b) { return this->fin < b.fin; };
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int n;
	cin >> n;

	if (n == 0)  // fin de la entrada
		return false;

	vector<Pelicula> cartelera(n);

	int h, min, dur;
	char c;

	for (int i = 0; i < n; i++) {
		Pelicula aux;
		cin >> h >> c >> min >> dur;
		aux.ini = h * 60 + min;
		aux.fin = aux.ini + dur + 10;
		cartelera[i] = aux;
	}

	sort(cartelera.begin(), cartelera.end());

	// resolver el caso posiblemente llamando a otras funciones
	int cont = 1, horaOc = cartelera[0].fin;

	for (int i = 1; i < n; i++) {
		if (cartelera[i].ini >= horaOc) {
			cont++;
			horaOc = cartelera[i].fin;
		}
	}

	cout << cont << "\n";
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
