main: main.o get_user_groups.o
	gcc -o main main.o get_user_groups.o

main.o: main.c get_user_groups.h
	gcc -c main.c

checkgroup.o: get_user_groups.c get_user_groups.h
	gcc -c get_user_groups.c

clean:
	rm -f *.o main
