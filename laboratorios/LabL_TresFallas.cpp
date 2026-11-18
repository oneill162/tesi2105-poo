// ============================================================
//  TESI 2105 - Programacion Orientada a Objetos
//  Instituto Tecnologico de Puerto Rico - Recinto de Manati
//  Unidad L: Pruebas y debugging
//  Laboratorio L: El caso de las tres fallas
//  CODIGO BASE PARA EL ESTUDIANTE
//
//  Nombre: ______________________   Fecha: ____________
//
//  La clase Bitacora tiene EXACTAMENTE 3 fallas sembradas. No estan
//  marcadas. Las 6 pruebas que ya existen pasan todas: no las ven.
//  Complete los 6 TODO, en este orden:
//    TODO 1 a 3: escriba en pruebasNuevas() una prueba que exponga cada
//                falla (caso normal, caso limite y caso de error).
//                Corra la opcion 1: sus pruebas deben salir [FALLO].
//    TODO 4 a 6: corrija cada falla y deje, encima de la linea que
//                cambio, un comentario con este formato:
//       // CORREGIDA (falla n): que estaba mal.
//       // LA ENCONTRE CON: la prueba, el mensaje de g++ o gdb.
//  Al final, la opcion 1 debe decir "Pruebas: 9 de 9 pasaron".
//  No modifique main ni lo que esta despues de pruebasNuevas().
//  Compile con:
//      g++ -std=c++17 -Wall -Wextra -o fallas LabL_TresFallas.cpp
//  Para usar gdb, compile ademas con -g.
// ============================================================
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

// ---------- La clase bajo prueba ----------
//  Bitacora de temperaturas del CPU durante la prueba de esfuerzo del taller.
//  Lo que DEBE hacer (la especificacion):
//    agregar(g)     guarda la lectura g; si ya hay 8, la rechaza (false)
//                   y la bitacora queda igual que antes.
//    cantidad()     cuantas lecturas hay guardadas.
//    promedio()     el promedio de las lecturas guardadas, con decimales;
//                   0 si no hay ninguna.
//    enRango(g)     true si g esta de 30 a 85 grados, con 30 y 85 incluidos.
//    fueraDeRango() cuantas lecturas guardadas no estan en rango.
class Bitacora {
private:
    static const int CAP = 8;      // caben 8 lecturas
    static const int MIN = 30;     // rango normal: de 30 a 85 grados,
    static const int MAX = 85;     // los dos extremos incluidos
    int lecturas[CAP] = {};
    int n = 0;                     // cuantas lecturas hay
    int total = 0;                 // acumulador: suma de las lecturas guardadas

public:
    bool   agregar(int grados);    // false si la bitacora esta llena
    int    cantidad() const { return n; }
    double promedio() const;       // 0 si no hay lecturas
    static bool enRango(int grados);
    int    fueraDeRango() const;
};

// TODO 4, 5 y 6: las tres fallas estan en las cuatro funciones que siguen.
//   TODO 4: corrija la falla que expone su prueba del TODO 1.
//   TODO 5: corrija la falla que expone su prueba del TODO 2.
//   TODO 6: corrija la falla que expone su prueba del TODO 3.
//   Pista: si no ve la falla leyendo, compile con -g y use gdb:
//   break en la funcion, run, next, y print de cada variable.

bool Bitacora::agregar(int grados) {
    total += grados;
    if (n == CAP) return false;
    lecturas[n] = grados;
    n++;
    return true;
}

double Bitacora::promedio() const {
    if (n == 0) return 0;
    return total / n;
}

bool Bitacora::enRango(int grados) {
    return grados > MIN && grados < MAX;
}

int Bitacora::fueraDeRango() const {
    int k = 0;
    for (int i = 0; i < n; i++)
        if (!enRango(lecturas[i])) k++;
    return k;
}

// ---------- El mini marco de pruebas (YA HECHO) ----------
int pasaron = 0, corridas = 0;

void revisar(const string& nombre, bool condicion) {
    corridas++;
    if (condicion) {
        pasaron++;
        cout << "[PASO]  " << nombre << endl;
    } else {
        cout << "[FALLO] " << nombre << endl;
    }
}

// Dos double casi nunca son exactamente iguales: se comparan con tolerancia.
bool casiIgual(double a, double b) {
    return fabs(a - b) < 0.001;
}

// ---------- Pruebas que ya estaban (YA HECHAS: todas pasan) ----------
void pruebasDadas() {
    Bitacora vacia;
    revisar("bitacora nueva esta vacia", vacia.cantidad() == 0);
    revisar("promedio sin lecturas es 0", casiIgual(vacia.promedio(), 0));

    Bitacora b;
    b.agregar(60);
    b.agregar(80);
    revisar("promedio de 60 y 80 es 70", casiIgual(b.promedio(), 70));

    revisar("50 esta en rango", Bitacora::enRango(50));
    revisar("120 esta fuera de rango", !Bitacora::enRango(120));

    Bitacora llena;
    bool ochoEntran = true;
    for (int i = 0; i < 8; i++)
        if (!llena.agregar(70)) ochoEntran = false;
    revisar("acepta 8 lecturas y rechaza la novena",
            ochoEntran && !llena.agregar(70) && llena.cantidad() == 8);
}

// ---------- Pruebas nuevas (las escribe usted) ----------
//  Use EXACTAMENTE el nombre que se indica: el verificador lo busca.
void pruebasNuevas() {
    // TODO 1 (caso normal): cree una Bitacora, agregue 70 y 71, y llame a
    //   revisar("promedio de 70 y 71 es 70.5", ...) con casiIgual(..., 70.5).

    // TODO 2 (caso limite): llame a revisar("30 y 85 estan en rango", ...)
    //   con una condicion que exija que enRango(30) y enRango(85) sean true.

    // TODO 3 (caso de error): llene una Bitacora con 8 lecturas de 70,
    //   intente agregar 150 (debe rechazarse) y llame a
    //   revisar("la lectura rechazada no cuenta en el promedio", ...)
    //   exigiendo que agregar(150) haya dado false y que el promedio sea 70.
}

// ============ LO QUE SIGUE YA ESTA COMPLETO: NO LO MODIFIQUE ============

void correrPruebas() {
    pasaron = 0;
    corridas = 0;
    pruebasDadas();
    pruebasNuevas();
    cout << "Pruebas: " << pasaron << " de " << corridas << " pasaron" << endl;
}

void anotar(Bitacora& b) {
    int k = 0;
    cout << "Cuantas lecturas: ";
    cin >> k;
    for (int i = 0; i < k; i++) {
        int t = 0;
        cout << "Lectura: ";
        cin >> t;
        if (!b.agregar(t)) cout << "Rechazada: bitacora llena (" << t << ")" << endl;
    }
}

void informe(const Bitacora& b) {
    cout << "Lecturas: " << b.cantidad() << endl;
    cout << "Promedio: " << b.promedio() << " grados" << endl;
    cout << "Fuera de rango (30 a 85): " << b.fueraDeRango() << endl;
}

int main() {
    cout << fixed << setprecision(2);
    Bitacora cpu;
    int op = 0;
    do {
        cout << "\n===== BANCO DE PRUEBAS: BITACORA DEL CPU =====\n"
             << "1. Correr las pruebas  2. Anotar lecturas  3. Informe  0. Salir\n"
             << "Opcion: ";
        if (!(cin >> op)) break;
        if (op == 1)      correrPruebas();
        else if (op == 2) anotar(cpu);
        else if (op == 3) informe(cpu);
        else if (op != 0) cout << "Opcion invalida" << endl;
    } while (op != 0);
    return 0;
}
