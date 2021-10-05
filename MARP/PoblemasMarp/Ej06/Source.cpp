// Oscar García
// MARP21


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

struct Tarea {
	int ini, fin, rep;
};
inline bool operator<(const Tarea& a, const Tarea& b)  {
	return b.ini < a.ini;
}

// función que resuelve el problema
bool resolver(priority_queue<Tarea> agenda, int t) {
	int finUlt = 0;
	bool solapa = false;
	while (!solapa && !agenda.empty() && agenda.top().ini < t) {
		Tarea u = agenda.top();
		if (agenda.top().ini < finUlt)
			solapa = true;
		agenda.pop();

		if (u.rep != 0)
			agenda.push({ u.ini + u.rep, u.fin + u.rep, u.rep });
		finUlt = u.fin;
	}

	return solapa;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada

	priority_queue<Tarea> agenda;

	int tNoP, tP, t;
	cin >> tNoP;
	if (!cin)
		return false;

	cin >> tP >> t;

	for (int i = 0; i < tNoP; i++) {
		int ini, fin;
		cin >> ini >> fin;
		agenda.push({ ini, fin, 0 });
	}
	for (int i = 0; i < tP; i++) {
		int ini, fin, repe;
		cin >> ini >> fin >> repe;
		agenda.push({ ini, fin, repe });
	}

	// escribir sol
	resolver(agenda, t) ? cout << "SI\n" : cout << "NO\n";

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