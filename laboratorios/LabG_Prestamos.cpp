// ============================================================
//  TESI 2105 - Programacion Orientada a Objetos
//  Instituto Tecnologico de Puerto Rico - Recinto de Manati
//  Unidad G: Estructuras y uniones
//  Laboratorio G: Prestamo de laptops de la Biblioteca
//  CODIGO BASE PARA EL ESTUDIANTE
//
//  Nombre: ______________________   Fecha: ____________
//
//  Complete las 6 funciones marcadas con TODO. No modifique los tipos
//  ni main. Compile con:
//      g++ -std=c++17 -Wall -Wextra -o prestamos LabG_Prestamos.cpp
//  Mientras falten funciones, g++ avisa "unused parameter":
//  el aviso desaparece cuando la funcion usa su parametro.
// ============================================================
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;

// ---------- Tipos (YA HECHOS) ----------
struct Fecha {
    int dia, mes, anio;
};

enum TipoUsuario { ESTUDIANTE, EMPLEADO };

// Quien tiene la laptop: un numero de estudiante O un codigo de empleado.
union Identificacion {
    int  numEstudiante;   // ejemplo: 84231
    char empleado[8];     // ejemplo: "E-0457"
};

struct Prestamo {
    TipoUsuario    tipo;  // dice cual miembro de la union es el valido
    Identificacion id;
    Fecha          devolver;
};

struct Laptop {
    string   etiqueta;
    string   marca;
    int      ram;         // en GB
    bool     prestada;
    Prestamo prestamo;    // solo tiene sentido si prestada es true
};

const int N = 5;

// ---------- 1. Muestra el id segun el tipo de usuario ----------
//  "Estudiante 84231"  o  "Empleado E-0457"  (sin salto de linea)
void mostrarId(const Prestamo& p) {
    // TODO 1: si p.tipo es ESTUDIANTE, imprima "Estudiante " y p.id.numEstudiante;
    //         si no, "Empleado " y p.id.empleado. Lea SOLO el miembro que dice p.tipo.
}

// ---------- 2. Muestra una laptop en una linea ----------
//  "BIB-01 Dell 8 GB - disponible"
//  "BIB-02 HP 16 GB - prestada a Estudiante 84231 hasta 10/11/2026"
void mostrarLaptop(const Laptop& l) {
    // TODO 2: imprima etiqueta, marca, ram y " GB - ".
    //         Si no esta prestada: "disponible". Si lo esta: "prestada a ",
    //         llame a mostrarId(l.prestamo) y luego " hasta dia/mes/anio".
    //         Termine con endl.
}

// ---------- 3. Cuantas laptops no estan prestadas ----------
int contarDisponibles(const Laptop lista[], int n) {
    // TODO 3: recorra lista y cuente las que tienen prestada en false.
    return 0;
}

// ---------- 4. Promedio de RAM de todas las laptops ----------
double promedioRam(const Laptop lista[], int n) {
    // TODO 4: sume lista[i].ram y divida entre n. Cuidado con la division entera.
    return 0;
}

// ---------- 5. Busca por etiqueta; devuelve su direccion o nullptr ----------
Laptop* buscar(Laptop lista[], int n, string etiqueta) {
    // TODO 5: si lista[i].etiqueta es igual a etiqueta, devuelva &lista[i].
    //         Si no la encuentra, devuelva nullptr.
    return nullptr;
}

// ---------- 6. Presta la laptop: marca prestada y guarda el prestamo ----------
void prestar(Laptop* l, Prestamo p) {
    // TODO 6: l es un puntero: use -> para poner prestada en true
    //         y para copiar p en el miembro prestamo.
}

// ============ main: YA ESTA COMPLETO, NO LO MODIFIQUE ============
int main() {
    Laptop lista[N] = {
        {"BIB-01", "Dell",   8,  false, {}},
        {"BIB-02", "HP",     16, true,  {ESTUDIANTE, {84231}, {10, 11, 2026}}},
        {"BIB-03", "Lenovo", 8,  false, {}},
        {"BIB-04", "Acer",   4,  true,  {EMPLEADO, {}, {6, 11, 2026}}},
        {"BIB-05", "HP",     16, false, {}}
    };
    strcpy(lista[3].prestamo.id.empleado, "E-0457");

    int op;
    cout << fixed << setprecision(1);
    do {
        cout << "\n===== PRESTAMO DE LAPTOPS - BIBLIOTECA =====\n"
             << "1. Ver laptops  2. Resumen  3. Prestar  4. Devolver  0. Salir\nOpcion: ";
        if (!(cin >> op)) break;
        if (op == 1) {
            for (int i = 0; i < N; i++) mostrarLaptop(lista[i]);
        } else if (op == 2) {
            cout << "Disponibles: " << contarDisponibles(lista, N) << " de " << N << endl;
            cout << "Promedio de RAM: " << promedioRam(lista, N) << " GB" << endl;
        } else if (op == 3 || op == 4) {
            string et;
            cout << "Etiqueta: ";
            cin >> et;
            Laptop* l = buscar(lista, N, et);
            if (l == nullptr) {
                cout << "No existe la laptop " << et << endl;
            } else if (op == 4) {
                if (!l->prestada) cout << l->etiqueta << " no estaba prestada" << endl;
                else { l->prestada = false; cout << l->etiqueta << " devuelta" << endl; }
            } else if (l->prestada) {
                cout << l->etiqueta << " ya esta prestada" << endl;
            } else {
                Prestamo p;
                int t;
                cout << "Tipo (1 = estudiante, 2 = empleado): ";
                cin >> t;
                if (t == 1) {
                    p.tipo = ESTUDIANTE;
                    cout << "Numero de estudiante: ";
                    cin >> p.id.numEstudiante;
                } else {
                    p.tipo = EMPLEADO;
                    string cod;
                    cout << "Codigo de empleado: ";
                    cin >> cod;
                    strncpy(p.id.empleado, cod.c_str(), 7);
                    p.id.empleado[7] = '\0';
                }
                cout << "Devolver (dia mes anio): ";
                cin >> p.devolver.dia >> p.devolver.mes >> p.devolver.anio;
                prestar(l, p);
                cout << "Prestada: ";
                mostrarLaptop(*l);
            }
        } else if (op != 0) {
            cout << "Opcion invalida" << endl;
        }
    } while (op != 0);
    cout << "Fin del programa" << endl;
    return 0;
}
