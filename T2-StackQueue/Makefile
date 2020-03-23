run: prog
	./prog

prog: carro.o fila.o pilha.o projetoalg.o
	gcc carro.c fila.c pilha.c projetoalg.c -o prog

projetoalg.o:
	gcc -c projetoalg.c

carro.o:
	gcc -c carro.c

pilha.o:
	gcc -c pilha.c

fila.o:
	gcc -c fila.c

clean:
	rm -rf prog *.o