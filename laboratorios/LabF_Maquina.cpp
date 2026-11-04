// ============================================================
//  TESI 2105 - Programacion Orientada a Objetos
//  Instituto Tecnologico de Puerto Rico - Recinto de Manati
//  Unidad F: Arreglos y cadenas de caracteres
//  Laboratorio F: Maquina expendedora del A-201
//  CODIGO BASE PARA EL ESTUDIANTE
//
//  Nombre: ______________________   Fecha: ____________
//
//  Complete las 6 funciones marcadas con TODO. No modifique main
//  ni las funciones marcadas YA HECHA (para el reto puede modificar main).
//  Compile con:
//      g++ -std=c++17 -Wall -Wextra -o maquina LabF_Maquina.cpp
//  Mientras falten funciones, g++ avisa "unused parameter":
//  el aviso desaparece cuando la funcion usa su parametro.
// ============================================================
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

const int FILAS = 4;
const int COLS = 4;

// Nombre, precio (en centavos) y existencia de cada espacio.
// Fila 0 = A, fila 1 = B, ... ; columna 0 a 3.
string nombre[FILAS][COLS] = {
    {"Agua",      "Jugo china",   "Malta",       "Refresco"},
    {"Galletas",  "Papitas",      "Platanutres", "Mani"},
    {"Chocolate", "Barra granola","Gomitas",     "Chicle"},
    {"Sandwich",  "Empanadilla",  "Pastelillo",  "Quesito"}
};
int precio[FILAS][COLS] = {
    {100, 150, 175, 125},
    {125, 150, 175, 100},
    {150, 125, 100,  50},
    {350, 275, 250, 200}
};
int stock[FILAS][COLS] = {
    {5, 0, 7, 2},
    {3, 6, 1, 4},
    {8, 2, 0, 5},
    {1, 3, 9, 6}
};

// ---------- YA HECHA: convierte centavos a texto, 275 -> "$2.75" ----------
string dinero(int centavos) {
    string c = to_string(centavos % 100);
    if (c.length() < 2) c = "0" + c;
    return "$" + to_string(centavos / 100) + "." + c;
}

// ---------- 1. Devuelve una copia de s con todas las letras en mayuscula ----------
string aMayusculas(string s) {
    // TODO 1: recorra s con un for (use i < (int)s.length() para que g++ no
    //         avise) y cambie cada caracter con toupper(s[i]).
    return s;
}

// ---------- 2. Un codigo valido tiene 2 caracteres: letra A-D y digito 0-3 ----------
bool codigoValido(string cod) {
    // TODO 2: si cod.length() no es 2, devuelva false.
    //         Si cod[0] esta entre 'A' y 'D' y cod[1] entre '0' y '3', devuelva true.
    return false;
}

// ---------- 3. Fila y columna a partir del codigo (ya valido y en mayuscula) ----------
int filaDe(string cod) {
    // TODO 3a: 'A' es la fila 0, 'B' la 1... Pista: reste 'A' a cod[0].
    return 0;
}
int colDe(string cod) {
    // TODO 3b: '0' es la columna 0... Pista: reste '0' a cod[1].
    return 0;
}

// ---------- 4. Total de unidades en toda la maquina ----------
int totalUnidades(const int s[FILAS][COLS]) {
    // TODO 4: dos for anidados (filas y columnas) que sumen s[f][c].
    return 0;
}

// ---------- 5. Valor del inventario en centavos: suma de existencia x precio ----------
int valorInventario(const int s[FILAS][COLS], const int p[FILAS][COLS]) {
    // TODO 5: igual que el 4, pero sume s[f][c] * p[f][c].
    return 0;
}

// ---------- 6. Muestra el codigo y nombre de cada producto agotado ----------
void mostrarAgotados(const int s[FILAS][COLS]) {
    // TODO 6: recorra la matriz; si s[f][c] es 0, imprima dos espacios, el codigo
    //         (char('A' + f) y c), un espacio y nombre[f][c].
    //         Si no hay ninguno, imprima "  Ninguno".
}

// ============ main: YA ESTA COMPLETO, NO LO MODIFIQUE ============
void mostrarMaquina() {
    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLS; c++) {
            cout << char('A' + f) << c << " " << nombre[f][c] << " " << dinero(precio[f][c]);
            if (stock[f][c] == 0) cout << " (AGOTADO)";
            else cout << " (" << stock[f][c] << ")";
            cout << endl;
        }
    }
}

void comprar() {
    string cod;
    cout << "Codigo: ";
    cin >> cod;
    cod = aMayusculas(cod);
    if (!codigoValido(cod)) {
        cout << "Codigo invalido" << endl;
        return;
    }
    int f = filaDe(cod), c = colDe(cod);
    if (stock[f][c] == 0) {
        cout << nombre[f][c] << " esta agotado" << endl;
        return;
    }
    double pago;
    cout << nombre[f][c] << " cuesta " << dinero(precio[f][c]) << ". Pague: ";
    cin >> pago;
    int centavos = (int)round(pago * 100);
    if (centavos < precio[f][c]) {
        cout << "Pago insuficiente. Faltan " << dinero(precio[f][c] - centavos) << endl;
        return;
    }
    stock[f][c]--;
    cout << "Despachado: " << nombre[f][c] << ". Cambio: " << dinero(centavos - precio[f][c]) << endl;
}

void reporte() {
    cout << "Unidades: " << totalUnidades(stock) << endl;
    cout << "Valor del inventario: " << dinero(valorInventario(stock, precio)) << endl;
    cout << "Agotados:" << endl;
    mostrarAgotados(stock);
}

int main() {
    int op;
    do {
        cout << "\n1. Ver maquina  2. Comprar  3. Reporte  0. Salir\nOpcion: ";
        if (!(cin >> op)) break;
        if (op == 1) mostrarMaquina();
        else if (op == 2) comprar();
        else if (op == 3) reporte();
        else if (op != 0) cout << "Opcion invalida" << endl;
    } while (op != 0);
    cout << "Gracias por usar la maquina del A-201" << endl;
    return 0;
}
