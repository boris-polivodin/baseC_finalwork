all: sens

sens: main.o temp_functions.o
	gcc -o sens main.o temp_functions.o

main.o:
	gcc -c -o main.o main.c

temp_functions.o:
	gcc -c -o temp_functions.o temp_functions.c

clean:
	rm *.o
	rm sens
