all: date.o individu.o turing.o
	gcc -Wall date.o -ansi -pedantic individu.o turing.o -o ProgTuring

date.o: date.c date.h
	gcc -c -Wall -ansi -pedantic date.c

individu.o: individu.c individu.h
	gcc -c -Wall -ansi -pedantic individu.c

turing.o: turing.c turing.h
	gcc -c -Wall -ansi -pedantic turing.c

clean:
	rm *.o ProgTuring