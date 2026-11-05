#include <iostream>
#include <stdint.h>
#include <stdio.h>

using namespace std;

// ======================================================
// VALIDAR RANGO DE ENTRADA
// ======================================================

bool validar_entrada(float valor, int bits_fraccionarios) {

    float escala = 1 << bits_fraccionarios;

    float minimo = -32768.0f / escala;
    float maximo = 32767.0f / escala;

    if (valor < minimo || valor > maximo) {
        return false;
    }

    return true;
}

// ======================================================
// CONVERSION DE FLOAT A PUNTO FIJO
// ======================================================

int16_t convertir_a_Q(float valor, int bits_fraccionarios) {

    float escala = 1 << bits_fraccionarios;
    float temporal = valor * escala;

    if (temporal >= 0) {
        temporal = temporal + 0.5f;
    } else {
        temporal = temporal - 0.5f;
    }

    return (int16_t)temporal;
}

// ======================================================
// REDONDEO DE UNA DIVISION ENTERA
// ======================================================

int32_t division_redondeada(int32_t numerador, int32_t denominador) {

    if (denominador == 0) {
        return 0;
    }

    int signo = 1;

    if (numerador < 0) {
        signo = -signo;
        numerador = -numerador;
    }

    if (denominador < 0) {
        signo = -signo;
        denominador = -denominador;
    }

    int32_t cociente = numerador / denominador;
    int32_t resto = numerador % denominador;

    if (resto * 2 >= denominador) {
        cociente++;
    }

    return cociente * signo;
}

// ======================================================
// VERIFICAR RANGO DE UN FORMATO Q DE 16 BITS
// ======================================================

bool dentro_de_rango(int32_t valor) {
    return (valor >= -32768 && valor <= 32767);
}

// ======================================================
// REPRESENTACION BINARIA
// ======================================================

void binario(int16_t num, char salida[18], int Q_entera) {

    uint16_t bits = (uint16_t)num;
    int idx = 0;

    for (int bit = 15; bit >= 0; bit--) {

        salida[idx++] = ((bits >> bit) & 1) ? '1' : '0';

        if (bit == (15 - Q_entera)) {
            salida[idx++] = '.';
        }
    }

    salida[idx] = '\0';
}

// ======================================================
// MOSTRAR UN NUMERO EN FORMATO Q
// ======================================================

void mostrar_Q(const char* nombre, int16_t valor, int Q_entera) {

    char representacion[18];

    binario(valor, representacion, Q_entera);

    cout << nombre << endl;

    printf("Decimal: %d | Hexadecimal: x%04X | Binario: %s\n",
           valor, (uint16_t)valor, representacion);
}

// ======================================================
// PROGRAMA PRINCIPAL
// ======================================================

int main() {

    float num1, num2;

    int16_t num1_Q3_12;
    int16_t num2_Q7_8;

    int16_t num1_Q7_8;
    int16_t suma_Q7_8;

    int32_t suma_temporal;
    int32_t producto_temporal;
    int32_t producto_Q7_8;

    int32_t division_temporal;
    int32_t division_Q7_8;

    // --------------------------------------------------
    // 1. INGRESO DE NUMEROS
    // --------------------------------------------------

    cout << "Ingrese el primer numero (Q3.12): ";
    cin >> num1;

    cout << "Ingrese el segundo numero (Q7.8): ";
    cin >> num2;

    // --------------------------------------------------
    // 2. VALIDACION DE ENTRADAS
    // --------------------------------------------------

    if (!validar_entrada(num1, 12)) {
        cout << "\nERROR: el primer numero esta fuera del rango Q3.12.\n";
        return 0;
    }

    if (!validar_entrada(num2, 8)) {
        cout << "\nERROR: el segundo numero esta fuera del rango Q7.8.\n";
        return 0;
    }

    // --------------------------------------------------
    // 3. CONVERSION A FORMATOS Q DIFERENTES
    // --------------------------------------------------

    num1_Q3_12 = convertir_a_Q(num1, 12);
    num2_Q7_8  = convertir_a_Q(num2, 8);

    cout << "\n===== FORMATOS Q INICIALES =====\n";

    mostrar_Q("Numero 1 - Q3.12:", num1_Q3_12, 3);
    cout << endl;

    mostrar_Q("Numero 2 - Q7.8:", num2_Q7_8, 7);
    cout << endl;

    // --------------------------------------------------
    // 4. CONVERSION DE Q3.12 A Q7.8 Y SUMA
    // --------------------------------------------------

    cout << "\n===== ALINEACION Y SUMA =====\n";

    num1_Q7_8 = (int16_t)division_redondeada(num1_Q3_12, 16);

    mostrar_Q("Numero 1 convertido a Q7.8:", num1_Q7_8, 7);
    cout << endl;

    suma_temporal = (int32_t)num1_Q7_8 + num2_Q7_8;

    if (dentro_de_rango(suma_temporal)) {
        suma_Q7_8 = (int16_t)suma_temporal;
        mostrar_Q("Suma final en Q7.8:", suma_Q7_8, 7);
    } 
    
    else {
        cout << "ERROR: desbordamiento en la suma.\n";
    }

    cout << endl;

    // --------------------------------------------------
    // 5. MULTIPLICACION EN PUNTO FIJO
    // --------------------------------------------------

    cout << "\n===== MULTIPLICACION =====\n";

    producto_temporal = (int32_t)num1_Q3_12 * (int32_t)num2_Q7_8;

    cout << "Producto intermedio (escala Q10.20): "<< producto_temporal << endl;
    producto_Q7_8 = division_redondeada(producto_temporal, 4096);

    cout << endl;

    if (dentro_de_rango(producto_Q7_8)) {
        mostrar_Q("Producto final en Q7.8:", (int16_t)producto_Q7_8, 7);
    } 
    
    else {
        cout << "ERROR: desbordamiento en la multiplicacion.\n";
    }

    cout << endl;

    // --------------------------------------------------
    // 6. DIVISION EN PUNTO FIJO
    // --------------------------------------------------

    cout << "\n===== DIVISION =====\n";

    if (num2_Q7_8 == 0) {
        cout << "ERROR: no se puede dividir por cero.\n";
    } 
    
    else {

        division_temporal = (int32_t)num1_Q3_12 * 16;
        division_Q7_8 = division_redondeada(division_temporal, num2_Q7_8);

        if (dentro_de_rango(division_Q7_8)) {
            mostrar_Q("Division final en Q7.8:", (int16_t)division_Q7_8, 7);
        } 

        else {
            cout << "ERROR: desbordamiento en la division.\n";
        }
    }

    cout << "\n===== FIN DEL PROGRAMA =====\n";

    return 0;
}