// Oscar García
// MARP21


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

struct Paciente {
    string nombre;
    int gravedad;
    int numP;
};
struct mayor {
    inline bool operator()(const Paciente& a, const Paciente& b) const {
        return b.gravedad > a.gravedad || (b.gravedad == a.gravedad && b.numP < a.numP);
    }
};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int acciones;
    cin >> acciones;

    if (acciones == 0)
        return false;
    int pac = 0;
    priority_queue<Paciente, vector<Paciente>, mayor> cola;

    while (acciones > 0) {
        char a;
        cin >> a;
        if (a == 'I') {
            Paciente n;
            cin >> n.nombre;
            cin >> n.gravedad;
            n.numP = pac;
            cola.push(n);
            pac++;
        }
        else {
            cout << cola.top().nombre << "\n";
            cola.pop();
        }
        acciones--;
    }

    cout << "---\n";
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