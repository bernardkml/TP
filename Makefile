all: date.o individu.o laureat.o main_turing.o
	gcc date.o individu.o main_turing.o laureat.o -o prog_turing

date.o: date.c date.h
	gcc -c -Wall -ansi -Wfatal-errors date.c

individu.o: individu.c individu.h date.h
	gcc -c -Wall -ansi -Wfatal-errors individu.c

laureat.o: laureat.c laureat.h individu.h date.h
		gcc -c -Wall -ansi -Wfatal-errors laureat.c

main_turing.o: main_turing.c laureat.h individu.h date.h
	gcc -c -Wall -ansi -Wfatal-errors main_turing.c

clean:
	rm *.o prog_turing
