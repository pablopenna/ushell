count: main.o libcount.a
	gcc -Wall main.o -o count -L./ -lcount
main.o: main.c
	gcc -Wall -c main.c
readchar_R.o: readchar_R.c readchar_R.h
	gcc -Wall -c readchar_R.c
count_M.o: count_M.c count_M.h
	gcc -Wall -c count_M.c
libcount.a: readchar_R.o count_M.o
	ar rvs libcount.a readchar_R.o count_M.o
clean:
	rm *.o
	rm libcount.a
	rm count
