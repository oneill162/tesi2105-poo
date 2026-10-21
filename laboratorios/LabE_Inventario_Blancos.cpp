// ============================================================
//  TESI 2105 - Programacion Orientada a Objetos
//  Instituto Tecnologico de Puerto Rico - Recinto de Manati
//  Unidad E: Punteros
//  Laboratorio E: Inventario del Laboratorio A-201
//  VERSION DEL ESTUDIANTE - Complete los blancos ____(#)
//  Nombre: ______________________   Fecha: ____________
// ============================================================
#include <iostream>
#include <iomanip>   // fixed, setprecision, setw
#include <string>
using namespace std;

const int N = 5;   // cantidad de equipos en el inventario

// ------------------ PROTOTIPOS ------------------
// Recorrer arreglos con aritmetica de punteros
void   mostrarInventario(const string* nombres, const int* cant, const double* precio, int n);
int    totalUnidades(const int* cant, int n);
double valorInventario(const int* cant, const double* precio, int n);

// Funciones que devuelven un puntero
int*   buscarMayor(int* cant, int n);

// Punteros como parametros (modifican la variable original)
void   recibirEquipo(int* cantidad, int recibidas);
void   intercambiarEnteros(int* a, int* b);
void   intercambiarReales(double* a, double* b);
void   intercambiarTextos(string* a, string* b);

// Punteros a punteros
void   marcarDestacado(int** destacado, int* cant, int posicion);

// Concepto y declaracion de punteros
void   mostrarDirecciones(int* cant, int n);

void   mostrarMenu();

// ------------------ PROGRAMA PRINCIPAL ------------------
int main() {
    string nombres[N] = { "Computadora HP ProDesk", "Monitor 24 pulgadas",
                          "Teclado USB", "Mouse optico", "Proyector" };
    int    cant[N]    = { 12, 15, 20, 25, 2 };
    double precio[N]  = { 650.00, 139.99, 14.50, 9.75, 489.00 };

    int* destacado = ____(17);   // puntero que apunta a la cantidad del equipo destacado
    int  opcion;

    cout << fixed << setprecision(2);
    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            mostrarInventario(nombres, cant, precio, N);
            break;
        case 2:
            cout << "Total de unidades: " << totalUnidades(cant, N) << endl;
            break;
        case 3:
            cout << "Valor del inventario: $" << valorInventario(cant, precio, N) << endl;
            break;
        case 4: {
            int* mayor = buscarMayor(cant, N);
            int  indice = mayor - ____(18);           // resta de punteros = distancia en elementos
            cout << "Equipo con mas unidades: " << nombres[indice]
                 << " (" << *mayor << " unidades, posicion " << indice + 1 << ")" << endl;
            break;
        }
        case 5: {
            int pos, recibidas;
            cout << "Posicion del equipo (1-" << N << "): ";
            cin >> pos;
            cout << "Unidades recibidas: ";
            cin >> recibidas;
            if (pos < 1 || pos > N || recibidas <= 0) {
                cout << "Datos invalidos." << endl;
            } else {
                recibirEquipo(____(19)cant[pos - 1], recibidas);
                cout << nombres[pos - 1] << " ahora tiene " << cant[pos - 1] << " unidades." << endl;
            }
            break;
        }
        case 6: {
            int p1, p2;
            cout << "Primera posicion (1-" << N << "): ";
            cin >> p1;
            cout << "Segunda posicion (1-" << N << "): ";
            cin >> p2;
            if (p1 < 1 || p1 > N || p2 < 1 || p2 > N) {
                cout << "Datos invalidos." << endl;
            } else {
                intercambiarTextos(&nombres[p1 - 1], &nombres[p2 - 1]);
                intercambiarEnteros(&cant[p1 - 1], &cant[p2 - 1]);
                intercambiarReales(&precio[p1 - 1], &precio[p2 - 1]);
                cout << "Equipos intercambiados." << endl;
            }
            break;
        }
        case 7: {
            int pos;
            cout << "Posicion del equipo destacado (1-" << N << "): ";
            cin >> pos;
            if (pos < 1 || pos > N) {
                cout << "Datos invalidos." << endl;
            } else {
                marcarDestacado(____(20)destacado, cant, pos);
                cout << "Destacado: " << nombres[pos - 1] << " con "
                     << *destacado << " unidades." << endl;
            }
            break;
        }
        case 8:
            mostrarDirecciones(cant, N);
            break;
        case 0:
            cout << "Fin del programa." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);

    return 0;
}

// ------------------ DEFINICIONES: COMPLETE CADA ____(#) ------------------
void mostrarMenu() {
    cout << "\n===== INVENTARIO LABORATORIO A-201 =====" << endl;
    cout << "1. Ver inventario" << endl;
    cout << "2. Total de unidades" << endl;
    cout << "3. Valor del inventario" << endl;
    cout << "4. Equipo con mas unidades" << endl;
    cout << "5. Recibir equipo" << endl;
    cout << "6. Intercambiar dos equipos" << endl;
    cout << "7. Marcar equipo destacado" << endl;
    cout << "8. Ver direcciones de memoria" << endl;
    cout << "0. Salir" << endl;
}

// Recorre los tres arreglos con aritmetica de punteros: *(p + i)
void mostrarInventario(const string* nombres, const int* cant, const double* precio, int n) {
    cout << left << setw(4) << "#" << setw(26) << "Equipo"
         << right << setw(8) << "Cant." << setw(12) << "Precio" << endl;
    for (int i = 0; i < n; i++) {
        cout << left << setw(4) << i + 1 << setw(26) << *(nombres + ____(1))
             << right << setw(8) << ____(2) << setw(12) << *(precio + i) << endl;
    }
}

// Avanza el puntero p elemento por elemento (p++) hasta el final del arreglo
int totalUnidades(const int* cant, int n) {
    int suma = 0;
    for (const int* p = ____(3); p < cant + ____(4); p++)
        suma += ____(5);
    return suma;
}

// Dos punteros avanzan juntos por dos arreglos paralelos
double valorInventario(const int* cant, const double* precio, int n) {
    double total = 0;
    const int*    pc = cant;
    const double* pp = precio;
    for (int i = 0; i < n; i++) {
        total += ____(6) * ____(7);
        ____(8);
        pp++;
    }
    return total;
}

// Devuelve la DIRECCION del elemento mayor, no su valor
____(9) buscarMayor(int* cant, int n) {
    int* mayor = cant;
    for (int* p = cant + 1; p < cant + n; p++)
        if (*p > ____(10))
            mayor = ____(11);
    return mayor;
}

// Modifica la variable original a traves del puntero
void recibirEquipo(int* cantidad, int recibidas) {
    ____(12) += recibidas;
}

void intercambiarEnteros(int* a, int* b) {
    int temp = ____(13);
    *a = *b;
    ____(14) = temp;
}

void intercambiarReales(double* a, double* b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

void intercambiarTextos(string* a, string* b) {
    string temp = *a;
    *a = *b;
    *b = temp;
}

// Puntero a puntero: cambia HACIA DONDE apunta el puntero de main()
void marcarDestacado(int** destacado, int* cant, int posicion) {
    ____(15) = cant + (posicion - 1);
}

// Muestra que los elementos de un arreglo estan contiguos en memoria
void mostrarDirecciones(int* cant, int n) {
    cout << "Cada int ocupa " << sizeof(int) << " bytes." << endl;
    for (int i = 0; i < n; i++) {
        cout << "cant + " << i << " -> direccion " << (void*)(cant + ____(16))
             << "  valor " << *(cant + i) << endl;
    }
}
