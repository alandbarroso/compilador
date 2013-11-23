;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;; Teste ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Variaveis vindas da pilha
EMPILHA <
END_INICIAL <
TAMANHO <

DESEMPILHA <

TOPO <

@ /0000
JP MAIN

; bloco 1 a ser empilhado
TAMANHO1 K =7
BLOCO1 K /0001
K /0002
K /0003
K /0004
K /0005
K /0006
K /0007

; bloco 2 a ser empilhado
TAMANHO2 K =9
BLOCO2 K /0008
K /0009
K /000A
K /000B
K /000C
K /000D
$ =2
K /000E

MAIN LV BLOCO1
	MM END_INICIAL

	LD TAMANHO1
	MM TAMANHO

	SC EMPILHA

	LV BLOCO1
	MM END_INICIAL

	LD TAMANHO1
	MM TAMANHO

	SC EMPILHA

	SC DESEMPILHA

	LV BLOCO2
	MM END_INICIAL

	LD TAMANHO2
	MM TAMANHO

	SC EMPILHA	
ENDMAIN HM MAIN

# MAIN