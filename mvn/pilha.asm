;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;; REGISTRO DE ATIVACAO ;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EMPILHA > ; Funçao de empilhar
; PARAMETROS DA FUNCAO EMPILHA
ENDINICIAL > ; Endereço inicial do bloco a ser empilhado
TAMANHO > ; Tamanho do bloco a ser copado


DESEMPILHA > ; Funcao de desempilhar

TOPO > ; Guarda o endereco do topo da pilha

& /0000

TOPO K /0000

;=======================================================;
;====================== EMPILHA ========================;
;=======================================================;

; Parametros
END_INICIAL K /0000
TAMANHO K /0000

; Variaveis auxiliares
TAMANHO_MVN K /0000
TOPO_AUX K /0000

; Constantes
CTE_TAMANHO K =2
OLD_TOPO K /0000

EMPILHA JP /000
	; Multiplica o tamanho por 2
	LD TAMANHO
	* CTE_TAMANHO
	MM TAMANHO_MVN

	; Calcula a nova posicao do topo
	LD TOPO
	MM OLD_TOPO
	- TAMANHO_MVN
	MM TOPO
	MM TOPO_AUX

	; Copiando os arquivos
	LD TAMANHO_MVN
	LOOP_ COPIA JZ FIM_COPIA
		LD END_INICIAL
		MM END_ORIGEM

		LD TOPO_AUX
		MM END_ALVO

		SC COPIA ; Chama a funçao de copia

		; Adiciona 2 aos endereços inicial e ao topo aux
		LD END_INICIAL
		+ CTE_TAMANHO
		MM END_INCIAL

		LD TOPO_AUX
		+ CTE_TAMANHO
		MM TOPO_AUX

		; Diminui tamanho
		LD TAMANHO_MVN
		- CTE_TAMANHO
		MM TAMANHO_MVN

		JP LOOP_COPIA
	FIM_COPIA LD TOPO
	+ CTE_TAMANHO
	MM END_ALVO

	LD OLD_TOPO
	MM END_ORIGEM

	SC COPIA
RS EMPILHA

;===============================
; COPIA
;===============================

; Parametros
END_ORIGEM K /0000
END_ALVO K /0000

; Auxiliares
OP_LOAD LD /000
OP_MOVE MM /000

COPIA JP /000
	; Carrega o valor a ser copiado
	LD OP_LOAD
	+ END_ORIGEM
	MM CARREGA

	; Seta o endereço alvo
	LD OP_MOVE
	+ END_ALVO
	MM COPEIA

	; Carrega no acumulador o valor da origem
	CARREGA JP /000 ; Don't care

	; Copia o valor ao endereço alvo
	COPEIA JP /000 ; Don't care
RS COPIA

;=======================================================;
;===================== DESEMPILHA ======================;
;=======================================================;

DESEMPILHA JP /000
	LD TOPO
	+ CTE_TAMANHO
	+ OP_LOAD
	MM CG_OLD_TOPO

	CG_OLD_TOPO JP /000 ; Don't care

	MM TOPO
RS DESEMPILHA

;=======================================================;
;======================= ACESSA ========================;
;=======================================================;

ACESSA JP /000
	LD OP_LOAD
	+ END_ORIGEM
	MM JOGA_ACM

	; Joga pro acumulador o valor localizado no ponteiro do endereço de origem
	JOGA_ACM JP /000 ; Don't care
RS ACESSA