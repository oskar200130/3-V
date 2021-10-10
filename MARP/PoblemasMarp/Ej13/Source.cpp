
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>
class ManchaMayor {
private:
	vector<vector<bool>> visit;
	int tamMax, numMan, F, C;
	vector<pair<int, int>> dir = { {1,0}, {0,1}, {-1,0}, {0,-1} };
	int dfs(vector<string>& filas, int f, int c) {
		visit[f][c] = true;
		int tam = 1;
		for (auto d : dir) {
			int n = f + d.first, m = c + d.second;
			if (correcta(n, m) && filas[n][m] == '#' && !visit[n][m]) {
				tam += dfs(filas, n, m);
			}
		}
		return tam;
	}

	bool correcta(int f, int c) const { return f >= 0 && f < F&& c >= 0 && c < C; };
public:
	ManchaMayor(vector<string>& filas) : F(filas.size()), C(filas[0].size()), tamMax(0), numMan(0) {
		visit = vector<vector<bool>>(F, vector<bool>(C, false));
		for (int i = 0; i < F; i++) {
			for (int j = 0; j < C; j++) {
				if (!visit[i][j] && filas[i][j] == '#') {
					++numMan;
					tamMax = max(dfs(filas, i, j), tamMax);
				}
			}
		}
	}
	int numManchas() { return numMan; }
	int manchaMayor() { return tamMax; }
};

bool resuelveCaso() {

	// leer los datos de la entrada

	int f, c;

	cin >> f >> c;

	if (!cin)  // fin de la entrada
		return false;

	vector<string> filas(f);
	// resolver el caso posiblemente llamando a otras funciones
	for (string& linea : filas)
		cin >> linea;
	// escribir la soluci�n
	ManchaMayor m(filas);

	cout << m.numManchas() << " " << m.manchaMayor() << "\n";

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

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}