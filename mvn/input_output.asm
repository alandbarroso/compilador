;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;; FUNCOES INPUT/OUTPUT ;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

READ >
PRINT >

& /0000
;=======================================================;
;======================== READ =========================;
;=======================================================;
READ JP /000
GD /000
MM exptemp 		; 1 byte para decimal e um para unidade (DD UU)
/ CTEH100		; (00 DD)
SC ASCII_TO_HEX ; transforma o ascii da dezena em hexa (00 0D)
* CTEH10		; (00D0)
MM dezenatemp	
LD exptemp		; (DD UU)
* CTEH100		; (UU 00)
/ CTEH100		; (00 UU)
SC ASCII_TO_HEX ; transforma o ascii da unidade em hexa (00 0U)
+ dezenatemp	; (00 DU)
RS READ

;=======================================================;
;======================= PRINT =========================;
;=======================================================;
PRINT JP /000
MM exptemp		; (00 DU)
/ CTEH10		; (00 0D)
SC HEX_TO_ASCII	; transforma a dezena em ascii(00 DD)
* CTEH100		; (DD 00)
MM dezenatemp
LD exptemp		; (00 DU)
/ CTEH10		; (00 0D)
* CTEH10		; (00 D0)
MM temp			
LD exptemp		; (00 DU)
- temp			; (00 0U)
SC HEX_TO_ASCII	; transforma a unidade em ascii(00 UU)
+ dezenatemp	; (DD UU)
PD /100
RS PRINT

;=======================================================;
;===================== ASCII_TO_HEX ====================;
;=======================================================;
ASCII_TO_HEX JP /000
MM ascii
; Se é de 30 a 39 => é decimal
- CTEH40
JN DECIMAL
; Se é A ou a
LD ascii
- CTE_ASCII_A
JZ HEX_A
LD ascii
- CTE_ASCII_a
JZ HEX_A
; Se é B ou b
LD ascii
- CTE_ASCII_B
JZ HEX_B
LD ascii
- CTE_ASCII_b
JZ HEX_B
; Se é C ou c
LD ascii
- CTE_ASCII_C
JZ HEX_C
LD ascii
- CTE_ASCII_c
JZ HEX_C
; Se é D ou d
LD ascii
- CTE_ASCII_D
JZ HEX_D
LD ascii
- CTE_ASCII_d
JZ HEX_D
; Se é E ou e
LD ascii
- CTE_ASCII_E
JZ HEX_E
LD ascii
- CTE_ASCII_e
JZ HEX_E
; Se é F ou f
LD ascii
- CTE_ASCII_F
JZ HEX_F
LD ascii
- CTE_ASCII_f
JZ HEX_F

; Número decimal
DECIMAL LD ascii
- CTEH30
RS ASCII_TO_HEX ; retornando
; A
HEX_A LV /000A
RS ASCII_TO_HEX ; retornando
; B
HEX_B LV /000B
RS ASCII_TO_HEX ; retornando
; C
HEX_C LV /000C
RS ASCII_TO_HEX ; retornando
; D
HEX_D LV /000D
RS ASCII_TO_HEX ; retornando
; E
HEX_E LV /000E
RS ASCII_TO_HEX ; retornando
; F
HEX_F LV /000F
RS ASCII_TO_HEX ; retornando

;=======================================================;
;===================== HEX_TO_ASCII ====================;
;=======================================================;
HEX_TO_ASCII JP /000
MM hex
; Se é de 0 a 9 => é decimal
- CTE_HEX_A
JN ASCII_DECIMAL
; Se é A
LD hex
- CTE_HEX_A
JZ ASCII_A
; Se é B
LD hex
- CTE_HEX_B
JZ ASCII_B
; Se é C
LD hex
- CTE_HEX_C
JZ ASCII_C
; Se é D
LD hex
- CTE_HEX_D
JZ ASCII_D
; Se é E
LD hex
- CTE_HEX_E
JZ ASCII_E
; Se é F
LD hex
- CTE_HEX_F
JZ ASCII_F

; de 0 a 9
ASCII_DECIMAL LD hex
+ CTEH30
RS HEX_TO_ASCII
; A
ASCII_A LD CTE_ASCII_A
RS HEX_TO_ASCII
; B
ASCII_B LD CTE_ASCII_B
RS HEX_TO_ASCII
; C
ASCII_C LD CTE_ASCII_C
RS HEX_TO_ASCII
; D
ASCII_D LD CTE_ASCII_D
RS HEX_TO_ASCII
; E
ASCII_E LD CTE_ASCII_E
RS HEX_TO_ASCII
; F
ASCII_F LD CTE_ASCII_F
RS HEX_TO_ASCII

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;; CONSTANTES ;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
CTEH10 K /10
CTEH30 K /30
CTEH40 K /40
CTEH100 K /100
CTE_ASCII_A K /41
CTE_ASCII_a K /61
CTE_ASCII_B K /42
CTE_ASCII_b K /62
CTE_ASCII_C K /43
CTE_ASCII_c K /63
CTE_ASCII_D K /44
CTE_ASCII_d K /64
CTE_ASCII_E K /45
CTE_ASCII_e K /65
CTE_ASCII_F K /46
CTE_ASCII_f K /66
CTE_HEX_A K /A
CTE_HEX_B K /B
CTE_HEX_C K /C
CTE_HEX_D K /D
CTE_HEX_E K /E
CTE_HEX_F K /F

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;; VARIAVEIS ;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ascii K /0000
exptemp K /0000
dezenatemp K /0000
temp K /0000
hex K /0000

# MAIN