# Name: Ayokunle Amodu
# One card number: 1741545
# CCID: aaamodu

wordSearch2D: src/puzzle2D.o wordSearch2D.o
	gcc -Wall -ggdb -Wextra -Werror -std=c99 -o wordSearch2D src/puzzle2D.o wordSearch2D.o

wordSearch2D.o: src/wordSearch2D.c src/puzzle2D.h
	gcc -Wall -ggdb -Wextra -Werror -std=c99 -c src/wordSearch2D.c

src/puzzle2D.o: src/puzzle2D.c src/puzzle2D.h
	gcc -Wall -ggdb -Wextra -Werror -std=c99 -c src/puzzle2D.c -o src/puzzle2D.o

clean:
	rm -f wordSearch2D *.o src/*.o

