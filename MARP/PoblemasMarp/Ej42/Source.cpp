
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

int numCaminos(vector<vector<char>> c, int n, int m) {
	vector<int> cant(m);
	cant[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (c[i][j] == 'P')
				cant[j] = 0;
			else if (j > 0)
				cant[j] += cant[j - 1];
		}
	}
	return cant[m - 1];
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int n, m;

	cin >> n >> m;

	if (!cin)  // fin de la entrada
		return false;

	vector<vector<char>> a(n);

	for (int i = 0; i < n; i++) {
		vector<char> s(m);
		for (int j = 0; j < m; j++) {
			cin >> s[j];
		}
		a[i] = s;
	}

	// resolver el caso posiblemente llamando a otras funciones
	cout << numCaminos(a, n, m) << "\n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("casos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
