/*
Bruno Germano do Nascimento - 10893131
Maria Fernanda Lucio de Mello - 11320860
*/


// Carro
	typedef struct carro Carro;

	Carro* lerCarro(int placa, int cheg, int horas);

// Pilha
	typedef struct pilha Pilha;
	Pilha* pilhaCria(Pilha *p);
	void pilhaEsvazia(Pilha *p);
	int pilhaVazia(Pilha p); // parametro passado por valor
	int pilhaCheia(Pilha p); // parametro passado por referecia
	void pilhaPush(Pilha *p, Carro *c);
	void pilhaPop(Pilha *p);
	void pilhaImprime(Pilha p, int hora);
	int pilhaProcura(Pilha p, int procura);

// Fila
	typedef struct fila Fila;
	Fila* filaCria(Fila *f);
	void filaEsvazia(Fila *f);
	int filaVazia(Fila f);
	int filaCheia(Fila f);
	void filaEntra(Fila *f, Carro *c);
	void filaSai(Fila *f);
	void filaImprime(Fila f, int hora);
	int filaProcura(Fila f, int procura);