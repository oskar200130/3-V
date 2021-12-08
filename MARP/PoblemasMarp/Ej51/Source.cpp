
/*@ <answer>
 *
 * Nombre y Apellidos:Oscar Garc�a Castro
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "EnterosInf.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>
struct Casilla {
	EntInf v;
	vector<int> canti;
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int N;
	cin >> N;

	if (!cin)  // fin de la entrada
		return false;

	vector<int> valores(N);
	vector<int> cantidades(N);

	for (int i = 0; i < N; i++) {
		cin >> valores[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> cantidades[i];
	}

	int P;
	cin >> P;

	vector<Casilla> tabla(P + 1);
	vector<Casilla> anterior(P + 1, { Infinito, cantidades });

	// resolver el caso posiblemente llamando a otras funciones
	for (int i = 0; i < N; i++) {
		//for (int k = 0; k < cantidades[i]; k++) {

		anterior[0].v = 0;
		anterior[0].canti = cantidades;
		tabla[0] = anterior[0];
		for (int j = valores[i]; j <= P; j++) {
			if (valores[i] <= j && anterior[j].canti[i] > 0) {
				if (anterior[j].v < anterior[j - valores[i]].v + 1 && anterior[j].v < tabla[j - valores[i]].v + 1) {
					tabla[j] = anterior[j];
				}
				else {
					if (tabla[j - valores[i]].canti[i] <= 0 || anterior[j - valores[i]].v < tabla[j - valores[i]].v) 
						tabla[j] = anterior[j - valores[i]];
					else 
						tabla[j] = tabla[j - valores[i]];
					
					tabla[j].v = tabla[j].v + 1;
					tabla[j].canti[i]--;
				}
			}
		}
		anterior = tabla;
		//}
	}

	// escribir la soluci�n
	if (tabla[P].v != Infinito)
		cout << "SI " << tabla[P].v << "\n";
	else
		cout << "NO\n";

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
