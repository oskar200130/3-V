/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Nombre y Apellidos: Oscar García Castro
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "Matriz.h"
using namespace std;


/*@ <answer>

 Sol(i, j) = Longitud de la mayor subsecuencia entre las palabras X, de longitud i, e Y, de longitud j.
		 
 Sol(i,j){	Sol(i-1, j-1)					si X[i] == Y[j]
		 {	max(Sol(i-1, j), Sol(i, j-1)	si X[i] =/= Y[j]

Casos base:												+-+-+-+-+
	Sol(0, j) = 0										|0| | |0|
	Sol(i, 0) = 0										+-+-+-+-+
														| | | | |
														+-+-+-\^+	^, < y \ son flechas que indican las casillas necesarias para obtener el valor de * 
														|0| | <*|	No es posible la reducción de memoria ya que para la reconstrucción necesitas los valores
														+-+-+-+-+	por lo que el coste en memoria seria de O(n*m)

El coste en tiempo del algoritmo es O(n*m) siendo n la longitud de la primera palabra y m la longitud de la segunda.
 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

string subsecuencia(string x, string y) {
	int n = x.size(), m = y.size();
	Matriz<int> mat(n + 1, m + 1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (x[i - 1] == y[j - 1])
				mat[i][j] = mat[i - 1][j - 1] + 1;
			else
				mat[i][j] = max(mat[i - 1][j], mat[i][j - 1]);
		}
	}

	int c = mat[n][m];
	string sol;

	if (c != 0) {
		int i = n, j = m;
		while (i > 0 && j > 0) {
			if (x[i - 1] == y[j - 1] && mat[i][j] == mat[i - 1][j - 1] + 1) {
				sol.push_back(x[i - 1]);
				c--;
				j--;
				i--;
			}
			else if (mat[i][j] == mat[i - 1][j])
				--i;
			else if (mat[i][j] == mat[i][j - 1])
				--j;
		}
	}
	string aux = sol;
	for (int i = 0; i < sol.size(); i++)
		sol[i] = aux[mat[n][m] - 1 - i];

	return sol;
}


bool resuelveCaso() {

	// leemos la entrada
	string X, Y;
	cin >> X >> Y;

	if (!cin)
		return false;

	// resolver el caso
	cout << subsecuencia(X, Y) << "\n";

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
