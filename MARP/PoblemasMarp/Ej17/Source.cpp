
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "Digrafo.h" // propios o los de las estructuras de datos de clase
#include <queue>

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>
const int MAX = 10000;

int adyacente(int v, int i) {
	switch (i)
	{
	case(0): return (v + 1) % MAX;
		break;
	case(1): return (v * 2) % MAX;
		break;
	case(2): return v / 3;
		break;
	}
 }

int bfs(int origen, int destino) {
	if (origen == destino) return 0;
	vector<int> distancia(MAX, -1);
	distancia[origen] = 0;
	queue<int> cola;
	cola.push(origen);

	while (!cola.empty()) {
		int v = cola.front();
		cola.pop();
		for (int i = 0; i < 3; i++) {
			int w = adyacente(v, i);
			if (distancia[w] == -1) {
				distancia[w] = distancia[v]+1;
				if (w == destino) return distancia[w];
				else cola.push(w);
			}
		}
	}
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int ori, dest;

	cin >> ori >> dest;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones

	cout << bfs(ori, dest) << "\n";

	// escribir la soluci�n

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
