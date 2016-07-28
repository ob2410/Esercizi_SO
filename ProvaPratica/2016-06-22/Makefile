main: main.o checkgroup.o
	gcc -o main main.o checkgroup.o

main.o: main.c checkgroup.h
	gcc -c main.c

checkgroup.o: checkgroup.c checkgroup.h
	gcc -c checkgroup.c

clean:
	rm -f *.o main
