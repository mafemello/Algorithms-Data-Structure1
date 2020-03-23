#ifndef PILHA_H
    #define PILHA_H

    #define boolean int
    #define TRUE 1
    #define FALSE 0
    #define ERRO -32000

    typedef struct pilha_ PILHA;
    typedef struct no_ NO;

    PILHA* pilha_criar(void); //função que cria a pilha
    void pilha_apagar(PILHA** pilha); //função que apaga a pilha da memória
    int pilha_vazia(PILHA* pilha); //função que retorna 1 caso a pilha esteja vazia e 0 caso não esteja
    int pilha_tamanho(PILHA* pilha); //função que retorna o tamanho da pilha
    CARRO* pilha_topo(PILHA* pilha); //função que retorna o primeiro carro da pilha
    int pilha_empilhar(PILHA* pilha, CARRO* carro); //função que insere um carro no começo da pilha
    CARRO* pilha_desempilhar(PILHA* pilha); //função que remove o primeiro carro da pilha
    void pilha_imprimir(PILHA* p); //função que imprime a pilha
    CARRO* pilha_busca(PILHA* p, int chave); //função de procura que busca com base na posição do carro na pilha e retorna o carro encontrado
    boolean pilha_cheia(PILHA* p); //função que retona 1 se a pilha já atingiu sua capacidade máxima e 0 caso contrário
    CARRO* pilha_busca2(PILHA* p, int chave); //função de busca que se baseia na placa do carro. caso encontrado, retorna o carro. caso contrário, retorna NULL

    #endif