// ============================================================
//  TESI 2105 - Programacion Orientada a Objetos
//  Instituto Tecnologico de Puerto Rico - Recinto de Manati
//  Unidad H: Clases y objetos
//  Laboratorio H: La cooperativa del recinto
//  CODIGO BASE PARA EL ESTUDIANTE
//
//  Nombre: ______________________   Fecha: ____________
//
//  Complete las 8 partes marcadas con TODO, en ese orden. No modifique
//  la declaracion de la clase ni lo que esta despues de la parte 8.
//  Compile con:
//      g++ -std=c++17 -Wall -Wextra -o cooperativa LabH_Cooperativa.cpp
//  Mientras falten partes, g++ avisa "unused parameter":
//  el aviso desaparece cuando la funcion usa su parametro.
// ============================================================
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// ---------- La clase (YA DECLARADA: no la modifique) ----------
//  private: solo las funciones de la clase pueden tocar estos datos.
//  public:  la ventanilla; es lo unico que puede usar el resto del programa.
class Cuenta {
private:
    // El valor despues de cada = es el que tiene el dato mientras el
    // constructor no le ponga otro.
    int    numero = 0;
    string socio  = "(sin socio)";
    double saldo  = 0.0;
    static int totalCuentas;      // un solo contador para toda la clase

public:
    Cuenta(int n, const string& s, double inicial);
    ~Cuenta();

    // Una cuenta no se copia: con = delete, g++ rechaza cualquier copia.
    // Para referirse a una cuenta use una referencia, un puntero o su posicion.
    Cuenta(const Cuenta&) = delete;
    Cuenta& operator=(const Cuenta&) = delete;

    bool depositar(double monto);
    bool retirar(double monto);
    bool transferir(Cuenta& destino, double monto);

    Cuenta& operator+=(double monto);
    bool    operator==(const Cuenta& otra) const;
    friend ostream& operator<<(ostream& os, const Cuenta& c);

    int    obtenerNumero() const  { return numero; }
    double consultarSaldo() const { return saldo; }
    static int cuantas()          { return totalCuentas; }
};

int Cuenta::totalCuentas = 0;

// ---------- 1. Constructor ----------
//  Deja la cuenta lista desde que nace.
Cuenta::Cuenta(int n, const string& s, double inicial) {
    // TODO 1: guarde n, s e inicial en numero, socio y saldo (con la lista de
    //         inicializacion o dentro del cuerpo del constructor).
    //         Si el saldo inicial es negativo, el saldo queda en 0.
    //         Sume 1 a totalCuentas.
}

// ---------- 2. Operador <<  (permite escribir cout << cuenta) ----------
//  Formato:  Cuenta 1001 | Marta | $500.00      (sin salto de linea)
ostream& operator<<(ostream& os, const Cuenta& c) {
    // TODO 2: escriba en os (no en cout) "Cuenta ", c.numero, " | ", c.socio,
    //         " | $" y c.saldo. Por ser friend, puede leer los datos privados.
    return os;
}

// ---------- 3. Destructor ----------
//  Corre solo, cuando el objeto deja de existir.
Cuenta::~Cuenta() {
    // TODO 3: imprima "Se cierra la cuenta " y el numero, con endl.
    //         Reste 1 a totalCuentas.
}

// ---------- 4. Depositar ----------
//  Devuelve true si el deposito se hizo y false si se rechazo.
bool Cuenta::depositar(double monto) {
    // TODO 4: si monto es 0 o negativo, devuelva false sin tocar el saldo.
    //         Si no, sume monto al saldo y devuelva true.
    return false;
}

// ---------- 5. Retirar ----------
//  Se puede retirar hasta el saldo completo, pero no mas.
bool Cuenta::retirar(double monto) {
    // TODO 5: si monto es 0 o negativo, o si es mayor que el saldo, devuelva false.
    //         Si no, reste monto del saldo y devuelva true.
    return false;
}

// ---------- 6. Operador ==  (dos cuentas son la misma si tienen el mismo numero) ----------
bool Cuenta::operator==(const Cuenta& otra) const {
    // TODO 6: devuelva el resultado de comparar numero con otra.numero.
    return false;
}

// ---------- 7. Transferir de esta cuenta a otra ----------
bool Cuenta::transferir(Cuenta& destino, double monto) {
    // TODO 7: si destino es esta misma cuenta (*this == destino), devuelva false.
    //         Retire monto de esta cuenta; si el retiro falla, devuelva false.
    //         Deposite monto en destino y devuelva true.
    return false;
}

// ---------- 8. Operador +=  (cuenta += 10.00 deposita 10.00) ----------
Cuenta& Cuenta::operator+=(double monto) {
    // TODO 8: deposite monto con la funcion depositar.
    return *this;                 // devuelve esta misma cuenta
}

// ============ LO QUE SIGUE YA ESTA COMPLETO: NO LO MODIFIQUE ============

// Busca una cuenta por su numero. Devuelve su direccion, o nullptr si no existe.
Cuenta* buscar(Cuenta lista[], int n, int numero) {
    for (int i = 0; i < n; i++)
        if (lista[i].obtenerNumero() == numero) return &lista[i];
    return nullptr;
}

// Pregunta un numero de cuenta y la busca. Si no existe, lo dice.
Cuenta* pedirCuenta(Cuenta lista[], int n, const string& pregunta) {
    int numero = 0;
    cout << pregunta;
    cin >> numero;
    Cuenta* c = buscar(lista, n, numero);
    if (c == nullptr) cout << "No existe la cuenta " << numero << endl;
    return c;
}

double pedirMonto() {
    double monto = 0;
    cout << "Monto: ";
    cin >> monto;
    return monto;
}

void menu(Cuenta cuentas[], int n) {
    int op = 0;
    do {
        cout << "\n===== COOPERATIVA DEL RECINTO =====\n"
             << "1. Ver cuentas  2. Depositar  3. Retirar  "
             << "4. Transferir  5. Dividendo  0. Salir\n"
             << "Opcion: ";
        if (!(cin >> op)) break;

        if (op == 1) {
            double total = 0;
            for (int i = 0; i < n; i++) {
                cout << cuentas[i] << endl;                 // usa el operador <<
                total += cuentas[i].consultarSaldo();
            }
            cout << "Cuentas abiertas: " << Cuenta::cuantas() << endl;
            cout << "Total en la cooperativa: $" << total << endl;
        } else if (op == 2 || op == 3) {
            Cuenta* c = pedirCuenta(cuentas, n, "Numero de cuenta: ");
            if (c != nullptr) {
                double monto = pedirMonto();
                if (op == 2) {
                    bool ok = c->depositar(monto);
                    cout << (ok ? "Deposito aprobado" : "Deposito rechazado") << endl;
                } else {
                    bool ok = c->retirar(monto);
                    cout << (ok ? "Retiro aprobado" : "Retiro rechazado") << endl;
                }
                cout << *c << endl;
            }
        } else if (op == 4) {
            Cuenta* o = pedirCuenta(cuentas, n, "Cuenta origen: ");
            if (o != nullptr) {
                Cuenta* d = pedirCuenta(cuentas, n, "Cuenta destino: ");
                if (d != nullptr) {
                    double monto = pedirMonto();
                    bool ok = o->transferir(*d, monto);
                    cout << (ok ? "Transferencia aprobada" : "Transferencia rechazada") << endl;
                    cout << *o << endl << *d << endl;
                }
            }
        } else if (op == 5) {
            double monto = pedirMonto();
            double antes = cuentas[0].consultarSaldo();
            for (int i = 0; i < n; i++) cuentas[i] += monto;       // usa el operador +=
            bool ok = cuentas[0].consultarSaldo() > antes;
            cout << (ok ? "Dividendo pagado" : "Dividendo rechazado") << endl;
        } else if (op != 0) {
            cout << "Opcion invalida" << endl;
        }
    } while (op != 0);
}

const int N = 4;

int main() {
    cout << fixed << setprecision(2);
    {   // las cuentas viven dentro de este bloque
        Cuenta cuentas[N] = {             // cada renglon llama al constructor
            {1001, "Marta", 500.00},
            {1002, "Tito", 75.50},
            {1003, "Yara", 1200.00},
            {1004, "Nico", -50.00}        // saldo inicial invalido: debe quedar en 0
        };
        menu(cuentas, N);
        cout << "Fin del programa" << endl;
    }   // aqui termina el bloque: corre el destructor de cada cuenta
    cout << "Cuentas abiertas: " << Cuenta::cuantas() << endl;
    return 0;
}
