all: date.o individu.o opera.o main_opera.o
	gcc date.o individu.o main_opera.o opera.o -o prog_opera

date.o: date.c date.h
	gcc -c -Wall -ansi -Wfatal-errors date.c

individu.o: individu.c individu.h date.h
	gcc -c -Wall -ansi -Wfatal-errors individu.c

opera.o: opera.c opera.h individu.h date.h
	gcc -c -Wall -ansi -Wfatal-errors opera.c

main_opera.o: main_opera.c opera.h individu.h date.h
	gcc -c -Wall -ansi -Wfatal-errors main_opera.c

clean:
	rm *.o prog_opera
