#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double promedio(double a, double b, double c);
char letra(double p);
void reporte(string nombre, double p);

int main() {
    string nombre;
    double p1, p2, p3;
    cin >> nombre >> p1 >> p2 >> p3;
    reporte(nombre, promedio(p1, p2, p3));
}

double promedio(double a, double b, double c) {
    return (a + b + c) / 3;
}

char letra(double p) {
    if (p >= 90) return 'A';
    if (p >= 80) return 'B';
    if (p >= 70) return 'C';
    if (p >= 60) return 'D';
    return 'F';
}

void reporte(string nombre, double p) {
    cout << nombre << ": " << fixed << setprecision(1)
         << p << " (" << letra(round(p)) << ")" << endl;
}
