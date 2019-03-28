all: main timing1 timing2

main: main.o secret.o
	g++ -g -o main main.o secret.o

timing1: timing1.o secret.o
	g++ -g -o timing1 timing1.o secret.o

timing1.o: timing1.cpp secret.h
	g++ -g -c -o timing1.o timing1.cpp

timing2: timing2.o secret.o
	g++ -g -o timing2 timing2.o secret.o

timing2.o: timing2.cpp secret.h
	g++ -g -c -o timing2.o timing2.cpp

main.o: main.cpp secret.h
	g++ -g -c -o main.o main.cpp

secret.o: secret.cpp secret.h
	g++ -g -c -o secret.o secret.cpp

clean:
	rm main *.o
