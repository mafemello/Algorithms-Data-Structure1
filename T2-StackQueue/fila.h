#ifndef FILA_H
    #define FILA_H

    #define TRUE 1
    #define FALSE 0
    #define boolean int
    #define ERRO -32000

    typedef struct fila_ FILA;
    typedef struct no_ NO;

    FILA *fila_criar(void); //função que cria a fila
    void fila_apagar(FILA **f); //função que apaga a fila da memória
    boolean fila_inserir(FILA *fila, CARRO *carro); //função que insere um carro no fim da fila
    CARRO *fila_remover(FILA *fila); //função que remove o primeiro carro da fila
    CARRO *fila_busca(FILA *fila, int chave); //função de procura que busca com base na posição do carro na fila e retorna o carro encontrado
    int fila_tamanho(FILA *fila); //função que retorna o tamanho da fila
    int fila_vazia(FILA *fila); //função que retorna 1 caso a fila esteja vazia e 0 caso não esteja
    boolean fila_cheia(FILA *fila); //função que retona 1 se a fila já atingiu sua capacidade máxima e 0 caso contrário
    void fila_imprimir(FILA* fila); //função que imprime a fila
    CARRO* fila_ultimo(FILA *f); //função que retorna o último carro da fila
    CARRO* fila_primeiro(FILA *f);  //função que retorna o primeiro carro da fila
    CARRO* fila_busca2(FILA *fila, int chave); //função de busca que se baseia na placa do carro. caso encontrado, retorna o carro. caso contrário, retorna NULL

    #endif