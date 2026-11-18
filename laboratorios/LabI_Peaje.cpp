// ============================================================
//  TESI 2105 - Programacion Orientada a Objetos
//  Instituto Tecnologico de Puerto Rico - Recinto de Manati
//  Unidad I: Herencia y polimorfismo
//  Laboratorio I: La caseta de peaje
//  CODIGO BASE PARA EL ESTUDIANTE
//
//  Nombre: ______________________   Fecha: ____________
//
//  Complete las 6 partes marcadas con TODO. Las partes 1, 2 y 3 se
//  repiten en las cuatro clases derivadas. No modifique la clase
//  Vehiculo ni lo que esta despues de la parte 6.
//  Compile con:
//      g++ -std=c++17 -Wall -Wextra -o peaje LabI_Peaje.cpp
//  Mientras falten partes, g++ avisa "unused parameter":
//  el aviso desaparece cuando la funcion usa su parametro.
// ============================================================
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// ---------- La clase base (YA HECHA: no la modifique) ----------
//  Es abstracta: tiene funciones virtuales puras (= 0), asi que no se
//  puede crear un Vehiculo; solo un Auto, una Motora, un Camion o una Guagua.
//  El destructor es virtual: delete con un Vehiculo* llama al de la derivada.
class Vehiculo {
protected:
    string tablilla;              // protected: las derivadas pueden leerla
    static int enMemoria;         // cuantos vehiculos hay creados con new

public:
    Vehiculo(const string& t) : tablilla(t) { enMemoria++; }
    virtual ~Vehiculo() { enMemoria--; }

    virtual double tarifa() const = 0;
    virtual string tipo() const = 0;

    string obtenerTablilla() const { return tablilla; }
    static int cuantos() { return enMemoria; }
};

int Vehiculo::enMemoria = 0;

//  TODO 1 (en las cuatro clases): el constructor llama al de Vehiculo en la
//         lista de inicializacion, pasandole la tablilla t (no "???"), e
//         inicializa ahi mismo los datos propios de la clase.
//  TODO 2 (en las cuatro clases): tarifa() devuelve lo que paga ese vehiculo.
//         Escriba override despues de const.
//  TODO 3 (en las cuatro clases): tipo() devuelve el nombre que sale en la
//         pantalla de la caseta. Tambien con override.

// ---------- Auto: paga $1.50.  tipo: "Auto" ----------
class Auto : public Vehiculo {
public:
    Auto(const string& t) : Vehiculo("???") {}             // TODO 1
    double tarifa() const { return 0.0; }                  // TODO 2
    string tipo() const { return "?"; }                    // TODO 3
};

// ---------- Motora: paga $0.75.  tipo: "Motora" ----------
class Motora : public Vehiculo {
public:
    Motora(const string& t) : Vehiculo("???") {}           // TODO 1
    double tarifa() const { return 0.0; }                  // TODO 2
    string tipo() const { return "?"; }                    // TODO 3
};

// ---------- Camion: paga $1.25 por cada eje ----------
//  tipo: "Camion de 3 ejes" (pista: "Camion de " + to_string(ejes) + " ejes")
class Camion : public Vehiculo {
private:
    int ejes = 2;

public:
    // TODO 1: ademas de la tablilla, guarde e en ejes. Un camion tiene al
    //         menos 2 ejes: si e es menor que 2, ejes queda en 2.
    //         Pista: ejes(e < 2 ? 2 : e)
    Camion(const string& t, int e) : Vehiculo("???") {}
    double tarifa() const { return 0.0; }                  // TODO 2
    string tipo() const { return "?"; }                    // TODO 3
};

// ---------- Guagua: paga $3.00; si es escolar, la mitad ($1.50) ----------
//  tipo: "Guagua escolar" o "Guagua"
class Guagua : public Vehiculo {
private:
    bool escolar = false;

public:
    // TODO 1: ademas de la tablilla, guarde esc en escolar.
    Guagua(const string& t, bool esc) : Vehiculo("???") {}
    double tarifa() const { return 0.0; }                  // TODO 2
    string tipo() const { return "?"; }                    // TODO 3
};

// ---------- 4. La pantalla de la caseta ----------
//  Recibe CUALQUIER vehiculo por referencia constante y escribe, sin endl:
//      ABC-123 | Auto | $1.50
void mostrar(const Vehiculo& v) {
    // TODO 4: escriba v.obtenerTablilla(), " | ", v.tipo(), " | $" y v.tarifa().
    //         No pregunte que clase de vehiculo es: el polimorfismo lo resuelve.
}

// ---------- 5. Liberar la memoria ----------
//  Cada vehiculo de la fila se creo con new: hay que devolverlo con delete.
void vaciarFila(vector<Vehiculo*>& fila) {
    // TODO 5: haga delete de cada puntero de la fila y despues fila.clear().
}

// ---------- 6. Cobrar la fila ----------
//  Para cada vehiculo escribe una linea   Cobro: ABC-123 | Auto | $1.50
//  y devuelve la suma de las tarifas.
double cobrarFila(const vector<Vehiculo*>& fila) {
    // TODO 6: recorra la fila con un Vehiculo* (for (Vehiculo* v : fila)).
    //         Escriba "Cobro: ", llame a mostrar(*v) y termine con endl.
    //         Sume v->tarifa() a un total y devuelvalo.
    return 0.0;
}

// ============ LO QUE SIGUE YA ESTA COMPLETO ============

Vehiculo* llegaVehiculo() {
    int t = 0;
    string tab;
    cout << "Tipo (1 Auto, 2 Motora, 3 Camion, 4 Guagua): ";
    cin >> t;
    if (t < 1 || t > 4) {
        cout << "Tipo invalido" << endl;
        return nullptr;
    }
    cout << "Tablilla: ";
    cin >> tab;
    if (t == 1) return new Auto(tab);
    if (t == 2) return new Motora(tab);
    if (t == 3) {
        int e = 0;
        cout << "Ejes: ";
        cin >> e;
        return new Camion(tab, e);
    }
    int esc = 0;
    cout << "Escolar (1 si, 0 no): ";
    cin >> esc;
    return new Guagua(tab, esc == 1);
}

int main() {
    cout << fixed << setprecision(2);
    vector<Vehiculo*> fila;
    fila.push_back(new Auto("ABC-123"));
    fila.push_back(new Camion("TRK-450", 3));
    fila.push_back(new Motora("MTR-077"));
    fila.push_back(new Guagua("BUS-210", true));
    fila.push_back(new Guagua("BUS-318", false));

    double turno = 0;
    int op = 0;
    do {
        cout << "\n===== CASETA DE PEAJE - PLAZA DEL RIO =====\n"
             << "1. Ver la fila  2. Llega un vehiculo  3. Cobrar la fila  0. Salir\n"
             << "Opcion: ";
        if (!(cin >> op)) break;

        if (op == 1) {
            for (Vehiculo* v : fila) {
                mostrar(*v);
                cout << endl;
            }
            cout << "En la fila: " << fila.size() << endl;
        } else if (op == 2) {
            Vehiculo* v = llegaVehiculo();
            if (v != nullptr) {
                fila.push_back(v);
                cout << "Llega: ";
                mostrar(*v);
                cout << endl;
            }
        } else if (op == 3) {
            double total = cobrarFila(fila);
            turno += total;
            cout << "Total cobrado: $" << total << endl;
            vaciarFila(fila);
            cout << "Se abre la barrera. Vehiculos en memoria: " << Vehiculo::cuantos() << endl;
        } else if (op != 0) {
            cout << "Opcion invalida" << endl;
        }
    } while (op != 0);

    vaciarFila(fila);
    cout << "Fin del turno. Total del turno: $" << turno << endl;
    cout << "Vehiculos en memoria: " << Vehiculo::cuantos() << endl;
    return 0;
}
