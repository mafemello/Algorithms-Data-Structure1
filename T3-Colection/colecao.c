#include <stdlib.h>
#include "colecao.h"

struct _no {
    int valor;
    struct _no* esq;
    struct _no* dir;
    int altura; // Usado somente na AVL
} ;

struct _c {
    No* inicio;
    int estrutura_id;
};

//////////////////////////   FUNCOES AUXILIARES DA ARVORE AVL   /////////////////////////
No *criarNo(int valor, No *esq, No *dir, int altura) {
    No *nova = malloc(sizeof(No));
    nova->valor = valor;
    nova->esq = esq;
    nova->dir = dir;
    nova->altura = altura;
    return nova;
}

void rotacionarE(No **p) {
    No *realocar, *novaRaiz;
    novaRaiz = (*p)->dir;
    realocar = novaRaiz->esq;
    novaRaiz->esq = *p;
    (*p)->dir = realocar;
    *p = novaRaiz;
    return;
}

void rotacionarD(No **p) {
    No *realocar, *novaRaiz;
    novaRaiz = (*p)->esq;
    realocar = novaRaiz->dir;
    novaRaiz->dir = *p;
    (*p)->esq = realocar;
    *p = novaRaiz;
    return;
}

void rotacionarED(No **p) {
    rotacionarE(&((*p)->esq)); //rotaciona filho esquerdo a esquerda
    rotacionarD(p); //rotaciona raiz a direita
    return;
}

void rotacionarDE(No **p) {
    rotacionarD(&((*p)->dir)); //rotaciona filho direito a direita
    rotacionarE(p); //rotaciona raiz a esquerda
    return;
}

void atualizarFB(No *p) {
    switch (p->altura) { //fator de balanceamento atual do raiz
        case 0:
            p->dir->altura = 0;
            p->esq->altura = 0;
            break;
        case -1:
            p->dir->altura = 1;
            p->esq->altura = 0;
            break;
        case 1:
            p->dir->altura = 0;
            p->esq->altura = -1;
            break;
    }
    p->altura = 0;
    return;
}

int inserirSubarvore(No **p, int valor, int *cresceu) {
    int retorno;
    if (*p == NULL) {
        *p = criarNo(valor, NULL, NULL, 0); 
        *cresceu = 1; //subarvore cresceu
        return 0; //sucesso
    }

    if ((*p)->valor == valor)
        return 1; //erro, elemento ja existe
    retorno = (valor < (*p)->valor) ? inserirSubarvore( &((*p)->esq), valor, cresceu) : inserirSubarvore( &((*p)->dir), valor, cresceu); // insere recursivamente
    
    // verifica se ha atualizacao a fazer
    if (*cresceu) { // ha algo a fazer, se a subarvore na qual o elemento foi inserido cresceu
        (*p)->altura += (valor < (*p)->valor) ? -1 : 1; // atualize fb
    
        if ((*p)->altura == 0 || (*p)->altura == 2 || (*p)->altura == -2) {
            *cresceu = 0; // subarvore atual nao cresceu; 0 => balanceamento foi melhorado; 2 ou -2: desbalanceamento sera corrigido
    
            switch ((*p)->altura) {
                case 2: // arvore pende para a direita
                    if ((*p)->dir->altura == 1) {
                        // caso 1: sinais iguais
                        rotacionarE(p); // rotaciona a esquerda
                        // atualiza fatores de balanceamento
                        (*p)->altura = 0;
                        (*p)->esq->altura = 0;
                    } else {
                        // caso 2: sinais opostos
                        rotacionarED(p); // rotacao dupla
                        atualizarFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
    
                case -2: // arvore pende para a esquerda
                    if ((*p)->esq->altura == -1) {
                        // caso 1: sinais iguais
                        rotacionarD(p); // rotaciona a direita
                        // atualiza fatores de balanceamento
                        (*p)->altura = 0;
                        (*p)->dir->altura = 0;
                    } else {
                        // caso 2: sinais opostos
                        rotacionarDE(p); // rotacao dupla
                        atualizarFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
            }
        }
        
    }
    return retorno; // retorna resultado da insercao recursiva
}

int inserir(Colecao *c, int valor) {
    int cresceu = 0; // subarvore nao cresceu, a principio
    return inserirSubarvore(&(c->inicio), valor, &cresceu); // inicia recursividade
}
//////////////////////////   FIM DAS FUNCOES AUXILIARES DA ARVORE AVL   ///////////////////////////////



Colecao* cria_colecao(int estrutura_id) {
    Colecao *c;
    c = malloc (sizeof(Colecao));
    c->inicio = NULL;
    c->estrutura_id = estrutura_id;

    return c;
}

No* cria_no(int valor) {
    No* criado;
    criado = malloc(sizeof(No));
    criado->valor = valor;
    criado->esq = NULL;
    criado->dir = NULL;

    return criado;
}

void adiciona(Colecao* c, int valor) {
    No* n;
    No* aux;
    n = cria_no(valor);
    if(c->inicio == NULL) {
        n->altura = 0;
        c->inicio = n;
        return;
    }

    switch(c->estrutura_id) {    
        case 1: 
        // Lista ordenada
            aux = c->inicio;
            if(aux->valor < valor) {
                c->inicio->esq = n;
                n->dir = c->inicio;
                c->inicio = n;
            }
            while(aux->dir != NULL) {
                if(aux->valor > valor) {
                    aux->esq->dir = n;
                    n->esq = aux->esq;
                    aux->esq = n;
                    n->dir = aux;
                    return;
                }
                aux = aux->dir;
            }
            n->esq = aux;
            aux->dir = n;
            break;

        case 2: 
        // Lista com inserçao na ultima posicao
            aux = c->inicio;
            while(aux->dir != NULL) {
                aux = aux->dir;
            }
            aux->dir = n;
            n->esq = aux;
            break;

        case 3: 
        // Lista com insercao na primeira posicao
                n->dir = c->inicio;
                c->inicio->esq = n;
                c->inicio = n;
            break;

        case 4:
        // Arvore binaria
            aux = c->inicio;
            while(aux != NULL) {
                if(valor < aux->valor) {
                    if(aux->esq == NULL) {
                        n->altura = aux->altura + 1;
                        aux->esq = n;
                        aux = NULL;
                    } else {
                        aux = aux->esq;
                    }
                } else {
                    if(aux->dir == NULL) {
                        n->altura = aux->altura + 1;
                        aux->dir == n;
                        aux = NULL;
                    } else {
                        aux = aux->dir;
                    }
                }
            }
            break;
        case 5: 
        // Arvore AVL
            inserir(c, valor);             
            break;
    }
    return;
}

int existe(Colecao* c, int valor) {
    No *aux;
    switch(c->estrutura_id) {
        case 1: 
        // Lista ordenada
        case 2: 
        // Lista com inserçao na ultima
        case 3: 
        // Lista com insercao na primeira
            if(c->inicio != NULL) {
                No* aux;
                aux = c->inicio;
                while(aux->dir != NULL) {
                    if(aux->valor == valor) {
                        return 1;
                    } else {
                        aux = aux->dir;
                    }
                }
                if(aux->valor == valor) {
                    return 1;
                } else {
                    return 0;
                }
            }
            break;
        case 4: 
        // Arvore binaria
        case 5: 
        // Arvore AVL
            aux = c->inicio;
                while(aux != NULL) {
                    if(valor < aux->valor) {
                        if(aux->esq == NULL) {
                            return 0;
                        } else {
                            aux = aux->esq;
                        }
                    } else if(valor > aux->valor) {
                        if(aux->dir == NULL) {
                            return 0;
                        } else {
                            aux = aux->dir;
                        }
                    } else {
                        return 1;
                    }
                }
            break;
    }
    return 0;
}

void destroiSubArvore(No* inicio) {
    if(inicio != NULL) {
        destroiSubArvore(inicio->esq);
        inicio->esq = NULL;
        destroiSubArvore(inicio->dir);
        inicio->dir = NULL;
        free(inicio);
    }
}

void destroi(Colecao* c) {
    No *aux, *delete;
    aux = c->inicio;
    switch(c->estrutura_id) {
        case 1:
        // Lista ordenada
        case 2:
        // Lista com inserçao na ultima
        case 3:
        // Lista com insercao na primeira
            while(aux != NULL) {
                delete = aux;
                aux = aux->dir;
                if(aux != NULL) {
                    aux->esq = NULL;
                }
                free(delete);
                delete = NULL;
            }
            break;
        case 4:
        // Arvore binaria
        case 5:
        // Arvore AVL
            //recursivo pra deletar subarvore ate não ter mais folha
            destroiSubArvore(aux);
            break;
    }
}