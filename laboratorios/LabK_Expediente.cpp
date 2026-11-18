// ============================================================
//  TESI 2105 - Programacion Orientada a Objetos
//  Instituto Tecnologico de Puerto Rico - Recinto de Manati
//  Unidad K: Ficheros y excepciones
//  Laboratorio K: El expediente academico
//  CODIGO BASE PARA EL ESTUDIANTE
//
//  Nombre: ______________________   Fecha: ____________
//
//  El programa lee un archivo de datos de la Oficina de Registro
//  (numero,nombre,nota1,nota2,nota3), calcula los promedios, muestra
//  un resumen y escribe informe.txt. Las lineas danadas se rechazan
//  con la excepcion que las detuvo y el programa sigue.
//
//  Complete las 6 partes marcadas con TODO. No modifique el tipo
//  Estudiante, convertirNota, mostrarResumen ni main.
//  Guarde LabK_estudiantes.txt, LabK_seccion2.txt y LabK_seccion3.txt
//  en la misma carpeta donde ejecuta el programa. Compile con:
//      g++ -std=c++17 -Wall -Wextra -o expediente LabK_Expediente.cpp
//  Mientras falten partes, g++ avisa "unused parameter":
//  el aviso desaparece cuando la funcion usa su parametro.
// ============================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// ---------- Tipo (YA HECHO) ----------
struct Estudiante {
    int    numero;
    string nombre;
    double nota1, nota2, nota3;
    double promedio() const { return (nota1 + nota2 + nota3) / 3; }
};

// ---------- 1. La excepcion propia ----------
//  Se lanza cuando el archivo de datos no existe.
//  e.what() debe decir:  no se encontro el archivo LabK_seccion9.txt
class ArchivoNoEncontrado : public runtime_error {
public:
    ArchivoNoEncontrado(const string& nombre)
        : runtime_error("") {
        // TODO 1: el mensaje se le pasa a runtime_error en la lista de
        //         inicializacion. Cambie "" por:
        //         "no se encontro el archivo " + nombre
        //         (el cuerpo de este constructor queda vacio)
    }
};

// ---------- 2. Abrir y validar ----------
void abrirDatos(ifstream& f, const string& nombre) {
    // TODO 2: abra el archivo con f.open(nombre).
    //         Si f.is_open() es false, lance la excepcion propia:
    //         throw ArchivoNoEncontrado(nombre);
}

// ---------- 3. Separar los campos de una linea CSV ----------
//  "84231,Ana Rivera,90,85,92"  ->  {"84231", "Ana Rivera", "90", "85", "92"}
vector<string> separarCampos(const string& linea) {
    vector<string> campos;
    // TODO 3: cree un stringstream con la linea y, mientras
    //         getline(ss, campo, ',') funcione, guarde campo en campos.
    return campos;
}

// ---------- (YA HECHA) Convierte una nota y revisa el rango ----------
double convertirNota(const string& texto) {
    double n = stod(texto);                       // puede lanzar invalid_argument
    if (n < 0 || n > 100)
        throw out_of_range("nota fuera de rango: " + texto);
    return n;
}

// ---------- 4. Convertir los campos en un Estudiante ----------
Estudiante convertir(const vector<string>& c) {
    Estudiante e{};
    // TODO 4: si c.size() no es 5, lance
    //         invalid_argument("se esperaban 5 campos y hay " + to_string(c.size()))
    //         Luego: numero con stoi(c[0]), nombre = c[1] y las tres notas
    //         con convertirNota(c[2]), convertirNota(c[3]) y convertirNota(c[4]).
    //         Aqui NO va try: las excepciones suben a quien llamo.
    return e;
}

// ---------- 5. Leer el archivo linea a linea ----------
//  Para cada linea danada imprime, por ejemplo:
//  Linea 4 rechazada [invalid_argument]: stod
//  Linea 4 rechazada [out_of_range]: nota fuera de rango: 105
vector<Estudiante> leerExpedientes(ifstream& f, int& rechazadas) {
    vector<Estudiante> lista;
    // TODO 5: a) lea con getline la linea 1 (el encabezado) y no la use.
    //         b) while (getline(f, linea)): sume 1 al numero de linea
    //            (el encabezado es la linea 1) y salte las lineas vacias.
    //            NO use while (!f.eof()).
    //         c) dentro de un try:  lista.push_back(convertir(separarCampos(linea)));
    //         d) un catch para invalid_argument y otro para out_of_range:
    //            imprima el mensaje de arriba con e.what() y sume 1 a rechazadas.
    //         e) al salir del ciclo, cierre el archivo con f.close().
    return lista;
}

// ---------- 6. Escribir el informe ----------
//  informe.txt debe quedar asi (dos decimales):
//      INFORME DE PROMEDIOS - OFICINA DE REGISTRO
//      Datos: LabK_estudiantes.txt
//      84231,Ana Rivera,89.00
//      ...
//      Estudiantes: 5
//  Devuelve cuantos estudiantes escribio (0 si no pudo crear el archivo).
int escribirInforme(const vector<Estudiante>& lista, const string& archivo, const string& origen) {
    // TODO 6: abra un ofstream con archivo y compruebe is_open().
    //         Use out << fixed << setprecision(2); escriba las dos lineas
    //         de encabezado, una linea por estudiante con e.promedio()
    //         y la linea final. Cierre con close() y devuelva la cantidad.
    return 0;
}

// ---------- (YA HECHA) Resumen en pantalla ----------
void mostrarResumen(const vector<Estudiante>& lista, int rechazadas) {
    cout << "----- Resumen -----" << endl;
    for (const Estudiante& e : lista)
        cout << e.numero << " " << e.nombre << ": " << e.promedio() << endl;
    cout << "Estudiantes leidos: " << lista.size() << endl;
    cout << "Lineas rechazadas: " << rechazadas << endl;
    if (lista.empty()) {
        cout << "No hay estudiantes validos" << endl;
        return;
    }
    double suma = 0;
    size_t mejor = 0;
    for (size_t i = 0; i < lista.size(); i++) {
        suma += lista[i].promedio();
        if (lista[i].promedio() > lista[mejor].promedio()) mejor = i;
    }
    cout << "Promedio del grupo: " << suma / lista.size() << endl;
    cout << "Mejor promedio: " << lista[mejor].numero << " " << lista[mejor].nombre
         << " (" << lista[mejor].promedio() << ")" << endl;
}

// ============ main: YA ESTA COMPLETO, NO LO MODIFIQUE ============
int main() {
    string nombre;
    cout << "===== EXPEDIENTE ACADEMICO - OFICINA DE REGISTRO =====" << endl;
    cout << "Archivo de datos: ";
    cin >> nombre;
    cout << fixed << setprecision(2);
    try {
        ifstream f;
        abrirDatos(f, nombre);
        int rechazadas = 0;
        vector<Estudiante> lista = leerExpedientes(f, rechazadas);
        mostrarResumen(lista, rechazadas);
        int n = escribirInforme(lista, "informe.txt", nombre);
        cout << "Informe guardado en informe.txt (" << n << " estudiantes)" << endl;
    } catch (const ArchivoNoEncontrado& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "Fin del programa" << endl;
    return 0;
}
