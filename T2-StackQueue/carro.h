#ifndef CARRO_H
    #define CARRO_H
    #define boolean int
    #define TRUE 1
    #define FALSE 0

    typedef struct carro_ CARRO;

    CARRO* criar_carro(int placa, int chegada, int saida); //função que cria o carro na memória e insere as informações necessárias sobre ele
    int placa_carro(CARRO* carro); //retorna a placa do carro
    int hora_valida(CARRO* carro); //verifica se a hora de chegada e saída do carro é válida para o contexto do estacionamento
    void imprimir_carro(CARRO* carro); //impressão da placa do carro e do valor a ser pago
    boolean verificar_retirada(CARRO* c1, CARRO* c2); //função que verifica se deve haver a retirada de um carro dos pátios (retorna 1, caso positivo)
    void aplicar_desconto(CARRO* c); //função para aplicar o desconto
    void carro_apagar(CARRO** aux); //função que apaga o carro da memória
    int tempo_restante(int hora_atual, CARRO* c); //função que retorna a hora restante para o carro sair do estacionamento
    int hora(CARRO* c); //função que retorna a hora atual baseado na hora de chegada do carro

#endif
