#include <stdio.h>
#include <stdlib.h>
#include "carro.h"

struct carro_{
    int placa_do_carro;
    int chegada;
    int saida;
    float desconto;
};


CARRO* criar_carro(int placa, int chegada, int saida){
    CARRO* novo = malloc(sizeof(CARRO));
    if(novo != NULL){
        novo->placa_do_carro = placa;
        novo->chegada = chegada;
        novo->saida = saida;
        novo->desconto = 0;
    }
    return novo;
}
int placa_carro(CARRO* carro){
    int p = carro->placa_do_carro;
    return(p);
}
int hora_valida(CARRO* carro){
    if(carro->chegada < 8){
        return 3;
    }
    else if(carro->saida > 22){
        return 4;
    }
    else if(carro->chegada >= carro->saida){
        return 6;
    }
    else{
        return 1;
    }
}
void imprimir_carro(CARRO* carro){
    float valor;
    valor = carro->saida - carro->chegada;
    valor = valor * 3;
    valor = valor - carro->desconto;
    printf("Placa do veículo: %d ", carro->placa_do_carro);
    printf("Valor a pagar: %.2f\n", valor);
    return;
}
boolean verificar_retirada(CARRO* c1, CARRO* c2){
    if(c1 != NULL && c2 != NULL){
        if(c1->saida <= c2->chegada)
            return TRUE;
        else
            return FALSE;
    }
    return FALSE;
}
void aplicar_desconto(CARRO* carro){
    carro->desconto = 3*(carro->saida - carro->chegada)/10;
}

void carro_apagar(CARRO** aux){
    (*aux)->chegada = 0;
    (*aux)->desconto = 0;
    (*aux)->placa_do_carro = 0;
    (*aux)->saida = 0;
    free(aux);
    //*aux = NULL;
    return;
}
int tempo_restante(int hora_atual, CARRO* c){
    if(c != NULL){
        return(c->saida - hora_atual);
    }
}

int hora(CARRO* c){
    return c->chegada;
}
