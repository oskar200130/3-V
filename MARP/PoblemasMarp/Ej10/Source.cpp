/*
 * MUY IMPORTANTE: Solo se corregir�n los comentarios y el c�digo
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificaci�n fuera de esas etiquetas no ser� corregida.
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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Creando el struc grupo que almacena el n�mero de m�sicos de cada grupo y las partituras asignadas
 podemos comprobar que grupo tiene mayor n�mero de m�sicos por partitura, pudiendo asignarle a
 este una m�s en caso de que sobren o pudiendo calcular el mayor grupo si est�n todas repartidas.

 Siendo P el n�mero de partituras menos el n�mero de grupos y N el tama�o de la cola
 tendr�a un coste de P*log(N)

 @ </answer> */

 // =======================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo, tras la etiqueta
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
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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