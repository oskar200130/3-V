/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Nombre y Apellidos: Oscar Garcia Castro
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <queue>// propios o los de las estructuras de datos de clase
#include <stack>
#include <string>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

 // =======================================================================
 // Escribe el código completo de tu solución aquí debajo, tras la etiqueta
 // =======================================================================
 //@ <answer>

struct comparador {
	bool operator()(const stack<int>& a, const stack<int>& b) {
		return a.top() > b.top();
	};
};


bool resuelveCaso() {

	// leemos la entrada
	int N;
	cin >> N;
	if (!cin) return false;

	// leer el resto del caso y resolverlo
	priority_queue<stack<int>, vector<stack<int>>, comparador> comics;
	int minId = 0;
	for (int i = 0; i < N; i++) {
		int tam;
		cin >> tam;
		stack<int> pila;
		while (tam > 0) {
			int id;
			cin >> id;
			if (minId == 0 || id < minId) 
				minId = id;
			pila.push(id);
			tam--;
		}
		comics.push(pila);
	}

	int cont = 1;
	bool found = false;

	while (!found && !comics.empty()) {
		if (comics.top().top() == minId) 
			found = true;
		else {
			stack<int> u = comics.top();
			comics.pop();
			u.pop();
			if (!u.empty()) 
				comics.push(u);
			
			cont++;
		}
	}

	if (found) cout << to_string(cont) + "\n";

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
