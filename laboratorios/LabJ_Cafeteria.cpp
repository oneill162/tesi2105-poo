// ============================================================
//  TESI 2105 - Programacion Orientada a Objetos
//  Instituto Tecnologico de Puerto Rico - Recinto de Manati
//  Unidad J: Principios de diseno de software
//  Laboratorio J: Remodelacion sin mudanza (la caja de la cafeteria)
//  CODIGO BASE PARA EL ESTUDIANTE
//
//  Nombre: ______________________   Fecha: ____________
//
//  La PARTE A es el programa original: funciona, pero es espagueti.
//  NO la modifique: es la referencia.
//  En la PARTE B usted lo remodela: complete las 7 partes marcadas
//  con TODO, en ese orden. La version remodelada debe imprimir
//  EXACTAMENTE lo mismo que la original con las mismas entradas.
//  Compile con:
//      g++ -std=c++17 -Wall -Wextra -o cafeteria LabJ_Cafeteria.cpp
//  Al ejecutar, escriba 1 para la version original o 2 para la suya.
//  Mientras falten partes, g++ avisa "unused parameter":
//  el aviso desaparece cuando la funcion usa su parametro.
// ============================================================
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// ============================================================
//  PARTE A: EL PROGRAMA ORIGINAL (NO LO MODIFIQUE)
//  Funciona, pero es "espagueti": todo en una funcion larga, codigo
//  repetido, numeros magicos y nombres que no dicen nada.
//  Es la referencia: su version debe imprimir EXACTAMENTE lo mismo.
// ============================================================
void programaOriginal() {
    cout << fixed << setprecision(2);
    int o, n = 0;
    double v = 0, iv = 0, ds = 0;
    do {
        cout << "===== CAJA DE LA CAFETERIA =====" << endl;
        cout << "1. Nueva orden" << endl;
        cout << "2. Resumen del dia" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> o;
        if (o == 1) {
            int c[20], q[20], k = 0, x;
            cout << "Codigo (1-4, 0 termina): ";
            cin >> x;
            while (x != 0) {
                if (x < 1 || x > 4) {
                    cout << "Codigo invalido" << endl;
                } else {
                    int y;
                    cout << "Cantidad: ";
                    cin >> y;
                    if (y <= 0) {
                        cout << "Cantidad invalida" << endl;
                    } else if (k < 20) {
                        c[k] = x;
                        q[k] = y;
                        k++;
                    }
                }
                cout << "Codigo (1-4, 0 termina): ";
                cin >> x;
            }
            if (k == 0) {
                cout << "Orden vacia: no se cobra" << endl;
            } else {
                int t;
                cout << "Cliente (1 estudiante, 2 empleado, 3 visitante): ";
                cin >> t;
                cout << "----- RECIBO -----" << endl;
                if (t == 1) cout << "Cliente: estudiante" << endl;
                else if (t == 2) cout << "Cliente: empleado" << endl;
                else cout << "Cliente: visitante" << endl;
                double s = 0;
                for (int i = 0; i < k; i++) {
                    if (c[i] == 1) {
                        cout << q[i] << " x Sandwich de pavo: $" << q[i] * 3.25 << endl;
                        s = s + q[i] * 3.25;
                    }
                    if (c[i] == 2) {
                        cout << q[i] << " x Empanadilla: $" << q[i] * 1.75 << endl;
                        s = s + q[i] * 1.75;
                    }
                    if (c[i] == 3) {
                        cout << q[i] << " x Jugo de china: $" << q[i] * 2.00 << endl;
                        s = s + q[i] * 2.00;
                    }
                    if (c[i] == 4) {
                        cout << q[i] << " x Cafe con leche: $" << q[i] * 1.25 << endl;
                        s = s + q[i] * 1.25;
                    }
                }
                cout << "Subtotal: $" << s << endl;
                double d = 0;
                if (t == 1) d = s * 0.10;
                if (t == 2) d = s * 0.15;
                if (d > 0) cout << "Descuento: -$" << d << endl;
                double i2 = (s - d) * 0.115;
                cout << "IVU: $" << i2 << endl;
                cout << "Total: $" << s - d + i2 << endl;
                n++;
                v = v + s - d + i2;
                iv = iv + (s - d) * 0.115;
                if (t == 1) ds = ds + s * 0.10;
                if (t == 2) ds = ds + s * 0.15;
            }
        } else if (o == 2) {
            cout << "----- RESUMEN DEL DIA -----" << endl;
            cout << "Ordenes: " << n << endl;
            cout << "Descuentos: $" << ds << endl;
            cout << "IVU cobrado: $" << iv << endl;
            cout << "Ventas: $" << v << endl;
        } else if (o != 0) {
            cout << "Opcion invalida" << endl;
        }
    } while (o != 0);
    cout << "Caja cerrada" << endl;
}

// ============================================================
//  PARTE B: LA REMODELACION (complete los TODO)
//  Misma entrada, misma salida: solo cambia COMO esta escrito.
// ============================================================

// ---------- 1. Constantes con nombre y tabla del menu ----------
//  Cada numero magico del original recibe un nombre.
// TODO 1: busque en la PARTE A el IVU y los dos descuentos y ponga aqui
//         sus valores (hoy estan en 0.0). Llene la tabla MENU con el
//         nombre y el precio de cada articulo, en el orden de los codigos
//         1 a 4. Escriba los nombres tal como salen en el recibo.
const double IVU                  = 0.0;
const double DESCUENTO_ESTUDIANTE = 0.0;
const double DESCUENTO_EMPLEADO   = 0.0;
const int    MAX_LINEAS           = 20;   // ya hecho
const int    CANT_ARTICULOS       = 4;    // ya hecho

enum TipoCliente { ESTUDIANTE = 1, EMPLEADO = 2, VISITANTE = 3 };

struct Articulo {
    string nombre;
    double precio;
};

const Articulo MENU[CANT_ARTICULOS] = {
    {"", 0.0},     // codigo 1
    {"", 0.0},     // codigo 2
    {"", 0.0},     // codigo 3
    {"", 0.0}      // codigo 4
};

// ---------- 2. Todo lo del tipo de cliente, en un solo lugar ----------
//  En el original, el "if (t == 1) ... if (t == 2)" se repite tres veces.
double porcentajeDescuento(int tipo) {
    // TODO 2a: devuelva DESCUENTO_ESTUDIANTE si tipo es ESTUDIANTE,
    //          DESCUENTO_EMPLEADO si es EMPLEADO y 0.0 en otro caso.
    return 0.0;
}

string nombreCliente(int tipo) {
    // TODO 2b: devuelva "estudiante", "empleado" o "visitante"
    //          (cualquier otro numero tambien es "visitante").
    return "";
}

// ---------- La clase Orden (YA DECLARADA: no la modifique) ----------
//  Su responsabilidad: guardar las lineas y CALCULAR. No imprime nada.
class Orden {
private:
    int codigos[MAX_LINEAS];
    int cantidades[MAX_LINEAS];
    int lineas = 0;
    int tipoCliente = VISITANTE;

public:
    void agregar(int codigo, int cantidad);
    void asignarCliente(int tipo)  { tipoCliente = tipo; }
    int  cliente() const           { return tipoCliente; }
    int  cuantasLineas() const     { return lineas; }
    int  codigo(int i) const       { return codigos[i]; }
    int  cantidad(int i) const     { return cantidades[i]; }
    double importe(int i) const    { return cantidades[i] * MENU[codigos[i] - 1].precio; }

    double subtotal() const;
    double descuento() const;
    double ivu() const;
    double total() const;
};

// ---------- 3. agregar y subtotal ----------
void Orden::agregar(int codigo, int cantidad) {
    // TODO 3a: si lineas < MAX_LINEAS, guarde codigo y cantidad en la
    //          posicion lineas de cada arreglo y sume 1 a lineas.
}

double Orden::subtotal() const {
    // TODO 3b: sume importe(i) de todas las lineas y devuelva la suma.
    return 0.0;
}

// ---------- 4. descuento, ivu y total ----------
//  Pista: haga las cuentas en el MISMO orden que el original
//  (el IVU se calcula sobre el subtotal MENOS el descuento).
double Orden::descuento() const {
    // TODO 4a: subtotal() por porcentajeDescuento(tipoCliente).
    return 0.0;
}

double Orden::ivu() const {
    // TODO 4b: (subtotal() - descuento()) por IVU.
    return 0.0;
}

double Orden::total() const {
    // TODO 4c: subtotal() - descuento() + ivu().
    return 0.0;
}

// ---------- 5. El recibo: IMPRIME (no calcula) ----------
//  Las cuatro lineas casi iguales del original se vuelven una funcion.
//  Formato:  2 x Sandwich de pavo: $6.50
void imprimirLinea(int cantidad, const Articulo& a) {
    // TODO 5a: imprima cantidad, " x ", a.nombre, ": $" y cantidad * a.precio, con endl.
}

void imprimirRecibo(const Orden& o) {
    // TODO 5b: imprima, como el original:
    //   "----- RECIBO -----"
    //   "Cliente: " y nombreCliente(o.cliente())
    //   una linea por articulo: imprimirLinea(o.cantidad(i), MENU[o.codigo(i) - 1])
    //   "Subtotal: $" ...
    //   "Descuento: -$" ...   SOLO si o.descuento() > 0
    //   "IVU: $" ...
    //   "Total: $" ...
}

// ---------- La clase Caja (YA DECLARADA: no la modifique) ----------
//  Su responsabilidad: llevar la cuenta del dia.
class Caja {
private:
    int    ordenes    = 0;
    double ventas     = 0;
    double impuestos  = 0;
    double descuentos = 0;

public:
    void registrar(const Orden& o);
    void mostrarResumen() const;
};

// ---------- 6. registrar ----------
void Caja::registrar(const Orden& o) {
    // TODO 6: sume 1 a ordenes y acumule o.total(), o.ivu() y o.descuento()
    //         en ventas, impuestos y descuentos.
}

// ---------- 7. mostrarResumen ----------
void Caja::mostrarResumen() const {
    // TODO 7: imprima, como el original:
    //   "----- RESUMEN DEL DIA -----", "Ordenes: ", "Descuentos: $",
    //   "IVU cobrado: $" y "Ventas: $" (una por linea, en ese orden).
}

// ============================================================
//  YA HECHO: el menu, la lectura de la orden y el programa remodelado
//  (no modifique lo que sigue; usa las partes 1 a 7)
// ============================================================
bool codigoValido(int codigo) {
    return codigo >= 1 && codigo <= CANT_ARTICULOS;
}

void mostrarMenu() {
    cout << "===== CAJA DE LA CAFETERIA =====" << endl;
    cout << "1. Nueva orden" << endl;
    cout << "2. Resumen del dia" << endl;
    cout << "0. Salir" << endl;
}

int leerEntero(const string& mensaje) {
    int valor = 0;      // si la lectura falla, queda en 0
    cout << mensaje;
    cin >> valor;
    return valor;
}

void leerOrden(Orden& o) {
    int codigo = leerEntero("Codigo (1-4, 0 termina): ");
    while (codigo != 0) {
        if (!codigoValido(codigo)) {
            cout << "Codigo invalido" << endl;
        } else {
            int cantidad = leerEntero("Cantidad: ");
            if (cantidad <= 0) cout << "Cantidad invalida" << endl;
            else o.agregar(codigo, cantidad);
        }
        codigo = leerEntero("Codigo (1-4, 0 termina): ");
    }
}

void programaRemodelado() {
    cout << fixed << setprecision(2);
    Caja caja;
    int opcion;
    do {
        mostrarMenu();
        opcion = leerEntero("Opcion: ");
        if (opcion == 1) {
            Orden orden;
            leerOrden(orden);
            if (orden.cuantasLineas() == 0) {
                cout << "Orden vacia: no se cobra" << endl;
            } else {
                orden.asignarCliente(leerEntero("Cliente (1 estudiante, 2 empleado, 3 visitante): "));
                imprimirRecibo(orden);
                caja.registrar(orden);
            }
        } else if (opcion == 2) {
            caja.mostrarResumen();
        } else if (opcion != 0) {
            cout << "Opcion invalida" << endl;
        }
    } while (opcion != 0);
    cout << "Caja cerrada" << endl;
}

// ============================================================
//  main: escoja la version al empezar (1 = original, 2 = remodelada)
// ============================================================
int main() {
    int version;
    cout << "Version (1 = original, 2 = remodelada): ";
    cin >> version;
    if (version == 1) {
        cout << ">> Version original" << endl;
        programaOriginal();
    } else {
        cout << ">> Version remodelada" << endl;
        programaRemodelado();
    }
    return 0;
}
