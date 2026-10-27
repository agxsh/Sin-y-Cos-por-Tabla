#include <iostream>
#include <stdint.h>
#include <cmath>

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
    const float PI = 3.14159265f;
    float errorMaxSeno = 0.0f;
    float errorMaxCoseno = 0.0f;
    int gradoMaxSeno = 0;
    int gradoMaxCoseno = 0;

    int errorMaxQ14Seno = 0;
    int errorMaxQ14Coseno = 0;

    for (int grado = 0; grado <= 90; grado++) {
        float angulo = grado * PI / 180.0f;

        float senoCalculado = calcularSeno(angulo);
        float cosenoCalculado = calcularCoseno(angulo);

        // Referencias utilizadas exclusivamente para validar.
        float senoReferencia = sin(angulo);
        float cosenoReferencia = cos(angulo);

        float errorSeno = fabs(senoCalculado - senoReferencia);
        float errorCoseno = fabs(cosenoCalculado - cosenoReferencia);

        if (errorSeno > errorMaxSeno) {
            errorMaxSeno = errorSeno;
            gradoMaxSeno = grado;
        }

        if (errorCoseno > errorMaxCoseno) {
            errorMaxCoseno = errorCoseno;
            gradoMaxCoseno = grado;
        }

        int diferenciaSeno =
            convertirAQ14(senoCalculado) -
            convertirAQ14(senoReferencia);

        int diferenciaCoseno =
            convertirAQ14(cosenoCalculado) -
            convertirAQ14(cosenoReferencia);

        if (diferenciaSeno < 0)
            diferenciaSeno = -diferenciaSeno;

        if (diferenciaCoseno < 0)
            diferenciaCoseno = -diferenciaCoseno;

        if (diferenciaSeno > errorMaxQ14Seno)
            errorMaxQ14Seno = diferenciaSeno;

        if (diferenciaCoseno > errorMaxQ14Coseno)
            errorMaxQ14Coseno = diferenciaCoseno;
    }

    cout << "ERROR MAXIMO EN PUNTO FLOTANTE\n";

    cout << "Seno: " << errorMaxSeno
         << " en " << gradoMaxSeno << " grados\n";

    cout << "Coseno: " << errorMaxCoseno
         << " en " << gradoMaxCoseno << " grados\n";

    cout << "\nDIFERENCIA MAXIMA EN Q1.14\n";

    cout << "Seno: " << errorMaxQ14Seno << " unidades\n";
    cout << "Coseno: " << errorMaxQ14Coseno << " unidades\n";

    return 0;
}
