invmat: main.c matrix.c
	gcc -o invmat main.c matrix.c -I.
clean:
	rm invmat