/*
Bruno Germano do Nascimento - 10893131
Maria Fernanda Lucio de Mello - 11320860
*/


#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

#define TAMANHO_PILHA 5
#define TAMANHO_FILA 10

#define DEBUG 0
//if(DEBUG) printf("\n");

// Structs
	struct carro
	{
		int placa;
		int chegada;
		int saida;
		float desconto;
		struct carro* proximo;
	};

	struct pilha
	{
		Carro* topo;
		int tamanho;
	};

	struct fila
	{
		Carro *comeco;
		Carro *fim;
		int tamanho;
	};

int procurarCarro(Pilha p, Fila f, int placa)
{
	// se pilha !vazia procura na pilha
	// achou, retorna 1
	// se fila !vazia procura na fila
	// achou, retorna 1
	// nao achou em nenhuma, retorna 0
	if(DEBUG) printf("Entrou no procurarCarro\n");
	if(filaProcura(f, placa))
	{
		//if(DEBUG) printf("Achou carro na fila\n");
		return 1;
	}else if(pilhaProcura(p, placa))
	{
		//if(DEBUG) printf("Achou carro na pilha\n");
		return 1;
	}else
	{
		//if(DEBUG) printf("Não achou carro\n");
		return 0;
	}
}

void imprimeCarros(Pilha p, Fila f, int hora)
{
	printf("\tPatio #1:\n");
	pilhaImprime(p, hora);
	printf("\tPatio #2:\n");
	filaImprime(f, hora);
	printf("\n");
}

Carro* checkIn(Pilha *p, Fila *f)
{
	Carro* novo;
	int placa, chegada, saida;
	printf("Digite a placa, horario de chegada e de saida\n");
	scanf("%d %d %d", &placa, &chegada, &saida);
	if(DEBUG) printf("Leu e vai entrar no lerCarro\n");
	novo = lerCarro(placa, chegada, saida);
	if(DEBUG) printf("Saiu do lerCarro\n");
	// Checar se placa dobrada no sistema
	if(procurarCarro(*p, *f, novo->placa))
	{
		// Dobrado -> retorna NULL
		return NULL;
	}else
		// Else, retorna carro
		return novo;
	if(DEBUG) printf("Saiu do checkIn\n");
}

void checkOut(Pilha *p, Fila *f, int hora)
{
	// Imprimir os carros expirados
	/// - placa e valor
	printf("Carros expirados:\n");
	imprimeCarros(*p, *f, hora);
	if(DEBUG) printf("Voltou do imprimeCarros\n");
	// Remover esses carros
	Carro* aux = p->topo;
	if(DEBUG) printf("Declarou aux\n");
	// procurar na pilha o primeiro carro expirado
	if(p->tamanho > 0)
	{
		while(aux != NULL && aux->saida <= hora)
		{
			if(DEBUG) printf("Vai popar da pilha\n");
			pilhaPop(p);
			aux = p->topo;
		}
	}
	if(DEBUG) printf("Passou do while pilha\n");
	if(f->tamanho > 0)
	{
		while(f->comeco != NULL && f->comeco->saida <= hora)
		{
			if(DEBUG) printf("Vai tirar da fila\n");
			filaSai(f);
			if(DEBUG) printf("Tirou da fila\n");

		}
	}
	if(DEBUG) printf("Passou do while fila\n");
	return;
}

void desconto(Pilha *p, Fila *f, Carro c)
{
	Carro** vet;
	Carro* aux;
	int tam = p->tamanho + f->tamanho;
	int count = 0;
	if((p->tamanho + f->tamanho) >= (TAMANHO_PILHA + TAMANHO_FILA) / 4)
	{
		if((c.chegada % 3) == 0 && c.chegada != 21)
		{
			vet = malloc(sizeof(Carro*) * tam);
			aux = f->comeco;
			while(aux != NULL)
			{
				vet[count] = aux;
				count++;
				aux = aux->proximo;
			}
			aux = p->topo;
			while(aux != NULL)
			{
				vet[count] = aux;
				count++;
				aux = aux->proximo;
			}
			count = rand() % tam;
			vet[count]->desconto = 0.1;
			printf("O carro de placa %d ganhou um desconto de 10%%!!\n", vet[count]->placa);
		}
	}
}

void insercaoPatio(Pilha *p, Fila *f, Carro *c)
{
	// Verificar se tem carro em f e em p
	if(DEBUG) printf("Entrou no insercaoPatio\n");
	if(c->chegada < 8 || c->saida > 22)
	{
		printf("Horario indisponivel, estacionamento fechado\n");
	}
	if((p->tamanho < TAMANHO_PILHA) && (f->tamanho < TAMANHO_FILA))
	{
		if(DEBUG) printf("Fila e Pilha nao cheias\n");
		int a = pilhaVazia(*p);
		int b = filaVazia(*f);

		if(a && b)
		{
			// Se p e f vazios -> p
			if(DEBUG) printf("Ambas vazias\n");
			pilhaPush(p, c);
			if(DEBUG) printf("Pushou na pilha\n");
			return;
		}else if(b)
		{
			// Se so f vazio -> f
			if(DEBUG) printf("Fila vazia\n");
			filaEntra(f, c);
			if(DEBUG) printf("Pushou na fila\n");
			return;
		}else if(a)
		{
			// Se so p vazio -> p
			if(DEBUG) printf("Pilha vazia\n");
			pilhaPush(p, c);
			if(DEBUG) printf("Pushou na pilha\n");
			return;
		}else
		{
			if(DEBUG) printf("Nenhum vazio\n");
			// Se os dois com 1 ou mais:
			if((c->saida <= p->topo->saida) && !(pilhaCheia(*p)))
			{
				if(DEBUG) printf("Condicao 1\n");
			// 		p:
			// 			So pode entrar se novo.saida <= topo.saida
				pilhaPush(p,c);
				if(DEBUG) printf("Pushou na pilha\n");
				return;
			}else if((c->saida >= f->fim->saida) && !(filaCheia(*f)))
			{
				if(DEBUG) printf("Condicao 2\n");
			// 		f:
			// 			so pode entrar se novo.saida >= cauda.saida
				filaEntra(f, c);
				if(DEBUG) printf("Pushou na fila\n");
				return;
			}
		}
	}else
	{
		printf("Estacionamento cheio, carro nao inserido\n");
		return;
	}
	printf("Não inserido no patio\n");
	return;
	// Se não entrar em nenhum, mensagem de rejeicao
}

int main(int argc, char const *argv[])
{

	int op;
	int exit = 0;

	Pilha *p1 = pilhaCria(p1); //max 5
	Fila *p2 = filaCria(p2); // max 10
	Carro* car;

	printf("ESTACIONAMENTO PnF\n");
	do
	{	
		// Print menu
		printf("\t1 - Registrar Carro\n");
		printf("\t2 - Imprimir Carros\n");
		printf("\t0 - Sair\n");
		scanf("%d", &op);
		switch(op)
		{
			// Registrar Carro
			case 1:
				if(DEBUG) printf("Vai entrar no check in\n");
				car = checkIn(p1, p2);
				if(DEBUG) printf("Saiu do check in\n");
				if(car != NULL)
				{
					checkOut(p1, p2, car->chegada);
					if(DEBUG) printf("Saiu do checkOut\n");
					desconto(p1, p2, *car);
					insercaoPatio(p1, p2, car);
					if(DEBUG) printf("Saiu do insercaoPatio\n");
				}else
				{
					printf("Carro já está no estacionamento\n");
				}
			break;

			// Imprimir Carros
			case 2:
				imprimeCarros(*p1, *p2, 25);
			break;

			// Sair
			case 0:
				// Desalocar tudo
				pilhaEsvazia(p1);
				filaEsvazia(p2);
				exit = 1;
			break;

			default:
				printf("Entrada invalida, tente novamente");
			break;
		}
	}while(!exit);

	return 0;
}