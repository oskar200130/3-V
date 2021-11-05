/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Nombre y Apellidos:
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

 Escribe también una demostración que justifique que tu solución encuentra
 siempre soluciones óptimas.

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>



bool resuelveCaso() {

	// leemos la entrada
	int N;
	cin >> N;  // número de partidos

	if (N == 0) {
		return false;
	}

	vector<int> rival(N);
	vector<int> boston(N);

	// leer el resto del caso y resolverlo
	for (int i = 0; i < N; i++) {
		cin >> rival[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> boston[i];
	}

	sort(rival.begin(), rival.end());
	sort(boston.begin(), boston.end());

	int max = 0;
	for (int i = 0; i < N; i++) {
		if (boston[N - i - 1] - rival[i] > 0)
			max += boston[N - i - 1] - rival[i];
	}

	cout << max << "\n";

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

	// Resolvemos
	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
