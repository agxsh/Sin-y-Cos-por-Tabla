#include <stdio.h>
#include <stdint.h>
#include <math.h>

int multiplicacion_cordic_q312(void) {
    // el algoritmo de cordic configurado en modo lineal se puede entender de la siguiente forma
    // funciona con 3 variables, la primera(x) donde estara el valor fijo del primer factor
    // la segunda(y) funciona como acumulador
    // y la tercera(z) como "contador" el cual iremos vaciando
    // la idea es que a Z se le resten (o sumen) potencias fijas de 2 (desplazamiento de bits)
    // mientras que, a la variable Y se le realiza la operacion inversa, pero multiplicada por X
    // es decir ->      z = z +- 2^(-n);        y = y +- x * 2^(-n)
    // se realiza en bucle hasta que Z llegue a 0
    // mientras Z > 0, se resta en Z y se suma en Y
    // si Z < 0, nos pasamos y se corrige, se suma en Z y se resta en Y
    // si Z == 0 llegamos a un resultado exacto, y en ese momento tendremos guardado en Y el resultado de a*b o x*z

    // variables
    float a, b, resultado;
    int16_t a_q12, b_q12;
    int32_t z;              // multiplicador que voy vaciar
    int32_t y_q12;
    int32_t current_z;      // constante movil
    int32_t current_x;      // multiplicando movil

    printf("Ingrese el primer factor: ");
    scanf("%f", &a);

    printf("Ingrese el segundo factor: ");
    scanf("%f", &b);

    // casteo de float a punto fijo formato Q3.12 --> multiplica por 2^12
    a_q12 = (int16_t)lroundf(a * 4096.0f);
    b_q12 = (int16_t)lroundf(b * 4096.0f);

    // se inicializa a z con el multiplicador
    z = b_q12;

    // se inicializa el acumulador en 0
    y_q12 = 0;

    // constante movil iniciada en 8(2^3)
    // multiplicada por 2^12
    current_z = 8 * 4096; // * 2^3 --> 8.0 en Q3.12

    // realizo lo mismo que en current_z pero multiplicado por x
    current_x = (int32_t)a_q12 * 8; // * 2^14 para evitar perder decimales

    for (int i=0; i < 16; i++) {
        if (z == 0) break;
        if (z > 0) {
            z -= current_z;
            y_q12 += current_x;
        } else {
            z += current_z;
            y_q12 -= current_x;
        }

        current_x /= 2;
        current_z /= 2;
    }

    // reduccion a Q3.12 con redondeo
    resultado = (float)y_q12 / 4096.0f;

    printf("Resultado directo (float original): %f\n", a * b);
    printf("Resultado ideal cuantizado: %f\n", (float)((int32_t)a_q12 * b_q12) / 16777216.0f);
    printf("Resultado en formato Q7.8: %i\n", y_q12);
    printf("Resultado convertido en decimal: %f\n", resultado);

    return (int16_t)y_q12;
    // return 0;
}