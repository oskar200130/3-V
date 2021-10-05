// Oscar García
// MARP21


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Pares {
	int gr, peq;
};

// función que resuelve el problema
void resolver(priority_queue<int>* grandes, priority_queue<int>* pequenas, int cantD) {
	vector<Pares> drones;
	while (!pequenas->empty() && !grandes->empty()) {
		int horas = 0;
		for (int i = 0; i < cantD; i++) {
			if (!pequenas->empty() && !grandes->empty()) {
				int g, p;
				g = grandes->top();
				p = pequenas->top();
				drones.push_back({ g, p });
				grandes->pop();
				pequenas->pop();
			}
		}
		while (!drones.empty()) {
			Pares p = drones.back();
			drones.pop_back();
			p.gr < p.peq ? horas += p.gr : horas += p.peq;
			if (p.gr > p.peq)
				grandes->push(p.gr - p.peq);
			else if (p.gr < p.peq)
				pequenas->push(p.peq - p.gr);
		}
		cout << horas << " ";
	}
	cout << "\n";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int drones;
	cin >> drones;

	if (!cin)
		return false;

	priority_queue<int> grandes, pequenas;
	int peq, gran, x;

	cin >> gran >> peq;

	for (int i = 0; i < gran; i++) {
		cin >> x;
		grandes.push(x);
	}
	for (int i = 0; i < peq; i++) {
		cin >> x;
		pequenas.push(x);
	}

	resolver(&grandes, &pequenas, drones);

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