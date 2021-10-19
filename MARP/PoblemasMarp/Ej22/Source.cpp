
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar García Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "ConjuntosDisjuntos.h"  // propios o los de las estructuras de datos de clase
#include <string>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class MapaPetroleo {
private:
	ConjuntosDisjuntos cd;
	vector<pair<int, int>> dir = { {1,0}, {1,1}, {1,-1}, {0,1}, {-1,0}, {-1,1}, {-1,-1}, {0,-1} };
	int max;
	int colum;
public:
	MapaPetroleo(vector<string>& mapa) : colum(mapa[0].size()), cd(mapa.size()* mapa[0].size()), max(0) {
		recorrido(mapa);
	}

	void recorrido(vector<string>& mapa) {
		for (int i = 0; i < mapa.size(); i++) {
			for (int j = 0; j < colum; j++) {
				if (mapa[i][j] == '#') {
					for (auto a : dir) {
						int x = i + a.first;
						int y = j + a.second;
						if (x > 0 && x < mapa.size() && y>0 && y < colum && mapa[x][y] == '#') {
							cd.unir(i * colum + j, x * colum + y);
							if (cd.cardinal(i * colum + j) > max) max = cd.cardinal(i * colum + j);
						}
					}
				}
			}
		}
	}

	void addMancha(vector<string>& m, int x, int y) {
		for (auto a : dir) {
			int x2 = x + a.first;
			int y2 = y + a.second;
			if (x2 > 0 && x2 < m.size() && y2>0 && y2 < colum && m[x2][y2] == '#') {
				cd.unir(x * colum + y, x2 * colum + y2);
				if (cd.cardinal(x * colum + y) > max) max = cd.cardinal(x * colum + y);
			}
		}
	}

	int getMax() const { return max; };
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int f, c;
	cin >> f >> c;
	cin.get();

	if (!std::cin)  // fin de la entrada
		return false;

	vector<string> lines(f);

	for (int i = 0; i < f; i++) {
		getline(cin, lines[i]);
	}
	// resolver el caso posiblemente llamando a otras funciones

	MapaPetroleo m(lines);
	cout << m.getMax() << "\n";
	// escribir la solución

	int num;
	cin >> num;

	for (int i = 0; i < num; i++) {
		int x, y;
		cin >> x >> y;
		m.addMancha(lines, --x, --y);
		cout << m.getMax() << "\n";
	}

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

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
