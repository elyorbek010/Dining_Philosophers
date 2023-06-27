hello:
	gcc -o main main.c logs.c philosophers.c -lpthread
	./main