/* TRABALHO DE ALGORITMOS E ESTRUTURAS DE DADOS 2
Leonardo Fonseca Pinheiro - NUSP 11219241
Ricardo Furbino - NUSP 11219133
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carro.h"
#include "pilha.h"
#include "fila.h"


boolean disponibilidade(CARRO* carro, FILA* f, PILHA * p){
    int h = hora(carro); //hora atual
    if(pilha_topo(p) == NULL && fila_primeiro(f) == NULL){ //caso pátio 1 e pátio 2 estejam vazios, entra no pátio 1
        pilha_empilhar(p, carro);
        return TRUE;
    }
    if(pilha_topo(p) != NULL && fila_primeiro(f) == NULL){ //caso pátio 2 esteja vazio, entra no pátio 2
        fila_inserir(f, carro);
        return TRUE;
    }
    if(pilha_topo(p) == NULL && fila_primeiro(f) != NULL){ //caso pátio 1 esteja vazio, entra no pátio 1
        pilha_empilhar(p, carro);
        return TRUE;
    }   
    if(tempo_restante(h, carro) <= tempo_restante(h, pilha_topo(p)) && pilha_cheia(p) == 0){ //caso o tempo os pátio 1 não esteja cheio e o último carro que entrou no pátio 1 sairá depois do atual, carro atual entra no pátio 1
        pilha_empilhar(p, carro);
        return TRUE;
    }
    if(tempo_restante(h, carro) <= tempo_restante(h, fila_ultimo(f)) && fila_cheia(f) == 0){ //caso o tempo os pátio 2 não esteja cheio e o último carro que entrou no pátio 2 sairá depois do atual, carro atual entra no pátio 2
        fila_inserir(f, carro);
        return TRUE;
    }
    return FALSE; //caso nenhuma das condições acima seja atendida, o carro não entrará no estacionamento
}


void desconto(FILA* f, PILHA* p){
    int sorteado = rand() % (pilha_tamanho(p)+fila_tamanho(f)); //geração do sorteio
    //aplicação do sorteio
    if(sorteado < pilha_tamanho(p)){
        aplicar_desconto(pilha_busca(p, sorteado));
    }
    else{
        sorteado -= pilha_tamanho(p);
        aplicar_desconto(fila_busca(f, sorteado));
    }
    return;
}


void rejeicao(int justificativa){ //está função indica o motivo de uma rejeição de um carro no estacionamento, seja por falta de vagas ou erro de lógica. cada printf explica o que número indica
    printf("O carro não foi aceito porque ");
    switch(justificativa){
    case 0: //relacionado à falta de vagas adequadas no estacionameto para o carro
        printf("não há possibildade para o carro entrar no estacionamento.");
        break;
    case 2:
        printf("o estacionamento está cheio.");
        break;
    case 3:
        printf("o carro chegou antes da abertura do estacionamento.");
        break;
    case 4:
        printf("o cliente deseja retirar o carro após o fechamento do estacionamento");
        break;
    case 5:
        printf("o carro ja está estacionado");
        break;
    case 6:
        printf("a hora de entrada é maior que a de saida");
        break;
    }
    printf("\n");
}


void imprimir_estacionamento(PILHA *p, FILA *f){  //imprime todos os carros presentes no estacionamento
    pilha_imprimir(p);
    fila_imprimir(f);
}


void checkout(PILHA * p, FILA * f, CARRO * c){ //remove de pilha e fila carros que já saíram do estacionamento (comparação feita com o horário atual)
    CARRO* aux;
    do{
        aux = pilha_desempilhar(p); //desempilha o carro do pátio 1
        if(aux == NULL){ //caso não haja carros, sai do loop do pátio 1
            break;
        }
        if(verificar_retirada(aux, c) == 0){ //caso não é é necessária a retirada do carro no horário atual, o carro retirado é recolocado no pátio 1
            pilha_empilhar(p, aux);
            aux = NULL; //para a saída do loop
        }
    }while(aux != NULL);
    do{
        aux = fila_primeiro(f);
        if(aux == NULL){ //caso não haja carros no pátio 2, sai do loop
            break;
        }
        if(verificar_retirada(aux, c) == 0){ //caso não é é necessária a retirada do carro no horário atual, saída do loop. senão, remoção do primeiro carro presente no pátio 2
            aux = NULL;
        }
        else{
            fila_remover(f);
        }
    }while(aux != NULL);
    //impressão dos pátios após as retiradas    
    pilha_imprimir(p);
    fila_imprimir(f);
    return;
}


void registrar_carro(PILHA *p, FILA *f, CARRO* c){
    if(c != NULL && p != NULL && f != NULL){ //verificação se pilha, fila e carro existem
        int acerto = 1; //variável que indica se houve a inserção. ela pode mudar ao longo de registrar carro, caso o carro não atenda as condições para entrar no estacionamento(será != 1).
        if(pilha_cheia(p) == 1 && fila_cheia(f) == 1){
            acerto = 2; //com os dois pátios cheios, o carro não entrará no estacionamento
            imprimir_estacionamento(p,f);
        }
        if(acerto == 1){
            acerto = hora_valida(c); //verificação se a hora apresentada é válida
            if(pilha_busca2(p,(placa_carro(c))) != NULL || fila_busca2(f,(placa_carro(c))) != NULL){ //verificação se o carro já existe no estacionamento
                acerto = 5;
            }
            if(acerto == 1){ //caso não haja nenhum empecilho até o momento que impeça a inserção do carro
                checkout(p, f, c); //função que retira os carros que já saíram do estacionemento (toma-se como base o horário de chegada do carro atual)
                if(fila_tamanho(f) + pilha_tamanho(p) > 3){ //caso haja mais que 3 carros no estacionamento, é gerado o sorteio de desconto, mas o carro atual não participa de tal sorteio
                    desconto(f, p);
                }
                acerto = disponibilidade(c, f, p); //verificação se há empecilhos em relação às vagas no estacionamento para a entrada do novo carro. caso haja, o retorno vale 0.
            }
            else{
                imprimir_estacionamento(p,f); 
            }
        }
        if(acerto != 1)
            rejeicao(acerto); //caso haja a rejeição de uma carro, está função indica o motivo, que está armazendo em acerto
        return;
    }
}


int main (void){
        int opcao; //número para seleção da opção
        PILHA * patio1;
        FILA * patio2;
        CARRO* carro; //ponteiro para carro que será inserido
        int placa; //variável para o número da placa do carro que será inserido
        int chegada; //variável para o horário de chegada do carro que será inserido
        int saida; //variável para o horário de saída da placa do carro que será inserido
        patio1 = pilha_criar();
        patio2 = fila_criar();
    for(;;){ //loop infinito para a volta para o menu toca vez que uma opção é realizada. o fim desse loop ocorre quando a opção 3 é selecionada
        printf("Menu:\n1 - Registrar Carro\n2 - Imprimir Carros\n3 - Sair\nDigite a opção: "); //menu de opções
        scanf("%d", &opcao); //leitura da opção
        switch(opcao){
        case 1: //Opção Registrar Carro: insere (ou não, dependendo das condições) um carro no estacionamento
            //obtenção das inforções necessárias para a inserção do carro (primeira parte do check-in)
            printf("Insira a placa do carro: \n");
            scanf("%d", &placa);
            printf("Insira a hora de chegada do carro: \n");
            scanf("%d", &chegada);
            printf("Insira a hora de saída do carro: \n");
            scanf("%d", &saida);
            carro = criar_carro(placa, chegada, saida); //criação do carro tipo CARRO
            registrar_carro(patio1, patio2, carro); //função que realiza: segunda parte do check-in, check-out, diponibilidade e rejeição
            break;
        
        case 2: //Opção Imprimir Carros
            imprimir_estacionamento(patio1, patio2);
            break;

        case 3: //Opção Sair:
            pilha_apagar(&patio1);
            fila_apagar(&patio2);   
            return 0;
            /*OBS: em alguns casos, na saída, o programa tem um problema com "double free".
             O erro parece ser ocasionado por um espaço de memoria na HEAP utilizado após o free.
             Contudo, não conseguimos encontrar o erro, uma vez que as linhas apontadas não aparentavam problema na lógica.
             Foi apontado erro nas linhas: Carro.c(l.69), fila.c(l. 39) e pilha(l.43 e 44) e por isso deixamos elas comentadas.
             Isso faz com que o programa tenha alguns vazamentos de memória.
             */
        }
    }
    return 0;
}