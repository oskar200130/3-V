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

#include "Digrafo.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 La solución crea un grafo en el que los vértices son las instrucciones+1, que indica que el programa acaba. En caso de que no hay ninguna arista a este último 
 no haría falta recorrer el grafo. Si hay, se hace un recorrido en profundidad, en caso de que se marque el último vértice como visitado es que acaba, y si no se 
 encuentran ciclos es que acaba siempre, si no es solo a veces. Siendo V el número de instrucciones+1 y A el de aristas(V+número de saltos condicionales),
 el programa tendría una complejidad de O(V+A).

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


class CuandoTermina {
private:
	vector<bool> visit;
	vector<bool> cam;
	int ult;
	bool siempre = true;
public:
	CuandoTermina(const Digrafo& g, int v) :visit(v, false), cam(v, false), ult(v - 1) {
		dfs(g, 0);
	}

	void dfs(const Digrafo& g, int v) {
		visit[v] = cam[v] = true;
		for (int w : g.ady(v)) {
			if (!visit[w]) {
				dfs(g, w);
			}
			else if (cam[w]) {
				siempre = false;
			}
		}
		cam[v] = false;
	}

	bool siemperAcab() const { return siempre; };
	bool acaba() const { return visit[ult]; };
};

bool resuelveCaso() {

	// leemos la entrada
	int L;
	cin >> L;
	if (!cin)
		return false;

	// leer el resto del caso y resolverlo

	Digrafo g(L + 1);
	bool fin = false;
	for (int i = 0; i < L; i++) {
		char inst;
		cin >> inst;
		int next = i + 1;

		if (inst == 'C') {
			g.ponArista(i, next);
			if (next == L)
				fin = true;
			cin >> next;
			next--;
		}
		else if (inst == 'J') {
			cin >> next;
			next--;
		}
		g.ponArista(i, next);
		if (next == L) fin = true;
	}

	if (fin) {
		CuandoTermina c(g, L + 1);
		if (c.acaba() && c.siemperAcab()) cout << "SIEMPRE\n";
		else if (c.acaba()) cout << "A VECES\n";
		else cout << "NUNCA\n";
	}
	else
		cout << "NUNCA\n";
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
