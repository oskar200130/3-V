
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"
using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

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
	int N = 0;
	cin >> N;
	if (N == 0)  // fin de la entrada
		return false;

	PriorityQueue<int64_t> q;
	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < N; i++) {
		int64_t x;
		cin >> x;
		q.push(x);
	}

	int64_t cont = 0;

	while (q.size() > 1) {
		int64_t a = q.top();
		q.pop();
		a += q.top();
		cont += a;
		q.pop();
		q.push(a);
	}

	cout << cont << "\n";
	// escribir la solución

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
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
