// Oscar García
// VJ19


#include <iostream>
#include <iomanip>
#include <fstream>
#include "PriorityQueue.h"

using namespace std;

struct Usuario {
	int id;
	int periodo;
	int vez;
	inline bool operator<(const Usuario& x) const {
		return this->vez < x.vez || (this->vez == x.vez && this->id < x.id);
	}
};

// función que resuelve el problema
void resolver(PriorityQueue<Usuario> list, int k) {
	for (int i = 0; i < k; i++) {
		Usuario x = list.top();
		cout << x.id << "\n";
		x.vez += x.periodo;
		list.pop();
		list.push(x);
	}
	cout << "---\n";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int pac = 0;
	cin >> pac;

	if (pac == 0)
		return false;

	PriorityQueue<Usuario> list;

	Usuario u;
	for (int i = 0; i < pac; i++) {
		cin >> u.id;
		cin >> u.periodo;
		u.vez = u.periodo;
		list.push(u);
	}

	int k;
	cin >> k;

	resolver(list, k);

	// escribir sol


	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	ifstream in("datos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}