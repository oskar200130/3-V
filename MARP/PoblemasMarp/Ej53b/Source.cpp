
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*@ <answer>

La funcion numTrim(i,j) devuelve el número de llamadas que se deben hacer a trim para que la palabra de la letra i hasta j pase a ser "".
La llamada base será numTrim(0, n). (n siendo el tamaño de la palabra)

				|numTrim(i + 1, j)									si Ci == Ci + 1
numTrim(i, j) = {numTrim(i, j - 1)									si Cj == Cj - 1
				|numTrim(i + 1, j -1)								si Ci != Ci + 1 && Cj != Cj - 1 && Ci == Cj 
				|numTin(numTrim(i + 1, j), numTrim(i, j - 1)) + 1	si Ci != Ci + 1 && Cj != Cj - 1 && Ci != Cj && i < j

Caso Base: numTrim(i, i) = 1                            +-+-+-+
														|1| <*|
														+-+-/∨+
														| |1| |
														+-+-+-+	  ∨, < y / son flechas que indican las casillas necesarias para obtener el valor de *
														| | |1|	  Es posible la reducción de memoria a dos vectores, ya que solo son necesarios valores
														+-+-+-+	  de la fila inferior y de la misma. Para esto será necesario recorrer la matriz de abajo a 
																  arriba y de izquierda a derecha.

Coste en tiempo: O(n*n) siendo n el tamaño de la palabra.
Coste en espacio adicional: O(n) ya que solo harán falta dos vectores de tamaño n.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

	// leer los datos de la entrada
	string p;
	cin >> p;

	if (!cin)  // fin de la entrada
		return false;

	vector<int> actual(p.size(), 1);
	vector<int> anterior(p.size(), 1);

	// resolver el caso posiblemente llamando a otras funciones
	for (int i = p.size() - 1; i >= 0; i--) {
		for (int j = i + 1; j < p.size(); j++) {
			if (p[i] == p[i + 1])
				actual[j] = anterior[j];
			else if (p[j] == p[j - 1])
				actual[j] = actual[j - 1];
			else if (p[i] == p[j])
				actual[j] = anterior[j - 1] + 1;
			else
				actual[j] = min(anterior[j], actual[j - 1]) + 1;
		}
		anterior = actual;
	}

	// escribir la solución
	cout << actual[p.size() - 1] << "\n";

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
