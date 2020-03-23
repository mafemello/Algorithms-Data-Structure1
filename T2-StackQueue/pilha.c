#include "stdio.h"
#include "stdlib.h"
#include "carro.h"
#include "pilha.h"


struct pilha_{
    NO* topo;
    int tamanho;
};

struct no_ {
    CARRO* carro;
    NO *anterior;
};

PILHA* pilha_criar(void){
    PILHA* pilha = (PILHA *) malloc(sizeof (PILHA));
    if (pilha != NULL) {
        pilha->topo = NULL;
        pilha->tamanho = 0;
    }
    return (pilha);
}
int pilha_empilhar(PILHA* pilha, CARRO* carro){
    NO* pnovo = (NO *) malloc(sizeof (NO));
    if (pnovo != NULL) {
        pnovo->carro = carro;
        pnovo->anterior = pilha->topo;
        pilha->topo = pnovo;
        pilha->tamanho++;
        return (1);
    }
    return (ERRO);
}
void pilha_apagar(PILHA** pilha){
    NO* paux;
    if ( ((*pilha) != NULL) && (!pilha_vazia(*pilha)) ) {
        while ( (*pilha)->topo != NULL) {
            paux = (*pilha)->topo;
            (*pilha)->topo = (*pilha)->topo->anterior;
            carro_apagar(&paux->carro);
            //paux->anterior = NULL;
            //free(paux); 
            paux = NULL;
        }
    }
    free(*pilha);
    *pilha = NULL;
    return;
}
    
int pilha_vazia(PILHA* pilha){
    if(pilha != NULL){
        if(pilha->tamanho == 0){
            return TRUE;
        }
    }
    return FALSE;

}

int pilha_tamanho(PILHA* pilha){
    if(pilha != NULL){
        return pilha->tamanho;
    }
}

CARRO* pilha_topo(PILHA* pilha){
    if ((pilha != NULL) && (pilha_vazia(pilha) == 0) ){
        return (pilha->topo->carro);
    }
    return (NULL);
}

CARRO* pilha_desempilhar(PILHA* pilha){
    if ((pilha != NULL)){
        if(pilha->topo != NULL){
            NO* pno = pilha->topo;
            CARRO* carro = pilha->topo->carro;
            pilha->topo = pilha->topo->anterior;
            pno->anterior=NULL;
            pilha->tamanho--;
            return (carro);
        }
    }
    return (NULL);
}

void pilha_imprimir(PILHA* p){
    NO* aux = malloc(sizeof(NO));
    aux = p->topo;
    if(p->topo == NULL){
    }
    while(aux != NULL){
        imprimir_carro(aux->carro);
        aux = aux->anterior;
    }
    return;
}

CARRO* pilha_busca(PILHA* p, int chave){
    if(p != NULL){
        if(chave == 0){
            return p->topo->carro;
        }
        NO* aux = p->topo;
        if(chave <= pilha_tamanho(p)){
            for(int i = 0; i<chave; i++){
                aux = aux->anterior;
            }
            if(aux != NULL){
                return aux->carro;
            }
        }
    }
}
boolean pilha_cheia(PILHA* p){
    if(p->tamanho >= 5){
        return TRUE;
    }
    return FALSE;
}

CARRO* pilha_busca2(PILHA* p, int chave){
    NO* aux = p->topo;
    while(aux != NULL){
        if(placa_carro(aux->carro) == chave)
            return aux->carro;
        else
            aux = aux->anterior;
    }
    return NULL;
}