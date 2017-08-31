microShell: microShell.o parser.o myexec_command.o
	gcc -g -Wall microShell.o myexec_command.o parser.o -o microShell
example: example.o parser.o
	gcc -g -Wall example.o parser.o -o example
microShell.o: microShell.c
	gcc -g -Wall -c microShell.c
example.o: example.c
	gcc -c -Wall example.c
parser.o: parser.c parser.h
	gcc -c -Wall parser.c
myexec_command.o: myexec_command.c myexec_command.h
	gcc -c -Wall myexec_command.c
clean:
	rm *.o
	rm microShell
cleanall:
	rm *.o
	rm microShell
	rm example
	rm *~
	
