all: main.o evaluate.o score.o optimizer.o validator.o
	$(CC) main.o optimizer.o evaluate.o score.o validator.o -lm -o brute

main.o: main.c
	$(CC) main.c -c -o main.o 

evaluate.o: evaluate.c
	$(CC) evaluate.c -c -o evaluate.o

score.o: score.c
	$(CC) score.c -c -o score.o

optimizer.o: opt.c
	$(CC) opt.c -c -o optimizer.o

validator.o: opt.c
	$(CC) validator.c -c -o validator.o
