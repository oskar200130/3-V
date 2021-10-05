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
using namespace std;

#include <queue>  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Creando el struc grupo que almacena el número de músicos de cada grupo y las partituras asignadas
 podemos comprobar que grupo tiene mayor número de músicos por partitura, pudiendo asignarle a
 este una más en caso de que sobren o pudiendo calcular el mayor grupo si están todas repartidas.

 Siendo P el número de partituras menos el número de grupos y N el tamaño de la cola
 tendría un coste de P*log(N)

 @ </answer> */

 // =======================================================================
 // Escribe el código completo de tu solución aquí debajo, tras la etiqueta
 // =======================================================================
 //@ <answer>

struct Grupo {
	int musicos;
	float musPP, partituras;

	bool operator<(const Grupo& a) const {
		return this->musPP < a.musPP;
	}
};
bool resuelveCaso() {

	// leemos la entrada
	int P, N;
	cin >> P >> N;
	if (!cin) return false;

	priority_queue<Grupo> musicos;
	for (int i = 0; i < N; i++) {
		Grupo g;
		cin >> g.musicos;
		g.partituras = 1;
		g.musPP = g.musicos;
		musicos.push(g);
	}

	P -= N;
	for (int i = 0; i < P; i++) {
		Grupo x = musicos.top();
		musicos.pop();
		x.partituras++;
		x.musPP = x.musicos / x.partituras;
		musicos.push(x);
	}

	// leer el resto del caso y resolverlo

	if (!musicos.empty()) {
		int res = musicos.top().musicos / musicos.top().partituras;
		if (musicos.top().musicos % (int)musicos.top().partituras > 0) res++;
		cout << res << "\n";
	}
	else
		cout << "0\n";

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