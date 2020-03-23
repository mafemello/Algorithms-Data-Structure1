#include <stdio.h>
#include <stdlib.h>
#include "trab1.h"

/*
 O programa deve apresentar um menu principal com 6
(seis) funções básicas: (1) Inserir Registro, 
(2) Remover Registro, 
(3) Imprimir Registros,
(4) Relatório de Aprovação, 
(5) Horas de estudo (Média) e 
(6) Sair. 
Ao selecionar uma função, o programa deve 
apresentar o menu específico da mesma e 
executar a função esperada, e, ao fim da execução 
retornar ao menu principal. 
Se uma opção inválida for selecionada, nada deve ser feito.
*/

// declracao da struct que identifica o aluno
struct aluno {
    int id;
    float tempo;
    float nota_p1, nota_p2;
    struct aluno *prox;
}; //ALUNO;

aluno A;

// declaracao da lista
struct lista {
    ALUNO *ini, *fim;
};

// cria e instancia a lista
void Create (Lista **l) {
    // inicia a lista
    *l = malloc (sizeof(Lista)); 

    // define lista vazia
    (*l)->ini = NULL;
    (*l)->fim = NULL;
    return;
}

// insere registro do aluno
void Insere (Lista *l, int id, float tempo, float nota_p1, float nota_p2) {
    ALUNO *aux;

    // cria no:
    aux = malloc(sizeof(ALUNO));
    aux->id = id;
    aux->tempo = tempo;
    aux-> nota_p1 = nota_p1;
    aux-> nota_p2 = nota_p2;
    aux-> prox = NULL;

    // atualiza ponteiros
    if (l->fim != NULL) {
        l->fim->prox = aux/
        l->fim = aux;
    }
    if (l->ini == NULL) {
        l->ini = aux;
    }
    return;
}

// remove registro da lista
void Remove (Lista *l, int id, float tempo, float nota_p1, float nota_p2) {
    ALUNO *atual, *ant;
    atual = l->ini;
    ant = NULL;

    while (atual != NULL) {
        if (atual->)
    }

}
