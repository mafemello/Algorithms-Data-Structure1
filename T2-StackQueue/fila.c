#include "stdio.h"
#include "stdlib.h"
#include "carro.h"
#include "fila.h"


struct no_{
    CARRO* carro;
    NO* proximo;
};

struct fila_{
    NO* inicio;
    NO* fim;
    int tamanho;
};


FILA *fila_criar(void){
    FILA *fila = (FILA *) malloc(sizeof(FILA));
    if(fila != NULL){
        fila->inicio = NULL;
        fila->fim = NULL;
        fila->tamanho = 0;    
    }
    else{
        printf("Não há memória suficiente");
    }
    return (fila);
}

void fila_apagar(FILA **f){
    NO* aux;
    if ( ((*f) != NULL) && (!fila_vazia(*f)) ) {
        while ( (*f)->inicio != NULL) {
            aux = (*f)->inicio;
            (*f)->inicio = (*f)->inicio->proximo;
            carro_apagar(&aux->carro);
            //free(aux); 
            aux = NULL;
        }
    }
    free(*f);
    *f = NULL;
    return;
}

boolean fila_inserir(FILA *fila, CARRO *carro){
    if (fila != NULL && (!fila_cheia(fila)) ){
        NO* n = (NO*) malloc(sizeof(NO));
        if(n != NULL){
            n->carro = carro;
            n->proximo = NULL;
            if(fila->inicio == NULL){
                fila->inicio = n;
            }
            if(fila->fim != NULL){
                fila->fim->proximo = n;
            }
            fila->fim = n;
            fila->tamanho++;
            return TRUE;
        }
    }
    return FALSE;
}

CARRO* fila_remover(FILA *fila){
    if (fila != NULL && (!fila_vazia(fila)) ) {
        NO* nret = fila->inicio;
        CARRO *ret = fila->inicio->carro;
        fila->inicio = fila->inicio->proximo;
        nret->proximo = NULL;
        if(nret == fila->fim){
            fila->fim == NULL;
        }
        free(nret);
        nret = NULL;
        fila->tamanho --;
        return (ret);
    }
    return (NULL);
}

CARRO* fila_busca(FILA *f, int chave){
     if(f != NULL){
        if(chave == 0){
            return f->inicio->carro;
        }
        NO* aux = f->inicio;
        if(chave <= fila_tamanho(f)){
            for(int i = 0; i<chave; i++){
                aux = aux->proximo;
            }
            if(aux != NULL){
                return aux->carro;
            }
        }
    }
}

int fila_tamanho(FILA *fila){
    if (fila != NULL)
        return (fila->tamanho);
    return (ERRO);
}

boolean fila_cheia(FILA *fila){
    if(fila->tamanho > 10){
        return TRUE;
    }
    return FALSE;
}

int fila_vazia(FILA *fila){
    return (fila->tamanho == 0);
}

void fila_imprimir(FILA* fila){
    NO* aux = fila->inicio;
    while(aux != NULL){
        imprimir_carro(aux->carro);
        aux = aux->proximo;
    }
    return;
}

CARRO* fila_ultimo(FILA* f){
    if(f->fim != NULL){
        return (f->fim->carro);
    }
    return NULL;
}
CARRO* fila_primeiro(FILA* f){
    if(f->inicio != NULL){
        return (f->inicio->carro);
    }
    return NULL;
}
CARRO* fila_busca2(FILA *fila, int chave){
    NO* naux = fila->inicio;
    while(naux != NULL){
        if(placa_carro(naux->carro) == chave){
            return(naux->carro);
        }
        else{
            naux = naux->proximo;
        }
    }
    return NULL;
}