
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
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
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
