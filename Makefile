risc.exe : main.o parser.o simulation.o print.o debug.o

	gcc -o risc main.o parser.o simulation.o print.o debug.o

main.o : main.c

	gcc -std=c11 -pedantic -Wall -Wextra -c -o main.o main.c

parser.o : parser.c

	gcc -std=c11 -pedantic -Wall -Wextra -c -o parser.o parser.c

simulation.o : simulation.c

	gcc -std=c11 -pedantic -Wall -Wextra -c -o simulation.o simulation.c

print.o : print.c

	gcc -std=c11 -pedantic -Wall -Wextra -c -o print.o print.c

debug.o : debug.c

	gcc -std=c11 -pedantic -Wall -Wextra -c -o debug.o debug.c