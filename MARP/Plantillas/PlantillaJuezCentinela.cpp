// Oscar Garcia
// VJ19

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// función que resuelve el problema
TipoSolucion resolver(TipoDatos datos) {
    
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    if (caso especial)
        return false;
    
    TipoSolucion sol = resolver(datos);
    
    // escribir sol
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     ifstream in("datos.txt");
     auto cinbuf = cin.rdbuf(in.rdbuf()); //save old buf and redirect cin to casos.txt
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
