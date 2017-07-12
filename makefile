a.out: proj1.o e.o
	g++ -g -Wall -ansi -o queue proj1.o e.o

proj1.o: proj1.cpp e.h
	g++ -g -Wall -ansi -c proj1.cpp

e.o: e.cpp e.h
	g++ -g -Wall -ansi -c e.cpp

