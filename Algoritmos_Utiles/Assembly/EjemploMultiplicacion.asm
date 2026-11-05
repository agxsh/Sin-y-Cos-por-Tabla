
        .ORIG x3000

; Calcular R2 = R0 * R1
; En esta prueba: 7 * 5 = 35

        AND R0, R0, #0
        ADD R0, R0, #7      ; Multiplicando

        AND R1, R1, #0
        ADD R1, R1, #5      ; Cantidad de sumas

        AND R2, R2, #0      ; Acumulador

MULT    ADD R2, R2, R0      ; Acumular R0
        ADD R1, R1, #-1     ; Una suma menos
        BRp MULT            ; Repetir mientras R1 > 0

FIN     HALT

        .END
