
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

bool resuelveCaso() {

	// leer los datos de la entrada
	int n;
	cin >> n;

	if (n == 0)  // fin de la entrada
		return false;

	vector<int> horasFin(n);

	int h, min;
	char c;

	for (int i = 0; i < n; i++) {
		cin >> h >> c >> min;
		horasFin[i] = h * 60 + min + 10;
	}

	sort(horasFin.begin(), horasFin.end());

	// resolver el caso posiblemente llamando a otras funciones
	int eq = n;
	int eqInd = 0;
	for (int i = 0; i < n && eqInd < m; i++) {
		if (jugadores[i] == equipaciones[eqInd] || jugadores[i] == equipaciones[eqInd] - 1) {
			eq--;
			eqInd++;
		}
		else if (jugadores[i] > equipaciones[eqInd]) {
			eqInd++;
			i--;
		}
	}

	// escribir la soluci�n
	cout << eq << "\n";

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
