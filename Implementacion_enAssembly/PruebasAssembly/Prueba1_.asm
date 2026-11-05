        .ORIG x3000
; En esta primer etapa hacemos pruebas para determinar la funcion de
; los cuadrantes, casos especiales y signos de Sen y Cos
; =====================================================
; PROGRAMA PRINCIPAL
; =====================================================

INICIO

        ; Cargar el angulo de prueba
        LEA R5, VARIABLES
        LD  R0, ANGULO_ENTRADA
        STR R0, R5, #0

        ; Determinar cuadrante
        JSR DETERMINAR_CUADRANTE

        ; Por ahora, detener ejecucion
        HALT


; =====================================================
; DETERMINAR_CUADRANTE
;
; ENTRADA:
;   ANGULO en memoria (Q3.12)
;
; SALIDAS:
;   REFERENCIA
;   CUADRANTE
;   SIGNO_SENO
;   SIGNO_COSENO
;   CASO_ESPECIAL
;
; =====================================================

DETERMINAR_CUADRANTE

        LEA R5, VARIABLES

        ; Cargar angulo original
        LDR R0, R5, #0

        ; Inicializar salidas
        AND R1, R1, #0
        STR R1, R5, #1
        STR R1, R5, #2
        STR R1, R5, #3
        STR R1, R5, #4
        STR R1, R5, #5

        ; ---------------------------------
        ; ANGULO = 0
        ; ---------------------------------

        ADD R1, R0, #0
        BRz CASO_0

        ; ---------------------------------
        ; ANGULO < PI/2 ?
        ; ---------------------------------

        LD  R1, C_PI2
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R0, R1

        BRn CUADRANTE_1
        BRz CASO_90

        ; ---------------------------------
        ; ANGULO < PI ?
        ; ---------------------------------

        LD  R1, C_PI
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R0, R1

        BRn CUADRANTE_2
        BRz CASO_180

        ; ---------------------------------
        ; ANGULO < 3PI/2 ?
        ; ---------------------------------

        LD  R1, C_3PI2
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R0, R1

        BRn CUADRANTE_3
        BRz CASO_270

        ; ---------------------------------
        ; ANGULO = 2PI ?
        ; ---------------------------------

        LD  R1, C_2PI
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R0, R1

        BRz CASO_360
        BRn CUADRANTE_4

        RET


; =====================================================
; CUADRANTE 1
; referencia = angulo
; seno = +1
; coseno = +1
; =====================================================

CUADRANTE_1

        LEA R5, VARIABLES

        LDR R0, R5, #0
        STR R0, R5, #1

        AND R1, R1, #0
        ADD R1, R1, #1

        STR R1, R5, #2
        STR R1, R5, #3
        STR R1, R5, #4

        RET


; =====================================================
; CUADRANTE 2
; referencia = PI - angulo
; seno = +1
; coseno = -1
; =====================================================

CUADRANTE_2 LEA R5, VARIABLES

        LD  R1, C_PI
        LDR R0, R5, #0

        NOT R0, R0
        ADD R0, R0, #1

        ADD R1, R1, R0
        STR R1, R5, #1       ; REFERENCIA

        AND R1, R1, #0
        ADD R1, R1, #2
        STR R1, R5, #2       ; CUADRANTE

        AND R1, R1, #0
        ADD R1, R1, #1
        STR R1, R5, #3       ; SIGNO_SENO = +1

        AND R1, R1, #0
        ADD R1, R1, #-1
        STR R1, R5, #4       ; SIGNO_COSENO = -1

        RET


; =====================================================
; CUADRANTE 3
; referencia = angulo - PI
; seno = -1
; coseno = -1
; =====================================================

CUADRANTE_3

        LEA R5, VARIABLES

        LDR R0, R5, #0
        LD  R1, C_PI

        NOT R1, R1
        ADD R1, R1, #1

        ADD R1, R0, R1
        STR R1, R5, #1

        AND R1, R1, #0
        ADD R1, R1, #3
        STR R1, R5, #2

        ADD R1, R1, #-4
        STR R1, R5, #3
        STR R1, R5, #4

        RET


; =====================================================
; CUADRANTE 4
; referencia = 2PI - angulo
; seno = -1
; coseno = +1
; =====================================================

CUADRANTE_4

        LEA R5, VARIABLES

        LD  R1, C_2PI
        LDR R0, R5, #0

        NOT R0, R0
        ADD R0, R0, #1

        ADD R1, R1, R0
        STR R1, R5, #1

        AND R1, R1, #0
        ADD R1, R1, #4
        STR R1, R5, #2

        ADD R1, R1, #-5
        STR R1, R5, #3

        NOT R1, R1
        ADD R1, R1, #1
        STR R1, R5, #4

        RET


; =====================================================
; CASOS ESPECIALES
; =====================================================

CASO_0
        BR CASO_EJE_0


CASO_90

        LEA R5, VARIABLES

        AND R1, R1, #0
        ADD R1, R1, #1
        STR R1, R5, #3

        AND R1, R1, #0
        STR R1, R5, #4

        BR CASO_ESPECIAL


CASO_180

        LEA R5, VARIABLES

        AND R1, R1, #0
        STR R1, R5, #3

        ADD R1, R1, #-1
        STR R1, R5, #4

        BR CASO_ESPECIAL


CASO_270

        LEA R5, VARIABLES

        AND R1, R1, #0
        ADD R1, R1, #-1
        STR R1, R5, #3

        AND R1, R1, #0
        STR R1, R5, #4

        BR CASO_ESPECIAL


CASO_360
        BR CASO_EJE_0


CASO_EJE_0

        LEA R5, VARIABLES

        AND R1, R1, #0
        STR R1, R5, #3

        ADD R1, R1, #1
        STR R1, R5, #4

        BR CASO_ESPECIAL


CASO_ESPECIAL

        LEA R5, VARIABLES

        AND R1, R1, #0
        STR R1, R5, #1

        STR R1, R5, #2

        ADD R1, R1, #1
        STR R1, R5, #5

        RET

; =====================================================
; ENTRADA DE PRUEBA
; =====================================================

ANGULO_ENTRADA .FILL #10000

; =====================================================
; CONSTANTES Q3.12
; =====================================================

C_PI2       .FILL #6434
C_PI        .FILL #12868
C_3PI2      .FILL #19302
C_2PI       .FILL #25736


; =====================================================
; VARIABLES DINAMICAS
; =====================================================

VARIABLES   .BLKW #6

; +0 ANGULO
; +1 REFERENCIA
; +2 CUADRANTE
; +3 SIGNO_SENO
; +4 SIGNO_COSENO
; +5 CASO_ESPECIAL

        .END
