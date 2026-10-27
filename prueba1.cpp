#include <iostream>
#include <stdint.h>

using namespace std;

int16_t convertirAQ14(float valor) {
    float escalado = valor * 16384.0f;

    if (escalado >= 0.0f)
        return (int16_t)(escalado + 0.5f);
    else
        return (int16_t)(escalado - 0.5f);
}

float calcularSeno(float angulo) {
    float termino = angulo;
    float suma = termino;
    float cuadrado = angulo * angulo;

    for (int n = 1; n <= 7; n++) {
        termino = -termino * cuadrado /
                  ((2 * n) * (2 * n + 1));
        suma = suma + termino;
    }

    return suma;
}

float calcularCoseno(float angulo) {
    float termino = 1.0f;
    float suma = termino;
    float cuadrado = angulo * angulo;

    for (int n = 1; n <= 7; n++) {
        termino = -termino * cuadrado /
                  ((2 * n - 1) * (2 * n));
        suma = suma + termino;
    }

    return suma;
}

int main() {
    float pi = 3.14159265f;
    float angulos[3] = {0.0f, pi / 4.0f, pi / 2.0f};

    for (int i = 0; i < 3; i++) {
        float angulo = angulos[i];
        float seno = calcularSeno(angulo);
        float coseno = calcularCoseno(angulo);

        cout << "Angulo: " << angulo << '\n';

        cout << "  Seno: " << seno
             << " | Q1.14: " << convertirAQ14(seno) << '\n';

        cout << "  Coseno: " << coseno
             << " | Q1.14: " << convertirAQ14(coseno) << '\n';

        cout << '\n';
    }

    return 0;
}
