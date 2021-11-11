/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Nombre y Apellidos: Oscar García Castro
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Escribe también una demostración que justifique que tu solución encuentra
 siempre soluciones óptimas.



 Suponemos que el vector de esquiadores está ordenado de forma que i<=j => E[i]<=E[j].
 El algoritmo voraz propuesto tomará los esquiadores de los extremos, emparejando al menor disponible con el mayor disponible
 maximizando así el peso que cada silla sube. En caso de que la suma supere el peso permitido, se subirá solo el mayor de todos.

 Suponemos que O es una asignación óptima de parejas igual a la voraz, siendo la solución ordenada según el peso del mayor de los dos,
 en las posiciones 0, ... i - 1, y difiere a partir de i:

 V : V[0] >= V[1] >= V[2] >= ... V[i-1] >= | V[i] >= ... V[n-1]
	  ==      ==      ==           ==      |  !=
 O : O[0] >= O[1] >= O[2] >= ... O[i-1] >= | O[i] >= ... O[n-1]

 Partimos de que O[i] <= V[i]. No puede darse que O[i] > V[i], ya que en ese caso ese elemento ya habría sido seleccionado antes por 
 la estrategia voraz.

 Por otra parte, el elemento V[i] debe estar en alguna posición O[j] tal que i < j ya que todos los elementos deben estar en la solución.
 Además la suma del peso de V[i] y O[i] debe ser válida:
 Caso A-El primer elemento de la pareja V[i] > Primero pareja O[i]:

	*Caso 1-El segudo elemento es el mismo en V[i] y O[i]: Debe exisitir otro elemento O[j] siendo j > i el cual sea también emparejable
		con el mayor de O[i], pudiendo cambiar de orden el elemento mayor de estas dos parejas, ya que el mayor de V[j] + el menor de 
		V[i] va a seguir siendo una pareja válida.

	*Caso 2-El segundo elemento es distinto en V[i] i O[i]: Debe exisitir otro elemento O[j] siendo j > i culla pareja también sea válida,
		por lo que podría cambiarse en el orden de la solucín para que se reduzca al caso anterior, dado que el orden de la solución no altera
		la optimalidad de la solución.

Caso B-El primer elemento de V[i] == primero pareja O[i]:

	*Caso 1-El segundo elemento es el mismo en V[i] y O[i]: No habría diferencia entre V[i] y O[i].

	*Caso 2-El segundo elemento es distinto en V[i] y O[i]: Debe exisitir otro primer elemento en algún O[j] siendo j > i el cual sea el mismo que 
		en V[i], por lo que podrían permutarse sin modificar el número de sillas hacer ninguna de las dos parejas superar el pero permitido y resuelve
		la desigualdad.

El coste del algoritmo voraz sería O[N*logN] siendo N el número de esquiadores, debido al coste de la ordenación de sus pesos.
 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>



bool resuelveCaso() {

	// leemos la entrada
	int peso_maximo, N;
	cin >> peso_maximo >> N;

	if (!cin)
		return false;

	vector<int> esquiadores(N);
	for (int& x : esquiadores) {
		cin >> x;
	}
	sort(esquiadores.begin(), esquiadores.end());
	// resolver el caso

	int sillas = 0, indIni = 0, indFin = N - 1;
	while (indIni <= indFin) {
		if (esquiadores[indIni] + esquiadores[indFin] <= peso_maximo) {
			sillas++;
			indIni++;
			indFin--;
		}
		else {
			sillas++;
			indFin--;
		}
	}

	cout << sillas << "\n";
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
