#include <iostream>
#include <stdint.h>
using namespace std;

int16_t convertirAQ312(float valor) {
    float escalado = valor * 4096.0f;

    if (escalado >= 0.0f) {
        return (int16_t)(escalado + 0.5f);
    } else {
        return (int16_t)(escalado - 0.5f);
    }
}

int calcularIndice(int16_t referenciaQ312) {
    // Convertimos la referencia Q3.12 a grados.
    float grados = ((float)referenciaQ312 / 4096.0f)
                   * (180.0f / 3.14159265f);

    // Redondeamos al grado más cercano.
    return (int)(grados + 0.5f);
}

int main() {
    const int16_t PI_2 = 6434;
    const int16_t PI = 12868;
    const int16_t TRES_PI_2 = 19302;
    const int16_t DOS_PI = 25736;

    float anguloDecimal;
    int16_t anguloQ3_12;
    int16_t diferencia;
    int16_t referencia;

    int cuadrante;
    int signoSeno;
    int signoCoseno;

    while(1){

    cout << "Ingrese el angulo en radianes: ";
    cin >> anguloDecimal;

    // 1. Convertir la entrada decimal a Q3.12.
    anguloQ3_12 = convertirAQ312(anguloDecimal);

    cout << "\n--- CONVERSION A Q3.12 ---" << endl;
    cout << "Angulo ingresado: " << anguloDecimal << endl;
    cout << "Entero Q3.12: " << anguloQ3_12 << endl;
    cout << "Angulo representado: "
         << (float)anguloQ3_12 / 4096.0f
         << " radianes" << endl;

    // 2. Identificar el cuadrante y calcular la referencia.
    if (anguloQ3_12 == 0 || anguloQ3_12 == DOS_PI) {
        referencia = 0;
        cuadrante = 0;
        signoSeno = 0;
        signoCoseno = 1;

        cout << "\nCaso especial: 0 o 2*pi" << endl;
    } else {
        diferencia = anguloQ3_12 - PI_2;

        if (diferencia < 0) {
            cuadrante = 1;
            referencia = anguloQ3_12;
            signoSeno = 1;
            signoCoseno = 1;
        } else if (diferencia == 0) {
            cuadrante = 0;
            referencia = PI_2;
            signoSeno = 1;
            signoCoseno = 0;

            cout << "\nCaso especial: pi/2" << endl;
        } else {
            diferencia = anguloQ3_12 - PI;

            if (diferencia < 0) {
                cuadrante = 2;
                referencia = PI - anguloQ3_12;
                signoSeno = 1;
                signoCoseno = -1;
            } else if (diferencia == 0) {
                cuadrante = 0;
                referencia = 0;
                signoSeno = 0;
                signoCoseno = -1;

                cout << "\nCaso especial: pi" << endl;
            } else {
                diferencia = anguloQ3_12 - TRES_PI_2;

                if (diferencia < 0) {
                    cuadrante = 3;
                    referencia = anguloQ3_12 - PI;
                    signoSeno = -1;
                    signoCoseno = -1;
                } else if (diferencia == 0) {
                    cuadrante = 0;
                    referencia = PI_2;
                    signoSeno = -1;
                    signoCoseno = 0;

                    cout << "\nCaso especial: 3*pi/2" << endl;
                } else {
                    cuadrante = 4;
                    referencia = DOS_PI - anguloQ3_12;
                    signoSeno = -1;
                    signoCoseno = 1;
                }
            }
        }
    }

    
    int indice = calcularIndice(referencia);

    cout << "Indice de tabla: " << indice << endl;


    // 3. Mostrar los resultados.
    cout << "\n--- RESULTADOS ---" << endl;
    cout << "Cuadrante: " << cuadrante << endl;
    cout << "Referencia Q3.12: " << referencia << endl;
    cout << "Referencia en radianes: "
         << (float)referencia / 4096.0f << endl;
    cout << "Signo del seno: " << signoSeno << endl;
    cout << "Signo del coseno: " << signoCoseno << endl;
system("pause");
system("cls");
    }
    return 0;
}
