/*
Bruno Germano do Nascimento - 10893131
Maria Fernanda Lucio de Mello - 11320860
*/


#include <stdio.h>
#include <stdlib.h>
#include "tad.h"
#define TAMANHO_PILHA 5
#define TAMANHO_FILA 10
#define VALOR_HORA 3

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

// funcoes pilha
	// cria pilha
	Pilha* pilhaCria(Pilha *p)
	{
		p = malloc(sizeof(Pilha));
		p->tamanho = 0;
		p->topo = NULL;
		return p;
	}
	// esvazia pilha
	void pilhaEsvazia(Pilha *p)
	{
		Carro* aux = p->topo;

		while(p->topo != NULL)
		{	
			pilhaPop(p);
		}
	}
	// esta vazia?
	int pilhaVazia(Pilha p) // parametro passado por valor
	{
		return (p.topo == NULL);
	}
	// esta cheia?
	int pilhaCheia(Pilha p) // parametro passado por referecia
	{
		return(p.tamanho == TAMANHO_PILHA);
	}
	// insere na pilha
	void pilhaPush(Pilha *p, Carro *c)
	{
		c->proximo = p->topo;
		p->topo = c;
		p->tamanho += 1;
	}
	// remove da pilha
	void pilhaPop(Pilha *p)
	{
		Carro* aux;
		if(p->topo != NULL)
		{
			aux = p->topo->proximo;
			free(p->topo);
			p->topo = aux;
			p->tamanho -= 1;
		}

	}

	// imprime elementos
	void pilhaImprime(Pilha p, int hora)
	{
		Carro *aux;
		if(p.tamanho > 0)
		{
			aux = p.topo;
		}
		for(int i = 0; i < p.tamanho; i++)
		{
			if(hora >= aux->saida)
			{
				printf("\tPlaca: %d\n\tValor: %.2f\n\n", aux->placa, (aux->saida - aux->chegada) * VALOR_HORA * (1.0 - aux->desconto));
			}
			aux = aux->proximo;
		}
	}

	int pilhaProcura(Pilha p, int procura)
	{
		Carro* aux = p.topo;	

		int achou = 0;

		while(!achou && aux != NULL)
		{
			if(aux->placa == procura)
			{
				achou = 1;
			}
			aux = aux->proximo;
		}

		return achou;
	}

// funcoes fila
	/*fila
		No* comeco, fim;
		int tamanho*/
	Fila* filaCria(Fila *f)
	{
		f = malloc(sizeof(Fila));
		f->tamanho = 0;
		f->comeco = NULL;
		f->fim = NULL;
		return f;
	}

	void filaEsvazia(Fila *f)
	{
		while(f->tamanho != 0)
		{
			filaSai(f);
		}
	}

	int filaVazia(Fila f)
	{
		// Verifica se fila esta vazia
		return(f.tamanho == 0);
	}

	int filaCheia(Fila f)
	{
		// Verifica se fila esta cheia
		return(f.tamanho == TAMANHO_FILA);
	}

	void filaEntra(Fila *f, Carro *c)
	{
		if(!filaVazia(*f))
		{
			f->fim->proximo = c;
			f->fim = c;
			f->tamanho += 1;
		}else
		{
			f->comeco = c;
			f->fim = c;
			f->tamanho += 1;
		}
	}

	void filaSai(Fila *f)
	{
		Carro* aux;
		if(f->tamanho != 0)
		{
			aux = f->comeco;
			f->comeco = f->comeco->proximo;
			free(aux);
			f->tamanho -= 1;
		}
	}

	void filaImprime(Fila f, int hora)
	{
		Carro *aux;
		if(f.tamanho > 0)
		{
			aux = f.comeco;
		}
		for(int i = 0; i < f.tamanho; i++)
		{
			if(hora > aux->saida)
			{
				printf("\tPlaca: %d\n\tValor: %.2f\n\n", aux->placa, (aux->saida - aux->chegada) * VALOR_HORA * (1.0 - aux->desconto));
			}
			aux = aux->proximo;
		}
	}

	int filaProcura(Fila f, int procura)
	{
		Carro* aux = f.comeco;
		int achou = 0;

		while(!achou && aux != NULL)
		{
			if(aux->placa == procura)
			{
				achou = 1;
			}
			aux = aux->proximo;
		}

		return achou;
	}

// Funcoes carro
	Carro* lerCarro(int placa, int cheg, int horas)
	{
		Carro* car;
		car = malloc(sizeof(Carro));
		car->placa = placa;
		car->chegada = cheg;
		car->saida = horas;
		car->desconto = 0.0;
		return car;
	}