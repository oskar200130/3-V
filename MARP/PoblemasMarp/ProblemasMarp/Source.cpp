// Oscar García

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Arbin.h"
#include "List.h"

using namespace std;
// función que resuelve el problema
bool resolver(Arbin<int> datos) {
	List<int>* in = datos.inorden();
	bool avl = true;
	
	if (!in->empty()) {
		int pre = in->front();
		cout << pre;
		in->pop_front();
		while (avl && !in->empty()) {
			if (pre >= in->front()) avl = false;
		}
	}
	else avl = true;

	return avl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	Arbin<int> arbol;
	arbol = arbol.leerArbol(-1);

	if (arbol.esAVL()) cout << "SI\n";
	else cout << "NO\n";
	// escribir sol
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	ifstream in("datos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}