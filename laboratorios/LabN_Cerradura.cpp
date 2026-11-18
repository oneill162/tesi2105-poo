// ============================================================
//  TESI 2105 - Programacion Orientada a Objetos
//  Instituto Tecnologico de Puerto Rico - Recinto de Manati
//  Unidad N: Fundamentos de seguridad en POO
//  Laboratorio N: La cerradura digital del laboratorio
//  CODIGO BASE PARA EL ESTUDIANTE
//
//  Nombre: ______________________   Fecha: ____________
//
//  Este programa YA FUNCIONA, pero tiene fallas de seguridad. Cada falla
//  esta marcada con TODO. Corrija las 5 partes, en ese orden. No modifique
//  main ni la declaracion de la clase.
//  Compile con:
//      g++ -std=c++17 -Wall -Wextra -o cerradura LabN_Cerradura.cpp
//  Para el Caso 2 compile ademas con los sanitizadores:
//      g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined -o cerradura LabN_Cerradura.cpp
//  Mientras falte la parte 1, g++ avisa "unused parameter":
//  el aviso desaparece cuando la funcion usa su parametro.
// ============================================================
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

bool formatoValido(const string& texto);

// ---------- La clase (YA DECLARADA: no la modifique) ----------
class Cerradura {
private:
    string pin;                     // el secreto: nunca debe salir de la clase
    int    fallidos  = 0;           // invariante: 0 <= fallidos <= MAX_INTENTOS
    bool   bloqueada = false;
    vector<string> bitacora;        // lo que paso, en orden

    void registrar(const string& evento) { bitacora.push_back(evento); }

public:
    static const int MAX_INTENTOS = 3;

    explicit Cerradura(const string& pinInicial);
    string intentarAbrir(const string& intento);   // devuelve el mensaje para el usuario
    void   mostrarBitacora() const;
    void   mostrarEntrada(int n) const;
    bool   estaBloqueada() const { return bloqueada; }
};

// ---------- Constructor (completo): valida antes de que el objeto exista ----------
Cerradura::Cerradura(const string& pinInicial) {
    if (!formatoValido(pinInicial))
        throw invalid_argument("PIN inicial invalido");
    pin = pinInicial;
}

// ---------- 1a. Leer una linea completa ----------
//  FALLA: el arreglo char tiene 8 espacios y cin >> no sabe cuantos caben.
//  Con una entrada larga escribe fuera del arreglo (AddressSanitizer lo detecta).
string leerLinea() {
    // TODO 1a: borre el arreglo char y lea con un string y getline(cin, linea).
    //          Si getline falla (se acabo la entrada), devuelva "0".
    char entrada[8] = "";
    if (!(cin >> entrada)) return "0";
    return entrada;
}

// ---------- 1b. Formato del PIN: de 4 a 6 digitos ----------
//  FALLA: acepta cualquier cosa.
bool formatoValido(const string& texto) {
    // TODO 1b: devuelva false si texto tiene menos de 4 o mas de 6 caracteres,
    //          o si alguno no esta entre '0' y '9'. Si pasa todo, true.
    return true;
}

// ---------- 2, 3 y 4. Intentar abrir ----------
string Cerradura::intentarAbrir(const string& intento) {
    // TODO 2: si la cerradura ya esta bloqueada, anote en la bitacora
    //         "Intento rechazado: cerradura bloqueada" y devuelva
    //         "Cerradura bloqueada. Acuda a la oficina de seguridad" sin comparar.

    if (!formatoValido(intento)) {
        registrar("Entrada rechazada: formato invalido");
        return "Formato invalido: el PIN lleva de 4 a 6 digitos";
    }

    // TODO 4: FALLA: este ciclo dice que digito falla (una pista para adivinar)
    //         y ademas abre con "25801", porque solo mira los primeros digitos.
    //         Reemplacelo por una sola comparacion: intento == pin.
    for (size_t i = 0; i < pin.size(); i++) {
        if (i >= intento.size() || intento[i] != pin[i]) {
            fallidos++;
            // TODO 3: FALLA: la bitacora guarda el PIN tecleado. Arme el aviso
            //         "PIN incorrecto (intento N de 3)" con to_string(fallidos) y
            //         to_string(MAX_INTENTOS), anotelo con registrar y devuelvalo.
            registrar("Intento con PIN " + intento + ": incorrecto");
            // TODO 2: FALLA: no hay limite. Si fallidos llega a MAX_INTENTOS:
            //         bloqueada = true, anote "Cerradura bloqueada tras 3 intentos"
            //         y devuelva el aviso seguido de ". Cerradura bloqueada".
            return "PIN incorrecto: falla el digito " + to_string(i + 1);
        }
    }
    fallidos = 0;
    // TODO 3: la entrada debe decir solo "Puerta abierta".
    registrar("Puerta abierta con PIN " + intento);
    return "Puerta abierta. Bienvenido al laboratorio";
}

// ---------- 3. Mostrar la bitacora ----------
void Cerradura::mostrarBitacora() const {
    // TODO 3: FALLA: borre esta linea. El PIN no se muestra nunca.
    cout << "PIN guardado: " << pin << endl;
    cout << "Entradas en la bitacora: " << bitacora.size() << endl;
    for (size_t i = 0; i < bitacora.size(); i++)
        cout << i + 1 << ". " << bitacora[i] << endl;
}

// ---------- 5a. Convertir texto en numero ----------
//  FALLA: stoi lanza una excepcion con letras ("hola") o con numeros enormes,
//  y el programa se cae ("terminate called after throwing...").
int aNumero(const string& texto) {
    // TODO 5a: devuelva -1 si texto esta vacio, tiene mas de 4 caracteres
    //          o alguno no es un digito. Solo entonces use stoi.
    return stoi(texto);
}

// ---------- 5b. Mostrar una entrada de la bitacora ----------
//  FALLA: no comprueba el indice; con 9 lee fuera del vector.
void Cerradura::mostrarEntrada(int n) const {
    // TODO 5b: si n es menor que 1 o mayor que bitacora.size(), imprima
    //          "Entrada fuera de rango: la bitacora tiene " y el tamano, y regrese.
    cout << n << ". " << bitacora[n - 1] << endl;
}

// ============ LO QUE SIGUE YA ESTA COMPLETO: NO LO MODIFIQUE ============
int main() {
    Cerradura puerta("2580");       // PIN de fabrica (el reto pide cambiarlo)
    int op = -1;
    do {
        cout << "\n===== CERRADURA DIGITAL DEL LABORATORIO =====\n"
             << "1. Abrir la puerta  2. Ver la bitacora  3. Ver una entrada  0. Salir\n"
             << "Opcion: ";
        op = aNumero(leerLinea());
        if (op == 1) {
            cout << "PIN: ";
            cout << puerta.intentarAbrir(leerLinea()) << endl;
        } else if (op == 2) {
            puerta.mostrarBitacora();
        } else if (op == 3) {
            cout << "Numero de entrada: ";
            puerta.mostrarEntrada(aNumero(leerLinea()));
        } else if (op != 0) {
            cout << "Opcion invalida" << endl;
        }
    } while (op != 0);
    cout << "Fin del programa" << endl;
    return 0;
}
