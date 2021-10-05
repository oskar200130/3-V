// Oscar García
// MARP21


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
void ordena(priority_queue<int>& menores, priority_queue<int, vector<int>, greater<int>>& mayores) {
	if (mayores.size() > menores.size()) {
		menores.push(mayores.top());
		mayores.pop();
	}
	else if (menores.size() > mayores.size() + 1) {
		mayores.push(menores.top());
		menores.pop();
	}
}
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int acciones;
	cin >> acciones;
	if (!cin)
		return false;
	priority_queue<int> menores;
	priority_queue<int, vector<int>, greater<int>> mayores;

	while (acciones > 0) {
		int x;
		cin >> x;
		if (x == 0) {
			if (menores.empty()) {
				cout << "ECSA ";
			}
			else {
				cout << menores.top() << " ";
				menores.pop();
				ordena(menores, mayores);
			}
		}
		else if (menores.empty()) {
			menores.push(x);
		}
		else if (!menores.empty() && x < menores.top()) {
			menores.push(x);
			ordena(menores, mayores);
		}
		else {
			mayores.push(x);
			ordena(menores, mayores);
		}
		acciones--;
	}
	cout << "\n";
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