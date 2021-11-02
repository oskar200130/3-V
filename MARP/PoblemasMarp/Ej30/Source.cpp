
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
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
	int n, l;
	cin >> n >> l;

	if (!cin)  // fin de la entrada
		return false;

	vector<int> dist(n);
	for (int i = 0; i < n; i++) {
		cin >> dist[i];
	}

	// resolver el caso posiblemente llamando a otras funciones
	int parches = 1;
	int ultParc = dist[0]+l;

	for (int i = 1; i < n; i++) {
		if (ultParc < dist[i]) {
			parches++;
			ultParc = dist[i] + l;
		}
	}
	// escribir la soluci�n

	cout << parches << "\n";

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
